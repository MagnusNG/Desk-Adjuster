#include <Servo.h>
#include <Servo.h>
#include "SR04.h"
#include <LiquidCrystal.h>

//initialize the library with the numbers of the interface pins
LiquidCrystal lcd(5, 6, 7, 8, 9, 10);

//initilize the ultrasonic sensor pins
int trig_pin = 12;
int echo_pin = 11;
SR04 sensor = SR04(echo_pin, trig_pin);

//intilize servo motors
Servo raisingservo;
Servo loweringservo;
long distance;

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);

  loweringservo.attach(3);
  loweringservo.write(160);
  raisingservo.attach(2);
  raisingservo.write(90);

  lcd.print("Initialzing...");

  delay(3000);
}

void loop() {
  distance = sensor.DistanceAvg();
  Serial.println(distance);
  delay(50);

  if( distance < 30 ){
    if( distance < 15 ){
      //lowering function
      lcd.setCursor(1, 0);
      lcd.clear();
      lcd.print( "Lowering Desk..." );
      raisingservo.write(100);
      loweringservo.write(110);
    } else if ( distance >= 15 ){
      //raising function
      lcd.setCursor(1, 0);
      lcd.clear();
      lcd.print( "Raising Desk..." );
      loweringservo.write(160);
      raisingservo.write(158);
    }
  } else {
    //standby function
    lcd.setCursor(1, 0);
    lcd.clear();
    lcd.print( "Standby" );
    raisingservo.write(100);
    loweringservo.write(160);
  }
  lcd.setCursor(0, 1);
  lcd.print( "distance: " );
  lcd.print( sensor.DistanceAvg() );
}
