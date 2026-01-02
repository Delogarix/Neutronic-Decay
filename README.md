# Neutronic Decay

## Building project

First create a build folder inside the root directory
```bash
mkdir build
cd src
```

### To build for Windows :
```bash
g++ *.cpp -o ../build/game.exe -Wall -I ../include/ -L ../lib/Windows/ -lraylib -lgdi32 -lwinmm -lopengl32
```
### To build for GNU/Linux
```bash
g++ *.cpp -o ../build/game.out -Wall -std=c++14 -I ../include/ -L ../lib/GNU-Linux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
To build for HTML5 :
```bash
em++ -o ../build/game.html main.cpp Entity.cpp Player.cpp AnimatedSprite.cpp Arrow.cpp Homing.cpp Sequencer.cpp Game.cpp Timer.cpp -Os -Wall ../lib/Web/libraylib.a -I. -I ../include -L. -s USE_GLFW=3 --shell-file ../shell/shell_custom.html -DPLATFORM_WEB --preload-file assets --preload-file wave
```
## Setup the database
replace <password> with the generated password from your docker
```bash
mariadb --user="root" --password=<password> -e 'CREATE DATABASE gamedb'
mariadb --user="root" --password=<password> gamedb < Neutronic-Decay/server/gamedb.sql
```
Then change the password inside server/structure/script_data.php
