# Ludo para Symbian S60v3, s60v5 y Symbian Belle
Ludo creado para Symbian con opcion de jugar de a 2 a 4 jugadores.
Originalmente lo hice para jugar con mis amigos en un cumpleaños y aprender como programar en OpenGL ES 1.1.
Fue el primer proyecto para s60v3 que hice. y que aprobechaba la aceleracion grafica del Nokia N95 (aunque tambien funciona en otros modelos)

Proximamente pienso darle soporte para pantallas tactiles

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