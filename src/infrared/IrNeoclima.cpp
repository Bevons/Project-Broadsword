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

IrNeoclima::IrNeoclima() {
    pinMode( TRANSMITTER_PIN, OUTPUT );
    airConditional = new IRNeoclimaAc( TRANSMITTER_PIN, true );
    airConditional->begin();

//    Log.notice( "Default state" CR );
//    Log.notice( "Set initial settings" CR );
    airConditional->off();
};

IrNeoclima::~IrNeoclima(){
    delete airConditional;
};

bool IrNeoclima::handleCommand( const String& cmd, const String& args ){
     SWITCH( cmd.c_str() ) {
     // ==========================================
        CASE( "fanon" ): {
            airConditional->on();
            for( int i = 0; i < 100; i++ ) {
                airConditional->setFan(kNeoclimaFanMed);
            }
            handleCommandResults( cmd, args, Messages::OK );
            return true;
        }
        CASE( "fanoff" ): {
            airConditional->off();
            handleCommandResults( cmd, args, Messages::OK );
            return true;
        }
        DEFAULT_CASE:
            return false;
        /*
        CASE( "IrNeoclima fan swing on" ): {
            airConditional->setSwing(true);
        }
        CASE( "IrNeoclima fan swing off" ): {
            airConditional->setSwing(false));
        }
        CASE( "irneoclim fan low" ): {
            airConditional->setFan(kNeoclimaFanLow);
        }
        CASE( "irneoclim fan med" ): {
            airConditional->setFan(kNeoclimaFanMed);
        }
        CASE( "irneoclim fan high" ): {
            airConditional->setFan(kNeoclimaFanHigh);
        }
        CASE( "irneoclim fan cool" ): {
            airConditional->setMode(kNeoclimaCool);
        }
        CASE( "irneoclim fan dry" ): {
            airConditional->setMode(kNeoclimaDry);
        }
        CASE( "irneoclim temp auto" ): {
            airConditional->setFan(kNeoclimaFanAuto);
        }
        CASE( "irneoclim temp maxC" ): {
            airConditional->setTemp(kNeoclimaMaxTempC);
        }
        CASE( "irneoclim temp maxF" ): {
            airConditional->setTemp(kNeoclimaMaxTempF);
        }
        CASE( "irneoclim temp minC" ): {
            airConditional->setTemp(kNeoclimaMinTempC);
        }
        CASE( "irneoclim temp maxF" ): {
            airConditional->setTemp(kNeoclimaMinTempF);
        }
        CASE( "irneoclim temp 30" ): {
            airConditional->setTemp(30);
        }
        */
     }
    // ==========================================
}
