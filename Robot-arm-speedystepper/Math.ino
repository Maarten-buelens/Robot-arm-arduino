/*float CalcRatio(float pulley1,float pulley2){
  return pulley2/pulley1;
}*/

float degToPulse(float deg, float ratio, float PPR){
  // 1 PPR = 360 deg pulley1
  // 1 PPR * ratio = 360 deg pulley 2
  // (PPR * ratio) / 360 = 1 deg pulley 2
  // ((PPR * ratio) / 360) * deg = desired deg pulley 2

  float result = ((PPR / 360.0)* ratio) * deg;
  debug("degToPulse pulses: ", result);
  if(result < 0){
    error("degToPulse: INVALID CALC PULSE NEG");
  }
  return result;
}

float pulseToDeg(float pulses, float ratio, float PPR){
  // 1 PPR = 360 deg pulley1
  // 1 PPR * ratio = 360 deg pulley 2
  // (PPR * ratio) / 360 = 1 deg pulley 2

  float result = (pulses/ (PPR*ratio)) * 360 ;
  debug("Pulsestodeg deg: ", result);

  return result;

}

int checkLimit(float position, float posLimit, float negLimit){
  debug("checkLimit position", position);
  if(position > posLimit){
    SerialPrintVar("checkLimit: OUTSIDE pos LIMIT position:", position);
    return 1;
  }
  else if (position < negLimit) {
    SerialPrintVar("checkLimit: OUTSIDE neg LIMIT position:", position);
    return 2;
  }
  return 0;
}