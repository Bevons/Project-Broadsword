#include <Arduino.h>
#include "ir_Neoclima.h"
#include <algorithm>
#include "IRac.h"
#include "IRsend.h"
#include "IRrecv.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "infrared/IrNeoclima.h"
#include "str_switch.h"
#include "Utils.h"

IrNeoclima::IrNeoclima() {
   // pinMode( TRANSMITTER_PIN, OUTPUT );
    properties.has_module_webpage = true;
    airConditional = new IRNeoclimaAc( TRANSMITTER_PIN );
    airConditional->begin();

//    Log.notice( "Default state" CR );
//    Log.notice( "Set initial settings" CR );
    airConditional->off();
};

IrNeoclima::~IrNeoclima(){
    delete airConditional;
};

const String IrNeoclima::getModuleWebpage() {
  return makeWebpage( "/module_ir_ac.html" );
}

bool IrNeoclima::handleCommand( const String& cmd, const String& args ){
     SWITCH( cmd.c_str() ) {
    // ==========================================
        CASE( "fan" ): {
            SWITCH( args.c_str() ){
                CASE( "on" ): {
                    airConditional->on();
                    airConditional->send();
                    handleCommandResults( cmd, args, Messages::OK );
                    return true;
                }
                CASE( "off" ): {
                    airConditional->off();
                    airConditional->send();
                    handleCommandResults( cmd, args, Messages::OK );
                    return true;
                }
                CASE( "low" ): {
                    airConditional->setFan(kNeoclimaFanLow);
                    airConditional->send();
                    handleCommandResults( cmd, args, Messages::OK );
                    return true;
                }
                CASE( "med" ): {
                    airConditional->setFan(kNeoclimaFanMed);
                    airConditional->send();
                    handleCommandResults( cmd, args, Messages::OK );
                    return true;
                }
                CASE( "high" ): {
                    airConditional->setFan(kNeoclimaFanHigh);
                    airConditional->send();
                    handleCommandResults( cmd, args, Messages::OK );
                    return true;
                }
            }
        }
        CASE( "mode" ): {
            SWITCH( args.c_str() ){
                CASE( "cool" ): {
                    airConditional->setMode( kNeoclimaCool );
                    airConditional->send();
                    handleCommandResults( cmd, args, Messages::OK );
                    return true; 
                }
                CASE( "heat" ):{
                    airConditional->setMode( kNeoclimaHeat );
                    airConditional->send();
                    handleCommandResults( cmd, args, Messages::OK );
                    return true;
                }
            }
        }
        CASE( "temp" ): {
            uint8_t number = Utils::toByte( args.c_str() );
            if( number <= 15 || number >= 30 ) {
                handleCommandResults( cmd, args, Messages::COMMAND_INVALID_VALUE );
            } else {
                airConditional->setTemp(number);
                airConditional->send();
                handleCommandResults( cmd, args, Messages::OK );
            }
            return true;
        }
        DEFAULT_CASE:
            return false;
     }
    // ==========================================
}


void IrNeoclima::resolveTemplateKey( const String& key, String& out ) {
  SWITCH( key.c_str() ) {
    // Module template parameters
    CASE( "MTITLE" ):  {
        out += Utils::formatModuleSettingsTitle( getId(), getName() );  break;
    }  
    CASE( "PIN_NUM" ): {
        out += TRANSMITTER_PIN; break;
    } 
  }
}