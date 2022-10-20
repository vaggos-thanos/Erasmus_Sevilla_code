// main reference source: https://dronebotworkshop.com/dc-volt-current/
#include <LiquidCrystal.h>
#define V_ADC_PIN A0
#define C_ADC_PIN A1

#define VS1_R1 30000.0
#define VS1_R2 7500.0 

#define BITS_PRECISION 10
#define REF_VOLTAGE 5.0

// NOTE: Use a SCALE_FACTOR that matches your version of ACS712
//#define SCALE_FACTOR 0.185 //5A
#define SCALE_FACTOR 0.1 //20A
//#define SCALE_FACTOR 0.066 //30A

int adc_value;


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

byte energy[8] =  // icon for power
{
  0b00010,
  0b00100,
  0b01000,
  0b11111,
  0b00010,
  0b00100,
  0b01000,
  0b00000
};

byte charge[8] = // icon for battery charge
{
  0b01010,
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b01110,
  0b00100,
  0b00100,
};
byte not_charge[8]=
{
  0b00000,
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000,
};

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/* lcd.setCursor(0,1);
 lcd.write(2);
 lcd.setCursor(2, 1);
  lcd.print("4.70"); */

void setup(){
   // Setup Serial Monitor
   Serial.begin(9600);
   lcd.begin(16, 2); 
   lcd.createChar(2, charge);
  
   
}

void loop(){
  //float v = calculate_voltage(V_ADC_PIN, VS1_R1, VS1_R2);
  //float c = calculate_current(C_ADC_PIN);
  float v = calculate_voltage(0, VS1_R1, VS1_R2);
  float c = calculate_current(1);

  
  Serial.print("Vout = ");           
  Serial.print(v,2); 
  Serial.print(" Volts");                            
  Serial.print("\t Current = ");                  
  Serial.print(c, 2);
  Serial.println(" Amps");

  lcd.setCursor(0, 1);
  lcd.write(2);

  lcd.setCursor(2,1);
  lcd.print(v);
  lcd.setCursor(6,1);
  lcd.print("V");

  lcd.setCursor(8, 1);
  lcd.print(round(c));
  lcd.setCursor(13, 1);
  lcd.print("A");


  delay(50);
}
  
float calculate_voltage(int pin, float r1, float r2){
   float adc_voltage = 0.0;
   float in_voltage = 0.0;
   if(pin == -1){
    adc_value = random(0, pow(2, BITS_PRECISION)); 
   }else{
    adc_value = analogRead(pin);
      
      }
   
   adc_voltage  = (adc_value * REF_VOLTAGE) / pow(2, BITS_PRECISION); 
   
   // Calculate voltage at divider input
   // voltage divider formula ==> Vout = (Vin*R2) / (R1 + R2); Vin = (Vout * (R1+R2))/R2
   // https://ohmslawcalculator.com/voltage-divider-calculator
   in_voltage = adc_voltage / (r2/(r1+r2)); 
   
   return in_voltage;
  }



float calculate_current(int pin){
  double v_out = 0;
  double current = 0;
  // Constants for A/D converter resolution
  // Reference voltage is 5V if not using AREF external reference
  // Zero point is half of Reference Voltage

  double adc_voltage = REF_VOLTAGE/ pow(2, BITS_PRECISION);
  double zero_point = REF_VOLTAGE / 2; 
  

  
  // Vout is read 1000 Times for precision
  if (pin == -1){
    int adc_read = random(0, pow(2, BITS_PRECISION));
    for(int i = 0; i < 1000; i++) {
      v_out = (v_out + (adc_voltage * adc_read));   
      delay(1);
    }
  }else{
    for(int i = 0; i < 1000; i++) {
    v_out = (v_out + (adc_voltage * analogRead(pin)));   
    delay(1);
    }
  }
  
  // Get v_out in mv
  v_out = v_out /1000;
  
  // Convert v_out into current using Scale Factor
  current = (v_out - zero_point)/ SCALE_FACTOR;                   
  return (float)current;
}
