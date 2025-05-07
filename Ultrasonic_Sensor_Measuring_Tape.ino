// Include OLED display library
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display dimensions and I2C address
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

// Sensor pins
const int trigPin = 7;
const int echoPin = 6;

// Variables for measurement
long duration;
float distanceCm;
float distanceInch;
float distanceMm;

// OLED display object (no reset pin used)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.display();

  // Set sensor pins as output/input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  distanceCm = duration * 0.0343 / 2;
  distanceInch = distanceCm * 0.393701;
  distanceMm = distanceCm * 10.0;

  // --- Visual Ruler Display ---
  display.clearDisplay();

  // Display numerical values
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Cm: ");
  display.print(distanceCm);

  display.setCursor(64, 0);
  display.print("In: ");
  display.print(distanceInch);

  display.setCursor(0, 10);
  display.print("Mm: ");
  display.print(distanceMm);

  // Draw the ruler line (moved down to accommodate text)
  display.drawLine(0, 30, SCREEN_WIDTH - 1, 30, SSD1306_WHITE);

  // Mark centimeter intervals (adjust range if needed)
  for (int i = 0; i <= 20; i++) {
    int x = map(i, 0, 20, 0, SCREEN_WIDTH - 1);
    display.drawLine(x, 28, x, 32, SSD1306_WHITE);
    if (i % 5 == 0) {
      display.setTextSize(1);
      display.setCursor(x - 3, 34);
      display.print(i);
    }
  }

  // Indicate the measured distance on the ruler
  int indicatorX = map(distanceCm, 0, 20, 0, SCREEN_WIDTH - 1);
  indicatorX = constrain(indicatorX, 0, SCREEN_WIDTH - 1);
  display.drawLine(indicatorX, 18, indicatorX, 42, SSD1306_WHITE);
  display.fillCircle(indicatorX, 18, 2, SSD1306_WHITE);
  display.fillCircle(indicatorX, 42, 2, SSD1306_WHITE);

  display.display();

  delay(200);
}
