/*void SerialLocal() {
  String SerialLocalBuff = "";
  bool term = false;
  while (Serial.available()) {
    delay(2);
    char c = Serial.read();
    if (c == '\n') {
      term = true;
      break;
    } else {
      SerialLocalBuff += c;
    }
  }
  if (SerialLocalBuff.length() > 0 && term == true) {
    parseSerialCommand(SerialLocalBuff);
  }
  SerialLocalBuff = "";
}

void SerialIK(){
  String SerialIKBuff = "";
  bool term = false;
  while (Serial1.available()) {
    delay(2);
    char c = Serial1.read();
    if (c == '\n') {
      term = true;
      break;
    } else {
      SerialLocalBuff += c;
    }
  }
  if (SerialIKBuff.length() > 0 && term == true) {
    parseEspCommand(SerialIKBuff);
  }
  SerialIKBuff = "";
}

void SerialAPI(){
  String SerialAPIBuff = "";
  bool term = false;
  while (Serial2.available()) {
    delay(2);
    char c = Serial2.read();
    if (c == '\n') {
      term = true;
      break;
    } else {
      SerialAPIBuff += c;
    }
  }
  if (SerialIKBuff.length() > 0 && term == true) {
    Serial.println("WEB COMMAND: ");
    Serial.println(SerialAPIBuff);
    parseSerialCommand(SerialAPIBuff);
  }
  SerialAPIBuff = "";
}*/