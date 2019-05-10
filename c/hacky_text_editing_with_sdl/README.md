A ***VERY*** hacky text editing gui with SDL & SDL_TTF
---
This is the **very first** non-trivial project I made with C.  
It is completely **hacked together without much planning to learn C quickly**.  
I was still learning the ***basics***, so it's all extremely rough around the edges.  
**The project is at best a C & SDL example because it barely works and is structured hackily.**  
**I would rewrite the project with better planning instead of fixing anything here.**  
Before beginning this project I didn't know:  
- basics of SDL & SDL_TTF
- malloc/calloc & free
- arrays of pointers
- how to structure a project in C larger than a couple of files

It also doesn't act much like a real Text Editor because:  
- **line count & line width is FIXED**, that means you can't type more characters than can fit in the window
- **it only saves to** `/tmp/main.c` **by default**, so I could write a hello world program.
- **it only uses a default monospace font** specified at `/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf`

The code in the `game_h` folder was extracted to see what an SDL game engine could look like for use in other projects.  
The UI only updates after an event, but it can run at ~60 FPS with modification (the timers are integers).  
The render timer is seperate from the logic timer so they can work at different speeds.  
That is only useful because the logic/render code isn't given a time delta from the previous loop.  
**The timers will probably overflow after INT_MAX ticks**  

### I still had plenty of fun hacking this together!

The makefile should be self-explanatory if you want to run it.