#include <ArduinoEigen.h>
#include <ArduinoEigenDense.h>
#include <ArduinoEigenSparse.h>
#include <cmath>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define resetPin 16

SoftwareSerial ik(2, 0);
SoftwareSerial api(5, 4);

ESP8266WebServer server(80);
const char* ssid = "robot-arm";
const char* password = "mbisthebest";
int timeout = 8000;
long previous;
long start;

DynamicJsonDocument doc(2048);

using namespace Eigen;
using namespace std;
typedef Matrix<float, 2, 1> Vector2f;
typedef Matrix<float, 3, 1> Vector3f;

String SerialData = "";
String command;

String angle1 = "";
String angle2 = "";
String angle3 = "";

const float l1 = 19.2;  // Length of the first segment
const float l2 = 18.0;  // Length of the second segment
const float l3 = 16.0;  // Length of the third segment

void setup() {
  Serial.begin(9600);
  ik.begin(19200);
  api.begin(19200);
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, HIGH);
  WiFi.softAP(ssid, password);

  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());  //Print the local IP
  setupRoutes();
  server.begin(); //Start the server
}

void loop() {
  while (ik.available() > 0) {
    SerialData = ik.readStringUntil('\n');
    if(SerialData != ""){
      String action = getValue(SerialData,';',0);
      Serial.println(action);

      if(action == "calc"){
        Serial.println("Running Calc:");
      float x = getValue(SerialData,';',1).toFloat();
      float y = getValue(SerialData,';',2).toFloat();
      SerialData = "";
      String data = calc(x,y);
      Serial.print("Result: ");
      Serial.println(data);
      ik.write(data.c_str());
      } else if(action == "ip"){
        Serial.println("IP request");
        String ip = IpAddress2String(WiFi.localIP());
        String response = "ip;" + ip + ";";
        Serial.println(response);
        ik.write(response.c_str());
        ik.write("\n");
      }
    }
  }
  server.handleClient();
}
