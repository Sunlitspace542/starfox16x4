# Star Fox 16 x 4
(todo: cool logo thing)  
Based on [HackerSM64](https://github.com/HackerN64/HackerSM64)

## What??
I've started reading through and documenting the source code of the original Star Fox as part of my [UltraStarFox](https://github.com/Sunlitspace542/ultrastarfox) fork of the source code.  
After various observations regarding SM64's development and Star Fox's influence on it, I decided to try to port the game to the N64 using the SM64 engine.  

## Credits (so far)
AloXado320: Programming assistance, answering my dumb questions  
Church of Kondo: Restored music used for BGM  
HackerSM64 developers/contributors: Making HackerSM64 in the first place  
Kandowontu: Answering my Star Fox related questions  
Monika: assistance  
Sunlit: programming, assets  


## TODO
- Strip Mario's behaviors down to only what is needed for the game to still work  
- get PSTRATS up and running  
- Rename all obj_helper and bhv macros to their PATH and STRAT equivalents  
- Remove all objects/behaviors/models (clean slate)  
- Figure out how i'm going to handle music/sounds  
- Start porting strats/paths/models  

## List of important things to be done

### Freeing up ROM space:
- [X] Remove all SM64 object behaviors
- [ ] Remove SM64 actor models (partially done)
- [ ] Remove all vanilla music and their instrument banks

### Game:
``src/game/hud.c``:  
- [X] Implement HUD (shield, boost, brake, bombs)
``src/game/pstrats.c``:  
- [ ] Player pitch, yaw & roll
- [X] Get a basic laser strat in
- [ ] Proper boosting and braking