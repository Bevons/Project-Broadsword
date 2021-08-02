#pragma once
#include "Module.h"
#include "ir_Neoclima.h"

class IrNeoclima : public Module {
    private:
        const uint8_t TRANSMITTER_PIN = LED_BUILTIN;
        IRNeoclimaAc* airConditional;
    public:
        IrNeoclima();
        virtual ~IrNeoclima();
        // Module identification
        virtual const char*   getId()    { return NEOCLIMA_MODULE; }
        virtual const char*   getName()  { return Messages::TITLE_NEOCLIMA_MODULE; }
    protected:
        virtual bool          handleCommand( const String& cmd, const String& args );
  };
