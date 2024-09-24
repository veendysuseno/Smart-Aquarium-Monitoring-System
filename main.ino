#include <Blynk.h>
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>

#define Buzz D7
#define Fan D6
#define Heater D5
#define ONE_WIRE_BUS D8

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address and display size

char auth[] = "m8750eUzNJNw1ZqUeh35_62ZWxGbjwxz";  // Blynk auth token
char ssid[] = "Redmi";  // WiFi SSID
char pass[] = "q1w2e3r4t5y6";  // WiFi password

OneWire oneWire(ONE_WIRE_BUS);  // OneWire for temperature sensor
DallasTemperature sensorSuhu(&oneWire);  // Dallas Temperature sensor instance
float suhuSekarang;  // Current temperature variable

void setup() {
  Blynk.begin(auth, ssid, pass);  // Blynk initialization
  Serial.begin(115200);  // Start serial monitor
  lcd.begin();  // Initialize LCD
  lcd.backlight();  // Turn on LCD backlight
  sensorSuhu.begin();  // Start the temperature sensor

  pinMode(Buzz, OUTPUT);  // Set pins for buzzer, fan, heater
  pinMode(Fan, OUTPUT);
  pinMode(Heater, OUTPUT);
}

void loop() {
  Blynk.run();  // Run Blynk services

  // Reading the analog value from the pH sensor connected to A0
  int sensorValue = analogRead(A0);

  // Convert the analog reading to voltage (using 3.3V reference for ESP8266)
  float voltage = sensorValue * (3.3 / 1023.0);

  // Convert voltage to pH value (14 / 5.0 = 2.8)
  float nilaiph = voltage * 2.8;

  // Control the buzzer based on pH range
  if (nilaiph < 6.0 || nilaiph > 8.0) {
    digitalWrite(Buzz, HIGH);  // Turn on buzzer if pH is out of range
    Blynk.notify("Kuras Akuarium Sekarang!");  // Send notification to Blynk
  } else {
    digitalWrite(Buzz, LOW);  // Turn off buzzer if pH is normal
  }

  // Send the pH value to Blynk (use a virtual pin, e.g., V0)
  Blynk.virtualWrite(V0, nilaiph);

  // Get the current temperature
  suhuSekarang = ambilSuhu();

  // Send the temperature to Blynk (use a virtual pin, e.g., V6)
  Blynk.virtualWrite(V6, suhuSekarang);

  // Control fan and heater based on temperature thresholds
  if (suhuSekarang < 24.0) {
    digitalWrite(Heater, HIGH);  // Turn heater on if temperature is too low
    digitalWrite(Fan, LOW);  // Turn fan off
  } else if (suhuSekarang > 30.0) {
    digitalWrite(Heater, LOW);  // Turn heater off
    digitalWrite(Fan, HIGH);  // Turn fan on
  } else {
    digitalWrite(Heater, LOW);  // Keep both off if temperature is normal
    digitalWrite(Fan, LOW);
  }

  // Display pH and temperature on LCD
  lcd.setCursor(0, 0);  // First line of LCD
  lcd.print("pH : ");
  lcd.print(nilaiph, 2);  // Print pH with 2 decimal places

  lcd.setCursor(0, 1);  // Second line of LCD
  lcd.print("Suhu air : ");
  lcd.print(suhuSekarang, 1);  // Print temperature with 1 decimal place

  // Print pH and temperature to Serial Monitor
  Serial.print("Sensor pH : ");
  Serial.print(nilaiph);
  Serial.print(" | Sensor Suhu : ");
  Serial.println(suhuSekarang);

  delay(2000);  // Wait for 2 seconds before next reading
}

// Function to read the current temperature from the Dallas temperature sensor
float ambilSuhu() {
  sensorSuhu.requestTemperatures();  // Request temperature data
  return sensorSuhu.getTempCByIndex(0);  // Return temperature in Celsius
}
