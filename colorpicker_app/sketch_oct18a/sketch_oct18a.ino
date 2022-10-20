void setup() {
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() == 0) {}     //wait for data available
  String input = Serial.readString();  //read until timeout
  input.trim();                        // remove any \r \n whitespace at the end of the String
  String color_code = input.substring(1);
  long number = (long) strtol( &color_code[0], NULL, 16);
  int r = number >> 16;
  int g = number >> 8 & 0xFF;
  int b = number & 0xFF;

  Serial.print("red is ");
  Serial.println(r);
  Serial.print("green is ");
  Serial.println(g);
  Serial.print("blue is ");
  Serial.println(b);
}
