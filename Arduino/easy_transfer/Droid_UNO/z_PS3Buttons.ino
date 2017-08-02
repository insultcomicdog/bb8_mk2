// NOTE: you can also use: getButtonPress, getAnalogButton, getButtonClick
// Calling BB8_SoundControl(XX) with a number value - you can review which file on z_SndControls.ino will play selected snd byte
// if you wish to call randoms... those are stored in 99-105

void getMoveButtons(){
  if (PS3Nav2->PS3NavigationConnected) {
    if (PS3Nav2->getAnalogButton(L2)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNAV2 L2:"));
      #endif
    }
    if (PS3Nav2->getAnalogButton(L2) && PS3Nav2->getButtonClick(PS)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nDisconnecting Nav2 SHADOW Controller"));
      #endif
      #ifdef SFX_SERIAL
      Serial1.print("PT02NEXT0OGG\n");
      #endif
      #ifdef DEBUG_SFX
      Serial.print("Played PT02NEXT0OGG\n");
      #endif
      PS3Nav2->disconnect();
      PS3Nav2->disconnect();
    }
  }


  if (PS3Nav->PS3NavigationConnected) {

    // Force disconnect the Move navigation controller using L2 + PS buttons combo.
    if (PS3Nav->getAnalogButton(L2) && PS3Nav->getButtonClick(PS)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nDisconnecting Nav1 SHADOW Controller"));
      #endif
      #ifdef SFX_SERIAL
      Serial1.print("PT02NEXT0OGG\n");
      #endif
      #ifdef DEBUG_SFX
//      Serial.print("Played PT02NEXT0OGG\n");
        BB8_SoundControl(21);
      #endif
      PS3Nav->disconnect();
      PS3Nav->disconnect();
    }
  
  }

  if (PS3Nav->PS3NavigationConnected && PS3Nav2->PS3NavigationConnected) {
  
    if (PS3Nav->getButtonPress(PS) ) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav1 PS"));
      #endif
    }
    if (PS3Nav2->getButtonPress(PS) ) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav2 PS"));
      #endif
    }
    if (PS3Nav->getButtonPress(CIRCLE)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav1 Circle"));
      #endif
      #ifdef SFX_SERIAL
      BB8_SoundControl(1);
      #endif
    }
    
    if (PS3Nav2->getButtonPress(CIRCLE)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav2 Circle"));
      #endif
    }
    
    if (PS3Nav->getButtonClick(CROSS)) {
      if (mydata.but4 == 0) mydata.but4 = 1;
      else mydata.but4 = 0;
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav1 Cross:"));
        Serial.print(mydata.but4);
      #endif
    }
    
    if (PS3Nav2->getButtonClick(CROSS)) {
      if (mydata.but4 == 0) mydata.but4 = 1;
      else mydata.but4 = 0;
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav2 Cross:"));
        Serial.print(but4);
      #endif
    }
    
    // Button 1 Assignment UP 
    if (PS3Nav->getButtonPress(UP) && !PS3Nav2->getAnalogButton(L1)&& !PS3Nav2->getAnalogButton(L2)) {
      #ifdef DEBUG_SFX
        Serial.print(F("\r\nNav1 UP (BUT1)"));
      #endif
      mydata.but1=0;
      #ifdef SFX_SERIAL
      Serial1.print("q\n");
      Serial1.print("PT01NEXT4OGG\n");
      #endif
      #ifdef DEBUG_SFX
      Serial.print("Played PT01NEXT4OGG\n");
      #endif
    } else mydata.but1=1;
    
    if (PS3Nav->getButtonPress(RIGHT) && !PS3Nav2->getAnalogButton(L1)&& !PS3Nav2->getAnalogButton(L2)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav1 RIGHT (BUT2)"));
      #endif
      mydata.but2=0;
      #ifdef SFX_SERIAL
      Serial1.print("q\n");
      Serial1.print("PT04NEXT3OGG\n");
      #endif
      #ifdef DEBUG_SFX
      Serial.print("Played PT04NEXT3OGG\n");
      #endif
    } else mydata.but2=1;
    
    if (PS3Nav->getButtonPress(DOWN) && !PS3Nav2->getAnalogButton(L1)&& !PS3Nav2->getAnalogButton(L2)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav1 DOWN (BUT3)"));
      #endif
      mydata.but3=0;
      #ifdef SFX_SERIAL
      Serial1.print("q\n");
      Serial1.print("PT03NEXT3OGG\n");
      #endif
      #ifdef DEBUG_SFX
      Serial1.print("q\n");
      Serial1.print("PT03NEXT3OGG\n");
      #endif
    } else mydata.but3=1;
        
    if (PS3Nav2->getButtonPress(UP) && !PS3Nav->getAnalogButton(L1)&& !PS3Nav->getAnalogButton(L2)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav2 UP (BUT5)"));
      #endif
      mydata.but5=0;
      #ifdef SFX_SERIAL
      Serial1.print("q\n");
      Serial1.print("PT04NEXT7OGG\n"); // Countdown sound effects...
      #endif
    } else mydata.but5=1;
    
    if (PS3Nav2->getButtonClick(RIGHT) && !PS3Nav->getAnalogButton(L1)&& !PS3Nav->getAnalogButton(L2)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav2 RIGHT (BUT6)"));
      #endif
      mydata.but6=0;
      #ifdef SFX_SERIAL
      Serial1.print("q\n");
      Serial1.print("PT03NEXT9OGG\n");
      #endif
      #ifdef DEBUG_SFX
  
      #endif
    } else mydata.but6=1;
    
    if (PS3Nav2->getButtonPress(DOWN) && !PS3Nav->getAnalogButton(L1)&& !PS3Nav->getAnalogButton(L2)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav2 DOWN (BUT7)"));
      #endif
      //mydata.but7=1;
      #ifdef SFX_SERIAL
      Serial1.print("q\n");
      Serial1.print("PT03NEXT2OGG\n");
      #endif
    } else //mydata.but7=0;
    
    if (PS3Nav2->getButtonClick(LEFT) && !PS3Nav->getAnalogButton(L1)&& !PS3Nav->getAnalogButton(L2)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav2 LEFT (BUT8)"));
      #endif
      //mydata.but8=1;
      #ifdef SFX_SERIAL
      Serial1.print("q\n");
//      Serial1.print("PT02NEXT7OGG\n");
      BB8_SoundControl(28);
      #endif
    } else //mydata.but8=0;
    
    if (PS3Nav2->getButtonPress(L1) && PS3Nav->getButtonClick(UP)) {
      #ifdef DEBUG_SFX
        Serial.println(F("\r\nNav2 L1 + Nav UP"));
      #endif
      #ifdef SFX_SERIAL
        Serial1.print("q\n");
        Serial1.print("PT05NEXT1OGG\n");
      #endif
    }
    if (PS3Nav2->getButtonPress(L1) && PS3Nav->getButtonClick(RIGHT)) {
      #ifdef DEBUG_SFX
        Serial.print(F("\r\nNav2 L1 + Nav RIGHT"));
      #endif
      #ifdef SFX_SERIAL
        Serial1.print("q\n");
        Serial1.print("PT05NEXT2OGG\n");
      #endif
    }
    if (PS3Nav2->getButtonPress(L1) && PS3Nav->getButtonPress(DOWN)) {
    #ifdef DEBUG_SFX
      Serial.print(F("\r\nNav2 L1 + Nav DOWN"));
    #endif
    #ifdef SFX_SERIAL
      Serial1.print("q\n");
      Serial1.print("PT05NEXT3OGG\n");
    #endif
    }
    if (PS3Nav2->getButtonPress(L1) && PS3Nav->getButtonPress(LEFT)) {
    #ifdef DEBUG_SFX
      Serial.print(F("\r\nNav2 L1 + Nav LEFT"));
    #endif
    #ifdef SFX_SERIAL
      Serial1.print("q\n");
      Serial1.print("PT05NEXT4OGG\n");
    #endif
    }
  
    
    if (PS3Nav2->getAnalogButton(L1)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav2 L1"));
      #endif
    }
    
    
    if (PS3Nav->getButtonClick(L3)) {
      #ifdef DEBUG_NAV
      Serial.print(F("\r\nNav Joy Push"));
      #endif
    }
    
    if (PS3Nav2->getButtonClick(L3)) {
      #ifdef DEBUG_NAV
        Serial.print(F("\r\nNav2 Joy Push"));
      #endif
    }
  }
}
