# ¡Tuludo!
Tuludo es un juego de Ludo multiplataforma y de código abierto, creado originalmente para Symbian S60v3, que permite jugar con amigos de 2 a 4 jugadores.

Originalmente lo desarrollé para jugar con mis amigos en un cumpleaños y, al mismo tiempo, aprender a programar en OpenGL ES 1.1. Fue mi primer proyecto para Symbian S60v3 y aprovechaba la aceleración gráfica del Nokia N95

# Como se juega
aun no hay menu. asi que la forma de arrancar el juego es la siguiente
primero: selecciona la cantidad de jugadores apretan de izquierda a derecha. se puede jugar de 2 a 4. y apreta enter
segundo: selecciona el modo manual (el dado 6) o al azar (dado 1). el dado manual te permite seleccionar que dado sale
despues las reglas son como las de cualquier (o casi cualquier) ludo

# Linux
Estoy probando un port multiplataforma de Linux/Symbian
debido a esto. estoy haciendo una gran reescritura. acomodando las cosas. etc.

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