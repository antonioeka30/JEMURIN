#include <Stepper.h>
#define BLYNK_PRINT Serial
#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//stepper
int IN1=D1;
int IN2=D2;
int IN3=D3;
int IN4=D4;
int step = 100;
int delaytime=2; //makin kecil delay, makin cepat motor berputar

const int sensor_hujan = D0;
const int ldr = A0;
int nilai;

char auth[] = "4c47d7933fe44b3f9797eebfccabdee3";
char ssid[] = "PKWUIOT";
char pass[] = "PAKOCIN123";
WidgetLCD lcd1(V5);

void setup () {
Blynk.begin(auth, ssid, pass);
pinMode (sensor_hujan, INPUT);
//pinMode (LED, OUTPUT); 
Serial.begin(9600);
lcd1.clear();
lcd1.print(0, 0, "Kondisi : ");
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
}
 
void loop() {
  Blynk.run();
// Sensor hujan---------
  lcd1.clear();  
  lcd1.print(0, 0, "Cuaca : "); 
  int kondisi_sensor = digitalRead(sensor_hujan);
  Serial.print("Cuaca Saat Ini : ");
  if (kondisi_sensor == LOW){
    //digitalWrite(LED, HIGH);
    lcd1.print(8,0, "Hujan");  
  }else {
    //digitalWrite(LED, LOW);
    lcd1.print(8,0, "Cerah");
  }
  delay (1000);
//LDR------------
  nilai= analogRead(ldr);
  Serial.print("Keadaan Saat Ini : ");  
    if(nilai < 500){
    //digitalWrite(led, HIGH);
    lcd1.print(0,1,"Kondisi : Terang");
  }
  else{
    //digitalWrite(led, LOW);
    lcd1.print(0,1,"Kondisi : Petang");
  }
  delay (1000);
}


BLYNK_WRITE(V1){
  int i;
for(i=0; i <=500; i++)
{
//step 4
step4();
delay(delaytime);

//step 3
step3();
delay(delaytime);

//step 2
step2();
delay(delaytime);

//step 1
step1();
delay(delaytime);
}
}
void step1(){
  digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,HIGH);
}

void step2(){
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
}

void step3(){
digitalWrite(IN1,HIGH);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
}

void step4(){
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
}
BLYNK_WRITE(V2){
  int i;
for(i=0; i <=500; i++)
{
//step 4
step1();
delay(delaytime);

//step 3
step2();
delay(delaytime);

//step 2
step3();
delay(delaytime);

//step 1
step4();
delay(delaytime);
}
}
