/*
 * ==============================================================================
 *  Name        : LudoDocument.cpp
 *  Part of     : OpenGLEx / Ludo
 *
 *  Copyright (c) 2004-2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

// INCLUDE FILES
#include "LudoDocument.h"
#include "LudoAppUi.h"

// ================= MEMBER FUNCTIONS =======================

// -----------------------------------------------------------------------------
// CLudoDocument::CLudoDocument
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CLudoDocument::CLudoDocument(CEikApplication& aApp)
: CAknDocument(aApp)
    {
    }

// -----------------------------------------------------------------------------
// ?classname::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLudoDocument::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// CLudoDocument::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLudoDocument* CLudoDocument::NewL(
        CEikApplication& aApp)     // CLudoApp reference
    {
    CLudoDocument* self = new (ELeave) CLudoDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }

// destructor
CLudoDocument::~CLudoDocument()
    {
    }

// ----------------------------------------------------
// CLudoDocument::CreateAppUiL()
// constructs CLudoAppUi
// ----------------------------------------------------
//
CEikAppUi* CLudoDocument::CreateAppUiL()
    {
    return new (ELeave) CLudoAppUi;
    }

// End of File
