void setPinModes() {

  pinMode(powerPin, OUTPUT);

  pinMode(limitSwitch1, INPUT_PULLUP);
  pinMode(limitSwitch2, INPUT_PULLUP);
  pinMode(limitSwitch3, INPUT_PULLUP);
}

void calcLimits() {
  BaseLimitpos = degToPulse(170.0, BaseRatio, BasePPR);
  BaseLimitneg = -BaseLimitpos;
  Arm1Limitpos = degToPulse(90.0, Arm1Ratio, Arm1PPR);
  Arm1Limitneg = -Arm1Limitpos;
  Arm2Limitpos = degToPulse(90.0, Arm2Ratio, Arm2PPR);
  Arm2Limitneg = -Arm2Limitpos;
  Arm3Limitpos = degToPulse(90.0, Arm3Ratio, Arm3PPR);
  Arm3Limitneg = -Arm3Limitpos;
}

void setupSteppers() {
  Basemotor.connectToPins(Basestep, Basedir);
  Basemotor.setSpeedInStepsPerSecond(BaseSpeed);
  Basemotor.setAccelerationInStepsPerSecondPerSecond(BaseAccel);

  Arm1motor.connectToPins(Arm1step, Arm1dir);
  Arm1motor.setSpeedInStepsPerSecond(Arm1Speed);
  Arm1motor.setAccelerationInStepsPerSecondPerSecond(Arm1Accel);

  Arm2motor1.connectToPins(Arm2step1, Arm2dir1);
  Arm2motor2.connectToPins(Arm2step2, Arm2dir2);
  Arm2motor1.setSpeedInStepsPerSecond(Arm2Speed);
  Arm2motor2.setSpeedInStepsPerSecond(Arm2Speed);
  Arm2motor1.setAccelerationInStepsPerSecondPerSecond(Arm2Accel);
  Arm2motor2.setAccelerationInStepsPerSecondPerSecond(Arm2Accel);

  Arm3motor.connectToPins(Arm3step, Arm3dir);
  Arm3motor.setSpeedInStepsPerSecond(Arm3Speed);
  Arm3motor.setAccelerationInStepsPerSecondPerSecond(Arm3Accel);
}


void printStartup() {
  Serial.println("##     ## ########             ###    ########  ##     ## ");
  Serial.println("###   ### ##     ##           ## ##   ##     ## ###   ### ");
  Serial.println("#### #### ##     ##          ##   ##  ##     ## #### #### ");
  Serial.println("## ### ## ########  ####### ##     ## ########  ## ### ## ");
  Serial.println("##     ## ##     ##         ######### ##   ##   ##     ## ");
  Serial.println("##     ## ##     ##         ##     ## ##    ##  ##     ## ");
  Serial.println("##     ## ########          ##     ## ##     ## ##     ## ");


  Serial.println("READY, ENTER COMMAND OR HELP.");
}
