
#include <ESP8266WiFi.h>
//#include <FirebaseArduino.h>
//#include <ArduinoJson.h>
//#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
SoftwareSerial MCU (D5,D6);
String chipid;
int randnum;

const String barcode_id[15] = {"75269394" ,  "71894653"  ,         "81576943",   "49253189"          ,   "69327159"   ,  "24869395"        ,  "34218957"   ,    "74196925"           ,  "76982413"            ,   "52841739" ,  "47981536"     ,  "52637849"   ,    "31894275" , "94213875"      ,  "39751862"};
const String plantname[15] =  {"Coreopsis",  "Baston ni San Jose", "Pacova"  ,   "Painter's palette"  ,  "Sago Palm"  ,  "Pinstripe Plant",  "Zebra Plant"  ,  "Dwarf Snake Plant"  ,  "Chinese evergreens"  ,  "Dumbcane"  ,  "Desert Rose"  ,  "Peace lily"  ,   "Mayana"  ,  "Spider Plant"  ,  "San Francisco"};

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

#include "secrets.h"



//Variable Declaration
String myString;
unsigned long items=0;
unsigned long sendDataPrevMillis = 0;
unsigned long lastTime = 0;
int count = 0;
bool signupOK = false;
char check;
String lastScanned;
bool found;


void setup(){
  Serial.begin(115200); //CHANGE FROM 9600 to 115200

  //WIFI SETUP
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  randnum = random(11111,99999);
  chipid = String(randnum);

  config.database_url = DATABASE_URL;
  config.api_key = API_KEY;
  config.service_account.data.client_email = FIREBASE_CLIENT_EMAIL;
  config.service_account.data.project_id = FIREBASE_CLIENT_PROJECT_ID;
  config.service_account.data.private_key = PRIVATE_KEY;

  //Firebase.signUp(&config, &auth);

  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    Firebase.RTDB.setInt(&fbdo, chipid+"/Begin", 0);
  }

}

void loop(){
  if (Serial.available()){           //Change MCU to Serial
    char check=Serial.read();        //Change Serial to MCU

    if(check=='c'){
      for(int i=0;i<chipid.length()+1;i++){
        Serial.write(chipid[i]);     //Change Serial to MCU
        delay(10);
      }
    }else if (check == 'v'){
      //Insert FCM
      if (Firebase.ready() && signupOK &&(millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
        lastTime = millis();
        sendViewEvent();
      }
    }else if (check == 'p'){
      //Insert FCM
      if (Firebase.ready() && signupOK &&(millis() - sendDataPrevMillis > 1500 || sendDataPrevMillis == 0)) {
        lastTime = millis ();
        sendPayEvent();
      }
    }else{
      int j=0;
      lastScanned="";
      lastScanned=Serial.readString();
      if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1500 || sendDataPrevMillis == 0)){
        lastTime = millis ();
        Firebase.RTDB.setInt(&fbdo, chipid+"/PlantID"+String(items++), String(check) + lastScanned);
      }
    }
  }
}

void sendViewEvent(){
  FCM_HTTPv1_JSON_Message msg;
  msg.token = DEVICE_REGISTRATION_ID_TOKEN;

  msg.notification.body = "Notification body";
  msg.notification.title = "Notification title";

  FirebaseJson payload;

  payload.add("cart_id", "chipid");
  payload.add("state", "view");
  msg.data = payload.raw();
  Firebase.FCM.send(&fbdo, &msg);
}

void sendPayEvent(){
  FCM_HTTPv1_JSON_Message msg;
  msg.token = DEVICE_REGISTRATION_ID_TOKEN;

  msg.notification.body = "Notification body";
  msg.notification.title = "Notification title";

  FirebaseJson payload;

  payload.add("barcode_id", "String(check) + lastScanned");
  payload.add("state", "view");
  msg.data = payload.raw ();
  Firebase.FCM.send(&fbdo, &msg);
}
