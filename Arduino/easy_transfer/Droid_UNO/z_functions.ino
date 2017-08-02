void senddata() {
if(currentMillis - previousMillis > interval) {
  previousMillis = currentMillis; 
  #ifdef UNO

    mydata.ch1 = map(mydata.ch1, 0,255,512,0);
    mydata.ch2 = map(mydata.ch2, 0,255,512,0);
    mydata.ch3 = map(mydata.ch3, 0,255,512,0);
    mydata.ch4 = map(mydata.ch4, 0,255,512,0);
    mydata.ch5 = map(mydata.ch5, 0,255,512,0);
    mydata.ch6 = map(mydata.ch6, 0,255,512,0);
  
//    Serial.print (mydata.ch1);
//    Serial.print (",");
//    Serial.print (mydata.ch2);
//    Serial.print (",");
//    Serial.print (mydata.ch3);
//    Serial.print (",");
//    Serial.print (mydata.ch4);
//    Serial.print (",");
//    Serial.print (mydata.ch5);
//    Serial.print (",");
//    Serial.print (mydata.ch6);
//    Serial.print (",");
//    Serial.print (mydata.but1);
//    Serial.print (",");
//    Serial.print (mydata.but2);
//    Serial.print (",");
//    Serial.print (mydata.but3);
//    Serial.print (",");
//    Serial.print (mydata.but4);
//    Serial.print (",");
//    Serial.print (mydata.but5);
//    Serial.print (",");
//    Serial.print (mydata.but6);
//    Serial.print ("\n");
    
    ET.sendData();

  #else
    Serial2.print (ch1);
    Serial2.print (",");
    Serial2.print (ch2);
    Serial2.print (",");
    Serial2.print (ch3);
    Serial2.print (",");
    Serial2.print (ch4);
    Serial2.print (",");
    Serial2.print (ch5);
    Serial2.print (",");
    Serial2.print (ch6);
    Serial2.print (",");
    Serial2.print (but1);
    Serial2.print (",");
    Serial2.print (but2);
    Serial2.print (",");
    Serial2.print (but3);
    Serial2.print (",");
    Serial2.print (but4);
    Serial2.print (",");
    Serial2.print (but5);
    Serial2.print (",");
    Serial2.print (but6);
    Serial2.print ("\n");
  #endif
  
  }
}


