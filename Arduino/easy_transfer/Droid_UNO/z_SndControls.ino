void BB8_SoundControl (int SoundCtrl){
  #ifdef SFX_SERIAL
  String strCmd;
          strCmd = "P";
          strCmd += Sound[random(1, 21)];
          strCmd += "\n";
      switch (SoundCtrl)
      {          
        case 1:
          Serial1.print("q\n");
//          Serial1.print("PT00NEXT0OGG\n");
          strCmd = "P";
          strCmd += Sound[random(1, 21)];
          strCmd += "\n";
          Serial1.print(strCmd);
          break;
          
        case 2:
          Serial1.print("q\n");
          Serial1.print("PT00NEXT1OGG\n");
          break;
          
        case 3:
          Serial1.print("q\n");
          Serial1.print("PT00NEXT2OGG\n");
          break;
          
        case 4:
          Serial1.print("q\n");
          Serial1.print("PT00NEXT3OGG\n");
          break;
          
        case 5:
          Serial1.print("q\n");
          Serial1.print("PT00NEXT4OGG\n");
          break;
          
        case 6:
          Serial1.print("q\n");
          Serial1.print("PT00NEXT5OGG\n");
          break;
          
        case 7:
          Serial1.print("q\n");
          Serial1.print("PT00NEXT6OGG\n");
          break;
          
        case 8:
          Serial1.print("q\n");
          Serial1.print("PT00NEXT7OGG\n");
          break;
          
        case 9:
          Serial1.print("q\n");
          Serial1.print("PT00NEXT8OGG\n");
          break;
          
        case 10:
          Serial1.print("q\n");
          Serial1.print("PT00NEXT9OGG\n");
          break;
          
        case 11:
          Serial1.print("q\n");
          Serial1.print("PT01NEXT0OGG\n");
          break;
          
        case 12:
          Serial1.print("q\n");
          Serial1.print("PT01NEXT1OGG\n");
          break;
          
        case 13:
          Serial1.print("q\n");
          Serial1.print("PT01NEXT2OGG\n");
          break;
          
        case 14:
          Serial1.print("q\n");
          Serial1.print("PT01NEXT3OGG\n");
          break;
          
        case 15:
          Serial1.print("q\n");
          Serial1.print("PT01NEXT4OGG\n");
          break;
          
        case 16:
          Serial1.print("q\n");
          Serial1.print("PT01NEXT5OGG\n");
          break;
          
        case 17:
          Serial1.print("q\n");
          Serial1.print("PT01NEXT6OGG\n");
          break;
          
        case 18:
          Serial1.print("q\n");
          Serial1.print("PT01NEXT7OGG\n");
          break;
          
        case 19:
          Serial1.print("q\n");
          Serial1.print("PT01NEXT8OGG\n");
          break;
          
        case 20:
          Serial1.print("q\n");
          Serial1.print("PT01NEXT9OGG\n");
          break;
          
        case 21:
          Serial1.print("q\n");
          Serial1.print("PT02NEXT0OGG\n");
          break;
          
        case 22:
          Serial1.print("q\n");
          Serial1.print("PT02NEXT1OGG\n");
          break;
          
        case 23:
          Serial1.print("q\n");
          Serial1.print("PT02NEXT2OGG\n");
          break;
          
        case 24:
          Serial1.print("q\n");
          Serial1.print("PT02NEXT3OGG\n");
          break;
          
        case 25:
          Serial1.print("q\n");
          Serial1.print("PT02NEXT4OGG\n");
          break;
          
        case 26:
          Serial1.print("q\n");
          Serial1.print("PT02NEXT5OGG\n");
          break;
          
        case 27:
          Serial1.print("q\n");
          Serial1.print("PT02NEXT6OGG\n");
          break;
          
        case 28:
          Serial1.print("q\n");
          Serial1.print("PT02NEXT7OGG\n");
          break;
          
        case 29:
          Serial1.print("q\n");
          Serial1.print("PT02NEXT8OGG\n");
          break;
          
        case 30:
          Serial1.print("q\n");
          Serial1.print("PT02NEXT9OGG\n");
          break;
          
        case 31:
          Serial1.print("q\n");
          Serial1.print("PT03NEXT0OGG\n");
          break;
          
        case 32:
          Serial1.print("q\n");
          Serial1.print("PT03NEXT1OGG\n");
          break;
          
        case 33:
          Serial1.print("q\n");
          Serial1.print("PT03NEXT2OGG\n");
          break;
          
        case 34:
          Serial1.print("q\n");
          Serial1.print("PT03NEXT3OGG\n");
          break;
          
        case 35:
          Serial1.print("q\n");
          Serial1.print("PT03NEXT4OGG\n");
          break;
          
        case 36:
          Serial1.print("q\n");
          Serial1.print("PT03NEXT5OGG\n");
          break;
          
        case 37:
          Serial1.print("q\n");
          Serial1.print("PT03NEXT6OGG\n");
          break;
          
        case 38:
          Serial1.print("q\n");
          Serial1.print("PT03NEXT7OGG\n");
          break;
          
        case 39:
          Serial1.print("q\n");
          Serial1.print("PT03NEXT8OGG\n");
          break;
          
        case 40:
          Serial1.print("q\n");
          Serial1.print("PT03NEXT9OGG\n");
          break;
          
        case 41:
          Serial1.print("q\n");
          Serial1.print("PT04NEXT0OGG\n");
          break;
          
        case 42:
          Serial1.print("q\n");
          Serial1.print("PT04NEXT1OGG\n");
          break;
          
        case 43:
          Serial1.print("q\n");
          Serial1.print("PT04NEXT2OGG\n");
          break;
          
        case 44:
          Serial1.print("q\n");
          Serial1.print("PT04NEXT3OGG\n");
          break;
          
        case 45:
          Serial1.print("q\n");
          Serial1.print("PT04NEXT4OGG\n");
          break;
          
        case 46:
          Serial1.print("q\n");
          Serial1.print("PT04NEXT5OGG\n");
          break;
          
        case 47:
          Serial1.print("q\n");
          Serial1.print("PT04NEXT6OGG\n");
          break;
          
        case 48:
          Serial1.print("q\n");
          Serial1.print("PT04NEXT7OGG\n");
          break;
          
        case 49:
          Serial1.print("q\n");
          Serial1.print("PT04NEXT8OGG\n");
          break;
          
        case 50:
          Serial1.print("q\n");
          Serial1.print("PT04NEXT9OGG\n");
          break;
          
        case 51:
          Serial1.print("q\n");
          Serial1.print("PT05NEXT0OGG\n");
          break;
          
        case 52:
          Serial1.print("q\n");
          Serial1.print("PT05NEXT1OGG\n");
          break;
          
        case 53:
          Serial1.print("q\n");
          Serial1.print("PT05NEXT2OGG\n");
          break;
          
        case 54:
          Serial1.print("q\n");
          Serial1.print("PT05NEXT3OGG\n");
          break;
          
        case 55:
          Serial1.print("q\n");
          Serial1.print("PT05NEXT4OGG\n");
          break;
          
        case 56:
          Serial1.print("q\n");
          Serial1.print("PT05NEXT5OGG\n");
          break;

        case 99:
          Serial.print("q\n");
          Serial.print(strCmd);
          break;
      }
#endif
}
