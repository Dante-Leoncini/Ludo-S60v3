#ifndef LUDODOCUMENT_H
#define LUDODOCUMENT_H

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
 * Document class that is just used as the container for the application
 * (as required by the Symbian UI application architecture).
 */
class CLudoDocument : public CAknDocument
    {
    public: // Constructors and destructor

        /**
         * Factory method for creating a new CLudoDocument object.
         */
        static CLudoDocument* NewL(CEikApplication& aApp);

        /**
         * Destructor. Does nothing.
         */
        virtual ~CLudoDocument();

    private:  // Functions from base classes

        /**
         * C++ constructor. Just passes the given application reference to the baseclass.
         */
        CLudoDocument(CEikApplication& aApp);

        /**
         * Second phase constructor. Does nothing.
         */
        void ConstructL();

    private: // New functions

        /**
         * From CEikDocument, creates and returns CLudoAppUi application UI object.
         */
        CEikAppUi* CreateAppUiL();
    };

#endif

// End of File

