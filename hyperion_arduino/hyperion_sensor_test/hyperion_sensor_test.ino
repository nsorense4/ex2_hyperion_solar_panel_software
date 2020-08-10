#include "adc_handler.h"

ADC_Handler handle;

void setup() {
  Serial.begin(9600);
  if(handle.adc_init()){
     Serial.println("AD7298 Initialized!");
  }
  else
  {
    Serial.println("Unable to initialize AD7298");
  }
}

void loop() {
  // Do stuff here
}
