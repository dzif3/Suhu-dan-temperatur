#define BLYNK_PRINT Serial

#include <DHT.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "sLecfj9GRvYHHZiJxzfrfiOVQTRCDiE6";
char ssid[] = "A50s";
char pass[] = "kirana321";

#define DHTPIN 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor(){
float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t)) { // mengecek kondisi apa bila suhu dan kelembapan tidak ada
  Serial.println("Failed to read temp and humidity");
  return;
}
Blynk.virtualWrite(V1, t); // setting virtual suhu di blynk
Blynk.virtualWrite(V2, h); // setting virtual kelembapan di blynk
timer.setInterval(1000L, sendSensor);
}

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
Blynk.begin(auth, pass, ssid);
dht.begin(); // sensor mulai membaca suhu dan kelembapan
}

void loop() {
  // put your main code here, to run repeatedly:
Blynk.run();
timer.run();
}
