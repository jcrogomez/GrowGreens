// compressorController.cpp
//
// Copyright (C) 2019 Grow

#include "compressorController.h"

/***   compressorController   ***/
// Statics variables definitions

compressorController::compressorController(bool comprLogic, bool nutrLogic, bool waterLogic) // Constructor
   { __State = LOW ;
     __Enable = LOW ;
     __Valve_Compressor = LOW ;
     __Valve_Nutrition = LOW ;
     __Valve_Water = LOW ;
     __Compressor_invertedLogic = comprLogic;
     __Nutrition_invertedLogic = nutrLogic;
     __Water_invertedLogic = waterLogic;
   }

void compressorController::turnOn()
 { __State = HIGH;
   Serial.println(F("Compressor: Turn On"));
 }

void compressorController::turnOff()
 { __State = LOW;
   Serial.println(F("Compressor: Turn Off"));
 }

void compressorController::doNothing()
  { turnOff();
    __Valve_Compressor = LOW;
    __Valve_Nutrition = LOW;
    __Valve_Water = LOW;
  }

void compressorController::openCompressor()
  { turnOff();
    turnOn_ValveCompressor(__Compressor_invertedLogic);
    turnOff_ValveNutrition(__Nutrition_invertedLogic);
    turnOff_ValveWater(__Water_invertedLogic);
  }

void compressorController::openNutrition()
  { turnOff();
    turnOn_ValveCompressor(__Compressor_invertedLogic);
    turnOn_ValveNutrition(__Nutrition_invertedLogic);
    turnOff_ValveWater(__Water_invertedLogic);
  }

void compressorController::openWater()
  { turnOff();
    turnOff_ValveCompressor(__Compressor_invertedLogic);
    turnOff_ValveNutrition(__Nutrition_invertedLogic);
    turnOn_ValveWater(__Water_invertedLogic);
  }

void compressorController::openEverything()
  { turnOff();
    turnOn_ValveCompressor(__Compressor_invertedLogic);
    turnOn_ValveNutrition(__Nutrition_invertedLogic);
    turnOn_ValveWater(__Water_invertedLogic);
  }

void compressorController::fillCompressor()
  { turnOn();
    turnOn_ValveCompressor(__Compressor_invertedLogic);
    turnOff_ValveNutrition(__Nutrition_invertedLogic);
    turnOff_ValveWater(__Water_invertedLogic);
  }

void compressorController::fillNutrition()
  { turnOn();
    turnOn_ValveCompressor(__Compressor_invertedLogic);
    turnOn_ValveNutrition(__Nutrition_invertedLogic);
    turnOff_ValveWater(__Water_invertedLogic);
  }

void compressorController::fillWater()
  { turnOn();
    turnOff_ValveCompressor(__Compressor_invertedLogic);
    turnOff_ValveNutrition(__Nutrition_invertedLogic);
    turnOn_ValveWater(__Water_invertedLogic);
  }

void compressorController::fillEverything()
  { turnOn();
    turnOn_ValveCompressor(__Compressor_invertedLogic);
    turnOn_ValveNutrition(__Nutrition_invertedLogic);
    turnOn_ValveWater(__Water_invertedLogic);
  }

void compressorController::turnOn_ValveCompressor(bool inverted_logic)
  { if(inverted_logic){__Valve_Compressor = LOW;}
    else{__Valve_Compressor = HIGH;}
  }

void compressorController::turnOff_ValveCompressor(bool inverted_logic)
  { if(inverted_logic){__Valve_Compressor = HIGH;}
    else{__Valve_Compressor = LOW;}
  }

void compressorController::turnOn_ValveNutrition(bool inverted_logic)
  { if(inverted_logic){__Valve_Nutrition = LOW;}
    else{__Valve_Nutrition = HIGH;}
  }

void compressorController::turnOff_ValveNutrition(bool inverted_logic)
  {  if(inverted_logic){__Valve_Nutrition = HIGH;}
    else{__Valve_Nutrition = LOW;}
  }

void compressorController::turnOn_ValveWater(bool inverted_logic)
  { if(inverted_logic){__Valve_Water = LOW;}
    else{__Valve_Water = HIGH;}
  }

void compressorController::turnOff_ValveWater(bool inverted_logic)
  { if(inverted_logic){__Valve_Water = HIGH;}
    else{__Valve_Water = LOW;}
  }

bool compressorController::getState() // Constructor
  { return __State; }

bool compressorController::getValvCompressorState()
  { return __Valve_Compressor; }

bool compressorController::getValvNutritionState()
  { return __Valve_Nutrition; }

bool compressorController::getValvWaterState()
  { return __Valve_Water; }

void compressorController::close_ValveNutrition()
  { turnOff_ValveNutrition(__Nutrition_invertedLogic); }

void compressorController::close_ValveWater()
  { turnOff_ValveWater(__Water_invertedLogic); }

void compressorController::enable(bool en)
  { __Enable = en;
    Serial.print(F("Compressor: "));
    if(__Enable){Serial.println(F("Enabled"));}
    else{Serial.println(F("Disabled"));}
  }

bool compressorController::isEnable()
  { return __Enable; }

byte compressorController::setMode(byte mode)
  { switch(mode){
      case 0: // Do nothing
        doNothing();
        break;
      case 1: // Equal pressures in compressor kegs
        openCompressor();
        break;
      case 2: // Equal pressures in nutrition kegs
        openNutrition();
        break;
      case 3: // Equal pressures in water kegs
        openWater();
        break;
      case 4: // Equal all pressures
        openEverything();
        break;
      case 5: // Fill just compressor kegs
        fillCompressor();
        break;
      case 6: // Fill just nutrition kegs
        fillNutrition();
        break;
      case 7: // Fill just water kegs
        fillWater();
        break;
      case 8: // Fill everything
        fillEverything();
        break;
      default: // Do nothing
        doNothing();
        break;
      }
      if(mode>=0 && mode<=8){return mode;}
      else{return 0;}
  }