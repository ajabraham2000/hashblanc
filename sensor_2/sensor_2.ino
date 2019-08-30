#include "MQ135.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char sid[] = "Pole Star";
char pass[] = "atix7014";
float ppm;

MQ135 gasSensor = MQ135(A0);

String apiKey="Z59FB6YV9ZLZOBJC";
char auth[] = "T-hYUmbPhVsgzhb0WcH5pX7hu79nDf-D";

const char* server = "api.thingspeak.com";

BlynkTimer timer;
WiFiClient client;

void myTimerEvent()
{
  Blynk.virtualWrite(V0, ppm);
  if (client.connect(server,80))
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(ppm);
                            // postStr +="&field2=";
                            // postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
                             client.stop();
                        }
}


void setup()
{
  Blynk.begin(auth, sid, pass);
  timer.setInterval(2000L, myTimerEvent);         
  pinMode(4,OUTPUT);  
}
void loop()
{
  ppm = gasSensor.getPPM();
  Blynk.run();
  timer.run();
  
  
  }      
