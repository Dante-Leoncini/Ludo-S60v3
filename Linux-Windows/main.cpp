#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#include "../Shared/recorridos.h"
#include "../Shared/dado.h"
#include "../Shared/global-variable.h"
#include "../Shared/ficha.h"
#include "../Shared/tablero.h"
#include "../Shared/sombra.h"
#include "../Shared/seleccion.h"
#include "../Shared/constructor.h"
#include "../Shared/render.h"

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

int main(int argc, char* argv[]) {
    //constructor symbian, linux y windows
    ConstructL();

    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
        return -1;
    }

    // ---- CONFIGURAR ANTIALIASING ----
    // Pedir un framebuffer con multisampling
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // 4x MSAA (puedes probar 8, 16 si tu GPU soporta)

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

    // Cargar textura
    if (!LoadTexture("../Shared/tablero.jpg", texTablero)) {
        std::cerr << "Error cargando tablero.jpg" << std::endl;
        return -1;
    }
    if (!LoadTexture("../Shared/dice-texture.jpg", texDado)) {
        std::cerr << "Error cargando dice-texture.jpg" << std::endl;
        return -1;
    }
    if (!LoadTexture("../Shared/sombra.png", texSombra)) { 
        std::cerr << "Error cargando sombra.png" << std::endl;
        return -1;
    }
    if (!LoadTexture("../Shared/seleccion.png", texSeleccion)) {
        std::cerr << "Error cargando seleccion.png" << std::endl;
        return -1;
    }

    bool running = true;
    SDL_Event e;

    // Cámara y transformaciones
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(0, 0, 8000,   // ojo
        0, 0, 0,      // centro
        0, 1, 0);     // up

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

	//iluminacion
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;

			//eventos del teclado
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_RETURN:  // Enter
						Confirmar();
						break;
					case SDLK_RIGHT:   // Flecha derecha
						ClickDerecha();
						break;
					case SDLK_LEFT:    // Flecha izquierda
						ClickIzquierda();
						break;
					// si querés, agregá más teclas aquí
					case SDLK_ESCAPE:  // Esc para salir rápido
						running = false;
						break;
				}
			}
        }

        Render();

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