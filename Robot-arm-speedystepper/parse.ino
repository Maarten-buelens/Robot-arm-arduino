void parseSerialCommand(String command) {
  //vars
  int deg;
  float x;
  float y;

  float deg1;
  float deg2;
  float deg3;
  float deg0;

  float angle;
  String espcommand;
  String motor = "";

  float angleBase;
  float angleArm1;
  float angleArm2;
  float angleArm3;

  String response;
  command = command + "\n";

  String action = getValue(command, ';', 0);
  const char* actionChar = action.c_str();

  switch (hashS(actionChar)) {
    case hashS("deg"):
      motor = getValue(command, ';', 1);
      deg = getValue(command, ';', 2).toInt();

      MoveDeg(deg, motor);
      dualSerialPrint("DONE",true);
      break;

    // #############################################
    case hashS("move"):
      x = getValue(command, ';', 1).toFloat();
      y = getValue(command, ';', 2).toFloat();

      if (y < 0) {
        error("parseCommand move: INVALID Y");
      }

      debug("parseSerialCommand: sending calc request", 0);

      espcommand = "calc;" + String(x) + ";" + String(y);

      SendEspCommand(espcommand);
      moveSync(angle1, angle2, angle3, pulseToDeg(Basemotor.getCurrentPositionInSteps(),BaseRatio,BasePPR));
      dualSerialPrint("DONE",true);

      break;
    case hashS("sync"):
      deg1 = getValue(command, ';', 1).toFloat();
      deg2 = getValue(command, ';', 2).toFloat();
      deg3 = getValue(command, ';', 3).toFloat();
      deg0 = getValue(command, ';', 4).toFloat();

      moveSync(deg1, deg2, deg3, deg0);
      dualSerialPrint("DONE",true);
      break;
    // #############################################
    case hashS("inverse"):
      x = getValue(command, ';', 1).toFloat();
      y = getValue(command, ';', 2).toFloat();

      if (y < 0) {
        error("parseCommand move: INVALID Y");
      }

      debug("parseSerialCommand: sending calc request", 0);

      espcommand = "calc;" + String(x) + ";" + String(y);
      SendEspCommand(espcommand);

      if (not enableDebug) {
        SerialPrintVar("Angle1: ", angle1);
        SerialPrintVar("Angle2: ", angle2);
        SerialPrintVar("Angle3: ", angle3);
      }
      dualSerialPrint("DONE",true);
      break;
    case hashS("servo"):
      angle = getValue(command, ';', 1).toFloat();

      if (angle < 0) {
        error("parseCommand servo: INVALID ANGLE");
      }
      Gripper.write(angle);


      dualSerialPrint("DONE",true);
      break;
    case hashS("ip"):
      SendEspCommand("ip");
      dualSerialPrint("DONE",true);
      break;
    case hashS("angle"):
      angleBase = pulseToDeg(-Basemotor.getCurrentPositionInSteps(),BaseRatio,BasePPR);
      angleArm1 = pulseToDeg(-Arm1motor.getCurrentPositionInSteps(),Arm1Ratio,Arm1PPR);
      angleArm2 = pulseToDeg(-Arm2motor1.getCurrentPositionInSteps(),Arm2Ratio,Arm2PPR);
      angleArm3 = pulseToDeg(-Arm3motor.getCurrentPositionInSteps(),Arm3Ratio,Arm3PPR);
      response = "angles;" + String(angleBase) + ";"+ String(angleArm1) + ";"+ String(angleArm2)+ ";"+ String(angleArm3)+ ";";
      dualSerialPrint(response, false);
      dualSerialPrint("DONE",true);
      break;
    case hashS("OK"):
      dualSerialPrint("OK", false);
      dualSerialPrint("DONE",true);
      break;
    case hashS("calibrate"):
      Arm1motor.setCurrentPositionInSteps(0);
      Arm2motor1.setCurrentPositionInSteps(0);
      Arm2motor2.setCurrentPositionInSteps(0);
      Arm3motor.setCurrentPositionInSteps(0);
      dualSerialPrint("DONE",true);
      break;
    case hashS("power-off"):
      digitalWrite(powerPin, LOW);
      power = false;
      dualSerialPrint("DONE",true);
      break;
    case hashS("power-on"):
      digitalWrite(powerPin, HIGH);
      power = true;
      dualSerialPrint("DONE",true);
      break;
    case hashS("power-get"): 
      dualSerialPrint(String(power),false);
      dualSerialPrint("DONE",true);
      break;
    case hashS("limits"): 
      dualSerialPrint(String(digitalRead(limitSwitch1)),false);
      dualSerialPrint(String(digitalRead(limitSwitch2)),false);
      dualSerialPrint(String(digitalRead(limitSwitch3)),false);
      dualSerialPrint("DONE",true);
      break;
    case hashS("home"): 
      home();
      break;
    case hashS("full_help"):
      dualSerialPrint("full_help",true);
      Serial.println("########## FULL HELP ##########");
      Serial.println("deg: move motor by deg, deg;{motor};{deg};");
      Serial.println("servo: move gripper to deg, servo;{deg};");
      Serial.println("sync: move all motors by deg, sync;{arm1};{arm2};{arm3};");
      Serial.println("move: move motor to xy, move;{x};{y};");
      Serial.println("inverse: runs only inverse kinematics, inverse;{x};{y};");
      Serial.println("calibrate: resets all positions , calibrate;");
      Serial.println("########## FULL HELP ##########");
      dualSerialPrint("DONE",true);
      break;

    default:
      dualSerialPrint("help",true);
      Serial.println("########## HELP ##########");
      Serial.println("COMMANDS MUST END WITH ';'");
      Serial.println("COMMANDS: ");
      Serial.println("deg;{motor};{deg};");
      Serial.println("servo;{deg};");
      Serial.println("sync;{arm1};{arm2};{arm3};");
      Serial.println("move;{x};{y};");
      Serial.println("inverse;{x};{y};");
      Serial.println("calibrate;");
      Serial.println("For more help run 'full_help'");
      Serial.println("########## HELP ##########");
      dualSerialPrint("DONE",true);
      break;
  }
}