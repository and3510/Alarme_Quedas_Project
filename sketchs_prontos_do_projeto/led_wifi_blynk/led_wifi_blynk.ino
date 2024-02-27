/*************************************************************

  This sketch shows how to read values from Virtual Pins

  App dashboard setup:
    Slider widget (0...100) on Virtual Pin V1
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL2rm1y8y-C"
#define BLYNK_TEMPLATE_NAME         "and"
#define BLYNK_AUTH_TOKEN            "4D53tOZEShd8dD2qHES39xxkd7ZqNJhe"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define led 4




// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ORA_2.4G";
char pass[] = "86988134365";

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (pinValue == 1) {
    digitalWrite(led,1);

  }else {
    digitalWrite(led,0);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);


}

void loop()
{
  Blynk.run();
}
