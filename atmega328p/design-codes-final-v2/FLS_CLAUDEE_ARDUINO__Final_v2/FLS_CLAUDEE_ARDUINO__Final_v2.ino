#include <SoftwareSerial.h>
#include<String.h>
SoftwareSerial MCU (5,6); // RX, TX
#include <LiquidCrystal_I2C.h>
//#include <LiquidCrystal.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x3F for a 16 chars and 2 line display

const char *const plantNames[15] =   {"Coreopsis",  "Baston ni San Jose", "Pacova"  ,   "Painter's palette"  ,  "Sago Palm"  ,  "Pinstripe Plant",  "Zebra Plant"  ,  "Dwarf Snake Plant"  ,  "Chinese evergreens"  ,  "Dumbcane"  ,  "Desert Rose"  ,  "Peace lily"  ,   "Mayana"  ,  "Spider Plant"  ,  "San Francisco"};
const char *const plantBCD[15] =     {"75269394" ,  "71894653"  ,         "81576943",   "49253189"          ,   "69327159"   ,  "24869395"        ,  "34218957"   ,    "74196925"           ,  "76982413"            ,   "52841739" ,  "47981536"     ,  "52637849"   ,    "31894275" , "94213875"      ,  "39751862"};
const char *const care[15] =         { "LOW"    ,   "LOW"    ,            "MEDIUM"   ,  "LOW"    ,              "LOW"   ,       "HIGH"   ,          "LOW"   ,         "LOW"   ,               "LOW"    ,                "MEDIUM" ,    "LOW"    ,        "MEDIUM"     ,    "LOW"    ,   "LOW"   ,          "MEDIUM"};
const char *const sunlight[15] =     { "HIGH"   ,   "LOW"    ,            "LOW"    ,    "LOW"    ,              "LOW"   ,       "LOW"   ,           "LOW"   ,         "LOW"   ,               "LOW"    ,                "LOW"     ,   "LOW"    ,        "HIGH"     ,      "LOW"    ,   "LOW"   ,          "LOW"};
const char *const water[15] =        { "LOW"    ,   "LOW"    ,            "MEDIUM"  ,   "LOW"    ,              "MEDIUM"   ,    "MEDIUM"   ,        "LOW"   ,         "LOW"   ,               "MEDIUM"    ,             "MEDIUM"     ,"MEDIUM"    ,     "MEDIUM"     ,    "MEDIUM"   , "MEDIUM"   ,       "MEDIUM"};

//#define ADD 4
//#define REMOVE 5
//#define PROCCESS 6
const int in1 = 2;
const int in2 = 3;
const int in3 = 4;

void setup() {
  MCU.begin(9600);
  Serial.begin(115200);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(in3, INPUT);
  delay(1000);
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

String BCD;
String lastScanned;
bool found;
char ABC[10];
char AB[10];

void loop() {
  if (atoi(AB)==0){
    delay(10000);
    Serial.write('c');
    delay(500);
  }

  if(Serial.available()){
   int j=0;
    while (Serial.available()){
      char input = Serial.read();
      delay(5);
      AB[j]=input;
      j++;
    }
    Menue();
    delay(1000);
  }

  if (digitalRead(in3) == LOW && digitalRead(in2) == LOW && digitalRead(in1) == HIGH){    //<<== Change to in3=false  , in2=false, in1=true  FOR PAYMENT PROCESS
    Serial.write('p');
    delay(500);
    //while (digitalRead(in3) == LOW && digitalRead(in2) == LOW && digitalRead(in1) == HIGH); //<<== Change to in3=false  , in2=false, in1=true  FOR PAYMENT PROCESS
  }

  if (digitalRead(in3) == HIGH && digitalRead(in2) == LOW && digitalRead(in1) == LOW){    //<<== Change to in3=falsee  , in2=false, in1=true  FOR VIEW PROCESS
    for (int i=0;i<15;i++){
      if (atoi(plantBCD[i])==atoi(ABC)){
        Serial.write('v');
        found=true;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(plantNames[i]);
        lcd.setCursor(0,1);
        lcd.print("care: ");
        lcd.print(care[i]);
        lcd.setCursor(0,2);
        lcd.print("sunlight: ");
        lcd.print(sunlight[i]);
        lcd.setCursor(0,3);
        lcd.print("Water: ");
        lcd.print(water[i]);

        delay(10);
      }
    }
        delay(2000);
        Menue();
  }

  ////////////WHEN BARCODED IS SCANNED/////////////
  if (MCU.available()){
    int j=0;
    lastScanned="";
    while (MCU.available()){
      char input = MCU.read();
      delay(5);
      ABC[j]=input;
      j++;
    }

    for(int i=0;i<8;i++)lastScanned[i]=ABC[i];
    found=false;

    //////////////DISPLAYS SCANNED PLANT///////////////
    for (int i=0;i<15;i++){
      if (atoi(plantBCD[i])==atoi(ABC)){
        found=true;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(plantNames[i]);
        lcd.setCursor(0,1);
        lcd.print("care: ");
        lcd.print(care[i]);
        lcd.setCursor(0,2);
        lcd.print("sunlight: ");
        lcd.print(sunlight[i]);
        lcd.setCursor(0,3);
        lcd.print("Water: ");
        lcd.print(water[i]);
        delay(10);
      }
    }

    /////////////IF SCANNED BARCODE IS NOT FOUND///////////////////
    if (!found){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Plant not Registed");
      lcd.setCursor(0,1);
      lcd.print("with this Barcode");
      lcd.setCursor(0,2);
      lcd.print(lastScanned);
      delay(2000);
      Menue();
    }


    ////////////IF SCANNED BARCODE IS FOUND////////////////////
    if (found){
      unsigned long timerr=millis();
      while(millis()-timerr<5000){
        //////////////WHEN ADD IS PRESSED////////////////////
        if (digitalRead(in3) == LOW && digitalRead(in2) == HIGH && digitalRead(in1) == HIGH){     //<<== Change to in3=false  , in2=true, in1=true  FOR ADD PROCESS
          for(int i=0;i<8;i++){
            Serial.write(ABC[i]);
        }
         delay(2000);
         while (digitalRead(in3) == LOW && digitalRead(in2) == HIGH && digitalRead(in1) == HIGH);     //<<== Change to in3=false  , in2=true, in1=true  FOR ADD PROCESS
         }
         ////////////WHEN REMOVE IS PRESSED//////////////////
         if (digitalRead(in3) == LOW && digitalRead(in2) == HIGH && digitalRead(in1) == LOW){     //<<== Change to in3=false  , in2=true, in1=false  FOR REMOVE PROCESS
          char str[]="remove";
          for(int i=0;i<6;i++){
            Serial.write(str[i]);
          }
        while (digitalRead(in3) == LOW && digitalRead(in2) == HIGH && digitalRead(in1) == LOW);   //<<== Change to in3=false  , in2=true, in1=false  FOR REMOVE PROCESS
        }
      }
    Menue();
    }
  }
}

void showInfo(){
  found=false;
  for (int i=0;i<15;i++){
    if (String(ABC)==plantBCD[i]){
      found=true;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(plantNames[i]);
      lcd.setCursor(0,1);
      lcd.print("care: ");
      lcd.print(care[i]);
      lcd.setCursor(0,2);
      lcd.print("sunlight: ");
      lcd.print(sunlight[i]);
      lcd.setCursor(0,3);
      lcd.print("Water: ");
      lcd.print(water[i]);
      delay(10);
    }
  }

  if (!found){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plant not Registed");
    lcd.setCursor(0,1);
    lcd.print("with this Barcode");
    lcd.setCursor(0,2);
    delay(2000);
    Menue();
  }
}

void Menue(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Cart ID: ");
  lcd.setCursor(9,0);
  lcd.print(AB);
  lcd.setCursor(0,2);
  lcd.print("   Scan the plant");
}
