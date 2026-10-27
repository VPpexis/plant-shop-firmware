
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

const char *plantNames[15] =   {"Coreopsis",  "Baston ni San Jose", "Pacova"  ,   "Painter's palette"  ,  "Sago Palm"  ,  "Pinstripe Plant",  "Zebra Plant"  ,  "Dwarf Snake Plant"  ,  "Chinese evergreens"  ,  "Dumbcane"  ,  "Desert Rose"  ,  "Peace lily"  ,   "Mayana"  ,  "Spider Plant"  ,  "San Francisco"};
const int plantBCD[15] =     {75269394 ,  71894653  ,         81576943,   49253189          ,   69327159   ,  24869395        ,  34218957   ,    74196925           ,  76982413            ,   52841739 ,  47981536     ,  52637849   ,    31894275 , 94213875      ,  39751862};

//FIREBASE
#include "secrets.h"


String myString;
unsigned long items=0;
String chipid;
int randnum;
int counter;


void setup(){
  Serial.begin(115200); //CHANGE FROM 9600 to 115200
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

    if(check=='c'){
      for(int i=0;i<chipid.length()+1;i++){
        Serial.write(chipid[i]);     //Change Serial to MCU
        delay(10);
      }
    }else if (check == 'p') {
        Firebase.setInt(chipid+"/End",0);
    }else if (check == 'v') {
        Firebase.setInt(chipid+"/View/barcode_id",lastScanned.toInt());
        for (int i=0;i<15;i++) {
          if (plantBCD[i]==lastScanned.toInt()){
            Firebase.setString(chipid+"/View/plant_name",plantNames[i]);
            break;
          }
        }
        delay(8000);
        Firebase.setString(chipid+"/View","");
    }else{
      int j=0;
      lastScanned="";
      lastScanned=Serial.readString();
      Firebase.setString(chipid+"/RFID"+String(items++),String(check)+lastScanned);
      lastScanned = String(check) + lastScanned;
      if (Firebase.failed()) {
        //Serial.print("setting /number failed:");
        //Serial.println(Firebase.error());
      }
    }
  }
}
