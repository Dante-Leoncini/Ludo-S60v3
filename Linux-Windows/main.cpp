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
    glPushMatrix();

    // Rotación
    glTranslatef( 0.0f, 3500.0f, 3000.0f );
	//glTranslatef( 0, 55*100, -cameraDistance+170*100);

	if (temblando){
		glTranslatef(temblandoAnim[temblandoFrame][0], temblandoAnim[temblandoFrame][2], temblandoAnim[temblandoFrame][1]);		
		temblandoFrame++;
		if (temblandoFrame > 9){
			temblando = false;
			temblandoFrame = 0;			
		}
	}
    glRotatef(angle, 1.0f, 0.0f, 0.0f);

	if (TurnoDe == Verde){
	    glClearColor( 0.01, 0.63, 0.29, 1.0 );		
	}
	else if (TurnoDe == Amarillo){
	    glClearColor( 1.0, 0.87, 0.02, 1.0 );		
	}	
	else if (TurnoDe == Azul){
	    glClearColor( 0.20, 0.36, 0.83, 1.0 );		
	}	
	else if (TurnoDe == Rojo){	
	    glClearColor( 0.92, 0.12, 0.15, 1.0 );	
	}

    // Limpiar pantalla
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glEnable(GL_TEXTURE_2D);

	//tablero
    glBindTexture(GL_TEXTURE_2D, texTablero);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_SHORT, 0, objVertexdataModel);
    glNormalPointer(GL_BYTE, 0, objNormaldataModel);
    glTexCoordPointer(2, GL_FLOAT, 0, objTexdataModelF);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseWhite);		

    glDrawElements(GL_TRIANGLES, objFacesModel * 3, GL_UNSIGNED_SHORT, objFacedataModel);

    //sombras
	glDisable( GL_DEPTH_TEST ); //se quita el zbuffer
	glEnable( GL_BLEND ); // Enable blending for transparency.
	glBindTexture(  GL_TEXTURE_2D, texSombra ); //selecciona la textura
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glVertexPointer( 3, GL_SHORT, 0, objVertexdataSombra ); //selecciona los vertices
    glTexCoordPointer(2, GL_FLOAT, 0, objTexdataSombraF);
	glNormalPointer( GL_BYTE, 0, objNormaldataSombra ); //selecciona las normales

	//glMaterialfv(   GL_FRONT_AND_BACK, GL_AMBIENT,  objAmbient  );
	//glMaterialfv(   GL_FRONT_AND_BACK, GL_SPECULAR, objSpecular );
	//glMaterialx( GL_FRONT_AND_BACK, GL_SHININESS,   12 << 16     );
	
	for(int i=0; i < NumJugadores*4; i++){
		glPushMatrix(); //guarda la matrix
		SetPos(i, true);
		if (Fichas[i].vivo && !Fichas[i].gano){
			if (casilleros[Fichas[i].casillero].visitantes > 9){
			    glScalef(0.5f,0.5f,0.5f);	
				glTranslatef( PosHabitantesDieciseis[Fichas[i].IndiceHabitante][0],
						      0,//-5000, 
						      PosHabitantesDieciseis[Fichas[i].IndiceHabitante][1]);	
				
			}
			else if (casilleros[Fichas[i].casillero].visitantes > 4){
			    glScalef(0.5f,0.5f,0.5f);	
				glTranslatef( PosHabitantesNueve[Fichas[i].IndiceHabitante][0],
						      0,//-5000, 
						      PosHabitantesNueve[Fichas[i].IndiceHabitante][1]);	
				
			}
			else if (casilleros[Fichas[i].casillero].visitantes > 1){
			    glScalef(0.6f,0.6f,0.6f);	
				glTranslatef( PosHabitantesCuatro[Fichas[i].IndiceHabitante][0],
						      0,//-3200, 
						      PosHabitantesCuatro[Fichas[i].IndiceHabitante][1]);					
			}	
		}
		glDrawElements( GL_TRIANGLES, objFacesSombra * 3, GL_UNSIGNED_SHORT, objFacedataSombra );
		glPopMatrix(); //reinicia la matrix a donde se guardo
	}
	
	//Seleccionado
	if (EstadoJuego == SeleccionFicha){
		glPushMatrix(); //guarda la matrix
		glVertexPointer( 3, GL_SHORT, 0, objVertexdataSeleccion ); //selecciona los vertices
		glTexCoordPointer( 2, GL_BYTE, 0, objTexdataSeleccion );
		glBindTexture(  GL_TEXTURE_2D, texSeleccion ); //selecciona la textura	
		glNormalPointer( GL_BYTE, 0, objNormaldataSeleccion ); //selecciona las normales
		if (TurnoDe == Verde){
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseGreen);			
		}
		else if (TurnoDe == Amarillo){
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseYellow);			
		}	
		else if (TurnoDe == Azul){
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseBlue);			
		}	
		else if (TurnoDe == Rojo){
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseRed);			
		}	
		glTranslatef(Fichas[FichaSeleccionada].posX, 0, Fichas[FichaSeleccionada].posY);
		//dibuja
		glDrawElements( GL_TRIANGLES, objFacesSombra * 3, GL_UNSIGNED_SHORT, objFacedataSeleccion );
		glPopMatrix(); //reinicia la matrix a donde se guardo	
	}

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	//Fichas
	glEnable( GL_DEPTH_TEST ); //se recupera el zbuffer
	glDisable( GL_TEXTURE_2D ); //desactiva las texturas
	glVertexPointer( 3, GL_SHORT, 0, objVertexdataFicha ); //selecciona los vertices
	glNormalPointer( GL_BYTE, 0, objNormaldataFicha ); //selecciona las normales

	glMaterialfv(   GL_FRONT_AND_BACK, GL_AMBIENT,  objAmbient  );
	glMaterialfv(   GL_FRONT_AND_BACK, GL_SPECULAR, objSpecular );
    #ifdef __SYMBIAN32__  
        // Symbian (OpenGL ES 1.1 con punto fijo)
        glMaterialx(GL_FRONT_AND_BACK, GL_SHININESS, 12 << 16);
    #else
        // PC (OpenGL normal)
        glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 12);
    #endif

	for(int e=0; e < NumJugadores; e++){
		//primero setea el color por equipo
		if (e == Verde){
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseGreen);
		}
		else if (e == Amarillo){
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseYellow);
		}
		else if (e == Azul){
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseBlue);
		}
		else {glMaterialfv(
			GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseRed);
		}
		//dibuja las 4 fichas
		for(int i=0; i < 4; i++){
			glPushMatrix(); //guarda la matrix
			int ficha = e*4+i;
			SetPos(ficha, false);	//lo dibuja en su posicion y reinicia la matrix	
			//esto es cuando hay varias ficahs en un mismo casillero
			if (Fichas[ficha].vivo && !Fichas[ficha].gano){		
				if (casilleros[Fichas[ficha].casillero].visitantes > 9){
				    glScalef(0.5f,0.5f,0.5f);	
					glTranslatef( 0+PosHabitantesDieciseis[Fichas[ficha].IndiceHabitante][0],
							      -5000, 
							      0+PosHabitantesDieciseis[Fichas[ficha].IndiceHabitante][1]);	
					
				}
				else if (casilleros[Fichas[ficha].casillero].visitantes > 4){
				    glScalef(0.5f,0.5f,0.5f);	
					glTranslatef( 0+PosHabitantesNueve[Fichas[ficha].IndiceHabitante][0],
							      -5000, 
							      0+PosHabitantesNueve[Fichas[ficha].IndiceHabitante][1]);	
					
				}
				else if (casilleros[Fichas[ficha].casillero].visitantes > 1){
				    glScalef(0.6f,0.6f,0.6f);	
					glTranslatef( 0+PosHabitantesCuatro[Fichas[ficha].IndiceHabitante][0],
							      -3200, 
							      0+PosHabitantesCuatro[Fichas[ficha].IndiceHabitante][1]);	
					
				}			    
			}

			glTranslatef( PosHabitantesCuatro[Fichas[ficha].IndiceHabitante][0],
						  0, //-3200
						  PosHabitantesCuatro[Fichas[ficha].IndiceHabitante][1]
						);	
			glDrawElements( GL_TRIANGLES, objFacesFicha * 3, GL_UNSIGNED_SHORT, objFacedataFicha );
			glPopMatrix(); //reinicia la matrix a donde se guardo
		}
	}
	
	//dado
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseWhite);	
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable( GL_TEXTURE_2D ); //activa la textura
	glBindTexture(  GL_TEXTURE_2D, texDado ); //selecciona la textura	
	glVertexPointer( 3, GL_SHORT, 0, objVertexdataDado ); //selecciona los vertices
	glNormalPointer( GL_BYTE, 0, objNormaldataDado ); //selecciona las normales
    glTexCoordPointer( 2, GL_BYTE, 0, objTexdataDado );

	if (TurnoDe == Verde){
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseGreen);			
	}
	else if (TurnoDe == Amarillo){
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseYellow);			
	}	
	else if (TurnoDe == Azul){
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseBlue);			
	}	
	else if (TurnoDe == Rojo){
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseRed);			
	}

	//reset pos rot
	glTranslatef(0, -4750, 0); //x, z, y
	glTranslatef(animacionPos[animacionPosFrame][0]+posDado[TurnoDe][0], 
			     animacionPos[animacionPosFrame][2], 
			     animacionPos[animacionPosFrame][1]+posDado[TurnoDe][1]); //x, z, y

	//rotacion del dado
	glRotatef(-animacionRot[animacionPosFrame][0], 0, 0, 1); //angulo, X Y Z
	glRotatef(-animacionRot[animacionPosFrame][1], 0, 1, 0); //angulo, X Y Z
	glRotatef(-animacionRot[animacionPosFrame][2], 1, 0, 0); //angulo, X Y Z
	SetDado();
	
	glDrawElements( GL_TRIANGLES, objFacesDado * 3, GL_UNSIGNED_SHORT, objFacedataDado );
	
	if (97 > animacionPosFrame){
		animacionPosFrame++;
	}
	else if (EstadoJuego == DadoLanzado){
		CalcOpciones();
	}
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();             // Restaurar matriz
}

void ConstructL(){
	for(int i=0; i<4; i++){
		Equipos[i].termino = false;
		Equipos[i].puesto = 0;
		Equipos[i].llegaron = 0;	
	}
	for(int i=0; i<16; i++){
		Fichas[i].vivo = false;	//nacen muertos	
		Fichas[i].gano = false;	//nacen sin ganar	
		Fichas[i].movimiento = false;	//no tiene movimiento
		Fichas[i].progreso = 0;
		Fichas[i].casillero = -1;
		Fichas[i].AnimFrame = 0;
		Fichas[i].IndiceHabitante = 1;
		if (i < 4){
			Fichas[i].equipo = Verde; 
			//Fichas[i].color[4] = MATERIALCOLOR(0.01, 0.63, 0.29, 1.0); //objDiffuseGreen;
		}
		else if (i < 8){
			Fichas[i].equipo = Amarillo;
			//Fichas[i].color[4] = MATERIALCOLOR(1.0, 0.87, 0.02, 1.0); //objDiffuseYellow;
		}
		else if (i < 12){
			Fichas[i].equipo = Azul;
			//Fichas[i].color[4] = MATERIALCOLOR(0.20, 0.36, 0.83, 1.0); //objDiffuseBlue;
		}
		else {
			Fichas[i].equipo = Rojo;
			//Fichas[i].color[4] = MATERIALCOLOR(0.92, 0.12, 0.15, 1.0); //objDiffuseRed;
		}
		Fichas[i].posX = posMuertos[i][0];
		Fichas[i].posY = posMuertos[i][1];
	}
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