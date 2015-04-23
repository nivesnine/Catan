int shiftData1 = 1;
int shiftClock1 = 2;
int shiftData2 = 3;
int shiftClock2 = 4;
int shiftData3 = 5;
int shiftClock3 = 6;
int shiftData4 = 7;
int shiftClock4 = 8;
int shiftData5 = 9;
int shiftClock5 = 10;
int shiftDataButtons = 11;
int shiftClockButtons = 12;
int shiftLatchButtons = 13;
int rollButton = A1;
int shiftData7seg = A2;
int shiftClock7seg = A3;

int ledsOne[] = {0,1,3,7,15,31,63,127,255};
int ledsTwo[] = {0,1,3,7,15,31,63,127,255};
int ledsThree[] = {0,1,3,7,15,31,63,127,255};
int ledsFour[] = {0,1,3,7,15,31,63,127,255};
                  //p1    p2   p3   p4
int ledsFive[] = {0,8,136,4,68,2,34,1,17};

int counterP1 = 0;
int counterP2 = 0;
int counterP3 = 0;
int counterP4 = 0;

int die1 = 0;
int die2 = 0;
int getDice = 0;
            //0   1   2   3   4   5   6   7   8   9   10 11  12
int dice[] = {255,249,164,176,153,146,130,248,128,152,64,121,36};
int dieButton = 0;

char buttonsIn[] = {'p1up','p2up','p3up','p4up','p1dn','p2dn','p3dn','p4dn'};

byte buttons = 0;
byte ledsOn = 0;

int count = 0;
int endCount = 0;

void setup(){
    pinMode(rollButton, INPUT);    // button inputs
  
    pinMode(shiftData1,OUTPUT);
    pinMode(shiftClock1,OUTPUT);
    
    pinMode(shiftData2,OUTPUT);
    pinMode(shiftClock2,OUTPUT);   
    
    pinMode(shiftData3,OUTPUT);
    pinMode(shiftClock3,OUTPUT);
    
    pinMode(shiftData4,OUTPUT);
    pinMode(shiftClock4,OUTPUT);

    pinMode(shiftData5,OUTPUT);
    pinMode(shiftClock5,OUTPUT);

    pinMode(shiftDataButtons, INPUT);
    pinMode(shiftLatchButtons,OUTPUT);
    pinMode(shiftClockButtons,OUTPUT); 
   
    pinMode(shiftData7seg, OUTPUT);
    pinMode(shiftClock7seg, OUTPUT);
    
    Serial.begin(9600);
}

void loop(){
  
  while(counterP1 < 10 && counterP2 < 10 && counterP3 < 10 && counterP4 < 10){
  randomSeed(analogRead(0));
  dieButton = digitalRead(rollButton);
  
  if (dieButton == HIGH) {
    die1 = random(1,7);
    die2 = random(1,7);
    getDice = die1 + die2;
    update7seg(); 
  }
  
  updateButtons();
  
  switch (buttons){
    case B10000000:
      counterP1 = counterP1 + 1;
      updateP1();
      break;
    case B01000000:
      counterP2 = counterP2 + 1;
      updateP2();
      break;
    case B00100000:
      counterP3 = counterP3 + 1;
      updateP3();
      break;
    case B00010000:
      counterP4 = counterP4 + 1;
      updateP4();
      break;
    case B00001000:
      if (counterP1 > 0){
        if (counterP1 == 9){
          ledsOn = ledsOn - ledsFive[1];
          shiftOut(shiftData5,shiftClock5,LSBFIRST,ledsOn);
        }
        counterP1 = counterP1 - 1;
        updateP1();
      }
      break;
    case B00000100:
      if (counterP2 > 0){
        if (counterP2 == 9){
          ledsOn = ledsOn - ledsFive[3];
          shiftOut(shiftData5,shiftClock5,LSBFIRST,ledsOn);
        }
        counterP2 = counterP2 - 1;
        updateP2();
      }
      break;
    case B00000010:
      if (counterP3 > 0){
        if (counterP3 == 9){
          ledsOn = ledsOn - ledsFive[5];
          shiftOut(shiftData5,shiftClock5,LSBFIRST,ledsOn);
        }
        counterP3 = counterP3 - 1;
        updateP3();
      }
      break;
    case B00000001:
      if (counterP4 > 0){
        if (counterP4 == 9){
          ledsOn = ledsOn - ledsFive[7];
          shiftOut(shiftData5,shiftClock5,LSBFIRST,ledsOn);
        }
        counterP4 = counterP4 - 1;
        updateP4();
      }
      break;
    default:
      break;
  }
  }
  delay(3000);
  while (endCount < 19){
    
    counterP1 = 0;
    counterP2 = 0;
    counterP3 = 0;
    counterP4 = 0;
    updateP1();     
    updateP2();
    updateP3();
    updateP4();
    
    while(count < 11){
    counterP1 = counterP1 + 1;
    counterP2 = counterP2 + 1;
    counterP3 = counterP3 + 1;
    counterP4 = counterP4 + 1;
    updateP1();
    delay(10);    
    updateP2();
    delay(10);
    updateP3();
    delay(10);
    updateP4();
    delay(10);
    }
    endCount = endCount + 1;
  }
}

void update7seg(){
  shiftOut(shiftData7seg,shiftClock7seg,LSBFIRST,dice[getDice]);
}
void updateButtons(){
  digitalWrite(shiftLatchButtons,HIGH);
  delayMicroseconds(20);
  digitalWrite(shiftLatchButtons,LOW);
  buttons = shiftIn(shiftDataButtons, shiftClockButtons, LSBFIRST);
}
void updateP1(){
  if (counterP1 <= 8){
    shiftOut(shiftData1, shiftClock1, LSBFIRST,ledsOne[counterP1]);
  }
  if (counterP1 == 9){
    ledsOn = ledsOn + ledsFive[1];
    shiftOut(shiftData5, shiftClock5, LSBFIRST,ledsOn);
  }
  if (counterP1 == 10){
    ledsOn = ledsOn + ledsFive[2];
    shiftOut(shiftData5, shiftClock5, LSBFIRST,ledsOn);
  }
}
void updateP2(){
  
  if (counterP2 <= 8){
    shiftOut(shiftData2, shiftClock2, LSBFIRST,ledsTwo[counterP2]);
  }
  if (counterP2 == 9){
    ledsOn = ledsOn + ledsFive[3];
    shiftOut(shiftData5, shiftClock5, LSBFIRST,ledsOn);
  }
  if (counterP2 == 10){
    ledsOn = ledsOn + ledsFive[4];
    shiftOut(shiftData5, shiftClock5, LSBFIRST,ledsOn);
  }
}
void updateP3(){
  
  if (counterP3 <= 8){
    shiftOut(shiftData3, shiftClock3, LSBFIRST,ledsThree[counterP3]);
  }
  if (counterP3 == 9){
    ledsOn = ledsOn + ledsFive[5];
    shiftOut(shiftData5, shiftClock5, LSBFIRST,ledsOn);
  }
  if (counterP3 == 10){
    ledsOn = ledsOn + ledsFive[6];
    shiftOut(shiftData5, shiftClock5, LSBFIRST,ledsOn);
  }
}
void updateP4(){
  
  if (counterP4 <= 8){
    shiftOut(shiftData4, shiftClock4, LSBFIRST,ledsFour[counterP4]);
  }
  if (counterP4 == 9){
    ledsOn = ledsOn + ledsFive[7];
    shiftOut(shiftData5, shiftClock5, LSBFIRST,ledsOn);
  }
  if (counterP4 == 10){
    ledsOn = ledsOn + ledsFive[8];
    shiftOut(shiftData5, shiftClock5, LSBFIRST,ledsOn);
  }
}
