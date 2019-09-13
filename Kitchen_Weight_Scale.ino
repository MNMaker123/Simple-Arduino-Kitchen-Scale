//MN Maker
//9.12.19

#include "HX711.h"

//OLED Display etup
#include <Wire.h>
#include <Math.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// HX711 Load Cell Setup
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

const int buttonPin = 4;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


HX711 scale;

void setup() {
  //Serial.begin(38400);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);  //Necessary delay for boot up
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 35);
  display.println("Initializing Scale");
  display.display();
  delay(250);
  display.clearDisplay();

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(111);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  
}

void loop() {

  buttonState = digitalRead(buttonPin);
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // tare scale:
    scale.tare();
  }
  
  display.clearDisplay();
  //Get the Current Weight and Display it On the OLED
  
  current_Weight = scale.get_units(10);
  //Serial.println(current_Weight);
  
  display.setTextSize(2);  //Size 2 means each pixel is 12 width and 16 high
  display.setCursor(25, 10);
  display.print("Weight");
  display.setTextSize(2);
  display.setCursor(15, 36);
  display.print(abs(current_Weight));
  display.print(" grams");
  display.display();
  //scale.power_down();			        // put the ADC in sleep mode
  delay(500);
  //scale.power_up();
}
