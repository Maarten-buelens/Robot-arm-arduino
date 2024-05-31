#include <math.h>
#include "SpeedyStepper.h"
#include <Servo.h>

Servo Gripper;

String SerialData = "";

constexpr unsigned long long hashS(const char *str, unsigned long long hash = 5381) {
  return !*str ? hash : hashS(str + 1, (hash * 33ULL) ^ *str);
}
// ######################################
#define enableVerbose false  // e.g: MoveDeg: moving motor base deg: 360.00
#define enableDebug false    // degToPulse:
// ######################################
#define powerPin 2
bool power = false;
// ######################################
#define limitSwitch1 4
#define limitSwitch2 5
#define limitSwitch3 6

// ######################################
float angle0 = 0.0;
float angle1 = 0.0;
float angle2 = 0.0;
float angle3 = 0.0;

// ######################################
#define Basedir 29   //pin
#define Basestep 28  //pin
#define Basepulley1Teeth 20.0
#define Basepulley2Teeth 218.34
#define BasePPR 6400  // pulses per rotation
#define BaseSpeed 7000
#define BaseAccel 4000

SpeedyStepper Basemotor;

float BasePosition = 0;
const float BaseRatio = Basepulley2Teeth / Basepulley1Teeth;
float BaseLimitpos;
float BaseLimitneg;
// ######################################
#define Arm1dir 23   //pin
#define Arm1step 22  //pin
#define Arm1pulley1Teeth 31.4
#define Arm1pulley2Teeth 113.0
#define Arm1PPR 25000  // pulses per rotation
#define Arm1Speed 10000
#define Arm1Accel 5000

SpeedyStepper Arm1motor;

const float Arm1Ratio = Arm1pulley2Teeth / Arm1pulley1Teeth;
float Arm1Limitpos;
float Arm1Limitneg;

// ######################################
#define Arm2dir1 27   //pin
#define Arm2step1 26  //pin
#define Arm2dir2 25   //pin
#define Arm2step2 24  //pin
#define Arm2pulley1Teeth 20.0
#define Arm2pulley2Teeth 113.8
#define Arm2PPR 6400  // pulses per rotation
#define Arm2Speed 6000
#define Arm2Accel 2500


SpeedyStepper Arm2motor1;
SpeedyStepper Arm2motor2;

const float Arm2Ratio = Arm2pulley2Teeth / Arm2pulley1Teeth;
float Arm2Limitpos;
float Arm2Limitneg;
// ######################################
#define Arm3dir 31   //pin
#define Arm3step 30  //pin
#define Arm3pulley1Teeth 20.0
#define Arm3pulley2Teeth 105.0
#define Arm3PPR 6400  // pulses per rotation
#define Arm3Speed 6000
#define Arm3Accel 2500

SpeedyStepper Arm3motor;

float Arm3Position = 0;  // degree position
const float Arm3Ratio = Arm3pulley2Teeth / Arm3pulley1Teeth;
float Arm3Limitpos;
float Arm3Limitneg;
// ######################################

void setup() {
  Serial.begin(19200);
  Serial.setTimeout(400);

  Serial1.begin(19200);
  Serial1.setTimeout(400);

  Serial2.begin(19200);
  Serial2.setTimeout(800);
  printStartup();

  Gripper.attach(9);

  setupSteppers();

  setPinModes();
  calcLimits();
}

void loop() {

  //local commands
  while (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    Serial.println("COMMAND: ");
    Serial.println(command);
    parseSerialCommand(command);
  }
  //SerialLocal();
  //esp communication
  while (Serial1.available() > 0) {
    SerialData = Serial1.readStringUntil('\n');
    parseEspCommand(SerialData);
    SerialData = "";
  }
  //SerialIK();

  //SerialAPI();
  while (Serial2.available()) {
    String command = Serial2.readStringUntil('\n');
    Serial.println("WEB COMMAND: ");
    Serial.println(command);
    parseSerialCommand(command);
  }
}
