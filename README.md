## Neutronic Decay

### Building project

To build and test a new C++ file for Windows :
```bash
g++ *.cpp -o game.exe -Wall -I ../include/ -L ../lib/Windows/ -lraylib -lgdi32 -lwinmm -lopengl32
```
To build and test the HTML file :
```bash
em++ -o ../build/game.html main.cpp Entity.cpp Player.cpp AnimatedSprite.cpp Arrow.cpp Homing.cpp Sequencer.cpp -Os -Wall ../lib/Web/libraylib.a -I. -I ../include -L. -s USE_GLFW=3 --shell-file ../shell/shell.html -DPLATFORM_WEB --preload-file assets wave1.txt
```
