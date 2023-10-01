# Star Fox 16x4
(todo: cool logo thing)  
A remake of Star Fox (1993) for the Nintendo 64.
Based on [HackerSM64](https://github.com/HackerN64/HackerSM64)

## Credits (in alphabetical order)
AloXado320: Programming assistance, answering my dumb SM64 questions  
Church of Kondo: Restored music used for BGM  
HackerSM64 developers/contributors: Making HackerSM64 in the first place  
Kandowontu: Answering my Star Fox related questions, feedback, general encouragement  
Monika: Assistance, feedback, moral support  
Sunlit: Lead programmer, model porting, sprites, real N64 testing  

## TODO List

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
- [ ] Barrel rolls
- [ ] Player ship wobble

``src/game/skybox.c``:  
- [x] Get skyboxes working  

Other:  
- [ ] Camera really needs some work  
- [ ] Begin work on implementing Star Fox world functionality, object macros, levels, etc.  
- [ ] Port over PATH/strat commands from Star Fox as necessary  
- Find loop points for music  
