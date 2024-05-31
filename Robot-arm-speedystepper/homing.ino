bool Arm2Home(long directionTowardHome,
              float speedInStepsPerSecond, long maxDistanceToMoveInSteps, int homeLimitSwitchPin) {
  float originalDesiredSpeed_InStepsPerSecond;
  bool limitSwitchFlag;


  //
  // setup the home switch input pin
  //
  pinMode(homeLimitSwitchPin, INPUT_PULLUP);


  //
  // remember the current speed setting
  //



  //
  // if the home switch is not already set, move toward it
  //
  if (digitalRead(homeLimitSwitchPin) == HIGH) {
    //
    // move toward the home switch
    //
    Arm2motor1.setSpeedInStepsPerSecond(speedInStepsPerSecond);
    Arm2motor1.setupRelativeMoveInSteps(maxDistanceToMoveInSteps * directionTowardHome);

    Arm2motor2.setSpeedInStepsPerSecond(speedInStepsPerSecond);
    Arm2motor2.setupRelativeMoveInSteps(maxDistanceToMoveInSteps * directionTowardHome * -1);
    limitSwitchFlag = false;


    while (!Arm2motor1.motionComplete() || !Arm2motor2.motionComplete()) {
      Arm2motor1.processMovement();
      Arm2motor2.processMovement();
      if (digitalRead(homeLimitSwitchPin) == LOW) {
        limitSwitchFlag = true;
        break;
      }
    }

    //
    // check if switch never detected
    //
    if (limitSwitchFlag == false)
      return (false);
  }
  delay(25);


  //
  // the switch has been detected, now move away from the switch
  //
  Arm2motor1.setupRelativeMoveInSteps(maxDistanceToMoveInSteps * directionTowardHome * -1);

  Arm2motor2.setupRelativeMoveInSteps(maxDistanceToMoveInSteps * directionTowardHome);
  limitSwitchFlag = false;
  while (!Arm2motor1.motionComplete() || !Arm2motor2.motionComplete()) {
    Arm2motor1.processMovement();
    Arm2motor2.processMovement();
    if (digitalRead(homeLimitSwitchPin) == HIGH) {
      limitSwitchFlag = true;
      break;
    }
  }
  delay(25);

  //
  // check if switch never detected
  //
  if (limitSwitchFlag == false)
    return (false);


  //
  // have now moved off the switch, move toward it again but slower
  //
  Arm2motor1.setSpeedInStepsPerSecond(speedInStepsPerSecond / 8);
  Arm2motor1.setupRelativeMoveInSteps(maxDistanceToMoveInSteps * directionTowardHome);

  Arm2motor2.setSpeedInStepsPerSecond(speedInStepsPerSecond / 8);
  Arm2motor2.setupRelativeMoveInSteps(maxDistanceToMoveInSteps * directionTowardHome * -1);
  limitSwitchFlag = false;
  while (!Arm2motor1.motionComplete() || !Arm2motor2.motionComplete()) {
    Arm2motor1.processMovement();
    Arm2motor2.processMovement();
    if (digitalRead(homeLimitSwitchPin) == LOW) {
      limitSwitchFlag = true;
      break;
    }
  }
  delay(25);

  //
  // check if switch never detected
  //
  if (limitSwitchFlag == false)
    return (false);


  //
  // successfully homed, set the current position to 0
  //


  //
  // restore original velocity
  //
  Arm2motor1.setSpeedInStepsPerSecond(Arm2Speed);
  Arm2motor2.setSpeedInStepsPerSecond(Arm2Speed);
  return (true);
}