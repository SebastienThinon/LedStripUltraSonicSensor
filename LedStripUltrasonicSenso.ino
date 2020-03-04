//import  FastLED library
#include <FastLED.h>

//variables
int count1 = 0;
int count2 = 0;
int count3 = 0;
int temp1;
int temp2;
int temp3;
long duration;
int dist1;
int dist2;
int dist3;
//first captor
const int Tpin1 = 5;
const int Epin1 = 3;
//second captor
const int Tpin2 = 6;
const int Epin2 = 9;
//third captor
const int Tpin3 = 10;
const int Epin3 = 11;
//led strip
const int LedPin = 7;
#define LED_PIN    7
#define NUM_LEDS   30
CRGB leds[NUM_LEDS];

void setup() {
  //ultraSensor captor 1
  pinMode(Tpin1, OUTPUT);
  pinMode(Epin1, INPUT);
  //ultraSensor captor 2
  pinMode(Tpin2, OUTPUT);
  pinMode(Epin2, INPUT);
  //ultraSensor captor 3
  pinMode(Tpin3, OUTPUT);
  pinMode(Epin3, INPUT);
  
  Serial.begin(115200);  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  //captor
  digitalWrite(Tpin1, LOW);
  delayMicroseconds(2);
  digitalWrite(Tpin1, HIGH);
  delayMicroseconds(5);
  digitalWrite(Tpin1, LOW);

  duration = pulseIn(Epin1, HIGH, 55000);
  //dist1 = duration*0.034/2;
  dist1 = duration*0.073;
  Serial.print(duration);
  Serial.println();
  
  //captor2
  digitalWrite(Tpin2, LOW);
  delayMicroseconds(2);
  digitalWrite(Tpin2, HIGH);
  delayMicroseconds(5);
  digitalWrite(Tpin2, LOW);

  duration = pulseIn(Epin2, HIGH);
  //dist2 = duration*0.034/2;
  dist2 = duration*0.073;

  //captor3
  digitalWrite(Tpin3, LOW);
  delayMicroseconds(2);
  digitalWrite(Tpin3, HIGH);
  delayMicroseconds(5);
  digitalWrite(Tpin3, LOW);

  duration = pulseIn(Epin3, HIGH);
  //dist3 = duration*0.034/2;
  dist3 = duration*0.073;

  //delet inconsistent variable
  if((dist1 < temp1+50 || dist1 > temp1-50) || (count1 > 150)){
    count1 = 0;
    temp1 = dist1;
  }else{dist1 = temp1; count1++;}
  if((dist2 < temp2+50 || dist2 > temp2-50) || (count2 > 150)){
    count2 = 0;
    temp2 = dist2;
  }else{dist2 = temp2; count2++;}
  if((dist3 < temp3+50 || dist3 > temp3-50) || (count3 > 150)){
    count3 = 0;
    temp3 = dist3;
  }else{dist3 = temp3; count3++;}

  //terminal output
  Serial.print("Dist1: ");
  if(dist1 > 255){dist1 = 255;}
  if(dist1 < 8){dist1 += 8;}
  Serial.print(dist1-8);
  Serial.print("  ||  Dist2: ");
  if(dist2 > 255){dist2 = 255;}
  if(dist2 < 8){dist2 += 8;}
  Serial.print(dist2-8);
  Serial.print("  ||  Dist3: ");
  if(dist3 > 255){dist3 = 255;}
  if(dist3 < 8){dist3 += 8;}
  Serial.print(dist3-8);
  Serial.println();

  //LED Strip output
  for(int i = 0; i<NUM_LEDS; i++){
    leds[i] = CRGB(dist1-8, dist2-8, dist3-8);
    FastLED.show();
  }  
  delay(5); 
}
