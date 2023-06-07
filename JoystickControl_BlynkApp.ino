#define BLYNK_TEMPLATE_ID           "---------------"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "-----------------------"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>

char ssid[] = "----------------";
char pass[] = "----------------------";

#define IN_1 D1   // right connector motor
#define IN_2 D2
#define IN_3 D3   // left connector motor
#define IN_4 D4

#define En_A D0
#define En_B D5

// #define Manual_Line D0
// #define Break D7
// #define Spray D8
// #define Horn D9

void setup() {
  Serial.begin(9600);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(IN_1,OUTPUT);
  pinMode(IN_2,OUTPUT);
  pinMode(IN_3,OUTPUT);
  pinMode(IN_4,OUTPUT);
  
  pinMode(En_A,OUTPUT);
  pinMode(En_B,OUTPUT);

  // pinMode(Manual_Line,OUTPUT);
  // pinMode(Break,OUTPUT);
  // pinMode(Spray,OUTPUT);
  // pinMode(Horn,OUTPUT);
  
  digitalWrite(IN_1,LOW);
  digitalWrite(IN_2,LOW);
  digitalWrite(IN_3,LOW);
  digitalWrite(IN_4,LOW);

  // digitalWrite(Manual_Line,LOW);
  // digitalWrite(Break,LOW);
  // digitalWrite(Spray,LOW);
  // digitalWrite(Horn,LOW); 
}

BLYNK_WRITE(V1) {
  int x = param[0].asInt();
  int y = param[1].asInt();
  
  Serial.print("x - "); 
  Serial.println(x);
  Serial.print("; y - "); 
  Serial.println(y);

  if ((x == 512) && (y == 512)) // stop
  {
    Serial.print(" Stop "); 
    stop();
  }

  if (y >= 650) // forward
  {
    Serial.print(" Forward "); 
    forward();
  }

  if (y <= 400) // backward
  {
    Serial.print(" Backward "); 
    backward();
  }

  if (x >= 650) // right
  {
    Serial.print(" Right "); 
    right();
  }

  if (x <= 400) // left
  {
    Serial.print(" Left "); 
    left();
  }
}

BLYNK_WRITE(V2) {   // speed variable
  int speed = param.asInt();
  analogWrite(En_A,speed);
  analogWrite(En_B,speed);

  Serial.print(" speed - "); 
  Serial.println(speed);

  if (speed <= 60) // speed stop
  {
    Serial.print(" Stop "); 
    stop();
  }
}

void forward(void) {
  digitalWrite(IN_1,LOW);   // right connector motor
  digitalWrite(IN_2,HIGH);
  digitalWrite(IN_3,LOW);   // left connector motor
  digitalWrite(IN_4,HIGH);
  delay(20);
}

void backward(void) {
  digitalWrite(IN_1,HIGH);
  digitalWrite(IN_2,LOW);
  digitalWrite(IN_3,HIGH);
  digitalWrite(IN_4,LOW);
  delay(20);
}

void right(void) {
  digitalWrite(IN_1,HIGH);
  digitalWrite(IN_2,LOW);
  digitalWrite(IN_3,LOW);
  digitalWrite(IN_4,HIGH);
  delay(20);
}

void left(void) {
  digitalWrite(IN_1,LOW);
  digitalWrite(IN_2,HIGH);
  digitalWrite(IN_3,HIGH);
  digitalWrite(IN_4,LOW);
  delay(20);
}

void stop(void) {
  digitalWrite(IN_1,LOW);
  digitalWrite(IN_2,LOW);
  digitalWrite(IN_3,LOW);
  digitalWrite(IN_4,LOW);
  delay(20);
}

void loop() {
  Blynk.run();
}
