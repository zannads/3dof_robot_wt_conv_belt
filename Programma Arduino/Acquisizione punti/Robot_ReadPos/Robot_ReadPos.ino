/*
This example shows how to move G15 knob to certain angle with different speed.

Function:
  setLED(G15_ID, onOff); // Control G15 LED. onOff: ON or OFF
  setSpeed(G15_ID, speed); // Set G15 speed: 0 - 1023
  setPosAngle(G15_ID, angle); // Set G15 angle: 0 - 359

Product page:
  Cytron G15 Shield: http://www.cytron.com.my/p-shield-g15
  G15 Cube Servo: http://www.cytron.com.my/p-g15
  CT-UNO: http://www.cytron.com.my/p-ct-uno

Original written by:
            Ing Hui, Cytron Technologies

Modified:
  29/06/15  Idris, Cytron Technologies
*/

#include <SoftwareSerial.h>
#include <Cytron_G15Shield.h>

Cytron_G15Shield g15(10, 11, 8); // SoftwareSerial: Rx, Tx and Control pin
//Cytron_G15Shield g15(8); // HardwareSerial: Control pin

#define G15_1 1
#define G15_2 2
#define G15_3 3
#define G15_4 4
#define LED 13

word error = 0;
byte data[10];
word position = 0;

void setup()
{
  g15.begin(19200);
  Serial.begin(9600);

  g15.setTorqueOnOff(G15_1, 0);
  g15.setTorqueOnOff(G15_2, 0);
  g15.setTorqueOnOff(G15_3, 0);
  g15.setTorqueOnOff(G15_4, 0);
}

void loop()
{
  //MOTOR1
  error = g15.getPos(G15_1, data); // Get G15 ID1 knob position
  if(error == 0) // No error
  {
    digitalWrite(LED, LOW);
    position = data[0];
    position = position | (data[1] << 8);
    Serial.print("M1:   "); 
    Serial.println(ConvertPosToAngle(position)); // Print angle
  }
  else // Error occur, LED on CT UNO will light up
  {
    digitalWrite(LED, HIGH);
  }

  //MOTROR2
  error = g15.getPos(G15_2, data); // Get G15 ID1 knob position
  if(error == 0) // No error
  {
    digitalWrite(LED, LOW);
    position = data[0];
    position = position | (data[1] << 8);
    Serial.print("M2:   ");
    Serial.println(ConvertPosToAngle(position)); // Print angle
  }
  else // Error occur, LED on CT UNO will light up
  {
    digitalWrite(LED, HIGH);
  }

  //MOTOR3
  error = g15.getPos(G15_3, data); // Get G15 ID1 knob position
  if(error == 0) // No error
  {
    digitalWrite(LED, LOW);
    position = data[0];
    position = position | (data[1] << 8);
    Serial.print("M3:   ");     
    Serial.println(ConvertPosToAngle(position)); // Print angle
  }
  else // Error occur, LED on CT UNO will light up
  {
    digitalWrite(LED, HIGH);
  }

  //MOTOR4
  error = g15.getPos(G15_4, data); // Get G15 ID1 knob position
  if(error == 0) // No error
  {
    digitalWrite(LED, LOW);
    position = data[0];
    position = position | (data[1] << 8);
    Serial.print("M4:   ");
    Serial.println(ConvertPosToAngle(position)); // Print angle
  }
  else // Error occur, LED on CT UNO will light up
  {
    digitalWrite(LED, HIGH);
  }

  Serial.println();
  delay(200);
}
