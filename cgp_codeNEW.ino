//libraries and libary variables
#include <FastLED.h>
#include <dht11.h>

//humidity sensor pin
#define DHT11PIN 4
dht11 DHT11;
//gas Level sesnor pin
#define sensor A0

//Led strip pin
#define LED_STRIP_PIN 2
#define NUM_LEDS 120



//colour function for leds
CRGB leds[NUM_LEDS];

//variables
int gasLevel = 0;
const int button1Pin = 7;
const int button2Pin = 8;
int button1State = 0;
int button2State = 0;
bool airQuality;
bool humidity;


void setup() {
  Serial.begin(9600);

  //initialise all pins and pin modes
  pinMode(sensor, INPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  //initialise turn on LEDS and refresh or clear the lights
  FastLED.addLeds<WS2812B, LED_STRIP_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
}
void loop() {


  //reading button pin states for pressing
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);


  //functions for when button is pressed switch modes
  if (humidity) {
    showHumdity();
  }
  if (airQuality) {
    showCarbonDioxide();
  }


  if (button1State == HIGH) {
    //yellow button
    Serial.println("Carbon Doxide");
    humidity = false;
    airQuality = true;
  }

  if (button2State == HIGH) {
    //green button
    Serial.println("Humidity");
    humidity = true;
    airQuality = false;
  }
}

//humidity function
void showHumdity() {

  //clear lights so lights dont overlap when switch modes
  FastLED.clear();

  //retrieve humidity and temp from sensor then display to serial monitor
  int chk = DHT11.read(DHT11PIN);
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);
  float humidityLevel = (float)DHT11.humidity;
  Serial.print("Temperature   (C): ");
  Serial.println((float)DHT11.temperature, 2);

  Serial.println(analogRead(0));


  //conditions for when the lights should change and hpw many and accoring to levels
  if (humidityLevel < 25) {
    for (int i = 0; i < 4; i++) {
      leds[i] = CRGB(255, 0, 0);
    }
    for (int j = 68; j < 72; j++) {
      leds[j] = CRGB(255, 0, 0);
    }
    for (int k = 23; k < 27; k++) {
      leds[k] = CRGB(255, 0, 0);
    }
    for (int l = 91; l < 95; l++) {
      leds[l] = CRGB(255, 0, 0);
    }
  } else if (humidityLevel >= 25 && humidityLevel < 70) {

    for (int i = 0; i < 6; i++) {
      leds[i] = CRGB(0, 0, 128);
    }
    for (int j = 66; j < 72; j++) {
      leds[j] = CRGB(0, 0, 128);
    }
    for (int k = 23; k < 29; k++) {
      leds[k] = CRGB(0, 0, 128);
    }
    for (int l = 89; l < 95; l++) {
      leds[l] = CRGB(0, 0, 128);
    }


    //Condition for when humidity is too high to make all lights turn on and flash
  } else {
    for (int i = 0; i < 120; i++) {
      leds[i] = CRGB(255, 0, 0);
    }
    FastLED.show();
    delay(200);
    FastLED.show();
    delay(200);
    FastLED.clear();
    delay(200);
    FastLED.show();
    delay(200);
    FastLED.clear();
    delay(200);
    FastLED.show();
  }


  FastLED.show();
}

//Function for carbon dioxide
void showCarbonDioxide() {
  //clear lights when switch modes
  FastLED.clear();
  //retrieve data from sensor
  gasLevel = analogRead(0)
               Serial.println(analogRead(0));

  //Conditions for how many lights turn on according to the air quality and CO2 Levels
  if (gasLevel < 100) {
    for (int i = 0; i < 4; i++) {
      leds[i] = CRGB(128, 100, 0);
    }
    for (int j = 68; j < 72; j++) {
      leds[j] = CRGB(128, 100, 0);
    }
    for (int k = 23; k < 27; k++) {
      leds[k] = CRGB(128, 100, 0);
    }
    for (int l = 91; l < 95; l++) {
      leds[l] = CRGB(128, 100, 0);
    }


  } else if (gasLevel >= 100 && gasLevel < 250) {
    for (int i = 0; i < 6; i++) {
      leds[i] = CRGB(128, 100, 0);
    }
    for (int j = 66; j < 72; j++) {
      leds[j] = CRGB(128, 100, 0);
    }
    for (int k = 23; k < 29; k++) {
      leds[k] = CRGB(128, 100, 0);
    }
    for (int l = 89; l < 95; l++) {
      leds[l] = CRGB(128, 100, 0);
    }

  } else if (gasLevel >= 250 && gasLevel < 500) {
    for (int i = 0; i < 8; i++) {
      leds[i] = CRGB(128, 100, 0);
    }
    for (int j = 64; j < 72; j++) {
      leds[j] = CRGB(128, 100, 0);
    }
    for (int k = 23; k < 31; k++) {
      leds[k] = CRGB(128, 100, 0);
    }
    for (int l = 87; l < 95; l++) {
      leds[l] = CRGB(128, 100, 0);
    }

  } else {
    for (int i = 0; i < 120; i++) {
      leds[i] = CRGB(255, 0, 0);
    }
     FastLED.show();
    delay(200);
    FastLED.show();
    delay(200);
    FastLED.clear();
    delay(200);
    FastLED.show();
    delay(200);
    FastLED.clear();
    delay(200);
    FastLED.show();
  }
  FastLED.show();
}
