/*
 * ==============================================================================
 *  Name        : LudoApp.h
 *  Part of     : OpenGLEx / Ludo
 *
 *  Copyright (c) 2005-2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

#ifndef LUDOAPP_H
#define LUDOAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
/** UID of the application. */
const TUid KUidLudo = { 0xA000321D };

// CLASS DECLARATION

/**
 * Application class. Provides factory method to create a concrete document object.
 */
class CLudoApp : public CAknApplication
    {
    private: // Functions from base classes

        /**
         * From CApaApplication, creates and returns CLudoDocument document object.
         * @return Pointer to the created document object.
         */
        CApaDocument* CreateDocumentL();

        /**
         * From CApaApplication, returns application's UID (KUidLudo).
         * @return Value of KUidLudo.
         */
        TUid AppDllUid() const;
    };

// OTHER EXPORTED FUNCTIONS

/**
 * Factory method used by the E32Main method to create a new application instance.
 */
LOCAL_C CApaApplication* NewApplication();

/**
 * Entry point to the EXE application. Creates new application instance and
 * runs it by giving it as parameter to EikStart::RunApplication() method.
 */
GLDEF_C TInt E32Main();

#endif

// End of File
