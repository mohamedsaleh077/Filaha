#include <DHT11.h>
#include <DIYables_LCD_I2C.h>

DHT11 dht11(2); // init DHT11 Sensor in A2 port

// Define the pins
int soilSensorPin = A0; // Soil Sensor Pin

// LED Pins
int redPin = 4; // DRY Soil
int yellowPin = 5; // Wet Soil
int greenPin = 6; // Moist Soil

// Variables to store sensor value
int soilSensorValue = 0;
// int sen2val = 0;
DIYables_LCD_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns, 2 rows

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);

  // Initialize the LED pin as an output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  
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

  // Print Soil Sensor Values
  soilSensorValue = analogRead(soilSensorPin);

  lcd.print("TMP: ");
  lcd.print(temperature);
  lcd.print(" HDY: ");
  lcd.print(humidity);

  Serial.print(",");

  lcd.setCursor(0, 1);
  // Check if the soil is dry
  if (soilSensorValue >= 700) {
    lcd.print("* DRY SOIL ");
    Serial.print("dry,");
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
  } else if (soilSensorValue >= 250) {
    lcd.print("MOIST SOIL ");
    Serial.print("moist,");
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPin, LOW);
  } else if (soilSensorValue < 250){
    lcd.print("* WET SOIL ");
    Serial.print("wet,");
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, HIGH);
  }

  // calculate percentage of the Soil Sensor Value
  float value = (((soilSensorValue / 1024.0) * 100) - 100 )* -1;
  lcd.print(value);
  if(soilSensorValue > 999) lcd.print("%");
  if(soilSensorValue <= 999) lcd.print("%");
  if(soilSensorValue <= 99) lcd.print("%  ");
  if(soilSensorValue <= 9) lcd.print("%   ");
  Serial.println(soilSensorValue);
  
  // Wait for a second before taking another reading
  delay(1000);
}
