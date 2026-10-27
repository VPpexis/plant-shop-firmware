
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
SoftwareSerial MCU (D5,D6);
String chipid;
int randnum;

//FIREBASE
#include "secrets.h"


String myString;
unsigned long items=0;

void setup(){
  Serial.begin(115200); //CHANGE FROM 9600 to 115200
  //MCU.begin(115200);  //CHANGE FROM 115200 to 9600
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  randnum = random(11111,99999);
  chipid = String(randnum);
  //Serial.println(chipid);
  //Serial.println();
  //Serial.print("connected: ");
  //Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(1000);
  Firebase.setString(chipid+"/Begin","0");
}
String lastScanned;  bool found;

void loop(){

  if (Serial.available()){           //Change MCU to Serial
    char check=Serial.read();        //Change Serial to MCU

    if(check=='c' ){
      for(int i=0;i<chipid.length()+1;i++){
        Serial.write(chipid[i]);     //Change Serial to MCU
        delay(10);
      }
    }else{
      int j=0;
      lastScanned="";
      lastScanned=Serial.readString();
      //Serial.println(lastScanned);

      Firebase.setString(chipid+"/RFID"+String(items++),String(check)+lastScanned);
      if (Firebase.failed()) {
        //Serial.print("setting /number failed:");
        //Serial.println(Firebase.error());
      }
    }
  }
}
