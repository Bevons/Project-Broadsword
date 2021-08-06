#pragma once
#include "Module.h"
#include "ir_Neoclima.h"

class IrNeoclima : public Module {
    private:
        const uint8_t                       TRANSMITTER_PIN = LED_BUILTIN;
        static constexpr const char* const  PIN_OPTION_KEY  = "Pin";
        IRNeoclimaAc*                       airConditional;

    public:
        IrNeoclima();
        virtual ~IrNeoclima();
        // Module identification
        virtual const char*   getId()    { return NEOCLIMA_MODULE; }
        virtual const char*   getName()  { return Messages::TITLE_NEOCLIMA_MODULE; }
        virtual const String  getModuleWebpage();
        virtual const String  getStatusWebpage();
        void                  resolveTemplateKey( const String& key, String& out );
    protected:
        virtual bool          handleCommand( const String& cmd, const String& args );
        ResultData            handleOption( const String& key, const String& value, Options::Action action );
  };
