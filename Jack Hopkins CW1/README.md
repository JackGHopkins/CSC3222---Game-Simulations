# CSC3222---Game-Simulations
## Overview
- Control character with Arrow Keys.
- Collect Randomly Spawning Food items. Bring these back to the shop to recieve points.
- Enemies parol the area. Will shoot at the player.
- Starts with 3 lives. If (Lives == 0) { Game = lost; }

## Wizzy:
- Walk on Platforms.
- Falls (Affected by Gravity).
- Climbs ladders.
- Loses a life if hit. Only Position is reset. Unless Lives = 0.

## Magic Spell:
- Press SPACE to cast.
- 4 Spells.
- Launches in RANDOM direction at a constant velocity. 
- Bounces of walls and floors up to 3 times.
- Delete Spell if speed = 0;
- Only collides with Enemies.

# Enemies
## Guards (Green Lads):
- 4 Guards in total. Distrubuted at random.
- Guards reset when you lose a life.
- Move horizontally for up to 10 tiles from their spawn point. Turn around if at the edge of a platform.
- If the player is within 3 tiles, the Guard will move towards the player. Attempting to hit them with their spear.
- Will return to normal movement if player is out of range, or Guard has moved 10 tiles from spawn.

- If hit but a spell:
    - Earn 200 points.
    - Guards is knocked backwards and stunned for 5 secs. While stunned they are no threat.

- If Spell knocks them off their platform, there new "Spawn point" is the tile they've landed on.


## King Froggo:
- After Player has collected 16 pieces of fruit, spawns at the top right of the map.
- Chases the player.
- Can use ladders.
- Can jump horizontally from platform to platform, but prefers not to.
- Has a range of 2 tiles.
- If player is within range, he will swing his trident.
- If Pixie Dust Spawns, he will try and protect it by moving to it and standing on it.

- If hit by spell:
    - Knocked back and stunned for 3 seconds.

# Collectables
## Fruit:
- Games begins with 16 items of fruit placed randomly on platforms through-out the level.

- If touched by player:
    - Disapears
    - player earns 1000 points.

- Enemies don't interact with Fruit.
- If player loses their life, remaining Fruit in level are randomly distributed. 
- If all fruit are collected:
    - Earn 5000 points.
    - All 16 pieces reappear.
    - New Guard will be added to the map.

## Pixie Dust:
- Every 30 second, there is a chance to spawn.
- Spawn point is random.
- Enemies do not collect Pixie Dust.
- If collected, earn 500 points.
- If player collects all 4, press CTRL to activate PIXIE MODE!
- Pixie dust won't spawn again until:
    - Pixie mode is activated.
    - Player dies.

# Pixies:
- Activating Pixie mode will spawn 8 pixes randomly throughout the level.
- Do not collide with Game World or Enemies.
- When collecte:
    - Earn 100 points.
    - Increase Spell Count by 1.

- Pixies should move around using Flocking Rules to avoid enemies.
- Should slowly move towards the player.
- If player dies while activated, remaining Pixies disapear.

## Ladders
- While on Ladder, Speed is halved.
