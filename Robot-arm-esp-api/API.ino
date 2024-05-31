void setupRoutes() {
  server.on("/", sendIndex);
  server.on("/command", handleCommand);
  server.on("/discovery", handleDiscovery);
  server.onNotFound(handleNotFound);
}

void sendHeaders() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");
  
}

void handleNotFound() {
  server.send(404, "text/plain", "Not Found");
}

void handleDiscovery(){
  sendHeaders();
  server.send(200, "text/plain", "robot-arm");
}

void sendIndex() {
  server.send(200, "text/html", getWebpage());
}


void handleCommand() {  //Handler for the body path
  Serial.println("Request made");
  
  
  if (server.hasArg("plain") == false) {  //Check if body received
  sendHeaders();
    server.send(200, "text/plain", "Body not received");
    return;
  }
  clearSerialBuffer();
  DeserializationError error = deserializeJson(doc, server.arg("plain"));
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  String command = doc["command"];

  Serial.print("Commannd: ");
  command = String(command);

  if(command == "reset"){
    Serial.println("resetting arduino");
    digitalWrite(resetPin, LOW);
    delay(300);
    digitalWrite(resetPin, HIGH);

    delay(500);
    sendHeaders();
    server.send(200, "text/plain", "reset");
    return;
  }

  Serial.println(String(command));
  api.write(command.c_str());
  api.write("\n");
  start = millis();
  SerialData = "";
  do {
    while (api.available() > 0) {
      SerialData += api.readStringUntil('\n');
    }
    if (SerialData != "") {
      sendHeaders();
      server.send(200, "text/plain", SerialData);
      break;
    }
  } while ((millis() - start) < timeout);
}
