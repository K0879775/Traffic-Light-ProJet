/* Project 5D - Creating the TRaffic Light with ambulance or police  car interaction for passing
 by Mahoutin ZiNvo

Add code to allow an ambulance or police car to force the traffic light green. 
 Use simple RF M4 receiver and rf remote control. 
  Check code in and out of GitHub. 
   Must show working prototype to instructor*/
   
/*PIN 0 to 6 define respectivelly Green, yellow, red,button, pedlight at west of the traffic and pedButton */
#define westGreen 0
#define westYellow 1
#define westRed 2
#define westButton 3
#define westPedLight 4
#define pedButton 6

/* PIN 9 to 13 define respectivelly Pedlight, Green, yellow, red and button at east of the traffic and PIN 7,8,for ambulance */
#define eastGreen 10
#define eastYellow 11
#define eastRed 12
#define eastButton 13
#define eastPedLight 9
#define RF_D0 7
#define RF_D1 8
//#define RF_D2 4



/* yellow blinking time*/
#define yellowBlinkTime 500

/* west = true, pedPassed = false*/
boolean trafficWest = true;
int flowTime = 1000;
int changeDelay = 2000;
bool pedPassed = false;


/*Pin button input and output Of the traffic light at west and east and PIN input of the ambulance*/
void setup() {
  pinMode(westButton, INPUT);
  pinMode(eastButton, INPUT);
  pinMode(westRed, OUTPUT);
  pinMode(westYellow, OUTPUT);
  pinMode(westGreen, OUTPUT);
  pinMode(eastRed, OUTPUT);
  pinMode(eastYellow, OUTPUT);
  pinMode(eastGreen, OUTPUT);

  pinMode(RF_D0, INPUT);
  pinMode(RF_D1, INPUT);
  //pinMode(4, INPUT);

  /*westRed of, WestYellow OFF westGreen ON ,EastRed ON, EastYellow OFF eastGreen OFF*/
  digitalWrite(westRed, LOW);
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);
  delay(5000);
}

/*West button can be used to Turn the traffic light west is true Or is not and also the ambulance LED turn ON and printing out for C button pressed*/
void loop() {
  if ((digitalRead(westButton) == HIGH) || (pedPassed)) {
    if (trafficWest != true) {
      trafficWest = true;
      delay(flowTime);
      if (digitalRead(RF_D0) == HIGH) {
        Serial.println("Button D Pressed");
      }
      if (digitalRead(RF_D1) == HIGH) {
        Serial.println("Button C Pressed");
      }

      //changing of the east green traffic light to Red
      digitalWrite(eastYellow, HIGH);
      delay(changeDelay);
      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, HIGH);
      delay(changeDelay);
      if (!pedPassed) changeGreenToRed(eastGreen, eastYellow, eastRed);
      pedPassed = false;
      //changing of the west yellow traffic ligh
      /*for (int a = 0; a < 5; a++) {
        digitalWrite(westYellow, LOW);
        delay(yellowBlinkTime);
        digitalWrite(westYellow, HIGH);
        delay(yellowBlinkTime);
      }*/
      changeYellowLight(westYellow);

      //changing of the west red traffic ligh to Green
      /* digitalWrite(westYellow, LOW);
      digitalWrite(westRed, LOW);
      digitalWrite(westGreen, HIGH);*/
      changeRedToGreen(westGreen, westYellow, westRed);
    }
  }
  /* East button can be used to turn ON or OFF the traffic ligh */
  if (digitalRead(eastButton) == HIGH || (pedPassed)) {
    if (trafficWest == true) {
      trafficWest = false;

      delay(flowTime);

      //changing of the west green traffic light  to Red
      /* digitalWrite(westGreen, LOW);
      digitalWrite(westYellow, HIGH);
      delay(changeDelay);
      digitalWrite(westYellow, LOW);
      digitalWrite(westRed, HIGH);
      delay(changeDelay);*/
      if (!pedPassed) changeGreenToRed(westGreen, westYellow, westRed);
      pedPassed = false;
      //changing of the east yellow traffic light
      /* for (int a = 0; a < 5; a++) {
        digitalWrite(eastYellow, LOW);
        delay(yellowBlinkTime);
        digitalWrite(eastYellow, HIGH);
        delay(yellowBlinkTime);
      }*/
      changeYellowLight(eastYellow);

      //changing of the East traffic light from Red to Green
      /*igitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, LOW);
      digitalWrite(eastGreen, HIGH);*/
      changeRedToGreen(eastGreen, eastYellow, eastRed);
    }
  }
  /* pedertrianLight turn ON or OFF at east and west of the traffic*/
  if ((digitalRead(pedButton) == HIGH)) {
    if (trafficWest) changeGreenToRed(westGreen, westYellow, westRed);  // turn off westGreen
    else changeGreenToRed(eastGreen, eastYellow, eastRed);              //turn off east Green

    turnOnOffPedestrianLight(eastPedLight, westPedLight);

    delay(1000);
  }
  if (digitalRead(RF_D0) == HIGH) {
    changeGreenToRed(westGreen, westYellow, westRed);  // turn off westGreen
    changeRedToGreen(eastGreen, eastYellow, eastRed);
    delay(1000);
  }
  if (digitalRead(RF_D1) == HIGH) {
    changeGreenToRed(eastGreen, eastYellow, eastRed);
    changeRedToGreen(westGreen, westYellow, westRed);
    delay(1000);
  }
}

//changing of the yellow traffic light color at  yellow direction
void changeYellowLight(int yellowDirection) {
  for (int a = 0; a < 5; a++) {
    digitalWrite(yellowDirection, LOW);
    delay(yellowBlinkTime);
    digitalWrite(yellowDirection, HIGH);
    delay(yellowBlinkTime);
  }
}
//changing of the traffic light ON and OFF between the traffic light
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

// turning ON And OFF of the pedestrianlight between eastpedlight and westpedlight whe the pedPassed is true
void turnOnOffPedestrianLight(int eastpedLight, int westpedLight) {
  digitalWrite(eastPedLight, HIGH);
  digitalWrite(westPedLight, HIGH);
  delay(2000);
  digitalWrite(westPedLight, LOW);
  digitalWrite(eastPedLight, LOW);
  pedPassed = true;
}
