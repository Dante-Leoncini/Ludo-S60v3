/*
 * ==============================================================================
 *  Name        : Ludo.h
 *  Part of     : OpenGLEx / Ludo
 *
 *  Copyright (c) 2004-2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

#ifndef LUDO_H
#define LUDO_H

// INCLUDES
#include <e32base.h> // for CBase definition
#include <GLES/gl.h> // OpenGL ES header file
#include "Utils3d.h" // Utilities (texmanager, textures etc.)
#include "Glutils.h" // Misc GLU and GLUT functions

// MACROS
#define TEX_WIDTH     256 // Texture size must be power of two and max size
#define TEX_HEIGHT    256 // for textures is 256 x 256

#define FRUSTUM_LEFT   -1.f     //left vertical clipping plane
#define FRUSTUM_RIGHT   1.f     //right vertical clipping plane
#define FRUSTUM_BOTTOM -1.f     //bottom horizontal clipping plane
#define FRUSTUM_TOP     1.f     //top horizontal clipping plane
#define FRUSTUM_NEAR    3.f     //near depth clipping plane
#define FRUSTUM_FAR  1000.f     //far depth clipping plane

// CLASS DECLARATION

/**
 * Class that does the actual OpenGL ES rendering.
 */
class CLudo : public CFiniteStateMachine, public MTextureLoadingListener
    {
    public:  // Constructors and destructor

        /**
         * Factory method for creating a new CSimpleCube object.
         */
        static CLudo* NewL( TUint aWidth, TUint aHeight);

        /**
         * Destructor. Does nothing.
         */
        virtual ~CLudo();

    public:  // New functions

        /**
         * Initializes OpenGL ES, sets the vertex and color
         * arrays and pointers. Also selects the shading mode.
         */
        void AppInit( void );

        /**
         * Called upon application exit. Does nothing.
         */
        void AppExit( void );

        /**
         * Renders one frame.
         * @param aFrame Number of the frame to be rendered.
         */
        void AppCycle( TInt aFrame );

    	/**
    	 * Called when the finite state machine enters a new state.
    	 * Does nothing in this implementation.
    	 * @param aState State that is about to be entered.
    	 */
    	void OnEnterStateL( TInt aState );
        
        /**
		 * Called when texture manager starts loading the textures.
		 * Sets the current state to "loading textures".
		 */
		void OnStartLoadingTexturesL();

		/**
		 * Called when texture manager has completed texture loading.
		 * Changes the current state to "running".
		 */
		void OnEndLoadingTexturesL();
        
        //mover al siguiente casillero
        void NextPos( int ficha, int movimiento );
        
        //posicion de inicio y fin
        void SetPos( int ficha, bool sombra );
        
        //Solo para testear cosas
        void TEST( int test );
        
        //progreso        
        int Animacion(int valor, int frame, int transicion);
        
        //gira el dado en la posicion correcta        
        void SetDado( void );
        
        //revisa si hay opciones posibles. sino pasa el turno
        void CalcOpciones( void );  

        //pasa al siguiente jugador
        void SetTurno( void );
        
        //cuando se apreta OK
        void Confirmar( void );
        
        void ClickDerecha( void );
        void ClickIzquierda( void );
        
        //Pone el index del casillero. de acuerdo a su ruta
        void SetCasilleroFicha( int ficha );
        
        //cuando se chocan
        void Choque(int ficha, int casillero );

        /**
         * Notifies that the screen size has dynamically changed during execution of
         * this program. Resets the viewport to this new size.
         * @param aWidth New width of the screen.
         * @param aHeight New height of the screen.
         */
        void SetScreenSize( TUint aWidth, TUint aHeight );

    protected: // New functions

        /**
         * Standard constructor that must never Leave.
         * Stores the given screen width and height.
         * @param aWidth Width of the screen.
         * @param aHeight Height of the screen.
         */
        CLudo( TUint aWidth, TUint aHeight );

        /**
         * Second phase contructor. Does nothing.
         */
        void ConstructL( void );

        /**
         * Helper function that is used to make the duck 'quak'.
         * Calculates the sine for the given angle. Returns 0 if any
         * errors occur while calling the Math::Sin() method.
         * @param aRad Radian angle whose sine is to be calculated.
         * @return The sine of the given angle or 0 if error occured while calculating the sine.
         */
        GLfloat sin( GLfloat aRad );

    public:  // Data

		/**
		 * Application states:
		 * ELoadingTextures - indicates that the app. is loading textures.
		 * ERunning - indicates that the app. is running.
		 */
		enum {
			ELoadingTextures,
			ERunning
		};

        /** Whether or not the lighting is enabled. Used when building the menu for the application. */
        TBool iLightingEnabled;

        /** Whether or not the lamp is enabled. Used when building the menu for the application. */
        TBool iLampEnabled;

        /** Whether or not the spotlight is enabled. Used when building the menu for the application. */
        TBool iSpotEnabled;

    private:  // Data

        	/** Texture manager that is used to load the used textures. */
        	CTextureManager * iTextureManager;
            /** Width of the screen */
            TUint iScreenWidth;
            /** Height of the screen */
            TUint iScreenHeight;
        	/** Textura del Tablero. */
        	TTexture iBaseColor;
        	/** Textura del Dado. */
        	TTexture iDadoTextura;  
        	TTexture iSombraTextura;
        	TTexture iSeleccionTextura;
    };

#endif // LUDO_H
