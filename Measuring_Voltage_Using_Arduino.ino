/*
  Voltage Measurement with Arduino and OLED Display

  This program reads voltage using Arduino's analog input (ADC).
  The ADC measures voltages between 0V and the Arduino's operating voltage (usually 5V).
  To measure higher voltages, use a voltage divider circuit to step down the voltage
  into the 0–5V range before connecting it to the analog pin.
*/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// OLED display dimensions and setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // No reset pin used

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Analog input pin
const int analogPin = A0;

void setup() {
  Serial.begin(9600); // Start serial monitor

  // Initialize the OLED display with I2C address 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 initialization failed"));
    while (true); // Halt execution if display fails
  }

  // Show welcome message
  display.clearDisplay();
  display.setTextSize(1);                // Small text
  display.setTextColor(SSD1306_WHITE);   // White color text
  display.setCursor(0, 0);               // Top-left corner
  display.println("TechsPassion");
  display.display();
  delay(2000);
}

void loop() {
  // Read analog input and convert to voltage - Read analog value (0 to 1023)
  int rawValue = analogRead(analogPin);
  // Convert to voltage (0V to 5V)
  float voltage = rawValue * (5.0 / 1023.0);

  // Clear screen and display voltage
  display.clearDisplay();
  
  display.setTextSize(2);                // Large text for voltage
  display.setCursor(0, 10);
  display.println("Voltage:");
  display.print(voltage, 2);             // Print with 2 decimal places
  display.println(" V");

  // Display raw analog reading
  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print("Analog: ");
  display.println(rawValue);

  display.display();                     // Push buffer to screen
  delay(1000);                           // Wait 1 second
}
