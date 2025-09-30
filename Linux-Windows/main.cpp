#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <filesystem>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <map>
#include <string>
#include <algorithm>
#include <cstring>

#include "../Shared/recorridos.h"
#include "../Shared/dado.h"
#include "../Whisk3D/Shared/clases.h"
#include "../Whisk3D/Shared/colores.h"
#include "../Whisk3D/Shared/OpcionesRender.h"
#include "../Whisk3D/Shared/import_obj.h"
#include "../Shared/variables.h"
#include "../Shared/ficha.h"
#include "../Shared/tablero.h"
#include "../Shared/sombra.h"
#include "../Shared/seleccion.h"
#include "../Shared/constructor.h"
#include "../Shared/font.h"
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

	Config cfg = loadConfig("./config.ini");

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

	InitOpenGL();

    // Cargar textura
    /*if (!LoadTexture("../Shared/tablero.jpg", texTablero)) {
        std::cerr << "Error cargando tablero.jpg" << std::endl;
        return -1;
    }*/
	//version HD para PC
    /*if (!LoadTexture("../Shared/tablero_HD.png", texTablero)) {
        std::cerr << "Error cargando tablero_HD.png" << std::endl;
        return -1;
    }	*/
    if (!LoadTexture("../Shared/dice-texture.jpg", texDado)) {
        std::cerr << "Error cargando dice-texture.jpg" << std::endl;
        return -1;
    }
    if (!LoadTexture("../Shared/sombra_HD.png", texSombra)) { 
        std::cerr << "Error cargando sombra_HD.png" << std::endl;
        return -1;
    }
    /*if (!LoadTexture("../Shared/sombra.png", texSombra)) { 
        std::cerr << "Error cargando sombra.png" << std::endl;
        return -1;
    }*/	
    /*if (!LoadTexture("../Shared/seleccion.png", texSeleccion)) {
        std::cerr << "Error cargando seleccion.png" << std::endl;
        return -1;
    }*/
    if (!LoadTexture("../Shared/seleccion_HD.png", texSeleccion)) {
        std::cerr << "Error cargando seleccion_HD.png" << std::endl;
        return -1;
    }

    if (!LoadTexture("../Shared/font.png", texFont)) {
        std::cerr << "Error cargando font.png" << std::endl;
        return -1;
    }	

    //if (!ImportOBJ("../Shared/OBJ_tests/triangulo.obj")) {
    //if (!ImportOBJ("../Shared/OBJ_tests/cubo_triangulos.obj")) {	
    //if (!ImportOBJ("../Shared/OBJ_tests/cubo_cuads.obj")) {		
    //if (!ImportOBJ("../Shared/OBJ_tests/monkey.obj")) {			
    /*if (!ImportOBJ("../Shared/models/morgan.obj")) {			
    //if (!ImportOBJ("../Shared/OBJ_tests/objetos.obj")) {		
        std::cerr << "Error al importar el OBJ\n";
        return -1;
    }*/
    if (!ImportOBJ("../Shared/modelos_basicos/tablero_procedural.obj")) {		
        std::cerr << "Error al importar el OBJ\n";
        return -1;
    }

	int lastIndex = Objects.size() - 1;
	int baseIndex = Objects.back().Id; // malla del último importado
	Object base = Objects[lastIndex];

	// Buscar índice del material "Equipo"
	int equipoId = -1;
	for (size_t i = 0; i < Materials.size(); i++) {
		if (Materials[i].name == "Equipo") {
			equipoId = (int)i;
			Materials[equipoId].diffuse[0] = colorEquipo1[0];
			Materials[equipoId].diffuse[1] = colorEquipo1[1];
			Materials[equipoId].diffuse[2] = colorEquipo1[2];
			Materials[equipoId].name = "Equipo_rojo";
			break;
		}
	}

	if (equipoId != -1) {
		// Duplicar 3 veces
		int azulId = DuplicateMaterial(equipoId);
		int amarilloId = DuplicateMaterial(equipoId);
		int verdeId = DuplicateMaterial(equipoId);

		// Cambiar colores difusos
		if (azulId != -1) {
			Materials[azulId].diffuse[0] = colorEquipo3[0];
			Materials[azulId].diffuse[1] = colorEquipo3[1];
			Materials[azulId].diffuse[2] = colorEquipo3[2]; // azul
			Materials[azulId].name = "Equipo_azul";
		}
		if (amarilloId != -1) {
			Materials[amarilloId].diffuse[0] = colorEquipo4[0];
			Materials[amarilloId].diffuse[1] = colorEquipo4[1];
			Materials[amarilloId].diffuse[2] = colorEquipo4[2]; // amarillo
			Materials[amarilloId].name = "Equipo_amarillo";
		}
		if (verdeId != -1) {
			Materials[verdeId].diffuse[0] = colorEquipo2[0];
			Materials[verdeId].diffuse[1] = colorEquipo2[1];
			Materials[verdeId].diffuse[2] = colorEquipo2[2]; // verde
			Materials[verdeId].name = "Equipo_verde";
		}

		// Crear 3 copias y cada una la rota 90 grados en Z
		for (int i = 1; i <= 3; i++) {
			Object rotated = base;
			rotated.rotZ += i * 90.0f;  // 90, 180, 270
			rotated.name = base.name + "_rot" + std::to_string(i * 90);

			int newMeshId = DuplicateMesh(baseIndex);
			rotated.Id = newMeshId;

			if (i == 1){
				Meshes[newMeshId].materialsGroup[0].material = azulId;
			}
			else if (i == 2){
				Meshes[newMeshId].materialsGroup[0].material = amarilloId;
			}
			else if (i == 3){
				Meshes[newMeshId].materialsGroup[0].material = verdeId;
			}

			Objects.push_back(rotated);
			Collection.push_back(Objects.size() - 1);
		}

	}

    bool running = true;
    SDL_Event e;

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

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
					case SDLK_KP_PLUS:  // Tecla + del numpad
						DebugRender(1); // suma al EtapaRender
						break;
					case SDLK_KP_MINUS: // Tecla - del numpad
						DebugRender(-1); // resta al EtapaRender
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
                    //case SDL_CONTROLLER_BUTTON_B: running = false; break;
                }
            }
			else if (e.type == SDL_CONTROLLERAXISMOTION) {
				float value = e.caxis.value / 32767.0f;
				if (fabs(value) < 0.30f) value = 0.0f; // deadzone

				axisState[e.caxis.axis] = value; // guardar el valor normalizado
			}
			// Botones del mouse
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT) { 
					//Confirmar();
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
			radXsombra = rotX * M_PI / 180.0f - 45.0f; // precalculo de sombra

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

		//std::cout << "PivotX: " << PivotX << " PivotY: " << PivotY << " PivotZ: " << PivotZ << std::endl;
		//std::cout << "rotY: " << rotY << std::endl;

		posY   += (axisState[SDL_CONTROLLER_AXIS_TRIGGERRIGHT] - 
				axisState[SDL_CONTROLLER_AXIS_TRIGGERLEFT]) * 10.0f;

		//limita el zoom y la posicion de la camara
		if (posY > 223){
			posY = 223;
		}
		if (posY < -6){
			posY = -6;
		}
		if (PivotX > 2500){
			PivotX = 2500;
		}
		if (PivotX < -2500){
			PivotX = -2500;
		}
		if (PivotY > 2500){
			PivotY = 2500;
		}
		if (PivotY < -2500){
			PivotY = -2500;
		}
		if (PivotZ > 1000){
			PivotZ = 1000;
		}
		if (PivotZ < -3000){
			PivotZ = -3000;
		}
		if (rotY > 90){
			rotY = 90;
		}
		if (rotY < 19){
			rotY = 19;
		}

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