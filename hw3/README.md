# HW3 - Space Invaders

## Controls

Left/Right - Move ship left and right  
Spacebar - Fire gun

## About

The game runs using 3 states: A beginning state, a game state, and an ending state. The beginning state simply displays the game title, the game state runs the game, and the ending state displays the game result.

In-game, there is a 5x5 enemy grid that moves as a single unit, similarly to the original space invaders enemies. The player's gun is also limited to 2 shots on screen to avoid spamming, and the enemies have a tunable random chance of spawning a bullet every frame, which is currently set at 1/1000.

The player loses by either getting hit by a bullet or by having the enemies come too close to the ground. The player wins by eliminating all of the enemies.