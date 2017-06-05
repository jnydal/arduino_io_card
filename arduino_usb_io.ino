#include <Servo.h>
#define COMMAND "CMD"
#define ON "ON"
#define OFF "OFF"
#define PORT_POS 0
#define OPERATOR_POS 1

int port;
int data;
int value;
char* st;

Servo servo1; Servo servo2;

/********
 * Arduino IO interface for serial control
 * 
 * 
 */
  
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  // initialize servo outputs:
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  servo1.attach(14); //analog pin 0
  //servo1.setMaximumPulse(2000);
  servo2.attach(15); //analog pin 1

  // init other ordinary digital outputs
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  readSerial();
}

void readSerial() {
  String command;
  String port;
  String operatorS;
  if (Serial.find("CMD")){
      delay(30);
      while (Serial.available() > 0) {
        char c = Serial.read();
        command += c;
      }
      operatorS = command.substring(OPERATOR_POS);
      port = command.substring(PORT_POS, PORT_POS + 1);
  }
  
  if (operatorS.startsWith(ON)) {
    digitalWrite(port.toInt(), HIGH);
    Serial.write("turned on port");
  } else if (operatorS.startsWith(OFF)) {
    digitalWrite(port.toInt(), LOW);
    Serial.write("turned off port");
  }/* else if (operatorS.startsWith(SERVO)) {
    digitalWrite(port.toInt(), HIGH);
    Serial.write("moved servo...");
  }*/
}

