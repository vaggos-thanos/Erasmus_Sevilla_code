int led_red = 10;
int led_green = 11;
int led_blue = 9;
int r;
int g;
int b;

int array[3] = {250, 242, 5};

void setup() {
  Serial.begin(9600);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_blue, OUTPUT);

}

void loop() {
  while (Serial.available() == 0) {}     //wait for data available
  String input = Serial.readString();  //read until timeout
  input.trim();                        // remove any \r \n whitespace at the end of the String
  String color_code = input.substring(1);
  long number = (long) strtol( &color_code[0], NULL, 16);
  array[0] = number >> 16;
  array[1] = number >> 8 & 0xFF;
  array[2] = number & 0xFF;
  
  analogWrite(led_red, array[0]);
  analogWrite(led_green, array[1]);
  analogWrite(led_blue, array[2]);

}


