#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Door"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_TOKEN_HERE"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// Serial bridge to UNO (RX, TX)
SoftwareSerial unoSerial(D5, D6); 

void setup() {
  Serial.begin(9600);
  unoSerial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  // Listen for physical door updates from the UNO
  if (unoSerial.available()) {
    String status = unoSerial.readStringUntil('\n');
    status.trim();
    
    if (status == "OPEN") {
      Blynk.virtualWrite(V0, "Door Opened (Auto)");
      Blynk.virtualWrite(V2, 255); // Turn ON Virtual LED
    } else if (status == "CLOSED") {
      Blynk.virtualWrite(V0, "Door Closed");
      Blynk.virtualWrite(V2, 0);   // Turn OFF Virtual LED
    }
  }
}

// Listen for the Blynk App Button (Manual Override)
BLYNK_WRITE(V3) {
  int buttonState = param.asInt();
  if (buttonState == 1) {
    unoSerial.println("MANUAL_OPEN"); // Tell UNO to open
  } else {
    unoSerial.println("MANUAL_CLOSE"); // Tell UNO to close
  }
}
