#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "../Shared/recorridos.h"
#include "../Shared/dado.h"
#include "../Shared/variables.h"
#include "../Shared/ficha.h"
#include "../Shared/tablero.h"
#include "../Shared/sombra.h"
#include "../Shared/seleccion.h"
#include "../Shared/constructor.h"
#include "../Shared/render.h"

// Función simple para leer el ini
Config loadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir " << filename << ", usando valores por defecto.\n";
        return cfg;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, eq, value;
        if (iss >> key >> eq >> value && eq == "=") {
            if (key == "fullscreen") cfg.fullscreen = (value == "true");
            else if (key == "width") cfg.width = std::stoi(value);
            else if (key == "height") cfg.height = std::stoi(value);
            else if (key == "displayIndex") cfg.displayIndex = std::stoi(value);
        }
    }

    return cfg;
}

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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
		std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
		return -1;
	}

    // Abrir el primer mando disponible
    if (SDL_NumJoysticks() > 0) {
        if (SDL_IsGameController(0)) {
            controller = SDL_GameControllerOpen(0);
            if (controller) {
                std::cout << "Control detectado: " 
                        << SDL_GameControllerName(controller) << std::endl;
            }
        }
    }

    // ---- CONFIGURAR ANTIALIASING ----
    // Pedir un framebuffer con multisampling
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // 4x MSAA (puedes probar 8, 16 si tu GPU soporta)

	Config cfg = loadConfig("./configuraciones.ini");

    Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	if (cfg.fullscreen) windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

    // Crear ventana con OpenGL
    window = SDL_CreateWindow(
		"Ludo",
    	SDL_WINDOWPOS_CENTERED_DISPLAY(cfg.displayIndex), // posición centrada en monitor 2
		SDL_WINDOWPOS_CENTERED_DISPLAY(cfg.displayIndex),
        cfg.width, cfg.height,
        windowFlags);

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
    gluPerspective(45.0,(float)cfg.width/(float)cfg.height, 10.0, 20000.0);

    // Cargar textura
    /*if (!LoadTexture("../Shared/tablero.jpg", texTablero)) {
        std::cerr << "Error cargando tablero.jpg" << std::endl;
        return -1;
    }*/
	//version HD para PC
    if (!LoadTexture("../Shared/tablero_HD.png", texTablero)) {
        std::cerr << "Error cargando tablero_HD.png" << std::endl;
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

            // gamepad (si usás SDL_INIT_GAMECONTROLLER)
            else if (e.type == SDL_CONTROLLERBUTTONDOWN) {
                switch (e.cbutton.button) {
                    case SDL_CONTROLLER_BUTTON_A: Confirmar(); break;
                    case SDL_CONTROLLER_BUTTON_Y: ResetCamara(); break;
                    //case SDL_CONTROLLER_BUTTON_X: Restar(); break;
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: ClickDerecha(); break;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:  ClickIzquierda(); break;
                    case SDL_CONTROLLER_BUTTON_B: running = false; break;
                }
            }
			else if (e.type == SDL_CONTROLLERAXISMOTION) {
				float value = e.caxis.value / 32767.0f;
				if (fabs(value) < 0.05f) value = 0.0f; // deadzone

				axisState[e.caxis.axis] = value; // guardar el valor normalizado
			}
			// Botones del mouse
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT) { 
					Confirmar();
				}
				else if (e.button.button == SDL_BUTTON_MIDDLE) {  // rueda clic
					middleMouseDown = true;
					GuardarMousePos();
				}
				/*else if (e.button.button == SDL_BUTTON_RIGHT) {  
				}*/
			}
			else if (e.type == SDL_MOUSEBUTTONUP) {
				if (e.button.button == SDL_BUTTON_MIDDLE) {
					middleMouseDown = false;
				}
			}
			else if (e.type == SDL_MOUSEMOTION){
				int mx = e.motion.x;
				int my = e.motion.y;
				if (middleMouseDown) {
					CheckWarpMouseInWindow(mx, my);
					// Chequear si Shift está presionado
					bool shiftHeld = (SDL_GetModState() & KMOD_SHIFT);

					if (shiftHeld) {

						PivotZ -= dy * factor * cosY;
						PivotX += dx * factor * cosX - dy * factor * sinY * sinX;
						PivotY += dx * factor * sinX + dy * factor * sinY * cosX;
					} 
					else {
						// ROTAR cámara
						rotX += dx * 0.2f;  
						rotY += dy * 0.2f;  
						recalcularCamara = true;
					}
				}
			}
        }

		rotX   += axisState[SDL_CONTROLLER_AXIS_RIGHTX] * 2.0f;
		rotY   += axisState[SDL_CONTROLLER_AXIS_RIGHTY] * 2.0f;

		// Limitar rotY para evitar giros extremos
		if(rotY > 180.0f) rotY -= 360.0f;
		if(rotY < -180.0f) rotY += 360.0f;
		if(rotX > 180.0f) rotX -= 360.0f;
		if(rotX < -180.0f) rotX += 360.0f;

		if (recalcularCamara || axisState[SDL_CONTROLLER_AXIS_RIGHTX] != 0.0f || axisState[SDL_CONTROLLER_AXIS_RIGHTY] != 0.0f ){
			//precalculos
			radY = rotY * M_PI / 180.0f; // Yaw
			radX = rotX * M_PI / 180.0f; // Pitch

			cosX = cos(radX);
			sinX = sin(radX);
			cosY = cos(radY);
			sinY = sin(radY);
			recalcularCamara = false;
		}

		// Movimiento cámara según sticks y gatillos
		PivotZ -= axisState[SDL_CONTROLLER_AXIS_LEFTY] * factor * cosY;
		PivotX += axisState[SDL_CONTROLLER_AXIS_LEFTX] * factor * cosX - axisState[SDL_CONTROLLER_AXIS_LEFTY] * factor * sinY * sinX;
		PivotY += axisState[SDL_CONTROLLER_AXIS_LEFTX] * factor * sinX + axisState[SDL_CONTROLLER_AXIS_LEFTY] * factor * sinY * cosX;

		//std::cout << "rotY: " << rotY << std::endl;

		posY   += (axisState[SDL_CONTROLLER_AXIS_TRIGGERRIGHT] - 
				axisState[SDL_CONTROLLER_AXIS_TRIGGERLEFT]) * 10.0f;

		//test   += (axisState[SDL_CONTROLLER_AXIS_TRIGGERRIGHT] - 
		//		axisState[SDL_CONTROLLER_AXIS_TRIGGERLEFT]) * 0.5f;

        Render();

        // Mostrar
        SDL_GL_SwapWindow(window);

        // Animación
        SDL_Delay(16); // ~60 fps
    }

	if (controller) {
		SDL_GameControllerClose(controller);
	}
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}