#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#include "../Shared/ficha.h"
#include "../Shared/tablero.h"

// --- ID de textura ---
GLuint texTablero = 0;

// --- Cargar textura ---
bool LoadTexture(const char* filename, GLuint &textureID) {
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        std::cerr << "Error cargando textura: " << IMG_GetError() << std::endl;
        return false;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Configurar filtros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Determinar formato
    GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0,
                 format, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, format, surface->w, surface->h,
                    format, GL_UNSIGNED_BYTE, surface->pixels);

    SDL_FreeSurface(surface);
    return true;
}

// --- Función para dibujar la ficha ---
void Render() {        
    glDisable(GL_TEXTURE_2D);

    // Darle color (sin iluminación, solo color plano)
    glColor3f(0.8f, 0.2f, 0.2f);

    // Activar arrays de vértices y normales
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // Punteros a tus datos en Shared/ficha.h
    glVertexPointer(3, GL_SHORT, 0, objVertexdataFicha);
    glNormalPointer(GL_BYTE, 0, objNormaldataFicha);

    // Dibujar con los índices
    glDrawElements(GL_TRIANGLES, objFacesFicha * 3, GL_UNSIGNED_SHORT, objFacedataFicha);

    // Desactivar arrays
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

// --- Función para dibujar el tablero con textura ---
void RenderTablero() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texTablero);

    glColor3f(1.0f, 1.0f, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_SHORT, 0, objVertexdataModel);
    glNormalPointer(GL_BYTE, 0, objNormaldataModel);
    glTexCoordPointer(2, GL_FLOAT, 0, objTexdataModelF);

    glDrawElements(GL_TRIANGLES, objFacesModel * 3, GL_UNSIGNED_SHORT, objFacedataModel);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glDisable(GL_TEXTURE_2D);
}

int main(int argc, char* argv[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Crear ventana con OpenGL
    SDL_Window* window = SDL_CreateWindow("SDL2 OpenGL Cube",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Error SDL_CreateWindow: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);

    // Configuración básica de OpenGL
    glEnable(GL_DEPTH_TEST); // Habilitar z-buffer
    //glDisable(GL_CULL_FACE); // desactivar culling
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0/600.0, 10.0, 20000.0);

    // Fondo gris para que no sea negro puro
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    // Cargar textura
    if (!LoadTexture("../Shared/tablero.jpg", texTablero)) {
        std::cerr << "Error cargando tablero.jpg" << std::endl;
        return -1;
    }

    float angle = 45.0f;
    bool running = true;
    SDL_Event e;

    // Cámara y transformaciones
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(0, 0, 8000,   // ojo
        0, 0, 0,      // centro
        0, 1, 0);     // up

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // Luz blanca desde arriba/delante
    GLfloat light_pos[] = { 5000.0f, 5000.0f, 5000.0f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        glPushMatrix();

        // Rotación
        glRotatef(angle, 1.0f, 0.0f, 0.0f);
        glTranslatef( 0.0f, 4500.0f, -1000.0f );

        // Limpiar pantalla
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderTablero();
        // Llamamos a la función que dibuja la ficha
        Render();

        glPopMatrix();             // Restaurar matriz

        // Mostrar
        SDL_GL_SwapWindow(window);

        // Animación
        SDL_Delay(16); // ~60 fps
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}