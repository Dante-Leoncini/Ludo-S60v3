/*
 * ==============================================================================
 *  Name        : LudoAppUi.h
 *  Part of     : OpenGLEx / Ludo
 *
 *  Copyright (c) 2004-2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

#ifndef LUDOAPPUI_H
#define LUDOAPPUI_H

// INCLUDES
#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <coeccntx.h>
#include <aknappui.h>

// FORWARD DECLARATIONS
class CLudoContainer;


// CLASS DECLARATION

/**
 * Application UI class that is contains the CLudoContainer
 * (as required by the Symbian UI application architecture).
 */
class CLudoAppUi : public CAknAppUi
    {
    public: // Constructors and destructor

        /**
         * Second phase constructor. Creates the CLudoContainer
         * and adds it to the control stack.
         */
        void ConstructL();

        /**
         * Destructor. Removes CLudoContainer from the control
         * stack and destroys it.
         */
        virtual ~CLudoAppUi();

    private: // Functions from base classes

        /**
         * This method is called by the EIKON framework just before it displays
         * a menu pane. Builds the dynamic menuitems for toggling the lights on and
         * off in the example.
         */
        void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);

        /**
         * CEikAppUi method that is used to handle user commands.
         * Handles menu commands and application exit request.
         * @param aCommand Command to be handled.
         */
        void HandleCommandL(TInt aCommand);

        /**
         * CEikAppUi method that is used to handle key events.
         * Does nothing in this implemenation.
         * @param aKeyEvent Event to handled (ignored by this implementation).
         * @param aType Type of the key event (ignored by this implementation).
         * @return Response code. Always EKeyWasNotConsumed in this implementation.
         */
        virtual TKeyResponse HandleKeyEventL(
            const TKeyEvent& aKeyEvent,TEventCode aType);

    private: //Data

        /** GUI container that resides in this application UI. */
        CLudoContainer* iAppContainer;
    };

#endif

// End of File
