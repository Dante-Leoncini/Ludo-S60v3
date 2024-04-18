/*
 * ==============================================================================
 *  Name        : LudoAppUi.cpp
 *  Part of     : OpenGLEx / Ludo
 *
 *  Copyright (c) 2004-2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

// INCLUDE FILES
#include "LudoAppUi.h"
#include "LudoContainer.h"
#include <Ludo.rsg>
#include "ludo.hrh"

#include <eikmenup.h>
#include <avkon.hrh>

// ================= MEMBER FUNCTIONS =======================
//
// ----------------------------------------------------------
// CLudoAppUi::ConstructL
// Symbian 2nd phase constructor can leave.
// ----------------------------------------------------------
//
void CLudoAppUi::ConstructL(){
    BaseConstructL();
    iAppContainer = new (ELeave) CLudoContainer;
    iAppContainer->SetMopParent(this);
    iAppContainer->ConstructL( ClientRect() );
    AddToStackL( iAppContainer );
}

// Destructor
CLudoAppUi::~CLudoAppUi(){
	if ( iAppContainer ){
		RemoveFromStack( iAppContainer );
		delete iAppContainer;
	}
}

// ------------------------------------------------------------------------------
//  CLudoAppUi::DynInitMenuPaneL
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
// ------------------------------------------------------------------------------
//
void CLudoAppUi::DynInitMenuPaneL(
    TInt aResourceId, CEikMenuPane* aMenuPane )
    {
    // Item texts for the lighting menu.
    if ( aResourceId == R_LUDO_LIGHTING_MENU ){
        // Text for switching the lights on/off.
        if ( iAppContainer->iLudo->iLightingEnabled ){aMenuPane->SetItemTextL( ELudoLights, R_LIGHTS_OFF );}
        else {aMenuPane->SetItemTextL( ELudoLights, R_LIGHTS_ON  );}

        // Text for switching the lamp on/off.
        if ( iAppContainer->iLudo->iLampEnabled )
            {
            aMenuPane->SetItemTextL( ELudoLamp, R_LAMP_OFF );
            }
        else
            {
            aMenuPane->SetItemTextL( ELudoLamp, R_LAMP_ON );
            }

        // Text for switching the spot on/off.
        if ( iAppContainer->iLudo->iSpotEnabled )
            {
            aMenuPane->SetItemTextL( ELudoSpot, R_SPOT_OFF );
            }
        else
            {
            aMenuPane->SetItemTextL( ELudoSpot, R_SPOT_ON );
		}
	}
    else if (aResourceId == R_LUDO_MENU){
        // Texto para setear la pantalla ancha
        if ( iAppContainer->iLudo->iWidescreenEnabled ){aMenuPane->SetItemTextL( ELudoWidescreen, R_WIDESCREEN_OFF );}
        else {aMenuPane->SetItemTextL( ELudoWidescreen, R_WIDESCREEN_ON  );}    	
    }
}

// ----------------------------------------------------
// CLudoAppUi::HandleKeyEventL
// Key event handler
// ----------------------------------------------------
//
TKeyResponse CLudoAppUi::HandleKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType ){
    if ( iAppContainer->iLudo->GetState() == CLudo::ERunning ){
		if( aType == EEventKeyDown ){
			TUint scan = aKeyEvent.iScanCode;
			switch(scan){
			case(167): //OK
				iAppContainer->iLudo->Confirmar();
				return EKeyWasConsumed;
			case(16): //arriba
				iAppContainer->iLudo->TEST(2);
				return EKeyWasConsumed;
			case(15): //derecha
				iAppContainer->iLudo->ClickDerecha();
				return EKeyWasConsumed;
			case(17): //abajo
				iAppContainer->iLudo->TEST(1);
				return EKeyWasConsumed;
			case(14): //izquierda
				iAppContainer->iLudo->ClickIzquierda();
				return EKeyWasConsumed;
			default:
				return EKeyWasNotConsumed;
			}
		}
	}
    return EKeyWasNotConsumed;
}

// ----------------------------------------------------
// CLudoAppUi::HandleCommandL
// Command handler
// ----------------------------------------------------
//
void CLudoAppUi::HandleCommandL(TInt aCommand){
    switch ( aCommand ){
        case EAknSoftkeyBack:
        case EEikCmdExit: {
            Exit();
            break;
        }   
        case ELudoWidescreen:
            iAppContainer->SetWidescreen();
            break;
        default:
            break;
    }
}

// End of File
