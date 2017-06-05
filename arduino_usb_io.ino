#include <Servo.h>
#define COMMAND "CMD"
#define OUT "OUT"
#define SER "SER"
#define ON "ON"
#define OFF "OFF"
#define PORT_POS 3
#define TYPE_POS 0
#define PARAMETER_POS 4

int port;
int data;
int value;
int angle;   // variable to hold the angle for the servo motor

Servo servo1;
Servo servo2;

/*****************************************
 * Arduino IO interface for serial control
 */
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  // initialize servo outputs:
  servo1.attach(2); //analog pin 2
  servo2.attach(3); //analog pin 3

  // init other ordinary digital outputs
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void handleDigitalOutputCommand(String port, String parameter) {
  if (parameter.startsWith(ON)) {
    digitalWrite(port.toInt(), HIGH);
    Serial.write("turned on port");
  } else if (parameter.startsWith(OFF)) {
    digitalWrite(port.toInt(), LOW);
    Serial.write("turned off port");
  }
}

void handleServoCommand(String port, String parameter) {
  Servo s;
  if (port.equals("1")) {
    s = servo1;
  } else if (port.equals("2")) {
    s = servo2;
  }
  // todo implement range for servos that can be choosen from via port
  char degree = parameter.charAt(0);
  angle = map(degree, 0, 1023, 0, 179);
  s.write(angle);
  Serial.write("moved servo...");
}

void loop() {
  readSerial();
}

void readSerial() {
  String command;
  String port;
  String type;
  String parameter;
  
  if (Serial.find("CMD")){
      delay(30);
      while (Serial.available() > 0) {
        char c = Serial.read();
        command += c;
      }
      type = command.substring(TYPE_POS,3);
      port = command.substring(PORT_POS, PORT_POS + 1);
      parameter = command.substring(PARAMETER_POS);
  }

  if (type.equals(OUT)) {
    handleDigitalOutputCommand(port, parameter);
  } else if (type.equals(SER)) {
    handleServoCommand(port, parameter);
  }
}


