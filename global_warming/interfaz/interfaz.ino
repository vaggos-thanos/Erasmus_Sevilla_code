int potentiometer_pin = A0; 
int button_pin = 12; 

int button_state = 0; 
int potentiometer_output = 0; 
int last_stored_year = 2010;
int year = 2010;
int reading = 0;
int last_button_state = 0; 

// Debounce https://docs.arduino.cc/built-in-examples/digital/Debounce
// https://www.arduino.cc/reference/en/language/variables/data-types/long/

unsigned long debounce_delay = 25;
unsigned long last_debounce_time = 0;


void setup() {

    Serial.begin(9600);
    pinMode(button_pin, INPUT);

}

void loop() {
  potentiometer_output = analogRead(potentiometer_pin);
  year = map(potentiometer_output, 1023, 0, 2010, 2060);
  //TODO: debounce for the potentiameter
  if (year != last_stored_year ){
    Serial.println(year); 
    last_stored_year = year;
   }
  
  
  reading = digitalRead(button_pin); 
      if (reading != button_state) {
            button_state = reading;
            if (button_state == HIGH) {
               Serial.println(1);
            }
        }
  /*
  if (reading != last_button_state) {

      // https://www.arduino.cc/reference/en/language/functions/time/millis/
       last_debounce_time = millis();
       last_button_state = reading;
      
    }
  
  if ((millis() - last_debounce_time) > debounce_delay) {
        if (reading != button_state) {
            button_state = reading;
            if (button_state == HIGH) {
               Serial.println(1);
            }
        }
    }*/
  

   





    
  
}
