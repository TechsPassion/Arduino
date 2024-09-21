#include <WiFiS3.h>
#include <ArduinoJson.h>
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>

// WiFi credentials
const char* ssid = "WiFi_Name";
const char* password = "WiFi_Pssword";

// OpenWeatherMap API details
const char* server = "api.openweathermap.org";
const char* apiKey = "Your_API_Key";
const char* location = "Dallas,US"; // Change to your desired location

ArduinoLEDMatrix matrix;

void setup() {
  Serial.begin(9600);
  matrix.begin();
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void displayTemperature(int temp, bool showF) {
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textFont(Font_5x7);
  
  matrix.beginText(0, 0, 0xFFFFFF);
  matrix.print(temp);
  if (showF) {
    matrix.print("F");
  }
  matrix.endText();
  
  matrix.endDraw();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    
    if (client.connect(server, 80)) {
      // Make HTTP request
      client.print("GET /data/2.5/weather?q=");
      client.print(location);
      client.print("&APPID=");
      client.print(apiKey);
      client.println("&units=imperial HTTP/1.1");
      client.print("Host: ");
      client.println(server);
      client.println("Connection: close");
      client.println();
      
      // Wait for response
      while (client.connected() && !client.available()) delay(10);
      
      // Skip HTTP headers
      char endOfHeaders[] = "\r\n\r\n";
      if (!client.find(endOfHeaders)) {
        Serial.println("Invalid response");
        return;
      }
      
      // Allocate JSON buffer
      DynamicJsonDocument doc(1024);
      
      // Parse JSON
      DeserializationError error = deserializeJson(doc, client);
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }
      
      // Extract and round temperature
      int temp = round(doc["main"]["temp"].as<float>());
      Serial.print("Temperature: ");
      Serial.println(temp);
      
      
      // Keep the temperature with F displayed
      displayTemperature(temp, true);
    }
    else {
      Serial.println("Connection failed");
    }
    
    client.stop();
  }
  
  delay(1000); 
}