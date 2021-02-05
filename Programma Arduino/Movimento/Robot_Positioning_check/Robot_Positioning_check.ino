/*
This program moves the robot in the 3 position.
Position1 R. takes the piece
Position2-3-4 R. leaves the piece
Position5-6 R. stand-by position

Tongs program open and close the tong, 
in open position(1) the angle of the 4th motor is 158 degrees.

Function used:
  setLED(G15_ID, onOff); // Control G15 LED. onOff: ON or OFF
  setSpeed(G15_ID, speed); // Set G15 speed: 0 - 1023
  setPosAngle(G15_ID, angle); // Set G15 angle: 0 - 359

Product page:
  Cytron G15 Shield: http://www.cytron.com.my/p-shield-g15
  G15 Cube Servo: http://www.cytron.com.my/p-g15
  CT-UNO: http://www.cytron.com.my/p-ct-uno

Original written by:
            Dennis Zanutto, 5H ITTS Volterra
            a.s. 2015/2016

*/

#include <SoftwareSerial.h>
#include <Cytron_G15Shield.h>

Cytron_G15Shield g15(10, 11, 8); // SoftwareSerial: Rx, Tx and Control pin

#define G15_1 1
#define G15_2 2
#define G15_3 3
#define G15_4 4
#define pinInput 22

float positions[] ={180, 226, 230, /**/180, 245, 225,/**/ 270, 245, 245, /**/270, 225, 245,/**/ 270, 270, 270, /**/180, 270, 270};
int tryCatching=0, catched=0;

word error = 0;
byte data[10];
word position = 0;

void setup()
{
  g15.begin(19200);
  Serial.begin(9600);
  
  pinMode(pinInput, INPUT);
  digitalWrite(pinInput, HIGH);
 
  g15.exitWheelMode(G15_1);
  g15.exitWheelMode(G15_2);
  g15.exitWheelMode(G15_3);
  g15.exitWheelMode(G15_4);

  g15.setSpeed(G15_1,100);
  g15.setSpeed(G15_2,100);
  g15.setSpeed(G15_3,100);
  g15.setSpeed(G15_4, 500);
}

void loop()
{
  tongs(1);
  if(digitalRead(pinInput)==0){
    delay(50);
    if(digitalRead(pinInput)==0){
      positioning(1);
      do{
          tongs(1);
          tongs(0);
          tryCatching= tryCatching + 1;
          catched=checkCatching();
      }
      while(catched==1 && tryCatching<10);
      if(tryCatching==10){
          positioning(6);
          tryCatching=0;
      }
      else{
          positioning(2);
          positioning(3);
          positioning(4);
          tongs(1);
          positioning(5);
          positioning(6);
          tryCatching=0;
      }
    }
    }
}

void positioning(int select){
    g15.setLED(select, ON);
    
    g15.setPosAngle(G15_1,positions[3*select-3]);
    g15.setPosAngle(G15_2,positions[3*select-2]);
    g15.setPosAngle(G15_3,positions[3*select-1]);
    
    delay(1100);
    g15.setLED(select, OFF);
}

void tongs(bool opCl){
   g15.setLED(G15_4, ON);
   
   g15.setPosAngle(G15_4,185 - opCl*30);
   
   delay(300);
   g15.setLED(G15_4, OFF);
}

int checkCatching(){
  error = g15.getPos(G15_4, data); // Get G15 ID1 knob position
  if(error == 0) // No error
  {
      position = data[0];
      position = position | (data[1] << 8);
      position=ConvertPosToAngle(position);
      if(position>=184 && position<=186){
          return 1;
          }
      else{
          return 0;
          }
  }
}

