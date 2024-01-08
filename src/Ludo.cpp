/*
 * ==============================================================================
 *  Name        : Ludo.cpp
 *  Part of     : OpenGLEx / Ludo
 *
 *  Copyright (c) 2004-2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

// INCLUDES
#include <e32std.h>
#include <e32math.h>

//debug
//#include <e32cons.h>
//LOCAL_D CConsoleBase* console;

#include "Ludo.h"

#include "tablero.h"        // Geometry, normals, and indices for the head model
#include "ficha.h"        // Geometry, normals, and indices for the head model
#include "dado.h"        // Geometry, normals, and indices for the head model
#include "sombra.h"        // Geometry, normals, and indices for the head model
#include "seleccion.h"        // Geometry, normals, and indices for the head model
#include "recorridos.h"        // datos del tablero

// MACROS
#define MATERIAL_MAX 1
#define LIGHT_MAX    1

#define cameraDistance 270

//para saber el tama�o de un array
# define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))


#define MATERIALCOLOR(r, g, b, a)     \
       (GLfloat)(r * MATERIAL_MAX),   \
       (GLfloat)(g * MATERIAL_MAX),   \
       (GLfloat)(b * MATERIAL_MAX),   \
       (GLfloat)(a * MATERIAL_MAX)

#define LIGHTCOLOR(r, g, b, a)        \
       (GLfloat)(r * LIGHT_MAX),      \
       (GLfloat)(g * LIGHT_MAX),      \
       (GLfloat)(b * LIGHT_MAX),      \
       (GLfloat)(a * LIGHT_MAX)

// CONSTANTS
/* Materials for the Models object. */
static const GLfloat objDiffuseHead[4]  = { MATERIALCOLOR(0.8, 0.8, 0.8, 1.0) };
static const GLfloat objAmbient[4]  = { MATERIALCOLOR(0.4, 0.4, 0.4, 1.0) };

//Specular Basico
static const GLfloat objSpecular[4] = { MATERIALCOLOR(1.0, 1.0, 1.0, 1.0) };
//Colores de Fichas
static const GLfloat objDiffuseRed[4]  = { MATERIALCOLOR(0.92, 0.12, 0.15, 1.0) };
static const GLfloat objDiffuseGreen[4]  = { MATERIALCOLOR(0.01, 0.63, 0.29, 1.0) };
static const GLfloat objDiffuseBlue[4]  = { MATERIALCOLOR(0.20, 0.36, 0.83, 1.0) };
static const GLfloat objDiffuseYellow[4]  = { MATERIALCOLOR(1.0, 0.87, 0.02, 1.0) };


/* Global ambient light. */
static const GLfloat globalAmbient[4]   = { LIGHTCOLOR(0.0, 0.0, 0.0, 1.0) };

/* Lamp parameters. */
static const GLfloat lightDiffuseLamp[4]   = { LIGHTCOLOR(0.8, 0.8, 0.8, 1.0) };
static const GLfloat lightAmbientLamp[4]   = { LIGHTCOLOR(0.4, 0.4, 0.4, 1.0) };
static const GLfloat lightPositionLamp[4]  = { -10, -5, 50, 0 }; // x, y, z

/* Spotlight parameters. */
static const GLfloat lightDiffuseSpot[4]   = { LIGHTCOLOR(0.0, 0.0, 0.0, 1.0) };
static const GLfloat lightAmbientSpot[4]   = { LIGHTCOLOR(0.0, 0.0, 0.0, 1.0) };
static const GLfloat lightSpecularSpot[4]  = { LIGHTCOLOR(0.0, 0.0, 3.0, 1.0) };
static const GLfloat lightPositionSpot[4]  = {  0, -10, -1, 0 };
static const GLfloat lightDirectionSpot[4] = {  0,  10,  1, 1 };

/** Enumerated value that is used to switch between duck and head models. */
typedef enum { Verde, Amarillo, Azul, Rojo } ColoresEquipo;
typedef enum { linear, easeIn, easeOut, easeInOut, RisingFalling } Transition;

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

/** Enumerated value that is used to switch between duck and head models. */
typedef enum { CantidadJugadores, ModoDado, SeleccionDado, DadoLanzado, SeleccionFicha, AnimacionFicha } EstadoLudo;
EstadoLudo EstadoJuego = CantidadJugadores;

//parametros del juego
bool DadoManual = true;
int Dado = 6;
int Tiros = 1;
int NumJugadores = 4;
int TurnoDe = static_cast<ColoresEquipo>(0);
int FichaSeleccionada = 0;

//Crea un array de objetos
Ficha Fichas[16];
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

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// sin
// Help function to make the duck 'quak'.
// -----------------------------------------------------------------------------
//
GLfloat CLudo::sin(GLfloat aRad){
    TReal trg, src = (TReal)aRad;
    if ( Math::Sin(trg, src) == KErrNone )
        {
        return (GLfloat)trg;
        }
    return 0;
}


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLudo::CLudo
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CLudo::CLudo( TUint aWidth, TUint aHeight )
:iScreenWidth(aWidth), iScreenHeight(aHeight){
}

// -----------------------------------------------------------------------------
// CLudo::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLudo::ConstructL( void ){
	//debuger
	//console = Console::NewL(_L("Consola"),TSize(KConsFullScreen, KConsFullScreen));
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


// -----------------------------------------------------------------------------
// CLudo::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLudo* CLudo::NewL( TUint aWidth, TUint aHeight ){
    /* Symbian 2-phase constructor. Calls both the default
       C++ constructor and Symbian ConstructL methods */
    CLudo* self = new (ELeave) CLudo( aWidth, aHeight );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
}


// Destructor.
CLudo::~CLudo(){
}



// -----------------------------------------------------------------------------
// CLudo::AppInit
// Initialize OpenGL ES, set the vertex and color arrays and pointers,
// and select the shading mode.
// -----------------------------------------------------------------------------
//
void CLudo::AppInit( void ){
    // Construct a texture manager that uses the application's private
    // directory as the location for all textures.
	iTextureManager = CTextureManager::NewL ( iScreenWidth, iScreenHeight,
											  FRUSTUM_TOP, FRUSTUM_BOTTOM, FRUSTUM_RIGHT, FRUSTUM_LEFT, FRUSTUM_NEAR,
											  this );
  
    // Initialize viewport and projection.
		SetScreenSize( iScreenWidth, iScreenHeight );

    // Set the screen background color.
	glClearColor( 0.23f, 0.23f, 0.23f, 1.f );

    // Enable depth testing, texturing, back face culling, and lighting.
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE  );
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_LIGHTING   );
    /* Make OpenGL ES automatically normalize all normals after tranformations.
       This is important when making irregular xforms like scaling, or if we
       have specified nonunit-length normals. */
    glEnable( GL_NORMALIZE  );
    
    /* Initialize appropriate texture matrix. First we have to translate the
          input texture coordinate values to be within a range of [0,255]. Hence
          we translate the x- and y-coordinate values by 128. Recall that the
          values in nokTexCoords are between [-128,127], now they are in a range
          of [0,255]. After that we scale the values by 1/255 to make the values
          to be in range [0,1]. */
    glMatrixMode( GL_TEXTURE );
    glLoadIdentity();
    glScalef(     1.0f/255.0f, 1.0f/255.0f, 1.0f );
    glTranslatef( 128.0f,      128.0f,      0.0f );

    /* Remember to change the matrix mode to modelview. */
    glMatrixMode( GL_MODELVIEW );

    // Enable vertex and normal arrays.
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );

    // Set up global ambient light.
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, globalAmbient );

    // Set up lamp.
    glEnable( GL_LIGHT0 );
    glLightfv(  GL_LIGHT0, GL_DIFFUSE,  lightDiffuseLamp  );
    glLightfv(  GL_LIGHT0, GL_AMBIENT,  lightAmbientLamp  );
    glLightfv(  GL_LIGHT0, GL_SPECULAR, lightDiffuseLamp  );
    glLightfv(  GL_LIGHT0, GL_POSITION, lightPositionLamp );

    // Set up spot.  Initially spot is disabled.
    glLightfv(  GL_LIGHT1, GL_DIFFUSE,  lightDiffuseSpot  );
    glLightfv(  GL_LIGHT1, GL_AMBIENT,  lightAmbientSpot  );
    glLightfv(  GL_LIGHT1, GL_SPECULAR, lightSpecularSpot );
    glLightfv(  GL_LIGHT1, GL_POSITION, lightPositionSpot );

    glLightf(   GL_LIGHT1, GL_CONSTANT_ATTENUATION,  1.5  );
    glLightf(   GL_LIGHT1, GL_LINEAR_ATTENUATION,    0.5  );
    glLightf(   GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.5  );

    glLightf(   GL_LIGHT1, GL_SPOT_CUTOFF,   17.0                );
    glLightf(   GL_LIGHT1, GL_SPOT_EXPONENT,  2.0                );
    glLightfv(  GL_LIGHT1, GL_SPOT_DIRECTION, lightDirectionSpot );

    // Set shading mode
    glShadeModel( GL_SMOOTH );
    //glShadeModel( GL_FLAT );

    // Do not use perspective correction
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );

    // Initialize menu state variables, Symbian menu stuff.
    iLightingEnabled = ETrue;          // Lighting is enabled
    iLampEnabled     = ETrue;          // Lamp is enabled
    iSpotEnabled     = EFalse;         // Spot is disabled

	// Push the textures into the loading queue.
	_LIT( KGrassTexture, "tablero.jpg" );
	_LIT( KCloudTexture, "dice-texture.jpg" );
	_LIT( KSombraTexture, "sombra.png" );
	_LIT( KSeleccionTexture, "seleccion.png" );
	iTextureManager->RequestToLoad( KGrassTexture, &iBaseColor, false );
	iTextureManager->RequestToLoad( KCloudTexture, &iDadoTextura, false );
	iTextureManager->RequestToLoad( KSombraTexture, &iSombraTextura, false );
	iTextureManager->RequestToLoad( KSeleccionTexture, &iSeleccionTextura, false );
	
	//Start to load the textures.
	iTextureManager->DoLoadL();
}


// -----------------------------------------------------------------------------
// CLudo::AppExit
// Release any allocations made in AppInit.
// -----------------------------------------------------------------------------
//
void CLudo::AppExit( void ){
	delete iTextureManager;
}


// -----------------------------------------------------------------------------
// CLudo::AppCycle
// Draws and animates the objects
// -----------------------------------------------------------------------------
//
void CLudo::AppCycle( TInt iFrame ){
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
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // If texture loading is still going on, return from this method without doing anything.
	if ( GetState() == ELoadingTextures ){
        return;
    }

    glLoadIdentity();
    glEnable( GL_DEPTH_TEST );

	glEnable( GL_TEXTURE_2D );
	// Set array pointers for head model.
	glVertexPointer( 3, GL_SHORT, 0, objVertexdataModel );
	glTexCoordPointer( 2, GL_BYTE, 0, objTexdataModel );
	glNormalPointer( GL_BYTE, 0, objNormaldataModel );

	// Set head front material
	glMaterialfv(   GL_FRONT_AND_BACK, GL_AMBIENT,  objAmbient  );
	glMaterialfv(   GL_FRONT_AND_BACK, GL_DIFFUSE,  objDiffuseHead  );
	glMaterialfv(   GL_FRONT_AND_BACK, GL_SPECULAR, objSpecular );
	glMaterialx( GL_FRONT_AND_BACK, GL_SHININESS,   12 << 16     );
	

	//glRotatex(-90 << 16, 1 << 16, 0, 0);
	//glRotatex( iFrame << 16, 5 << 16, 1 << 12, 0);
	//glRotatex( iFrame << 16, 0, 0, 1 << 16);
	
	//glRotatex( iFrame << 16, 1 << 16, 0      , 0       );
	//glRotatex( iFrame << 15, 0      , 1 << 16, 0       );
	//glRotatex(-45 << 1, 1 << 16, 90 << 16, 0);
	glTranslatef( 0, 55, -cameraDistance+170);
	if (temblando){
		glTranslatef(temblandoAnim[temblandoFrame][0], temblandoAnim[temblandoFrame][2], temblandoAnim[temblandoFrame][1]);		
		temblandoFrame++;
		if (temblandoFrame > 9){
			temblando = false;
			temblandoFrame = 0;			
		}
	}
	glRotatef(55, 1, 0, 0); //angulo, X Y Z
	//glRotatex( iFrame << 14, 0      , 0      , 1 << 16 );

	// Use some magic numbers to scale the head model to fit the screen.
	glScalex( 1 << 10, 1 << 10, 1 << 10 );
	glBindTexture(  GL_TEXTURE_2D, iBaseColor.iID ); //selecciona la textura	
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glDrawElements( GL_TRIANGLES, objFacesModel * 3, GL_UNSIGNED_SHORT, objFacedataModel );
	
	//Sombras
	glDisable( GL_DEPTH_TEST ); //se quita el zbuffer
	// Enable blending for transparency.
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glVertexPointer( 3, GL_SHORT, 0, objVertexdataSombra ); //selecciona los vertices
	glBindTexture(  GL_TEXTURE_2D, iSombraTextura.iID ); //selecciona la textura
	glNormalPointer( GL_BYTE, 0, objNormaldataSombra ); //selecciona las normales
	glMaterialfv(   GL_FRONT_AND_BACK, GL_AMBIENT,  objAmbient  );
	glMaterialfv(   GL_FRONT_AND_BACK, GL_SPECULAR, objSpecular );
	glMaterialx( GL_FRONT_AND_BACK, GL_SHININESS,   12 << 16     );
	
	for(int i=0; i < NumJugadores*4; i++){
		glPushMatrix(); //guarda la matrix
		SetPos(i, true);
		if (Fichas[i].vivo && !Fichas[i].gano){
			if (casilleros[Fichas[i].casillero].visitantes > 9){
			    glScalef(0.5f,0.5f,0.5f);	
				glTranslatef( 0+PosHabitantesDieciseis[Fichas[i].IndiceHabitante][0],
						      -5000, 
						      0+PosHabitantesDieciseis[Fichas[i].IndiceHabitante][1]);	
				
			}
			else if (casilleros[Fichas[i].casillero].visitantes > 4){
			    glScalef(0.5f,0.5f,0.5f);	
				glTranslatef( 0+PosHabitantesNueve[Fichas[i].IndiceHabitante][0],
						      -5000, 
						      0+PosHabitantesNueve[Fichas[i].IndiceHabitante][1]);	
				
			}
			else if (casilleros[Fichas[i].casillero].visitantes > 1){
			    glScalef(0.6f,0.6f,0.6f);	
				glTranslatef( 0+PosHabitantesCuatro[Fichas[i].IndiceHabitante][0],
						      -3200, 
						      0+PosHabitantesCuatro[Fichas[i].IndiceHabitante][1]);					
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
		glBindTexture(  GL_TEXTURE_2D, iSeleccionTextura.iID ); //selecciona la textura	
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
	
	//Fichas
	glEnable( GL_DEPTH_TEST ); //se recupera el zbuffer
	glDisable( GL_TEXTURE_2D ); //desactiva las texturas
	glVertexPointer( 3, GL_SHORT, 0, objVertexdataFicha ); //selecciona los vertices
	glNormalPointer( GL_BYTE, 0, objNormaldataFicha ); //selecciona las normales
	glMaterialfv(   GL_FRONT_AND_BACK, GL_AMBIENT,  objAmbient  );
	glMaterialfv(   GL_FRONT_AND_BACK, GL_SPECULAR, objSpecular );
	glMaterialx( GL_FRONT_AND_BACK, GL_SHININESS,   12 << 16     );
	
	//primero setea el color por equipo
	for(int e=0; e < NumJugadores; e++){
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
			glDrawElements( GL_TRIANGLES, objFacesFicha * 3, GL_UNSIGNED_SHORT, objFacedataFicha );
			glPopMatrix(); //reinicia la matrix a donde se guardo
		}
	}
	
	//dado
	glEnable( GL_TEXTURE_2D ); //activa la textura
	glBindTexture(  GL_TEXTURE_2D, iDadoTextura.iID ); //selecciona la textura	
	glVertexPointer( 3, GL_SHORT, 0, objVertexdataDado ); //selecciona los vertices
	glNormalPointer( GL_BYTE, 0, objNormaldataDado ); //selecciona las normales
    glTexCoordPointer( 2, GL_BYTE, 0, objTexdataDado );
	//if (EstadoJuego == SeleccionFicha || EstadoJuego == DadoLanzado){
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
	//}
	//else {
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseHead); //color blanco
	//}

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
	
	//_LIT(Estado, "Estado: %d \n");
	//console->Printf(Estado,GetState());
	
	//interface
	glVertexPointer( 3, GL_SHORT, 0, planeVertices ); //selecciona los vertices
	glNormalPointer( GL_BYTE, 0, objNormaldataModel ); //selecciona las normales
    glTexCoordPointer( 2, GL_BYTE, 0, objTexdataDado );
}

//Coloca la pieza viva o mierta
void CLudo::SetPos( int ficha, bool sombra ){		
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

//Calcula la animacion dependiendo la curva
int CLudo::Animacion(int valor, int frame, int transicion){
	if (transicion == linear){
		return valor*frame/100;
	}
	else if (transicion == easeIn){
		return valor*frame*frame/10000;
	}
	else if (transicion == easeOut){
		return int(sin(PI/2*frame/100.f)*valor);
	}
	else if (transicion == easeInOut){	
		return int(sin(PI*frame/200.f)*valor);
	}
	else if (transicion == RisingFalling){	
		return int(sin(PI*frame/100.f)*valor);
	}	
}

int OpcionSeleccionada = 0;
int CantOpciones = 0;
int OpcPosibles[4] = {0,0,0,0};
void CLudo::CalcOpciones(){
	CantOpciones = 0;
	OpcionSeleccionada = 0;
	if (TurnoDe == Verde){
		FichaSeleccionada = 0;		
	}
	else if (TurnoDe == Amarillo){
		FichaSeleccionada = 4;		
	}	
	else if (TurnoDe == Azul){
		FichaSeleccionada = 8;			
	}	
	else if (TurnoDe == Rojo){
		FichaSeleccionada = 12;			
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

void CLudo::SetTurno(){
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

// -------------------------------------------------------------------------------------------------------
// CBillboard::OnStartLoadingTextures()
// Called for a MTextureLoadingListener by the texture manager when texture loading operation starts
// -------------------------------------------------------------------------------------------------------

void CLudo::OnStartLoadingTexturesL(){
    SetStateL( ELoadingTextures );
}

// ------------------------------------------------------------------------------------------------------------
// CBillboard::OnEndLoadingTextures()
// Called for a MTextureLoadingListener by the texture manager when texture loading operation is completed
// ------------------------------------------------------------------------------------------------------------
void CLudo::OnEndLoadingTexturesL(){
	if ( GetState() == ELoadingTextures ){
		SetStateL( ERunning );
	}
}

// ---------------------------------------------------------
// CBillboard::OnEnterState( TInt aState )
// Called by TFiniteStateMachine when the f.s.m enters a new state
// ---------------------------------------------------------

void CLudo::OnEnterStateL( TInt /*aState*/ ){
	// Nothing to do here...
}

void CLudo::SetDado(){
	if (Dado == 1){
		glRotatef(270, 0, 0, 1);		
	}
	else if (Dado == 2){
		glRotatef(180, 0, 1, 0);		
	}
	else if (Dado == 3){
		glRotatef(270, 0, 1, 0);		
	}
	else if (Dado == 4){
		glRotatef(90, 0, 1, 0);	
	}
	else if (Dado == 6){
		glRotatef(90, 0, 0, 1);
	}
}

void CLudo::Confirmar (){
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
	    	if (!DadoManual){
	    		TTime now;
	    		now.HomeTime();
	    		Int64 randomSeed = now.Int64();
	    		Dado = TInt(Math::FRand(randomSeed)*6)+1;
	    		//_LIT(Estado, "Estado: %d \n");
	    		//console->Printf(Estado,Dado);
	    	}
	    	animacionPosFrame = 0;
	    	EstadoJuego = DadoLanzado;
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
	}	
}

void CLudo::ClickDerecha(){
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
	}	
}

void CLudo::ClickIzquierda(){
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
	}	
}

//mover al siguiente casillero
void CLudo::NextPos( int ficha, int movimiento ){
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
		//console->ClearScreen();
		/*_LIT(KTextFailed, "Casillero: %d \n Visitantes: %d \n");
		console->Printf(KTextFailed,
				        Fichas[ficha].casillero,
				        casilleros[Fichas[ficha].casillero].visitantes);*/
	}
	SetTurno();
}

//Pone el index del casillero. de acuerdo a su ruta
void CLudo::SetCasilleroFicha( int ficha ){	
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

void CLudo::TEST( int test ){	
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

//colision entre fichas
void CLudo::Choque( int ficha, int casillero){
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

// -----------------------------------------------------------------------------
// CLudo::SetScreenSize
// Reacts to the dynamic screen size change during execution of this program.
// -----------------------------------------------------------------------------
//
void CLudo::SetScreenSize( TUint aWidth, TUint aHeight ){
    iScreenWidth  = aWidth;
    iScreenHeight = aHeight;
    
    // Notify the texture manager of screen size change
    iTextureManager->SetScreenSize( aWidth, aHeight );

    // Reinitialize viewport and projection.
    glViewport( 0, 0, iScreenWidth, iScreenHeight );

    // Recalculate the view frustrum
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    GLfloat aspectRatio = (GLfloat)(iScreenWidth) / (GLfloat)(iScreenHeight);
    glFrustumf( FRUSTUM_LEFT * aspectRatio, FRUSTUM_RIGHT * aspectRatio,
                FRUSTUM_BOTTOM, FRUSTUM_TOP,
                FRUSTUM_NEAR, FRUSTUM_FAR );
    glMatrixMode( GL_MODELVIEW );
}

//  End of File
