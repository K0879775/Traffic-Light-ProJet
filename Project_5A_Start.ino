/* Project 5A - Creating the TRaffic Light 
 by Mahoutin ZiNvo*/

/*PIN 0 to 3 define respectivelly Green, yellow, red and button at west of the traffic*/
#define westGreen 0
#define westYellow 1
#define westRed 2
#define westButton 3

/* PIN 10 to 13define respectivelly Green, yellow, red and button at east of the traffic */
#define eastGreen 10
#define eastYellow 11
#define eastRed 12
#define eastButton 13

/* yellow blinking tine*/
#define yellowBlinkTime 500

/* west = true, east = false*/
boolean trafficWest = true;
int flowTime = 1000;
int changeDelay = 2000;


/*Pin button input and light color (red, yellow, green) output at west and east*/
void setup() {
  pinMode(westButton, INPUT);
  pinMode(eastButton, INPUT);
  pinMode(westRed, OUTPUT);
  pinMode(westYellow, OUTPUT);
  pinMode(westGreen, OUTPUT);
  pinMode(eastRed, OUTPUT);
  pinMode(eastYellow, OUTPUT);
  pinMode(eastGreen, OUTPUT);

  /*westRed of, WestYellow OFF westGreen ON ,EastRed ON, EastYellow OFF eastGreen OFF*/
  digitalWrite(westRed, LOW);
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);
  delay(5000);
}

/*West button can be at usedb to Turn the Colrs traffic ligh ON Or OFF*/
void loop() {
  if (digitalRead(westButton) == HIGH) {
    if (trafficWest != true) {
      trafficWest = true;
      delay(flowTime);
      /*digitalWrite(eastGreen, LOW);

//changing of the east traffic ligh from Green to Red
      digitalWrite(eastYellow, HIGH);
      delay(changeDelay);
      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, HIGH);
      delay(changeDelay);*/
      changeGreenToRed(eastGreen, eastYellow, eastRed);

      //changing of the west yellow traffic ligh
      /*for (int a = 0; a < 5; a++) {
        digitalWrite(westYellow, LOW);
        delay(yellowBlinkTime);
        digitalWrite(westYellow, HIGH);
        delay(yellowBlinkTime);
      }*/
      changeYellowLight(westYellow);

      //changing of the west traffic ligh from Red to Green
      /* digitalWrite(westYellow, LOW);
      digitalWrite(westRed, LOW);
      digitalWrite(westGreen, HIGH);*/
      changeRedToGreen(westGreen, westYellow, westRed);
    }
  }
  /* East button can be used to turn ON or OFF the traffic ligh */
  if (digitalRead(eastButton) == HIGH) {
    if (trafficWest == true) {
      trafficWest = false;
      delay(flowTime);

      //changing of the west traffic ligh from Green to Red
      /* digitalWrite(westGreen, LOW);
      digitalWrite(westYellow, HIGH);
      delay(changeDelay);
      digitalWrite(westYellow, LOW);
      digitalWrite(westRed, HIGH);
      delay(changeDelay);*/
      changeGreenToRed(westGreen, westYellow, westRed);

      //changing of the east yellow traffic ligh
      /* for (int a = 0; a < 5; a++) {
        digitalWrite(eastYellow, LOW);
        delay(yellowBlinkTime);
        digitalWrite(eastYellow, HIGH);
        delay(yellowBlinkTime);
      }*/
      changeYellowLight(eastYellow);

      //changing of the East traffic ligh from Red to Green
      /*igitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, LOW);
      digitalWrite(eastGreen, HIGH);*/
      changeRedToGreen(eastGreen, eastYellow, eastRed);
    }
  }
}
//changing of the yellow traffic ligh color betweem direction
void changeYellowLight(int yellowDirection) {
  for (int a = 0; a < 5; a++) {
    digitalWrite(yellowDirection, LOW);
    delay(yellowBlinkTime);
    digitalWrite(eastYellow, HIGH);
    delay(yellowBlinkTime);
  }
}
//changing of the traffic ligh between Color trafic ligh
void changeGreenToRed(int green, int yellow, int red) {
  digitalWrite(green, LOW);

  digitalWrite(yellow, HIGH);
  delay(changeDelay);
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  delay(changeDelay);
}
//changing of the  traffic ligh from Red to Green
void changeRedToGreen(int green, int yellow, int red) {
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
}
