#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd (0x27, 20, 4);
int inPin01 = 4;
int inPin02 = 5;
int inPin03 = 6;
bool init_genCartNo = false;
int CartNo;
int var01 = 0;
int var02 = 0;
int var03 = 0;

void disp_cartno();


void setup() {
  //LCD Initialization
  lcd.begin();
  lcd.backlight();

  //Pin Initialization
  pinMode(inPin01, INPUT);
  pinMode(inPin02, INPUT);
  pinMode(inPin03, INPUT);
  Serial.begin(9600);

}



void loop() {
  while (var03 == 0 and var02 == 0 and var01 == 0){
    //Checks for any input
    disp_cartno();
    for (int i = 0; i <= 5; i++){
      var01 = digitalRead(inPin01);
      var02 = digitalRead(inPin03);
      var03 = digitalRead(inPin03);
      delay(1000);
      Serial.println(var01);
      Serial.println(var02);
      Serial.println(var03);
      Serial.println();
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Main Menu");
  delay(1000);

  var01 = digitalRead(inPin01);
  var02 = digitalRead(inPin02);
  var03 = digitalRead(inPin03);

  //Checks the input from the button encoder.
  if (var03 == 0 && var02 == 0 && var01 == 1){
  }else if (var03 == 0 && var02 == 1 && var01 == 0){
  }else if (var03 == 0 && var02 == 1 && var01 == 1){
  }else if (var03 == 1 && var02 == 0 && var01 == 0){
  }else{
    //Error 01: Error in button input
    //Serial.print('Error 01');
  }
  Serial.println(var01);
  Serial.println(var02);
  Serial.println(var03);
  delay(1000);
  //Resets the output back to low.
  digitalWrite(Led01, LOW);
  digitalWrite(Led02, LOW);
  digitalWrite(Led03, LOW);
  digitalWrite(Led04, LOW);
}
}

void disp_cartno(){
  if(init_genCartNo == false){
      //Generate CartNo.
      //For Debugging
      CartNo = 1234;
    }
    //Display Generated Cart Number.
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Enter generated code");
    lcd.setCursor(0,1);
    lcd.setCursor(8,2);
    //Replace to var.
    lcd.print(CartNo);
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Press any button to continue.");
  }
