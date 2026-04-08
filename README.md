# Hidden Treasure
This is a game inspired by the game with the same name found on the phone Nokia 100. The goal is to reach as high level as possible. The player is promoted to a new level by mining enough gold. The problem is that the player slowley takes damage by time, and might also stumble across fire in the mine. The game is over when the player's health goes to zero.

## Creat your game
To creat a game you make an instance of the HiddenTreasure class. The constructur takes multiple arguments: 
```bash
HiddenTreasure(std::filesystem::path filename, int lack_of_air, double heart_chance, double gold_chance, double fire_chance, unsigned int lvl)
```

The filename argument 

### Chances
The chance for heart drop at a tile is initially 5% with new chance for new lvl at 0.9 of current chance.
Chance for gold drop is always 3%.