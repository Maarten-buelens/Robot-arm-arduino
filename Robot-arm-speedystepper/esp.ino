void parseEspCommand(String SerialData) {
  if (SerialData != "") {
    String action = getValue(SerialData, ';', 0);

    if (action == "ip") {
      String ip = getValue(SerialData, ';', 1);
      SerialPrintVar("ESP IP: ", ip);
    }
    else if (action == "response") {
      String angle1Check = getValue(SerialData, ';', 1);
      if (angle1Check == "INVALID") {
        error("parseEspCommand: INVALID RETURN FROM CALC");
      } else {
        angle1 = angle1Check.toFloat();
      }
      angle2 = getValue(SerialData, ';', 2).toFloat();
      angle3 = getValue(SerialData, ';', 3).toFloat();
      debug("angle1: ", angle1);
      debug("angle2: ", angle2);
      debug("angle3: ", angle3);
    }
  }
}


void SendEspCommand(String command) {
  Serial1.write(command.c_str());
  boolean done = false;
  long previous = millis();
  int timeout = 10000;
  
  do {
    while (Serial1.available() > 0) {
      SerialData = Serial1.readString();
      debug(SerialData,0);
    }
    if (SerialData != "") {
      parseEspCommand(SerialData);
      SerialData = "";
      done = true;
      break;
    }
  } while ((millis() - previous) < timeout);
  if (not done) {
    error("SendEspCommand: RESPONSE TIMOUT ESP");
  }
}