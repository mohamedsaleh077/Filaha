#include <DHT11.h>
#include <DIYables_LCD_I2C.h>

DHT11 dht11(2);

// Define the pins
int sensorPin = A0;
int ledPin = 4;
// int sensor2 = A2;
// int greenLed = 2;

// Variables to store sensor value
int sensorValue = 0;
// int sen2val = 0;
DIYables_LCD_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns, 2 rows

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);

  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  lcd.init();      // Initialize the LCD
  lcd.backlight(); // Turn on the backlight

}

void loop() {
  lcd.setCursor(0, 0);
  
  int temperature = 0;
  int humidity = 0;

  // Attempt to read the temperature and humidity values from the DHT11 sensor.
  int result = dht11.readTemperatureHumidity(temperature, humidity);

  // Check the results of the readings.
  // If the reading is successful, print the temperature and humidity values.
  // If there are errors, print the appropriate error messages.
  if (result == 0) {
      // Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.print(",");
      Serial.print(humidity);
      // Serial.println(" %");
  } else {
      // Print error message based on the error code.
      Serial.println(DHT11::getErrorString(result));
  }

  sensorValue = analogRead(sensorPin);
  // sen2val = analogRead(sensor2);

  lcd.print("TMP: ");
  lcd.print(temperature);
  lcd.print(" HDY: ");
  lcd.print(humidity);

  // Print the sensor value to the Serial Monitor
  // Serial.print("Soil Moisture Value: ");
  // Serial.println(sensorValue);
  
  // Serial.print("air Value: ");
  // Serial.println(sen2val);

  lcd.setCursor(0, 1);
  // Check if the soil is dry
  if (sensorValue > 500) {
    // Turn the LED on
    Serial.println(",DRY");
    lcd.print("DRY SOIL");
    digitalWrite(ledPin, HIGH);
    // digitalWrite(greenLed, LOW);
  } else {
    lcd.print("WET SOIL");
    Serial.println(",WET");
    // Turn the LED off
    digitalWrite(ledPin, LOW);
    // digitalWrite(greenLed, HIGH);
  }

  // Wait for a second before taking another reading
  delay(1000);
}
