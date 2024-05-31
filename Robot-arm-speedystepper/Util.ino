template<class T> void SerialPrintVar(String text, T var) {
  Serial.print(text);
  Serial.println(var);

  Serial2.write(text.c_str());
  Serial2.write(String(var).c_str());
  Serial2.write("\n");
}

void error(String message) {
  Serial.println("FATAL ERROR " + message);
  Serial.println("PLEASE RESET");
  digitalWrite(powerPin, LOW);
  power = false;
  while (true) {
    delay(25);
  }
}
void verbose(String message, long var) {
  if (enableVerbose) {
    SerialPrintVar(message, var);
    Serial2.write(message.c_str());
    Serial2.write(String(var).c_str());
    Serial2.write("\n");
  }
}

template<class T> void debug(String message, T var) {
  if (enableDebug) {
    SerialPrintVar(message, var);
    Serial2.write(message.c_str());
    Serial2.write(String(var).c_str());
    Serial2.write("\n");
  }
}

void dualSerialPrint(String message, bool end) {
  Serial.println(message);
  Serial2.write(message.c_str());
  if (end) {
    Serial2.write("\n");
  }
}

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
