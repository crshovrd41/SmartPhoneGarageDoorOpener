/*************************************************************
  This is the latest and likely final rev of my Smartphone Garage Door Opener sketch
  using the Adafruit Feather Huzzah board and the Blynk framework. It's pretty robust
  and yells at you when you leave the garage door open too long. I hope it serves you well.

  Tyler Winegarner, 2017
  Modified for blynk.cloud by Brandon Fox, 2021
*************************************************************/

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "XXXXX"
#define BLYNK_DEVICE_NAME "XXXXX"
#define BLYNK_AUTH_TOKEN  "AUTH_TOKEN";

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
const char* ssid = "SSID";
const char* pass = "PASSWORD";

// GPIOs
const int doorStatePin = 13; // Switched from 2 to not interfere with reboot on power loss/reset situations
const int openClosePin = 14;
int warnPin;
int warnThreshold = 2000; //apx 5 minutes
int tick = 0;

BlynkTimer timer;

BLYNK_WRITE(V1) {
  warnPin = param.asInt();
}

BLYNK_WRITE(V14) {
  // Trigger the garage door - door state can be open or closed, just like a real opener
  digitalWrite(openClosePin, HIGH);

  // Delay to ensure the signal gets through
  delay(1000);
  
  // Prep the pin for next trigger
  digitalWrite(openClosePin, LOW);
}

// V3 LED Widget represents the physical button state
WidgetLCD lcd(V3);

void buttonLedWidget()
{
  // Read door status

  // If state has changed...
  if (digitalRead(doorStatePin) == HIGH) {
    lcd.print(0, 0, "Door Open  ");
    tick++;
  }
  else {
    lcd.print(0, 0, "Door Closed");
    tick = 0;
    // Automatically enables the door open warning system
    Blynk.virtualWrite(warnPin, LOW);
  }

  // Alert if door open longer than defined threshold
  if (tick > warnThreshold) {
    if (warnPin == LOW) {
      Blynk.notify("Garage door is open!");
      tick = (tick - 500);
    }
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // Setup pins
  pinMode(doorStatePin, INPUT_PULLUP); // INPUT_PULLUP required to bring the pin to 3.3V
  pinMode(openClosePin, OUTPUT);

  timer.setInterval(10, buttonLedWidget);
}

void loop()
{
  Blynk.run();
  timer.run();
}
