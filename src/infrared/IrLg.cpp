#include <Arduino.h>
#include "ir_LG.h"
#include <algorithm>
#include "IRac.h"
#include "IRsend.h"
#include "IRrecv.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "infrared/IrLg.h"
#include "str_switch.h"

IrLg::IrLg() {
   // pinMode( TRANSMITTER_PIN, OUTPUT );
    airConditional = new IRLgAc( TRANSMITTER_PIN );
    airConditional->begin();

//    Log.notice( "Default state" CR );
//    Log.notice( "Set initial settings" CR );
    airConditional->off();
};

IrLg::~IrLg(){
    delete airConditional;
};

bool IrLg::handleCommand( const String& cmd, const String& args ){
    String test = cmd.c_str();
    Log.notice( "test : %s", CR , cmd.c_str());
     SWITCH( cmd.c_str() ) {
     // ==========================================
        CASE( "fanon" ): {
            airConditional->on();
            airConditional->setFan( kLgAcFanMedium );
            airConditional->send();
            
            
            handleCommandResults( cmd, args, Messages::OK );
            return true;
        }
        CASE( "fanoff" ): {
            airConditional->off();
            handleCommandResults( cmd, args, Messages::OK );
            airConditional->send();
            return true;
        }
        DEFAULT_CASE:
            return false;
    }
};