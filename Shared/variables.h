#include <cmath>   // std::sin, std::round (si quieres redondear)
#include <random>
#include <chrono>

//variables de SDL2
SDL_Window* window = nullptr;
SDL_GameController* controller = nullptr;
float axisState[6] = {0.0f};

//camara
int cameraDistance = 270;
GLfloat posX = 0.0f;
GLfloat posY = 100.0f;
GLfloat posZ = 0.0f;
GLfloat rotX = 0.0f;
GLfloat rotY = 45.0;
GLfloat PivotX = 0.0f;
GLfloat PivotY = 0.0f;
GLfloat PivotZ = 0.0f;
//float angle = 55.0f;

void ResetCamara(){
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;
	PivotX = 0.0f;
	PivotY = 0.0f;
	PivotZ = 0.0f;
}

#ifndef PI
#define PI 3.14159265358979323846
#endif

GLuint texTablero, texDado, texSombra, texSeleccion;

//parametros del juego
typedef enum { Verde, Amarillo, Azul, Rojo } ColoresEquipo;
typedef enum { linear, easeIn, easeOut, easeInOut, RisingFalling } Transition;
typedef enum { CantidadJugadores, ModoDado, SeleccionDado, DadoLanzado, SeleccionFicha, AnimacionFicha } EstadoLudo;

EstadoLudo EstadoJuego = CantidadJugadores;

#define MATERIAL_MAX 1
#define MATERIALCOLOR(r, g, b, a)     \
       (GLfloat)(r * MATERIAL_MAX),   \
       (GLfloat)(g * MATERIAL_MAX),   \
       (GLfloat)(b * MATERIAL_MAX),   \
       (GLfloat)(a * MATERIAL_MAX)

//Colores de Fichas
static const GLfloat objDiffuseWhite[4]  = { MATERIALCOLOR(1.0, 1.0, 1.0, 1.0) };
static const GLfloat objDiffuseRed[4]  = { MATERIALCOLOR(0.92, 0.12, 0.15, 1.0) };
static const GLfloat objDiffuseGreen[4]  = { MATERIALCOLOR(0.01, 0.63, 0.29, 1.0) };
static const GLfloat objDiffuseBlue[4]  = { MATERIALCOLOR(0.20, 0.36, 0.83, 1.0) };
static const GLfloat objDiffuseYellow[4]  = { MATERIALCOLOR(1.0, 0.87, 0.02, 1.0) };

static const GLfloat objAmbient[4]  = { MATERIALCOLOR(0.4, 0.4, 0.4, 1.0) };

//Specular Basico
static const GLfloat objSpecular[4] = { MATERIALCOLOR(1.0, 1.0, 1.0, 1.0) };

// Luz blanca desde arriba/delante
static const GLfloat light_pos[] = { -5000.0f, 5000.0f, 5000.0f, 1.0f };
static const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

struct Config {
    bool fullscreen = false;
    int width = 800;
    int height = 600;
	int displayIndex = 0; // monitor 1
};
Config cfg;

//precalculos
bool recalcularCamara = true;
float radY = 0.0f;
float radX = 0.0f;

float factor = 30.0f;

float cosX = 0.0f;
float sinX = 0.0f;
float cosY = 0.0f;
float sinY = 0.0f;

//mouse
bool middleMouseDown = false;
int lastMouseX, lastMouseY;
int dx = 0;
int dy = 0;

void CheckWarpMouseInWindow(int mx, int my){
    bool warped = false;
	dx = mx - lastMouseX;
	dy = my - lastMouseY;

    if (mx <= 0) {
        mx = cfg.width - 2;
        SDL_WarpMouseInWindow(window, mx, my);
        warped = true;
    }
    else if (mx >= cfg.width - 1) {
        mx = 1;
        SDL_WarpMouseInWindow(window, mx, my);
        warped = true;
    }

    // --- wrap vertical ---
    if (my <= 0) {
        my = cfg.height - 2;
        SDL_WarpMouseInWindow(window, mx, my);
        warped = true;
    }
    else if (my >= cfg.height - 1) {
        my = 1;
        SDL_WarpMouseInWindow(window, mx, my);
        warped = true;
    } 

    // Calcular delta solo si no hubo warp
    if (!warped) {
        dx = mx - lastMouseX;
        dy = my - lastMouseY;
    } else {
        dx = 0;
        dy = 0; // ignorar delta falso
    }
	
	// Guardar última posición
    lastMouseX = mx;
    lastMouseY = my;
}

void GuardarMousePos() {
    SDL_GetMouseState(&lastMouseX, &lastMouseY);
	/*std::cout << "Mouse guardado en: X=" << lastMouseX 
              << " Y=" << lastMouseY << std::endl;*/
}

bool DadoManual = true;
int Dado = 6;
int Tiros = 1;
int NumJugadores = 4;
int TurnoDe = static_cast<ColoresEquipo>(0);
int FichaSeleccionada = 0;
float test = 0.6f;

int OpcionSeleccionada = 0;
int CantOpciones = 0;
int OpcPosibles[4] = {0,0,0,0};

bool temblando = true;
int temblandoFrame = 0;
static const int temblandoAnim[10][3] = {
    {-6, -4, -1},
    {4, 0, 3},
    {-5, -2, -6},
    {3, 5, 4},
    {-1, -3, -5},
    {1, -1, -1},
    {2, 5, 3},
    {0, 2, 1},
    {-1, -1, -1},
    {0, 0, 0}
};

class Ficha { //clase ficha
	public:
	    ColoresEquipo equipo;
		bool vivo;
		bool gano;
		bool movimiento;
		int progreso;
		int casillero;
		int AnimFrame;	
		int IndiceHabitante;
		int posX;
		int posY;
		int posXanterior;
		int posYanterior;
		GLfloat color[4];
};

//Crea un array de objetos
Ficha Fichas[16];

//clase Equipo. con las propiedades generales del equipo
class Equipo {
	public:
		ColoresEquipo equipo;
		bool termino;
		int puesto;
		int llegaron;
		GLfloat color;
};
Equipo Equipos[4];

//Calcula la animacion dependiendo la curva
// Si ya tienes el enum, úsalo en la firma
int Animacion(int valor, int frame, int transicion) {
    // Normaliza frame al rango [0..100] para evitar desbordes
    if (frame < 0)   frame = 0;
    if (frame > 100) frame = 100;

    // t es 0..1
    const double t = frame / 100.0;
    double r = 0.0;

    switch (transicion) {
        case linear:
            r = valor * t;
            break;

        case easeIn:
            r = valor * t * t;
            break;

        case easeOut:
            // sin(π/2 * t)
            r = valor * std::sin(PI * 0.5 * t);
            break;

        case easeInOut:
            // sin(π * frame / 200) == sin(π * t / 2)
            r = valor * std::sin(PI * 0.5 * t);
            break;

        case RisingFalling:
            // sin(π * t)
            r = valor * std::sin(PI * t);
            break;

        default:
            // fallback razonable
            r = valor * t;
            break;
    }

    // Si prefieres truncar como antes: (int)r
    return static_cast<int>(r);
}

//Coloca la pieza viva o mierta
void SetPos( int ficha, bool sombra ){		
	//si gano
	//if (Fichas[ficha].gano){   
	//	glTranslatef(Fichas[ficha].posVictoria[0], 0, Fichas[ficha].posVictoria[1]);
	//}
	//else if (!Fichas[ficha].vivo){ //si murio  
    //	glTranslatef(Fichas[ficha].posX, 0, Fichas[ficha].posY);
	//}
	if (Fichas[ficha].movimiento){
		Fichas[ficha].AnimFrame+=2;
		if (Fichas[ficha].AnimFrame >= 100){
			Fichas[ficha].movimiento = false;
			Fichas[ficha].AnimFrame = 100;			
		}
		int AntX = Fichas[ficha].posXanterior;
		int AntY = Fichas[ficha].posYanterior;
		int PostX = Fichas[ficha].posX;
		int PostY = Fichas[ficha].posY;
		int newX = AntX+Animacion(PostX-AntX,Fichas[ficha].AnimFrame,easeInOut);
		int newY = AntY+Animacion(PostY-AntY,Fichas[ficha].AnimFrame,easeInOut);
		if (sombra){
			glTranslatef(newX+Animacion(400,Fichas[ficha].AnimFrame,RisingFalling), 0, 
					     newY-Animacion(400,Fichas[ficha].AnimFrame,RisingFalling));			
		}
		else {
			glTranslatef(newX, Animacion(600,Fichas[ficha].AnimFrame,RisingFalling), newY);
		}
	}
	else {
		glTranslatef(Fichas[ficha].posX, 0, Fichas[ficha].posY);
	}
}

//colision entre fichas
void Choque( int ficha, int casillero){
	int encontrados = 0;
	int visitantes = casilleros[Fichas[ficha].casillero].visitantes;
	int ListaVisitantes[visitantes];
	for(int i=0; i < NumJugadores*4; i++){	
		if (Fichas[i].casillero == casillero){
			ListaVisitantes[encontrados] = i;
			encontrados++;
			if (ficha == i){ //si se encontro a ella misma
				
			}
			//si es del otro equipo, la mata
			else if (casilleros[casillero].visitantes < 3 && !casilleros[Fichas[ficha].casillero].seguro && Fichas[i].equipo != Fichas[ficha].equipo){
				temblando = true;
				Fichas[i].vivo = false;
				Fichas[i].casillero = -1;
				Fichas[i].AnimFrame = 0;
				Fichas[i].movimiento = true;
				Fichas[i].posXanterior = Fichas[i].posX;
				Fichas[i].posYanterior = Fichas[i].posY;
				Fichas[i].posX = posMuertos[i][0];
				Fichas[i].posY = posMuertos[i][1];
				Tiros++; //tiene otro tiro
				casilleros[casillero].visitantes--;
			}
		}
		if (visitantes <= encontrados){
			//console->Printf(_L("\n SE ROMPE EL BUCLE \n"));
			break;		
		}
	}
	for(int i=0; i < visitantes; i++){
		Fichas[ListaVisitantes[i]].IndiceHabitante = i;
	}
}

//Pone el index del casillero. de acuerdo a su ruta
void SetCasilleroFicha( int ficha ){	
	//guarda el casillero previo para hacer la animacion
	//Fichas[ficha].posXanterior = casilleros[Fichas[ficha].casillero].x;
	//Fichas[ficha].posYanterior = casilleros[Fichas[ficha].casillero].y;
	if (Fichas[ficha].equipo == Verde){
		Fichas[ficha].casillero = RutaVerde[Fichas[ficha].progreso];			
	}
	else if (Fichas[ficha].equipo == Amarillo){
		Fichas[ficha].casillero = RutaAmarillo[Fichas[ficha].progreso];		
	}
	else if (Fichas[ficha].equipo == Azul){
		Fichas[ficha].casillero = RutaAzul[Fichas[ficha].progreso];	
	}
	else {
		Fichas[ficha].casillero = RutaRojo[Fichas[ficha].progreso];		
	}
	Fichas[ficha].posXanterior = Fichas[ficha].posX;
	Fichas[ficha].posYanterior = Fichas[ficha].posY;
	Fichas[ficha].posX = casilleros[Fichas[ficha].casillero].x;
	Fichas[ficha].posY = casilleros[Fichas[ficha].casillero].y;
	casilleros[Fichas[ficha].casillero].visitantes++;
	//revisa si hay un choque
	if (casilleros[Fichas[ficha].casillero].visitantes > 1){
		Choque(ficha, Fichas[ficha].casillero);
	}
}

void SetTurno(){
	Tiros--;
	EstadoJuego = SeleccionDado;
	if (Tiros < 1 || Equipos[TurnoDe].termino){
		Tiros = 1;
		for(int i=0; i < 4; i++){
			if (TurnoDe+1 > NumJugadores-1){
				TurnoDe = static_cast<ColoresEquipo>(0);
			}
			else{
				TurnoDe = static_cast<ColoresEquipo>(TurnoDe+1);
			}
			//si el equipo aun no gano. queda seleccionado
			if (!Equipos[TurnoDe].termino){
				break;
			}
		}	
	};
}

//mover al siguiente casillero
void NextPos( int ficha, int movimiento ){
	if (Fichas[ficha].gano) return; //si gano no hace nada
	//Si se mueve
	Fichas[ficha].posXanterior = Fichas[ficha].posX;
	Fichas[ficha].posYanterior = Fichas[ficha].posY;
	Fichas[ficha].AnimFrame = 0;
	Fichas[ficha].movimiento = true;
	//se paso
	if (!Fichas[ficha].vivo && movimiento == 6){
		Fichas[ficha].vivo = true;	
		Fichas[ficha].progreso = 0;
		SetCasilleroFicha(ficha);
	}
	else if (Fichas[ficha].progreso+movimiento > 56){
		return;
	}
	else if (Fichas[ficha].progreso+movimiento == 56){
		Fichas[ficha].gano = true;
		Equipos[Fichas[ficha].equipo].llegaron++;	
		if (Equipos[Fichas[ficha].equipo].llegaron >= 4){
			Equipos[Fichas[ficha].equipo].termino = true;			
		}
		Fichas[ficha].posX = posVictoria[ficha][0];
		Fichas[ficha].posY = posVictoria[ficha][1];
		casilleros[Fichas[ficha].casillero].visitantes--;	
		Tiros++;
		Fichas[ficha].progreso = 56;	
	}
	else {
		casilleros[Fichas[ficha].casillero].visitantes--;	
		Fichas[ficha].progreso+=movimiento;
		SetCasilleroFicha(ficha);
	}
	SetTurno();
}

void Sumar(){
	test += 0.1f;
}

void Restar(){
	test -= 0.1f;
}

void Confirmar (){
	switch(EstadoJuego){ 	
	    case CantidadJugadores:
	    	//confirma la cantidad de jugadores
	    	EstadoJuego = ModoDado;
		break;	
	    case ModoDado:
	    	//confirma si el dado es Manual o al azar
	    	EstadoJuego = SeleccionDado;
		break;		
	    case SeleccionDado:
	    	//Lanza el Dado
			if (!DadoManual) {
				#ifdef __SYMBIAN32__ 
					TTime now;
					now.HomeTime();
					Int64 randomSeed = now.Int64();
					Dado = int(Math::FRand(randomSeed)*6)+1;
				#else
					// RNG estándar C++: 1..6
					static std::mt19937 gen(
						(unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count()
					);
					std::uniform_int_distribution<int> dist(1, 6);
					Dado = dist(gen);
				#endif
			}
			animacionPosFrame = 0;
			EstadoJuego = DadoLanzado;
		break;
	    break;
	    case DadoLanzado:
	    	animacionPosFrame = 97;
		break;
	    case SeleccionFicha:
	    	if (Fichas[FichaSeleccionada].gano){
	    		break;
	    	}
	    	if (!Fichas[FichaSeleccionada].vivo && Dado == 6){
	    		Fichas[FichaSeleccionada].vivo = true;	
	    		Fichas[FichaSeleccionada].progreso = 0;
				Fichas[FichaSeleccionada].AnimFrame = 0;
				Fichas[FichaSeleccionada].movimiento = true;
	    		SetCasilleroFicha(FichaSeleccionada);
	    		SetTurno();
	    	}
	    	else if (Fichas[FichaSeleccionada].vivo && !Fichas[FichaSeleccionada].gano){
	    		NextPos(FichaSeleccionada, Dado);	
	    	}
	    break;
		case AnimacionFicha:
			// nada por ahora
			break;
	}	
}

void ClickDerecha(){
	if (temblando) return; //si hay una animacion. el juego no te deja jugar
	switch(EstadoJuego){
		//cuantos van a jugar		
	    case CantidadJugadores:
	    	NumJugadores++;
	    	if (NumJugadores > 4){
	    		NumJugadores = 1; //tiene que ser 2 minimo
	    	}
	    break;	
	    case ModoDado:
	    	if (Dado == 6){
	    		DadoManual = false;
	    		Dado = 1;
	    	}
	    	else {
	    		DadoManual = true;
	    		Dado = 6;	    		
	    	}
	    break;	    
	    case SeleccionDado:
	    	//cambia el dado
	    	if (DadoManual){
		    	Dado++;
		    	if (Dado > 6){Dado = 1;}
	    	}
	    break;
	    case SeleccionFicha:
	    	//cambia la ficha
	    	OpcionSeleccionada++;
	    	if (OpcionSeleccionada > CantOpciones-1){
	    		OpcionSeleccionada = 0;	    		
	    	}
		    FichaSeleccionada = OpcPosibles[OpcionSeleccionada];
		    /*
		    FichaSeleccionada++;
	    	if (TurnoDe == Verde && FichaSeleccionada > 3){
	    		FichaSeleccionada = 0;
	    	}
	    	else if (TurnoDe == Amarillo && FichaSeleccionada > 7){
	    		FichaSeleccionada = 4;	    		
	    	}
	    	else if (TurnoDe == Azul && FichaSeleccionada > 11){
	    		FichaSeleccionada = 8;	    		
	    	}
	    	else if (TurnoDe == Rojo && FichaSeleccionada > 15){
	    		FichaSeleccionada = 12;	    		
	    	}*/
	    break;
		case DadoLanzado: 
			// nada
			break;
		case AnimacionFicha:
			// nada por ahora
			break;
	}	
}

void ClickIzquierda(){
	if (temblando) return; //si hay una animacion. el juego no te deja jugar
	switch(EstadoJuego){
		//cuantos van a jugar		
	    case CantidadJugadores:
	    	NumJugadores--;
	    	if (NumJugadores < 0){
	    		NumJugadores = 4;
	    	}
	    break;	
	    case ModoDado:
	    	if (Dado == 6){
	    		DadoManual = false;
	    		Dado = 1;
	    	}
	    	else {
	    		DadoManual = true;
	    		Dado = 6;	    		
	    	}
	    break;	    
	    case SeleccionDado:
	    	//cambia el dado
	    	if (DadoManual){
		    	Dado--;
		    	if (Dado < 1){Dado = 6;}
	    	}
	    break;
	    case SeleccionFicha:
	    	//cambia la ficha
	    	OpcionSeleccionada--;
	    	if (OpcionSeleccionada < 0){
	    		OpcionSeleccionada = CantOpciones-1;	    		
	    	}
		    FichaSeleccionada = OpcPosibles[OpcionSeleccionada];
	    break;
		case DadoLanzado: 
			// nada
			break;
		case AnimacionFicha:
			// nada por ahora
			break;
	}	
}

void TEST( int test ){	
	//Revisa si al ganar, se marque como que gano
	if (test == 1){
		Equipos[Verde].llegaron = 3;	
		for(int i=0; i < 3; i++){	
			Fichas[i].vivo = true;	
			Fichas[i].gano = true;	
			Fichas[i].progreso = 56;		
			Fichas[i].casillero = -1;
			Fichas[i].posXanterior = Fichas[i].posX;
			Fichas[i].posYanterior = Fichas[i].posY;
			Fichas[i].posX = posVictoria[i][0];
			Fichas[i].posY = posVictoria[i][1];
		}	
		Fichas[3].vivo = true;	
		Fichas[3].progreso = 54;	
		SetCasilleroFicha(3);
	}
	//Equipo gana y es salteado
	else if (test == 2){
		Equipos[Verde].termino = true;	
		for(int i=0; i < 4; i++){	
			Fichas[i].vivo = true;	
			Fichas[i].gano = true;	
			Fichas[i].progreso = 56;		
			Fichas[i].casillero = -1;
			Fichas[i].posXanterior = Fichas[i].posX;
			Fichas[i].posYanterior = Fichas[i].posY;
			Fichas[i].posX = posVictoria[i][0];
			Fichas[i].posY = posVictoria[i][1];
		}		
	}
	//9 fichas en un solo casillero
	else if (test == 3){
		casilleros[2].visitantes = 9;	
		for(int i=0; i < 9; i++){	
			Fichas[i].vivo = true;	
			Fichas[i].casillero = 2;
			Fichas[i].IndiceHabitante = i;		
		}		
	}
	//16 fichas en un solo casillero
	else if (test == 4){
		casilleros[2].visitantes = 16;	
		for(int i=0; i < NumJugadores*4; i++){	
			Fichas[i].vivo = true;	
			Fichas[i].casillero = 2;
			Fichas[i].IndiceHabitante = i;		
		}		
	}
}

void SetDado(){
    switch(Dado){
        case 1:
            glRotatef(270, 0, 0, 1);
            break;
        case 2:
            glRotatef(180, 0, 1, 0);
            break;
        case 3:
            glRotatef(270, 0, 1, 0);
            break;
        case 4:
            glRotatef(90, 0, 1, 0);
            break;
        case 6:
            glRotatef(90, 0, 0, 1);
            break;
        default:
            // opcional: sin rotación o algún valor por defecto
            break;
    }
}

void CalcOpciones(){
	CantOpciones = 0;
	OpcionSeleccionada = 0;
	switch (TurnoDe) {
		case Verde:     FichaSeleccionada = 0;  break;
		case Amarillo:  FichaSeleccionada = 4;  break;
		case Azul:      FichaSeleccionada = 8;  break;
		case Rojo:      FichaSeleccionada = 12; break;
	}
	//revisa si alguna ficha del equipo tiene opciones
	for(int i=FichaSeleccionada; i<FichaSeleccionada+4; i++){
		//si la ficha ya gano o el dado se pasa de la victoria. 
		//la ficha no se puede mover
		if (!Fichas[i].gano && Fichas[i].progreso+Dado < 57){
			//si saca 6 o la ficha esta viva. puede moverse
			if (Dado == 6 || Fichas[i].vivo){
				OpcPosibles[CantOpciones] = i;
				CantOpciones++;			
			}			
		}		
	}	
	
	//si no hay jugadas posibles
	if (CantOpciones <= 0){
		SetTurno();
	}
	else if (CantOpciones == 1){
    	if (Dado == 6){Tiros++;}
		NextPos(OpcPosibles[0],Dado);
	}
	else {
    	//si saco 6. le suma 1 turno extra
    	if (Dado == 6){Tiros++;}
		FichaSeleccionada = OpcPosibles[0];
		EstadoJuego = SeleccionFicha;
	}
}

// Función para convertir y normalizar
void ConvertirTexData(const GLbyte* src, GLfloat* dst, int count) {
    const float minVal = -124.0f;   // mínimo de tus datos
    const float maxVal = 124.0f;    // máximo de tus datos
    const float range = maxVal - minVal; // 248.0f

    for (int i = 0; i < count; ++i) {
        dst[i] = (src[i] - minVal) / range; // normaliza a [0,1]
    }
}