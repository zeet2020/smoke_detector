#define BLYNK_TEMPLATE_ID "-----------"
#define BLYNK_DEVICE_NAME "smoke detector"
#define BLYNK_AUTH_TOKEN "----------------"


#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN; //Enter Authentication code sent by Blynk

char ssid[] = "----"; //Enter WIFI Name
char pass[] = "------"; //Enter WIFI Password
int buzzer = D2;
int smokeA0 = A0;

// Your threshold value. You might need to change it.
int sensorThres = 600;



void buzzer_runner() {
 tone(buzzer, 523) ; //DO note 523 Hz
 delay (1000); 
 tone(buzzer, 587) ; //RE note ...
 delay (1000); 
 noTone(buzzer) ; //Turn off the pin attached to the tone()
}

void setup() {
 pinMode(buzzer, OUTPUT);
 pinMode(smokeA0, INPUT);
 Serial.begin(9600);
 Blynk.begin(auth, ssid, pass);
}

void loop() {
 int analogSensor = analogRead(smokeA0);
 Blynk.run();
 Serial.print("Pin A0: ");
 Serial.println(analogSensor);
 Blynk.virtualWrite(V2, analogSensor);
 // Checks if it has reached the threshold value
 if (analogSensor > sensorThres)
 {
    Blynk.notify("Smoke Detected!"); 
    buzzer_runner();
 }
 else
 {
   noTone(buzzer);
 }
 delay(1000);
}



