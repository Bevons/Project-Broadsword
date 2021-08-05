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
#include "Utils.h"

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
                    airConditional->setFan(kLgAcFanLow);
                    airConditional->send();
                    handleCommandResults( cmd, args, Messages::OK );
                    return true;
                }
                CASE( "med" ): {
                    airConditional->setFan(kLgAcFanMedium);
                    airConditional->send();
                    handleCommandResults( cmd, args, Messages::OK );
                    return true;
                }
                CASE( "high" ): {
                    airConditional->setFan(kLgAcFanHigh);
                    airConditional->send();
                    handleCommandResults( cmd, args, Messages::OK );
                    return true;
                }
            }
        }
        CASE( "mode" ): {
            SWITCH( args.c_str() ){
                CASE( "cool" ): {
                    airConditional->setMode( kLgAcCool );
                    airConditional->send();
                    handleCommandResults( cmd, args, Messages::OK );
                    return true; 
                }
                CASE( "heat" ):{
                    airConditional->setMode( kLgAcHeat );
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
};