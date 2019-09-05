
#define switchL 2
#define switchR 3
#define switchB 4
#define lightFL 6
#define lightFR 7
#define lightRL 8
#define lightRR 9

unsigned long Time; //what the current time is
bool isontime; //if blinker should be on or off
int flshcntr; //how many times it's flashed
int flserstate; //the flasher state

void setup() {

  for(int i=2;i<5;i++){  //Inputs switchL,switchR,switchB
    pinMode(i,INPUT);
    digitalWrite(i,HIGH);
  }
  for(int i=6;i<10;i++){ //outputs for lights
    pinMode(i,OUTPUT);
  }  
}

void loop() {

  //see if this is an ontime or off time for the blinker
  unsigned long curr = millis();
  if(curr-Time>=500){
    isontime =!isontime;
    Time = curr;
  }
  int blnk = isontime ? HIGH:LOW;

  bool L = digitalRead(switchL)==LOW;
  bool R = digitalRead(switchR)==LOW;
  bool B = digitalRead(switchB)==LOW;
  if (!B)flshcntr=0;


  if(B && !L && !R){ //this should flash
    digitalWrite(lightFL,LOW);
    digitalWrite(lightFR,LOW);

    if(flshcntr<=10){
        digitalWrite(lightRL,flserstate);
        digitalWrite(lightRR,flserstate);
        flshcntr++;
        flserstate = flserstate ? LOW:HIGH;
        delay(100);
    }else{
        digitalWrite(lightRL,HIGH);
        digitalWrite(lightRR,HIGH);
    }   
  }else if(B && L){ //right break on solid, left flashes
    digitalWrite(lightFL,blnk);
    digitalWrite(lightFR,LOW);
    digitalWrite(lightRL,blnk);
    digitalWrite(lightRR,HIGH);
  }else if(B && R){ //left break on solid, right flashes
    digitalWrite(lightFL,LOW);
    digitalWrite(lightFR,blnk);
    digitalWrite(lightRL,HIGH);
    digitalWrite(lightRR,blnk);
  }else if(!B && L){ //left flashes
    digitalWrite(lightFL,blnk);
    digitalWrite(lightFR,LOW);
    digitalWrite(lightRL,blnk);
    digitalWrite(lightRR,LOW);
  }else if(!B && R){ //right flashes
    digitalWrite(lightFL,LOW);
    digitalWrite(lightFR,blnk);
    digitalWrite(lightRL,LOW);
    digitalWrite(lightRR,blnk);
  }else{ //no break or turn signals, fronts stay on as marker signals
    digitalWrite(lightFL,LOW);
    digitalWrite(lightFR,LOW);
    digitalWrite(lightRL,LOW);
    digitalWrite(lightRR,LOW);
  }

}
