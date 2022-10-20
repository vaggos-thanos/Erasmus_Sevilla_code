#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
byte battery[8] =  //icon for battery
{
  0b01110,
  0b11011,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b11111
};

float adc_voltage = 0.0;
float in_voltage = 0.0;

// Floats for resistor values in divider (in ohms)
float R1 = 30000.0;
float R2 = 7500.0; 

// Float for Reference Voltage
float ref_voltage = 5.0;

// Integer for ADC value
int adc_value = 0;

#define VOLTMETER A0
#define currentMeter A1

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  // lcd.print("EK Euosmoy MOVEU");
  lcd.createChar(2, battery);
}

void loop() {
  // Read the Analog Input
  adc_value = analogRead(VOLTMETER);
  
  // Determine voltage at ADC input
  adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
  
  // Calculate voltage at divider input
  in_voltage = adc_voltage / (R2/(R1+R2)); 
  
  // Print results to Serial Monitor to 2 decimal places
  Serial.println(in_voltage);
  
  // Short delay
  delay(100);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(12, 0);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
  lcd.setCursor(15, 0);
  lcd.print("%");
  lcd.setCursor(11, 0);
  lcd.write(2);

  lcd.setCursor(0,1);
  lcd.print("V");
  lcd.setCursor(1,1);
  lcd.print(in_voltage);
}