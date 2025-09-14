# Ludo-S60v3
Ludo creado para Symbian S60v3 con opcion de jugar de a 2 a 4 jugadores

# Linux
Estoy probando un port multiplataforma de Linux/Symbian
Para compilar en Ubuntu es necesario tener instalado: 

build-essential → incluye g++, make, etc. (herramientas básicas de compilación).
libsdl2-dev → cabeceras y librerías de desarrollo de SDL2.
libsdl2-image-dev → lo mismo pero para SDL2_image.
libglu1-mesa-dev, freeglut3-dev, mesa-common-dev → cabeceras y librerías de OpenGL/GLU.

se puede instalar haciendo: "sudo apt install build-essential libsdl2-dev libsdl2-image-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev"

para compilar en linux. abran la carpeta "Linux" y usen el comando:
"g++ main.cpp -o ludo -lSDL2 -lSDL2_image -lGL -lGLU"
o usa
"make linux" para usar el Makefile

para usar el ejecutable ./ludo

# Windows
"x86_64-w64-mingw32-g++ main.cpp -o juego.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglu32"