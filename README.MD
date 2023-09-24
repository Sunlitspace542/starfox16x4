# Star Fox 16 x 4
(todo: cool logo thing)  
Based on [HackerSM64](https://github.com/HackerN64/HackerSM64)

## What??
I've started reading through and documenting the source code of the original Star Fox as part of my [UltraStarFox](https://github.com/Sunlitspace542/ultrastarfox) fork of the source code.  
After various observations regarding SM64's development and Star Fox's influence on it, I decided to try to port the game to the N64 using the SM64 engine.  

## Credits (in alphabetical order)
AloXado320: Programming assistance, answering my dumb SM64 questions  
Church of Kondo: Restored music used for BGM  
HackerSM64 developers/contributors: Making HackerSM64 in the first place  
Kandowontu: Answering my Star Fox related questions, feedback, general encouragement  
Monika: Assistance, feedback, moral support  
Sunlit: Lead programmer, model porting, sprites, real N64 testing  

## List of important things to be done

### Freeing up/Conserving ROM Space:
- [X] Remove all SM64 object behaviors  
- [ ] Remove all the Mario behavior/action code that we don't need 
- [ ] Remove SM64 actor models (partially done)  
- [ ] Remove all vanilla music and their instrument banks
- [x] Settle on a good rate for streamed audio BGM (32000hz mono)  

### Game Code:
``src/game/hud.c``:  

- [X] Implement HUD (shield, boost, brake, bombs)  

``src/game/pstrats.c``:  

- [x] Player pitch, yaw & roll  
- [X] Get a basic laser strat in  
- [x] Proper boosting and braking  
- [x] Player ship flags working  
- [ ] Player ship wobble

Other:  
- [ ] Begin work on implementing Star Fox world functionality, object macros, levels, etc.  
- [ ] Port over PATH/strat commands from Star Fox as necessary  
- Find loop points for music  