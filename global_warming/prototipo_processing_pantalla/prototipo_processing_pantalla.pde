

import processing.serial.*;

Serial myPort;
PImage pg1;

String image_name;
String image_path;
String in_string = ""; 
int first_year = 2010;
int year; 
float avg_temp = 0.0;

void setup() {
  size(1366, 768); // size del canvas
 
  colorMode(HSB, 360, 100, 100);
  background(0, 0, 100);
  image_path = "data/images/"; 
  image_name = "world_map.png";
  pg1 = loadImage(image_path + image_name); 
  if (Serial.list().length == 0) { 
    println("No hay ningun puerto serie. Se debe conectar el Arduino.");
  } else {
    
    myPort = new Serial(this, Serial.list()[0], 9600);
    myPort.bufferUntil ( '\n' );
  }

  year = 2010; 
}

void draw() { 
  background(0, 0, 100);
  while (myPort.available() > 0) { 
    in_string = myPort.readStringUntil(10); 
    if (in_string != null) { 
      int in = Integer.parseInt(in_string.trim());
      if (in == 1) { // button has been pushed
        switch_map();
      } else if (in >= 2010) {// si in >= 2010 significa que lo que hemos enviado pòr el puerto serie desde arduino va a ser interpretado como el año
        year = in;
      }
    }
  }
  pg1 = loadImage(image_path + image_name);
  image(pg1, 0, 0);


  if (image_name == "world_map.png") { 
    boolean draw_temp = true;
    draw_legend(draw_temp);
    draw_temperature_circles(year);
  } else if (image_name == "amazonas.png") {
    boolean draw_temp = false;
    draw_legend(draw_temp);
    draw_deforestation();
  }
}


void switch_map() {
  if (image_name == "world_map.png") {
   image_name = "amazonas.png";
    //background(0, 0, 100);
  } else { 
    image_name = "world_map.png";
    //background(0, 0, 100);
  }
}



void draw_temperature_circles(int year) {
  String[] countries = { "Alaska", "Groelandia", "Suecia", "Rusia", "Canada", "Alemania", "Kazastan", "Mongolia", "Japon", "USA", "Turkia", "China", "Mexico", "Algeria", "India", "Colombia", "Congo", "Indonesia", "Brasil", "Surafrica", "Sudan", "ArabiaSaudi", "Australia", "Argentina", "Antartida"};
  int[][] coords = {{289, 116}, {630, 83}, {785, 130}, {1037, 130}, {380, 153}, {774, 181}, {980, 188}, {1108, 195}, {1255, 244}, {367, 230}, {869, 232}, {1115, 250}, {338, 306}, {745, 287}, {1046, 315}, {442, 403}, {827, 430}, {1190, 423}, {530, 483}, {824, 560}, {850, 347}, {906, 301}, {1257, 539}, {492, 580}, {780, 776}};
  float [] temps = {-10, -10, 6, -5.35, -5, 9.5, 8, 3, 14, 9.98, 12.90, 8, 21, 22.50, 24, 25.5, 25, 25.8, 26, 17.75, 27.90, 26.65, 26.25, 16.5, -20 };
  // rates de crecimeinto anual de la temperatura por pais
  float [] rates = {0.08, 0.09, 0.09, 0.1, 0.12, 0.1, 0.1, 0.09, 0.09, 0.12, 0.13, 0.08, 0.11, 0.08, 0.09, 0.09, 0.1, 0.08, 0.1, 0.09, 0.13, 0.13, 0.12, 0.08, 0.29};
  float [] radius = {25, 40, 14, 88, 30, 25, 40, 20, 6, 80, 16, 50, 20, 40, 37, 22, 50, 20, 50, 20, 25, 35, 40, 30, 50};
  // -20 36 -> 0 - 100
  int year_diff = year - 2010;
  avg_temp = 0.0;
  for (int i = 0; i < countries.length; i++) {
    float new_temp = (temps[i] + year_diff * rates[i]);
    // https://keisan.casio.com/exec/system/14059930973581
    // correlacion regresion exponencial (y = A * (B^X)) donde y seria la saturacion A y B son unas constantes calcualdas en
    // casio.com  y x es la temperatura nueva + 20 grados (para normalizar la in)
    // https://www.varsitytutors.com/assets/vt-hotmath-legacy/hotmath_help/topics/exponential-regression/f-er-1-1.gif
    int saturation = ceil(7.308924088 * pow(1.048150237, new_temp + 20)); // sumanos el 20 par anormalizar
    fill(0, saturation, 100);
    circle(coords[i][0], coords[i][1], radius[i]);
    avg_temp += new_temp;
  }
  avg_temp = avg_temp/temps.length;
}

void draw_legend(boolean draw_temp) {
  fill(0, 0, 0);
  textSize(45);
  // https://processing.org/reference/strconvert_.html
  text("Year: " + str(year), 1000, 100); // str es una funcion de processing para trasnformar de un tipo de dato a string, en este caso de int a string
  
  if (draw_temp == true) {
    text("Temp: " + nf(avg_temp, 0, 1), 1000, 150); // https://processing.org/reference/nf_.html
  }
}

void draw_deforestation() {
  String[] countries = { "Bolivia", "Brasil", "Colombia", "Ecuador", "Guyana", "Guyana Francesa", "Peru", "Surinam", "Venezuela"};
  int[][] coords = {{645, 576}, {714, 380}, {495, 255}, {417, 309}, {755, 164}, {871, 202}, {429, 370}, {816, 197}, {640, 174}, };
  float [] rates = {0.6, 2.9, 0.3, 0.3, 0.3, 0.3, 0.6, 0.6, 0.9 };
  float [] radius = {25, 50, 27, 15, 10, 15, 25, 10, 20};
  //
  int year_diff = year - 2010;
  for (int i = 0; i < countries.length; i++) {
    fill(30, 100, 54);
    circle(coords[i][0], coords[i][1], radius[i] + year_diff*rates[i]);
  }
}


/*void mousePressed() {
 print("{" + mouseX + "," + mouseY + "}, ");
 }*/


/*
https://en.wikipedia.org/wiki/List_of_countries_by_average_yearly_temperature
 
 2010 -> 14.5 (Temperatura promedio global)
 2060 -> 22
 
 289 116 -> Alaska -> -10 -> 0.08
 630 73  -> Groelandia -> -10 -> 0.09
 782 130 -> Suecia -> 6 -> 0.09
 1037 128 -> Rusia -> −5.35 -> 0.1
 380 153 -> Canada -> -5 -> 0.12
 774 181 -> Alemania -> 9.5 -> 0.1
 980 194 -> Kazastan -> 8 -> 0.1
 1136 186 -> Mongolia -> 3 -> 0.09
 1255 244 -> Japon -> 14 -> 0.09
 378 229 -> USA -> 9.98 -> 0.12
 873 234 -> Turkia -> 12.90 -> 0.13
 1122 241 -> China -> 8 -> 0.08
 336 306 -> Mexico -> 21 -> 0.11
 749 297 -> Algeria -> 22.50 -> 0.08
 1042 325 -> India -> 24 -> 0.09
 442 395 -> Colombia -> 25.5 -> 0.09
 827 430 -> Republica democratica del Congo -> 25 -> 0.1
 1190 423 -> Indonesia -> 25.8-> 0.08
 530 483 -> Brasil -> 26 -> 0.1
 829 555 -> Surafrica -> 17.75 -> 0.09
 850 347 -> Sudan -> 27.90 -> 0.13
 906 301 -> Arabia Saudi -> 26.65 -> 0.13
 1257 539 -> Australia -> 26.25 -> 0.12
 488 592 -> Argentina -> 16.5 -> 0.08
 961 776 -> Antartida -> -20 -> 0.1
 
 
 
 
 
 2010 2020 2040 2060
 
 Bolivia 3% 6.87% 8.4% 10.05% N
 
 Brasil 5% 60.3% 70.24% 36.18% F
 
 Colombia 3% 6.95% 5.56% 4.17% S
 
 Ecuador 10.7% 1.48% 1.18% 0.885% S
 
 Guyana 3.2% 3.02% 2.41% 1.80% S
 
 Guyana francesa 3.2% 3.2% 2.41% 1.80% S
 
 Peru 9.1% 11.3% 9.04% 6.78% N
 
 Surinam 3.2% 2.1% 2.41% 1.80% N
 
 Venezuela 3.3% 6.73% 5.384% 4.038%  F
 
 
 
 
 
 */
