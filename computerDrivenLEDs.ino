#include <Adafruit_NeoPixel.h>

#define PIN 22
#define NUMPIXELS 3
Adafruit_NeoPixel strip( NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800 );
int rgb[3] = { 0,0,0 };

/*
 * String to RGB converter
 * PARAMETERS: 11 character string in this format: "RRR,GGG,BBB"
 * RETURNS: Nothing, it edits the global rgb array
 */
void stringToRGB( String bytesIn );

/*
 * Writes a specific color to all the pixels in a NEOPIXEL strip
 * PARAMETERS: uint32_t Color to be written, int delay to wait between writing each pixel in milliseconds
 * RETURNS: None
 */
void colorWipe(uint32_t color, int wait);

void setup(){
    Serial.begin( 9600 );
    Serial1.begin( 9600 );
    strip.begin();
    strip.setBrightness( 255 );
    for( int i = 0; i < NUMPIXELS; i++ ) {
        colorWipe( strip.Color(255, 255, 0), 0 ); //default to yellow at reboot until a new color is assigned
    }
}
void loop(){
    delay(10);
    if( Serial.available() ){
        String bytesIn = Serial.readString();
        Serial1.print(bytesIn); 
        if( bytesIn[0] >= '0' && bytesIn[0] <= '9' ){
            stringToRGB(bytesIn);
            for( int i = 0; i < NUMPIXELS; i++ ) {
                colorWipe( strip.Color(rgb[0], rgb[1], rgb[2]), 0 );
            }
            strip.show();
        }
    }
}

void stringToRGB( String bytesIn ){
    rgb[0] = ((bytesIn[0] - '0') * 100) + ((bytesIn[1] - '0') * 10) + ((bytesIn[2] - '0') * 1); //subtract '0' to shift to 0-9 instead of 42-51
    rgb[1] = ((bytesIn[4] - '0') * 100) + ((bytesIn[5] - '0') * 10) + ((bytesIn[6] - '0') * 1);
    rgb[2] = ((bytesIn[8] - '0') * 100) + ((bytesIn[9] - '0') * 10) + ((bytesIn[10] - '0') * 1);
}
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}