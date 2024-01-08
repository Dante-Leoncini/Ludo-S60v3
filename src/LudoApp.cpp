/*
 * ==============================================================================
 *  Name        : LudoApp.cpp
 *  Part of     : OpenGLEx / Ludo
 *
 *  Copyright (c) 2004-2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

// INCLUDE FILES
#include    <eikstart.h>
#include    "LudoApp.h"
#include    "LudoDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CLudoApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CLudoApp::AppDllUid() const
    {
    return KUidLudo;
    }


// ---------------------------------------------------------
// CLudoApp::CreateDocumentL()
// Creates CLudoDocument object
// ---------------------------------------------------------
//
CApaDocument* CLudoApp::CreateDocumentL()
    {
    return CLudoDocument::NewL( *this );
    }


// ================= OTHER EXPORTED FUNCTIONS ==============


CApaApplication* NewApplication()
    {
    return new CLudoApp;
    }

TInt E32Main()
    {
        return EikStart::RunApplication(NewApplication);
    }

// End of File

