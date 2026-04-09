# Hidden Treasure
This is a game inspired by the game with the same name found on the phone Nokia 100. The goal is to reach as high level as possible. The player is promoted to a new level by mining enough gold. The problem is that the player slowley takes damage by time, and might also stumble across fire in the mine. The game is over when the player's health goes to zero.

## Create your game
To creat a game you make an instance of the HiddenTreasure class. The constructor takes multiple arguments: 
```bash
HiddenTreasure(std::filesystem::path filename, int lack_of_air, double heart_chance, double gold_chance, double fire_chance, unsigned int lvl)
```

The filename argument gives a path to a text file that gives the game instance it's initial layout. lack_of_air is the continuos damage to the player by time. heat_chance, gold_chance and fire_chance determin the chances for given item. lvl gives the player their level.

## How the game is ran
To start the game the member function .run() is used. This function creates a new window and starts a game.
The run() function handles all user input and drawing. It differs when the game is live and when it's not (the game is live when the user is actually playing the game and the player in the game world is still alive). When the game is live: 
-  Time chips away health points.
-  The player position and state (facing left or right) is updated based on user input.
-  The world is updated based on user input (mining, player hitting items).

When the game is over the user is presented with their result, the highscore table, and the option of starting a new game. The program ends when the game window is closed.

## The game world
The world is made of different tiles. Mainly "rock" tiles. When the world is created and new lines are added, at each rock tile there might be added a heart, gold or fire by chance. These chances is determined by the arguments given in the HiddenTreasure constructor. If a heart or gold is added the tile becomes empty and the item is visible. Fire items are hidden until the rock at the same possition is mined.

## GUI
To get the game's GUI the course' AnimationWindow is used. The class GameWindow inherits from AnimationWindow and has added  multiple draw functions.

## Files
To keep track of scores and to add new scores, the files highscore.txt and temp.txt are used. After a finished game, the score is recorded into the highscore.txt file and in this process the temp.txt file is used.

init_world.txt gives the initial world for a game.