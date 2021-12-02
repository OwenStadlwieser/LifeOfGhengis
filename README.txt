Description:
Welcome to the life of Ghengis
The goal of the game is to create a swarm by interacting with the women in the red shirt
Unfortunately your swarm does not like you and will attempt to kill you
Use WASD for controls, press P to play
Press 'esc' to quit
Messages will be displayed in the terminal
This game was created using an entity component system, each entity posseses multiple components storing related data. 
The game engine was built using C++ and the SDL2 library.

How to run:
Install SDL_2 x86 source image and development libraries from https://libsdl.org/projects/SDL_image/
Open the birch engine build solution in visual studio code 
Under Project properties: 
    Add the include folder from the source image directory to the project include directories
    Add the directory the development library was unzipped to, to the project include directories
    Add the lib\x86 folder from the source image directory to the project library directories 
    Add the directory the development library was unzipped to, to the project library directories
run the main.cpp file. 

Debugging:
If a linking error occurs resave texturemanager.cpp and compile it first.
Make sure the proper SDL2 dependecies are installed.
The game was developed on windows x86 debug settings.

Developed by Owen Stadlwieser



Refrences:
Engine development:
https://www.youtube.com/user/creaper