# Flappybird
 Flappybird game using SDL2 library in C/C++


## Build
To build the application run the following command: <br>
`g++ -g ./src/*.cpp -o ./bin/flappybird.exe -I./include -L./lib -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image`

**No additional libraries are required. All SDL required files are in the include and bin directory.*

## Run
```
cd bin
flappybird.exe
```
