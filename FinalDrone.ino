
#include <ESP32Servo.h>
#include <WiFi.h>
#define BLYNK_TEMPLATE_ID "TMPLFXusx_kE"
#define BLYNK_TEMPLATE_NAME "Drone"
#define BLYNK_AUTH_TOKEN "e4hXFCYRTvAcKseZkgOdAVpyg6LzZWAR"
#include <BlynkSimpleEsp32.h>
char ssid[] = "Blynk";
char pass[] = "#blynk123";
Servo m1, m2, m3, m4;
int throttle=0, x=50, y=50, yaw=50;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,pass);
    m1.attach(32, 1000, 2000);
   m2.attach(23, 1000, 2000);
   m3.attach(25, 1000, 2000);
    m4.attach(26, 1000, 2000);
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting to WiFi..");
    delay(500);
  };
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}


BLYNK_WRITE(V1) {
 Serial.println("reading v1");
  x = param[0].asInt();
}

BLYNK_WRITE(V2) {
 Serial.println("reading v2");
   y = param[0].asInt();
}
BLYNK_WRITE(V3)
{Serial.println("reading v3");
  yaw = param[0].asInt();
}
BLYNK_WRITE(V0) {
Serial.println("reading vo");
   throttle = param.asInt();
   throttle  = map(throttle, 0, 100, 0, 180);
   Serial.println(throttle);
}

void smartcar() {
  if (y > 70) {
    forwar();
  
  } else if (y < 30) {
   back();
    
  } else if (x < 30) {
     righ();
   
  }
   else if (x > 70) {
     lef();
  
  }
    else if(yaw>70){
    lya();
  }
  else if(yaw<30){
    rya();
  }
  else if (x < 70 && x > 30 && y < 70 && y > 30 && yaw<70 && yaw>30) {
    thro();

   }
}

void loop() {
  Blynk.run();
  smartcar();
}

void thro(){
Serial.println("throttle");

   m1.write(throttle);
  m2.write(throttle);
    m3.write(throttle); 
m4.write(throttle); 
}
void forwar(){
  Serial.println("forward");
  
    m1.write(throttle);
  m2.write(throttle);
    m3.write(throttle+20); 
m4.write(throttle+20);
}

void lef(){
  Serial.println("left");
   m1.write(throttle);
  m2.write(throttle+20);
    m3.write(throttle); 
m4.write(throttle+20); 
}
void righ(){
  Serial.println("right");
    m1.write(throttle+20);
  m2.write(throttle);
    m3.write(throttle+20); 
m4.write(throttle); 
}
void back(){
  Serial.println("backward");
    m1.write(throttle+20);
  m2.write(throttle+20);
    m3.write(throttle); 
m4.write(throttle); 
}
void lya()
{
Serial.println("left yaw");
   m1.write(throttle+20);
  m2.write(throttle);
    m3.write(throttle+20); 
m4.write(throttle);
}
void rya(){
  Serial.println("right yaw");
     m1.write(throttle);
  m2.write(throttle+20);
    m3.write(throttle); 
m4.write(throttle+20); 
}

