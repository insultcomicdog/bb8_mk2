#include <EasyTransfer.h>

//create object
EasyTransfer ET; 
EasyTransfer ET2; 

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t ch1;
  int16_t ch2;
  int16_t ch3;
  int16_t ch4;
  int16_t ch5;
  int16_t ch6;
  int16_t but1;
  int16_t but2;
  int16_t but3;
  int16_t but4;
  int16_t but5;
  int16_t but6;
};


struct RECEIVE_DATA_STRUCTURE2{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  float pitch;
  float roll;
};

RECEIVE_DATA_STRUCTURE mydata;
RECEIVE_DATA_STRUCTURE2 mydata2;

#include <PID_v1.h>  //PID loop from http://playground.arduino.cc/Code/PIDLibrary

#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

int ch3a;
int ch4a;
int ch5a;
int ch6a;

unsigned long previousMillis = 0;
const long interval = 20;


int current_pos_headturn;  // variables for smoothing head rotation
int target_pos_headturn;
int pot_headturn;   // target position/inout
int diff_headturn; // difference of position
double easing_headturn;

int current_pos_drive;  // variables for smoothing main drive
int target_pos_drive;
int pot_drive;   // target position/inout
int diff_drive; // difference of position
double easing_drive;

int current_pos_trousers;  // variables for smoothing trousers
int target_pos_trousers;
int pot_trousers;   // target position/inout
int diff_trousers; // difference of position
double easing_trousers;

int current_pos_head1;  // variables for smoothing head back/forward
int target_pos_head1;
int pot_head1;   // target position/inout
int diff_head1; // difference of position
double easing_head1;

int varServo1;
int varServo2;

float roll;
float pitch;
float bodge = 0;  //trim control
//int potBodge = 40; //high makes it go right
int potBodge = -33; //high makes it go right


int pot;

double Pk1 = 12;  //speed it gets there
double Ik1 = 0;
double Dk1 = 0.05;
double Setpoint1, Input1, Output1, Output1a;    // PID variables - tousers SERVO

PID PID1(&Input1, &Output1, &Setpoint1, Pk1, Ik1 , Dk1, DIRECT);    // PID Setup - tousers SERVO


double Pk2 = .6; // position it goes to
double Ik2 = 0;
double Dk2 = 0.35;
double Setpoint2, Input2, Output2, Output2a;    // PID variables - Trouser stability

PID PID2(&Input2, &Output2, &Setpoint2, Pk2, Ik2 , Dk2, DIRECT);    // PID Setup - Trouser stability


double Pk3 = 3; // position it goes to
double Ik3 = 0;
double Dk3 = 0.4;
double Setpoint3, Input3, Output3, Output3a;    // PID variables - Main drive motor

PID PID3(&Input3, &Output3, &Setpoint3, Pk3, Ik3 , Dk3, DIRECT);    // Main drive motor


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial1.begin(115200);
  Serial3.begin(115200);

  ET.begin(details(mydata), &Serial1);
  ET2.begin(details(mydata2), &Serial3);
  

  pinMode(31, OUTPUT);  // enable pin
  pinMode(33, INPUT);  // BT paired status
  pinMode(3, OUTPUT);  // motor drive pins
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT);  
  pinMode(7, OUTPUT);   
  pinMode(11, OUTPUT);  
  pinMode(12, OUTPUT);  
  pinMode(30, OUTPUT);

  servo1.attach(9);     //head servos
  servo2.attach(10);
  servo3.attach(8);


  // *********** PID setup ***********

  PID1.SetMode(AUTOMATIC);              // PID Setup - trousers SERVO
  PID1.SetOutputLimits(-255, 255);
  PID1.SetSampleTime(20);

  PID2.SetMode(AUTOMATIC);              // PID Setup - trousers Stability
  PID2.SetOutputLimits(-255, 255);
  PID2.SetSampleTime(20);

  PID3.SetMode(AUTOMATIC);              // PID Setup - main drive motor
  PID3.SetOutputLimits(-255, 255);
  PID3.SetSampleTime(20);
    
}

void loop() {

   unsigned long currentMillis = millis();
     if (currentMillis - previousMillis >= interval) {  //start timed event
        previousMillis = currentMillis;


      ET.receiveData();
      ET2.receiveData();

//        Serial.println("ET2...");
//        Serial.println("mydata2.roll");
//        Serial.println(mydata2.roll);
//        Serial.println("mydata2.pitch");
//        Serial.println(mydata2.pitch);


        //********** BT / motor enable output******************
        
        if(mydata.but4 == 0) {
          digitalWrite(31, HIGH);

          }
        else if (mydata.but4 == 1) {
          digitalWrite(31, LOW);
        }

        //*************sounds*****************************

        if (mydata.but1 == 0) {
          digitalWrite(30, LOW);
        }
        else {
          digitalWrite(30,HIGH);
        }

        //**********Trousers stability PID**************
        
         target_pos_trousers = map(mydata.ch2, 0,512,-110,110);

         //Serial.println(target_pos_trousers);
      
         easing_trousers = 80;          //modify this value for stick smoothing sensitivity
         easing_trousers /= 1000;
        
         // Work out the required travel.
         diff_trousers = target_pos_trousers - current_pos_trousers;    
        
         // Avoid any strange zero condition
         if( diff_trousers != 0.00 ) {
            current_pos_trousers += diff_trousers * easing_trousers;
         }

         Setpoint2 = current_pos_trousers;

         pot = analogRead(A0);   // read trousers pot

         //Serial.println(pot);

         Input2 = (mydata2.roll*-1)+bodge;   // ****add a bit to the IMU to get the real middle point
         
         //Serial.println(Input2);

         Setpoint2 = constrain(Setpoint2, -55,55);
         PID2.Compute();
         Setpoint1 = Output2;

         pot = map(pot, 0, 1024, -255,255);
         pot = pot+potBodge;
         
         Input1  = pot;
         Input1 = constrain(Input1,-35,35);
         Setpoint1 = constrain(Setpoint1, -35,35);
         Setpoint1 = map(Setpoint1,45,-45,-45,45);
-
         PID1.Compute();

         //Serial.println(Output1);

         // ************** drive trousers motor *************

         if (Output1 < 0)                                      // decide which way to turn the wheels based on deadSpot variable
            {
            Output1a = abs(Output1);
            analogWrite(5, Output1a);                                // set PWM pins 
            analogWrite(3, 0);
            }
         else if (Output1 >= 0)                          // decide which way to turn the wheels based on deadSpot variable
            { 
            Output1a = abs(Output1);
            analogWrite(3, Output1a);  
            analogWrite(5, 0);
            } 
         else
            {
            analogWrite(5, 0);  
            analogWrite(3, 0);
            }

         //***************Main Drive PID***************


         target_pos_drive = map(mydata.ch1, 0,512,65,-65);
      
         easing_drive = 80;          //modify this value for stick smoothing sensitivity
         easing_drive /= 1000;
        
         // Work out the required travel.
         diff_drive = target_pos_drive - current_pos_drive;    
        
         // Avoid any strange zero condition
         if( diff_drive != 0.00 ) {
            current_pos_drive += diff_drive * easing_drive;
         }

         Setpoint3 = current_pos_drive;
      
         Input3 = mydata2.pitch;

         PID3.Compute();

         Serial.println(Output3);
         
         if (Output3 <= 1)                                      // decide which way to turn the wheels based on deadSpot variable
            {
            Output3a = abs(Output3);
            analogWrite(11, Output3a);                                // set PWM pins 
            analogWrite(12, 0);
            }
         else if (Output3 > 1)                          // decide which way to turn the wheels based on deadSpot variable
            { 
            Output3a = abs(Output3);
            analogWrite(12, Output3a);  
            analogWrite(11, 0);
            }

         //****************move head servo******************

         ch3a=map(mydata.ch3,50,590,0,180);
         ch3a = ch3a-(pitch*4.5);
         ch3a=constrain(ch3a,0,180);

         target_pos_head1 = ch3a;
      
         easing_head1 = 100;          //modify this value for stick smoothing sensitivity
         easing_head1 /= 1000;
        
         // Work out the required travel.
         diff_head1 = target_pos_head1 - current_pos_head1;    
        
         // Avoid any strange zero condition
         if( diff_head1 != 0.00 ) {
            current_pos_head1 += diff_head1 * easing_head1;
            }

         varServo1 = current_pos_head1;
         varServo2 = current_pos_head1;

         ch4a=map(mydata.ch4,0,512,-45,45);
         
         varServo1 = varServo1-ch4a;
         varServo2 = varServo2+ch4a;
       
         
         varServo2 = map(varServo2,0,180,180,0);

         varServo1 = constrain(varServo1,10,170);
         varServo2 = constrain(varServo2,10,170);


         if (mydata.but4 == 1) {      // enable pin is off
          servo1.write(60);    //set servos to back/middle position
          servo2.write(120); 
         }

         else if (mydata.but4 == 0) {
         servo1.write(varServo1);    //set servos to stick positions
         servo2.write(varServo2); 
         }

         //****************spin flywheel***************************

         ch6a = map(mydata.ch6,0,512,255,-255);

         if (ch6a <= -10)                                      // decide which way to turn the wheels based on deadSpot variable
         {
            ch6a = abs(ch6a);
            analogWrite(6, ch6a);                                // set PWM pins 
            analogWrite(7, 0);
            }
         else if (ch6a > 10)                          // decide which way to turn the wheels based on deadSpot variable
            { 
            ch6a = abs(ch6a);
            analogWrite(7, ch6a);  
            analogWrite(6, 0);
            }

         else {
            analogWrite(7, 0);  
            analogWrite(6, 0);
         }

         //********************* turn head***************************

         target_pos_headturn = map(mydata.ch5, 0,512,0,180);

         if(target_pos_headturn >=80 && target_pos_headturn <=90){
          target_pos_headturn = 93;
         } 

         if(target_pos_headturn!=current_pos_headturn){
               Serial.println("current_pos_headturn");
               Serial.println(current_pos_headturn);
               Serial.println("target_pos_headturn");
               Serial.println(target_pos_headturn);
               servo3.write(target_pos_headturn);
               current_pos_headturn = target_pos_headturn;
         }

        //******************main code end****************************

     } // end of timed event
      


}  // end  of main loop
