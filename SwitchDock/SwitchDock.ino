
#include <Adafruit_NeoPixel.h>
 
#define PIN 6
#define N_LEDS 23
#define limit 7
int upperRLED = 16; //upper limit to the portion of rainbow effect LEDs
int lowerRLED = 7; //lower limit to the portion of rainbow effect LEDs
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  strip.begin();
  pinMode(limit ,INPUT);
  Serial.begin(9600);
}
 
void loop() {
  for(int i = 0; i<8; i++){
    strip.setPixelColor(i, 255, 255, 255);
  }
  for(int i = 16; i<25; i++){
    strip.setPixelColor(i, 255, 255, 255);
  }
    strip.show();
    rainbowCycle(3);
    

  
/*  if(digitalRead(limit) == HIGH){
    for(int i=0; i<N_LEDS; i++){
      strip.setPixelColor(i, 0, 0,0);
    }
    strip.show();
    Serial.println("open");
  }
 
*/
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256; j++) { // 5 cycles of all colors on wheel
    for(i=lowerRLED; i< upperRLED; i++) {
      c=Wheel(((i * 256 / N_LEDS) + j) & 255);
      strip.setPixelColor(i, *c, *(c+1), *(c+2));
    }
    strip.show();
    delay(SpeedDelay);
  }
}


byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}
