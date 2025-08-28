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
#define LIGHT_MAX    1

//para saber el tama�o de un array
# define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))

// CONSTANTS
/* Materials for the Models object. */
static const GLfloat objDiffuseHead[4]  = { MATERIALCOLOR(0.8, 0.8, 0.8, 1.0) };

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

    // Do not use perspective correction
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );

    // Initialize menu state variables, Symbian menu stuff.
    iWidescreenEnabled = ETrue;          // Lighting is enabled
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

// -----------------------------------------------------------------------------
// CLudo::SetScreenSize
// Reacts to the dynamic screen size change during execution of this program.
// -----------------------------------------------------------------------------
//
void CLudo::SetScreenSize( TUint aWidth, TUint aHeight, TBool widescreen = false ){
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
    if (widescreen && iScreenWidth > iScreenHeight){
        aspectRatio = (GLfloat)(16) / (GLfloat)(9);    	
    };
    glFrustumf( FRUSTUM_LEFT * aspectRatio, FRUSTUM_RIGHT * aspectRatio,
                FRUSTUM_BOTTOM, FRUSTUM_TOP,
                FRUSTUM_NEAR, FRUSTUM_FAR );
    glMatrixMode( GL_MODELVIEW );
}

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