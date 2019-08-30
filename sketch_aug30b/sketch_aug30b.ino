#define BLYNK_PRINT Serial
#include "MQ135.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
char auth[] = "T-hYUmbPhVsgzhb0WcH5pX7hu79nDf-D";
char ssid[] = "POLO";
char pass[] = "volkspolo3133";

int n;

void setup()
{

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  //pinMode(16,OUTPUT);
  //pinMode(5,OUTPUT);
  timer.setInterval(1000L, sendUptime);
}


void sendUptime()
{
  Blynk.virtualWrite(V0, n);
}

void loop()
{
  Blynk.run();
  timer.run();
  
  n=analogRead(A0);
  Serial.println(n);
  
}
