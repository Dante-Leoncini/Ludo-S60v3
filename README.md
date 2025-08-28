# Ludo-S60v3
Ludo creado para Symbian S60v3 con opcion de jugar de a 2 a 4 jugadores

# Linux
Estoy probando un port multiplataforma de Linux/Symbian
para compilar en linux. abran la carpeta "Linux" y usen el comando:
"g++ main.cpp -o ludo -lSDL2 -lSDL2_image -lGL -lGLU"
o usa
"make linux" para usar el Makefile

para usar el ejecutable ./ludo

# Windows
"x86_64-w64-mingw32-g++ main.cpp -o juego.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglu32"