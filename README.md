# CarRacing_Game_bullet3D

##Isaac calvis

https://github.com/isaaccalvis

## Controls

===========Movement_Keys===========
ARROW KEYS-------->Move
SPACE------------->Break
L_SHIFT----------->Sprint
R----------------->Restart

===========Change_Vehicle===========
Keep pressed "i" key
i + 1 ----------> Car
i + 2 ----------> Bike
i + 3 ----------> Truck
i + 4 ----------> Tri-Bike
i + 5 ----------> Big Tricicle

===========Make_Your_Own_Map========
Pulse "p" key to open Tiled.
Make your own map; when you have finished, press the Tiled button "save" and close Tiled.
Your map will be automatically loaded in the game. (You don't need to close the game)

In case that key "p" don't open Tiled.exe, go manually to the game folder, search at
/Game folder Tiled.exe, open it, and then inside the program open the document mapa.tmx
Then close Tiled and try again.

Player will appear at top-left part, looking down (respect the Tiled map editor).
Tiled buttons and layers.
Layers: you have 2 layers (elements & logic), at elements you have to put the blue
tiles, at logic the green (sensor), yellow (dynamic object), or purple (constraints).

--Constraints--
The 2 first constraints move in one angle, one its -90, and the other 90, the arrow
means where it will let pass the car. it can be used to block when the car pass.
The third have free movement.

--Sensor--
You can put 0 to 4 sensors (NO MORE THAN 4), if you put more sensors, Tiled will be opened,
and show you a mesaje on the console that mean that you can't put more than 4, in this case,
you will have to modify Tiled and change sensors (less than 5).
You will make a complete loop when the 4 sensors are On, then, they will be reseted, and
you will be able to make another loop. if you go back and touch one of them, it will turn
off, you need to touch it a 3rd time to put it to on if you do that, else, loops wouldn't
work correctly.

=======Disable_Graphic_Options======
F1-------------->Disable debug graphical mode 
F2-------------->Disable 3D meshes
(if you diable meshes game will go better, but remember to enable debug graphical mode)

WARNING :: GAME HAVE SOME MEMORY LEAK WITH MESHES THAT I CAN'T FIND, AND IF YOU RESET MORE THAN X TIMES
WITHOUT CLOSING THE GAME, SOME OBJECTS WILL NOT APPEAR !!!


## Objectives

All game is made with the idea that the user make his own map, but it starts with a basic racing
circuit to play without make any map, you can complete the circuit and make more loops, and you have
time, so you can count your records.