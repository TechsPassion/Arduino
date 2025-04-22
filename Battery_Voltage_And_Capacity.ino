/*
  Please do not measure more than 5V using the Arduino.
  This program reads voltage using Arduino's analog input (ADC) and displays
  both the voltage and a graphical battery level bar on the OLED display.
  It's configured for measuring the voltage of two 18650 batteries connected in parallel.
  The ADC measures voltages between 0V and the Arduino's operating voltage (usually 5V).

  Battery capacity estimation is a rough approximation based on a typical Li-ion
  discharge curve for 18650 cells. The accuracy can vary depending on the
  specific battery type, age, temperature, and load. You might need to fine-tune
  the voltage thresholds for the exact 18650 batteries you are using.
*/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// OLED display dimensions and setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1      // No reset pin used

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Analog input pin
const int analogPin = A0;

// --- Battery Specific Parameters (ADJUST THESE BASED ON YOUR 18650 BATTERIES) ---
// Typical voltage levels for a single 18650 Li-ion battery. These apply to parallel connection.
const float fullVoltage = 4.20;   // Voltage when the battery is considered fully charged
const float emptyVoltage = 3.00;  // Voltage when the battery is considered empty

// --- Battery Bar Display Parameters ---
const int barX = 0;           // X-coordinate of the battery bar
const int barY = 35;          // Y-coordinate of the battery bar
const int barWidth = 100;     // Width of the battery bar
const int barHeight = 20;     // Height of the battery bar
const int borderWidth = 2;    // Width of the bar's border

void setup() {
  Serial.begin(9600); // Start serial monitor

  // Initialize the OLED display with I2C address 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 initialization failed"));
    while (true); // Halt execution if display fails
  }

  // Show welcome message
  display.clearDisplay();
  display.setTextSize(1);          // Small text
  display.setTextColor(SSD1306_WHITE); // White color text
  display.setCursor(0, 0);          // Top-left corner
  display.println("TechsPassion");
  display.display();
  delay(2000);
}

void loop() {
  // Read analog input and convert to voltage - Read analog value (0 to 1023)
  int rawValue = analogRead(analogPin);
  // Convert to voltage (0V to 5V)
  float voltage = rawValue * (5.0 / 1023.0);

  // --- Battery Capacity Estimation ---
  float capacityPercentage = 0.0;
  if (voltage >= fullVoltage) {
    capacityPercentage = 100.0;
  } else if (voltage <= emptyVoltage) {
    capacityPercentage = 0.0;
  } else {
    capacityPercentage = mapfloat(voltage, emptyVoltage, fullVoltage, 0.0, 100.0);
  }

  // Calculate the filled width of the battery bar
  int filledWidth = static_cast<int>((capacityPercentage / 100.0) * (barWidth - 2 * borderWidth));
  if (filledWidth < 0) filledWidth = 0;
  if (filledWidth > (barWidth - 2 * borderWidth)) filledWidth = (barWidth - 2 * borderWidth);

  // Clear screen and display information
  display.clearDisplay();

  // Display Voltage
  display.setTextSize(1);          // Small text for voltage
  display.setCursor(0, 0);
  display.print("Voltage: ");
  display.print(voltage, 2);      // Print with 2 decimal places
  display.println(" V");

  // Draw the battery bar outline
  display.drawRect(barX, barY, barWidth, barHeight, SSD1306_WHITE);

  // Draw the filled portion of the battery bar
  display.fillRect(barX + borderWidth, barY + borderWidth, filledWidth, barHeight - 2 * borderWidth, SSD1306_WHITE);

  // Display Battery Capacity Percentage next to the bar
  display.setTextSize(1);          // Small text for percentage
  display.setCursor(barX + barWidth + 5, barY + (barHeight / 2) - 4); // Adjust Y for vertical centering
  display.print(static_cast<int>(capacityPercentage));
  display.print(" %");

  // Display raw analog reading (for debugging if needed)
  display.setTextSize(1);
  display.setCursor(0, 55);
  display.print("Analog: ");
  display.println(rawValue);

  display.display();              // Push buffer to screen
  delay(1000);                    // Wait 1 second
}

// Helper function 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
