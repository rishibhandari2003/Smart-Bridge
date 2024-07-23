#include <Servo.h>
#include <LiquidCrystal_I2C.h> //lcd

LiquidCrystal_I2C lcd(0x27,16,2); //lcd
const int soilMoisturePin = A0; // Connect the soil moisture sensor to analog pin A0
const int redLEDPin = 8;       // Connect the red LED to digital pin 8
const int greenLEDPin = 9;     // Connect the green LED to digital pin 9
const int buzzerPin = 10;      // Connect the buzzer to digital pin 10
const int servoMotor1Pin = 11; // Connect servo motor 1 to digital pin 11
const int servoMotor2Pin = 12; // Connect servo motor 2 to digital pin 12


Servo servoMotor1;
Servo servoMotor2;


void setup() {
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  servoMotor1.attach(servoMotor1Pin);
  servoMotor2.attach(servoMotor2Pin);
  Serial.begin(9600);

  //lcd
  //lcd.init():
  lcd.begin();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("SMART BRIDGE");

  // lcd.setCursor(0,1);
  // lcd.print("Title:SMART BRIDGE");
  
  //
}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin);
  float moisture_percentage;
  moisture_percentage=(100-((soilMoistureValue/1023.00)*100));
  Serial.println(moisture_percentage);

  if (moisture_percentage > 40.00) { // Change the threshold value for high water level
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(buzzerPin, LOW);
    servoMotor1.write(90); // Rotate servo motor 1 to the specified angle (e.g., 90 degrees)
    servoMotor2.write(90);
    lcd.setCursor(0,1);
    lcd.print("Water level high"); // Rotate servo motor 2 to the specified angle (e.g., 90 degrees)
  // } else if (moisture_percentage < 2.00) { // Change the threshold value for low water level
  //   digitalWrite(redLEDPin, LOW);
  //   digitalWrite(greenLEDPin, HIGH);
  //   digitalWrite(buzzerPin, LOW);
  //   servoMotor1.write(0); // Rotate servo motor 1 to the specified angle (e.g., 0 degrees)
  //   servoMotor2.write(0); // Rotate servo motor 2 to the specified angle (e.g., 0 degrees)
  } else {
    digitalWrite(redLEDPin, LOW);
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    servoMotor1.write(0); // Rotate servo motor 1 to the specified angle (e.g., 90 degrees)
    servoMotor2.write(0);
    // lcd.setCursor(0,1);
    // lcd.print();
    

  }
  delay(2000); // Adjust the delay time to your preference
}
