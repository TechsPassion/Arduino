#include <Wire.h>
#include <Adafruit_GFX.h>
#include <LiquidCrystal_I2C.h>

// Set the address, number of columns, and number of rows of the LCD
const int LCD_ADDRESS = 0x27; // I2C address of the LCD
const int LCD_COLS = 16; // Number of columns of the LCD
const int LCD_ROWS = 2; // Number of rows of the LCD
const int trigPin = 7; // Trigger Pin
const int echoPin = 6; // Echo Pin
// Create an instance of the LCD object
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

void setup() {
  pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
 // Initialize the I2C bus
 Wire.begin();
// Initialize the LCD
 lcd.init();

 
}
void loop() {
   long duration, distinches;
   
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   
   duration = pulseIn(echoPin, HIGH);
   distinches = duration / 74 / 2;

   // Update OLED display with current LED and score
  // Print a welcome message
 lcd.backlight(); // Turn on the backlight
 lcd.setCursor(0, 0);
 lcd.print("Distance");
 lcd.setCursor(0, 1);
 lcd.print(distinches);
}
