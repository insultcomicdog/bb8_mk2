// =======================================================================================
//                          readUSB Usb.Task() commands
// =======================================================================================
//  The more devices we have connected to the USB or BlueTooth, the more often 
//  Usb.Task need to be called to eliminate latency.

boolean readUSB()
{
  //The more devices we have connected to the USB or BlueTooth, the more often Usb.Task need to be called to eliminate latency.
  Usb.Task();
  if (PS3Nav->PS3NavigationConnected ) Usb.Task();
  if (PS3Nav2->PS3NavigationConnected ) Usb.Task();
  if (criticalFaultDetect())
  {
    //We have a fault condition that we want to ensure that we do NOT process any controller data!!!
    return false;
  }

  if (criticalFaultDetectNav2())
  {
    //We have a fault condition that we want to ensure that we do NOT process any controller data!!!
    return false;
  }
  return true;
}


// =====================================================================================================================
//                          Get JoyStick Values from the PS3 move controller(s)
// =====================================================================================================================
// ch1 = main drive forward and back (right Joy Y)
// ch2 = gyro side to side (right joy X)
// ch3 = head front/back (left Joy Y)
// ch4 = head side to side (left Joy X)
// ch5 = head spin (right L2 + Left Joy X)
// ch6 = flywheel spin (left L2 + right joy X)
// ch7 = Unassigned  (right L2 + Left Joy Y)
// ch8 = unassigned  (leftL2 + right Joy Y)

void GetMoveController() {
  currentMillis = millis();
  readUSB();
  if (PS3Nav->PS3NavigationConnected && PS3Nav2->PS3NavigationConnected) {

      mydata.ch1 = PS3Nav->getAnalogHat(LeftHatY);
      if (PS3Nav2->getButtonPress(L2)==false){
         mydata.ch2 = PS3Nav->getAnalogHat(LeftHatX);
      } else {
         mydata.ch2 = 127;      
      }
            
      mydata.ch3 = PS3Nav2->getAnalogHat(LeftHatY);

      if (PS3Nav->getButtonPress(L2)==false){
          mydata.ch4 = PS3Nav2->getAnalogHat(LeftHatX);
      }else {
          mydata.ch4 = 127;      
      }

      if (PS3Nav->getButtonPress(L2) && PS3Nav2->getAnalogHat(LeftHatX) || PS3Nav2->getAnalogHat(LeftHatX)==0)
      {
        mydata.ch5 = PS3Nav2->getAnalogHat(LeftHatX); // ch5 = head spin
      } else {
        mydata.ch5 = 127;   
      }
      
      if (PS3Nav2->getButtonPress(L2) && PS3Nav->getAnalogHat(LeftHatX) || PS3Nav->getAnalogHat(LeftHatX)==0)
      {
        mydata.ch6 = PS3Nav->getAnalogHat(LeftHatX); // ch6 = flywheel spin
      } else {
        mydata.ch6 = 127;   
      }
  }

  else {
    mydata.ch1 = 127; // send middle position value without fluctuating for forward and backwards
    mydata.ch2 = 127; // send middle position value without fluctuating for swing left and right
    mydata.ch3 = 127; // send middle position value when the head is not being moved around
    mydata.ch4 = 127; // send middle position value when 
    mydata.ch5 = 127;
    mydata.ch6 = 127;
    mydata.but1 = 1;
    mydata.but2 = 1;
    mydata.but3 = 1;
    mydata.but4 = 1;
    mydata.but5 = 1;
    mydata.but6 = 1;
  }

}



void onInitPS3()
{
  String btAddress = getLastConnectedBtMAC();
  PS3Nav->setLedOn(LED1);
  isPS3NavigatonInitialized = true;
  badPS3Data = 0;
#ifdef DEBUG
  Serial.print("\r\nBT Address of Last connected Device when Primary PS3 Connected: ");
  Serial.print(btAddress);
  if (btAddress == PS3MoveNavigatonPrimaryMAC)
  {
    Serial.print("\r\nWe have our primary controller connected.\r\n");
  }
  else
  {
    Serial.print("\r\nWe have a controller connected, but it is not designated as \"primary\".\r\n");
  }
#endif
}

void onInitPS3Nav2()
{
  String btAddress = getLastConnectedBtMAC();
  PS3Nav2->setLedOn(LED1);
  isSecondaryPS3NavigatonInitialized = true;
  badPS3Data = 0;
  if (btAddress == PS3MoveNavigatonPrimaryMAC) swapPS3NavControllers();
#ifdef DEBUG
  Serial.print("\r\nBT Address of Last connected Device when Secondary PS3 Connected: ");
  Serial.print(btAddress);
  if (btAddress == PS3MoveNavigatonPrimaryMAC)
  {
    Serial.print("\r\nWe have our primary controller connecting out of order.  Swapping locations\r\n");
  }
  else
  {
    Serial.print("\r\nWe have a secondary controller connected.\r\n");
  }
#endif
}

String getLastConnectedBtMAC()
{
  String btAddress = "";
  for (int8_t i = 5; i > 0; i--)
  {
    if (Btd.disc_bdaddr[i] < 0x10)
    {
      btAddress += "0";
    }
    btAddress += String(Btd.disc_bdaddr[i], HEX);
    btAddress += (":");
  }
  btAddress += String(Btd.disc_bdaddr[0], HEX);
  btAddress.toUpperCase();
  return btAddress;
}

void swapPS3NavControllers()
{
  PS3BT* temp = PS3Nav;
  PS3Nav = PS3Nav2;
  PS3Nav2 = temp;
  //Correct the status for Initialization
  boolean tempStatus = isPS3NavigatonInitialized;
  isPS3NavigatonInitialized = isSecondaryPS3NavigatonInitialized;
  isSecondaryPS3NavigatonInitialized = tempStatus;
  //Must relink the correct onInit calls
  PS3Nav->attachOnInit(onInitPS3);
  PS3Nav2->attachOnInit(onInitPS3Nav2);
}

// =======================================================================================
//                      Process PS3 Controller Fault Detection
// =======================================================================================
boolean criticalFaultDetect(){
  if (PS3Nav->PS3NavigationConnected || PS3Nav->PS3Connected)
  {
    lastMsgTime = PS3Nav->getLastMessageTime();
    currentTime = millis();
    if ( currentTime >= lastMsgTime)
    {
      msgLagTime = currentTime - lastMsgTime;
    } else
    {
      #ifdef DEBUG
        Serial.println("msgLagTime growing increase badPS3Data");
      #endif
      badPS3Data++;
      msgLagTime = 0;
    }

    if (msgLagTime > 300)
    {
      #ifdef DEBUG
        Serial.println("msgLagTime > 300");
      #endif
      return true;
    }
    if ( msgLagTime > 30000 ) {
      #ifdef DEBUG
        Serial.println("msgLagTime > 30000 disconnecting");
      #endif
      PS3Nav->disconnect();
      msgLagTime = 0;
    }
    //Check PS3 Signal Data
    if (!PS3Nav->getStatus(Plugged) && !PS3Nav->getStatus(Unplugged)) {
      delay(10); // We don't have good data from the controller. Wait 10ms, Update USB, and try again
      Usb.Task();
      if (!PS3Nav->getStatus(Plugged) && !PS3Nav->getStatus(Unplugged)) {
        badPS3Data++;
        #ifdef DEBUG
          Serial.println("We don't have good data from the controller. Wait 10ms, Update USB, and try again");
        #endif
        return true;
      }
    }
    else if (badPS3Data > 0)
    {

      badPS3Data = 0;
    }
    if ( badPS3Data > 10 )
    {
      #ifdef DEBUG
        Serial.println("badPS3Data > 10");
      #endif
      PS3Nav->disconnect();
      badPS3Data = 0;
    }
  } else lastMsgTime = millis();
  return false;
}

// =======================================================================================
// //////////////////////////Process of PS3 Secondary Controller Fault Detection//////////
// =======================================================================================
boolean criticalFaultDetectNav2() {
  if (PS3Nav2->PS3NavigationConnected || PS3Nav2->PS3Connected) {
    lastMsgTime = PS3Nav2->getLastMessageTime();
    currentTime = millis();

    if ( currentTime >= lastMsgTime) msgLagTime = currentTime - lastMsgTime;
    else {
      #ifdef DEBUG
        Serial.println("msgLagTime growing increase badPS3Data");
      #endif
      badPS3Data++;
      msgLagTime = 0;
    }

    if ( msgLagTime > 10000 ){
      #ifdef DEBUG
        Serial.println("msgLagTime > 10000");
      #endif
      PS3Nav2->disconnect();
      badPS3Data = 0;
      msgLagTime = 0;
      return true;
    }

    //Check PS3 Signal Data
    if (!PS3Nav2->getStatus(Plugged) && !PS3Nav2->getStatus(Unplugged)) {
      #ifdef DEBUG
        Serial.println("We don't have good data from the controller.");
        Serial.println("Wait 15ms, Update USB, and try again");
      #endif
      //  We don't have good data from the controller.
      //  Wait 15ms, Update USB, and try again
      delay(15);
      Usb.Task();
      if (!PS3Nav2->getStatus(Plugged) && !PS3Nav2->getStatus(Unplugged)) {
        badPS3Data++;
        #ifdef DEBUG
          Serial.println("BadPS3Data Increased");
        #endif
        return true;
      }
    }
    else if (badPS3Data > 0) badPS3Data = 0;

    if ( badPS3Data > 10 ) {
      PS3Nav2->disconnect();
      badPS3Data = 0;
      return true;
    }
  } else lastMsgTime = millis();
  return false;
}


