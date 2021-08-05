#pragma once
#include "Module.h"
#include "ir_LG.h"

class IrLg : public Module {
    private:
        const uint8_t TRANSMITTER_PIN = 4;
        IRLgAc* airConditional;
    public:
        IrLg();
        virtual ~IrLg();
        // Module identification
        virtual const char*   getId()    { return LG_MODULE; }
        virtual const char*   getName()  { return Messages::TITLE_LG_MODULE; }
        virtual const String  getModuleWebpage();
        virtual void          resolveTemplateKey( const String& key, String& out );
    protected:
        virtual bool          handleCommand( const String& cmd, const String& args );
  };
