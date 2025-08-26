/*
 * ==============================================================================
 *  Name        : LudoContainer.h
 *  Part of     : OpenGLEx / Ludo
 *
 *  Copyright (c) 2004-2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

#ifndef LUDOCONTAINER_H
#define LUDOCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <GLES/egl.h>
#include <akndef.h>
#include "Ludo.h"

// CLASS DECLARATION

/**
 * Container control class that handles the OpenGL ES initialization and deinitializations.
 * Also uses the CLudo class to do the actual OpenGL ES rendering.
 */
class CLudoContainer : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor

        /**
         * EPOC default constructor. Initializes the OpenGL ES and creates the rendering context.
         * @param aRect Screen rectangle for container.
         */
        void ConstructL(const TRect& aRect);

        /**
         * Destructor. Destroys the CPeriodic, CLudo and uninitializes OpenGL ES.
         */
        virtual ~CLudoContainer();

    public: // New functions

        /**
         * Callback function for the CPeriodic. Calculates the current frame, keeps the background
         * light from turning off and orders the CLudo to do the rendering for each frame.
         *@param aInstance Pointer to this instance of CLudoContainer.
         */
        static int DrawCallBack( TAny* aInstance );
        
        /**
         * Para cambiar al modo Widescreen
         */
        void SetWidescreen();

    private: // Functions from base classes

        /**
         * Method from CoeControl that gets called when the display size changes.
         * If OpenGL has been initialized, notifies the renderer class that the screen
         * size has changed.
         */
        void SizeChanged();

        /**
         * Handles a change to the control's resources. This method
         * reacts to the KEikDynamicLayoutVariantSwitch event (that notifies of
         * screen size change) by calling the SetExtentToWholeScreen() again so that
         * this control fills the new screen size. This will then trigger a call to the
         * SizeChanged() method.
         * @param aType Message UID value, only KEikDynamicLayoutVariantSwitch is handled by this method.
         */
        void HandleResourceChange(TInt aType);

        /**
         * Method from CoeControl. Does nothing in this implementation.
         */
        TInt CountComponentControls() const;

        /**
         * Method from CCoeControl. Does nothing in this implementation.
         */
        CCoeControl* ComponentControl(TInt aIndex) const;

        /**
         * Method from CCoeControl. Does nothing in this implementation.
         * All rendering is done in the DrawCallBack() method.
         */
        void Draw(const TRect& aRect) const;

        /**
         * Method from MCoeControlObserver that handles an event from the observed control.
         * Does nothing in this implementation.
		 * @param aControl   Control changing its state.
		 * @param aEventType Type of the control event.
         */
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

    private: //data

        /** Display where the OpenGL ES window surface resides. */
        EGLDisplay  iEglDisplay;

        /** Window surface that is the target of OpenGL ES graphics rendering. */
        EGLSurface  iEglSurface;

        /** OpenGL ES rendering context. */
        EGLContext  iEglContext;

        /** Active object that is the timing source for the animation. */
        CPeriodic*  iPeriodic;

        /**
         * Flag that indicates if OpenGL ES has been initialized or not.
         * Used to check if SizeChanged() can react to incoming notifications.
         */
        TBool iOpenGlInitialized;

    public:  //data

        /** Frame counter variable, used in the animation. */
        TInt iFrame;

        /** Used in DrawCallBack() method to do the actual OpenGL ES rendering.  */
        CLudo* iLudo;
    };

#endif

// End of File
