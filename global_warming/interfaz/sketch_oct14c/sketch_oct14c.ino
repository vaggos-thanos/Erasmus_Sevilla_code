// int led_red = 10;
// int led_green = 11;
// int led_blue = 9;

// int array[3] = {250, 242, 5};

// void setup() {
//   pinMode(led_red, OUTPUT);
//   pinMode(led_green, OUTPUT);
//   pinMode(led_blue, OUTPUT);

// }

// void loop() {

//   delay(1000 * 0.1);
//   int redBright = map(array[0], 0, 255, 0, 256);
//   analogWrite(led_red, redBright);

//   int greenBright = map(array[1], 0, 255, 0, 256);
//   analogWrite(led_green, greenBright);

//   int blueBright = map(array[2], 0, 255, 0, 256);
//   analogWrite(led_blue, blueBright);
// }


// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
  
//   if(Serial.available() > 0) {
//     String tester = Serial.readString();
//     tester.trim();
//     if(tester == "red") {
//       Serial.println("Primary color");
//     } else {
//       Serial.println("Something else");
//     }
//   }
// }