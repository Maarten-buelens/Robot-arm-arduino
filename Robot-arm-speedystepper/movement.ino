void step(int pin, int speed) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(speed);
  digitalWrite(pin, LOW);
  delayMicroseconds(speed);
}

void MoveDeg(float deg, String motor) {
  int dir = 2;
  float position;
  if (deg > 0) {
    dir = 1;
  } else {
    dir = 0;
  }
  debug("MoveDeg dir: ", dir);
  if (dir != 0 && dir != 1) {
    error("MoveDeg: INVALID DIR");
  }

  deg = abs(round(deg));

  if (motor == "base") {

    verbose("MoveDeg: moving motor base deg: ", deg);
    long steps = degToPulse(deg, BaseRatio, BasePPR);

    switch (checkLimit(BasePosition, BaseLimitpos, BaseLimitneg)) {
      case 0:
        if (dir == 0) {
          Basemotor.moveRelativeInSteps(-steps);
        } else {
          Basemotor.moveRelativeInSteps(steps);
        }
        break;
      case 1:
        //BasePosition = BaseLimitpos;
        break;
      case 2:
        //BasePosition = BaseLimitneg;
        break;
    }

    verbose("MoveDeg: moved motor base deg: ", deg);
    // ######################################
  } else if (motor == "arm1") {
    verbose("MoveDeg: moving motor arm1 deg: ", deg);
    long steps = degToPulse(deg, Arm1Ratio, Arm1PPR);

    if (dir == 0) {
      position = Arm1motor.getCurrentPositionInSteps() - steps;
    } else {
      position = Arm1motor.getCurrentPositionInSteps() + steps;
    }
    switch (checkLimit(position, Arm1Limitpos, Arm1Limitneg)) {
      case 0:
        if (dir == 0) {
          Arm1motor.moveRelativeInSteps(-steps);
        } else {
          Arm1motor.moveRelativeInSteps(steps);
        }
        break;
      case 1:

        break;
      case 2:

        break;
    }

    verbose("MoveDeg: moved motor Arm1 deg: ", deg);
  } else if (motor == "arm2") {
    verbose("MoveDeg: moving motor arm2 deg: ", deg);
    long steps = degToPulse(deg, Arm2Ratio, Arm2PPR);
    if (dir == 0) {
      position = Arm2motor1.getCurrentPositionInSteps() + steps;
    } else {
      position = Arm2motor1.getCurrentPositionInSteps() - steps;
    }

    switch (checkLimit(position, Arm2Limitpos, Arm2Limitneg)) {
      case 0:
        if (dir == 0) {
          Arm2motor1.setupRelativeMoveInSteps(-steps);
          Arm2motor2.setupRelativeMoveInSteps(steps);
        } else {
          Arm2motor1.setupRelativeMoveInSteps(steps);
          Arm2motor2.setupRelativeMoveInSteps(-steps);
        }
        while (!Arm2motor1.motionComplete() || !Arm2motor2.motionComplete()) {
          Arm2motor1.processMovement();
          Arm2motor2.processMovement();
        }
        break;
      case 1:

        break;
      case 2:

        break;
    }

    verbose("MoveDeg: moved motor Arm2 deg: ", deg);
  } else if (motor == "arm3") {
    verbose("MoveDeg: moving motor Arm3 deg: ", deg);
    long steps = degToPulse(deg, Arm3Ratio, Arm3PPR);
    if (dir == 0) {
      position = Arm3motor.getCurrentPositionInSteps() - steps;
    } else {
      position = Arm3motor.getCurrentPositionInSteps() + steps;
    }

    switch (checkLimit(position, Arm3Limitpos, Arm3Limitneg)) {
      case 0:
        if (dir == 0) {
          Arm3motor.moveRelativeInSteps(-steps);
        } else {
          Arm3motor.moveRelativeInSteps(steps);
        }
        break;
      case 1:
        break;
      case 2:
        break;
    }




    verbose("MoveDeg: moved motor Arm3 deg: ", deg);
  } else {
    error("MoveDeg: INVALID MOTOR");
  }
}


void moveSync(float arm1, float arm2, float arm3, float base) {
  float deg = 0;
  int dir = 2;
  float steps = 0;
  //########## BASE ##########
  if (base > 0) {
    dir = 1;
  } else {
    dir = 0;
  }
  base = abs(round(base));
  steps = degToPulse(base, BaseRatio, BasePPR);

  switch (checkLimit(Basemotor.getCurrentPositionInSteps(), BaseLimitpos, BaseLimitneg)) {
    case 0:
      if (dir == 0) {
        Basemotor.setupMoveInSteps(-steps);
      } else {
        Basemotor.setupMoveInSteps(steps);
      }
      break;
  }
  //########## ARM1 ##########
  if (arm1 > 0) {
    dir = 1;
  } else {
    dir = 0;
  }
  arm1 = abs(round(arm1));
  steps = degToPulse(arm1, Arm1Ratio, Arm1PPR);


  switch (checkLimit(Arm1motor.getCurrentPositionInSteps(), Arm1Limitpos, Arm1Limitneg)) {
    case 0:
      if (dir == 0) {
        Arm1motor.setupMoveInSteps(steps);
      } else {
        Arm1motor.setupMoveInSteps(-steps);
      }
      break;
  }
  //########## ARM2 ##########
  if (arm2 > 0) {
    dir = 1;
  } else {
    dir = 0;
  }
  arm2 = abs(round(arm2));
  steps = degToPulse(arm2, Arm2Ratio, Arm2PPR);

  switch (checkLimit(Arm2motor2.getCurrentPositionInSteps(), Arm2Limitpos, Arm2Limitneg)) {
    case 0:
      if (dir == 0) {
        Arm2motor1.setupMoveInSteps(steps);
        Arm2motor2.setupMoveInSteps(-steps);
      } else {
        Arm2motor1.setupMoveInSteps(-steps);
        Arm2motor2.setupMoveInSteps(steps);
      }
      break;
  }
  //########## ARM3 ##########
  if (arm3 > 0) {
    dir = 1;
  } else {
    dir = 0;
  }
  arm3 = abs(round(arm3));
  steps = degToPulse(arm3, Arm3Ratio, Arm3PPR);

  switch (checkLimit(Arm3motor.getCurrentPositionInSteps(), Arm3Limitpos, Arm3Limitneg)) {
    case 0:
      if (dir == 0) {
        Arm3motor.setupMoveInSteps(steps);
      } else {
        Arm3motor.setupMoveInSteps(-steps);
      }
      break;
  }
  //########## MOVE ##########

  while (!Basemotor.motionComplete() || !Arm1motor.motionComplete() || !Arm2motor1.motionComplete() || !Arm2motor2.motionComplete() || !Arm3motor.motionComplete()) {
    Basemotor.processMovement();
    Arm1motor.processMovement();
    Arm2motor1.processMovement();
    Arm2motor2.processMovement();
    Arm3motor.processMovement();
  }
}

void home() {
  bool result;
  dualSerialPrint("HOME: Starting arm3",false);
  result = Arm3motor.moveToHomeInSteps(1, Arm3Speed / 2, degToPulse(180, Arm3Ratio, Arm3PPR), limitSwitch3);
  if (result == false) {
    error("HOME: ERROR HOMING ARM1");
  }
  Arm3motor.setCurrentPositionInSteps(degToPulse(90, Arm3Ratio, Arm3PPR));
  dualSerialPrint("HOME: arm3 DONE",false);

  dualSerialPrint("HOME: Starting arm2",false);
  result = Arm2Home(1, Arm2Speed / 2, degToPulse(250, Arm2Ratio, Arm2PPR), limitSwitch2);
  if (result == false) {
    error("HOME: ERROR HOMING ARM2");
  }
  Arm2motor1.setCurrentPositionInSteps(degToPulse(90, Arm2Ratio, Arm2PPR));
  Arm2motor2.setCurrentPositionInSteps(-degToPulse(90, Arm2Ratio, Arm2PPR));
  dualSerialPrint("HOME: arm2 DONE",false);

  dualSerialPrint("HOME: Starting arm1",false);
  result = Arm1motor.moveToHomeInSteps(-1, Arm1Speed / 4, degToPulse(180, Arm1Ratio, Arm1PPR), limitSwitch1);
  if (result == false) {
    error("HOME: ERROR HOMING ARM1");
  }
  Arm1motor.setCurrentPositionInSteps(-degToPulse(90, Arm1Ratio, Arm1PPR));
  dualSerialPrint("HOME: DONE HOMING",false);
}