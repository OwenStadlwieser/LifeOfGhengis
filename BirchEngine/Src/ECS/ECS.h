#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>


class Component;
class Entity;
class Manager;
//stores maximum size dynamic memory?;
using ComponentID = std::size_t;
using Group = std::size_t;
// less overhead wherever its called puts code
inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}
// allows for type to be passed to function noexcept -> specifiecs if function throws exception
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}
// const
constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using GroupBitSet= std::bitset<maxGroups>;
using ComponentBitSet = std::bitset<maxComponents>;
// type and size
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	virtual  ~Component() {}
};
class Entity
{
public:
	Manager& manager;
	bool active = true;
	// pointer to class component used to initialize vector of components
	std::vector<std::unique_ptr<Component>> components;
	// defined earlier
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public:
	Entity(Manager& mManager) : manager(mManager)
	{

	}
	void update()
	{
		// for every component in components update
		for (auto& c : components) c->update();
	}
	void draw() 
	{
		for (auto& c : components) c->draw();
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }
	bool hasGroup(Group mGroup)
	{
		return groupBitSet[mGroup];
	}
	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitSet[mGroup] = false;
	}
	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}
	// template allows u to not specify a type, generic type T and generic args TArgs
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));
		// same components in same place
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;
		c->init();
		return *c;
	}
	template<typename T>T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
	// whole idea
	// gameobject.getComponent<PositionComponent>().setXpos(25)
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
	void update()
	{
		for (auto& e : entities) e->update();
		{

		}
	};
	void draw()
	{
		for (auto& e : entities) e->draw();
	};
	// removes entities if not active?
	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(entities));
	}
	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}
	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}
	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};
















