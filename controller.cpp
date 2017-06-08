int switches[]={8,9,10,11};
int navigationVibration[]={12,13,2,3};
int pushVibration[]={4,5,6,7};
int pinSize_switches=sizeof(switches)/sizeof(int);
int pinSize_nv=sizeof(navigationVibration)/sizeof(int);
int pinsize_pv=sizeof(navigationVibration)/sizeof(int);
int readByte=0;

int currOnOff;
int prevOnOff=1;
int counterOnOff=0;

int currRed;
int prevRed=1;
int counterRed=0;

int currGreen;
int prevGreen=1;
int counterGreen=0;

int currBlue;
int prevBlue=1;
int counterBlue=0;

void switchOffPushVibration()
{
   for(int i=0;i<pinsize_pv;i++)
  {
    if(i>=1)
    pinMode(pushVibration[i],INPUT);
  }
}

void switchOffNavigationVibration()
{
  for(int i=0;i<pinSize_nv;i++)
  {
    pinMode(navigationVibration[i],INPUT);
  }  
}

void allOff()
{
  for(int i=0;i<pinSize_nv;i++)
  {
    pinMode(navigationVibration[i],INPUT);
  }
  for(int i=0;i<pinsize_pv;i++)
  {
    pinMode(pushVibration[i],INPUT);
  }
 prevRed=1;
 counterRed=0;
 prevGreen=1;
 counterGreen=0;
  prevBlue=1;
 counterBlue=0;
}

void checkPinstateOnOff()
{
   currOnOff=digitalRead(switches[0]);
// Serial.print(currOnOff);
  if(currOnOff==0&&prevOnOff==1)                                                         
  {
    prevOnOff=0;
    counterOnOff++;
  }
   if(counterOnOff==1)
    {
      counterOnOff++;
    //Serial.print("ONPush");
    }//send on byte
    if(counterOnOff==2)
    {
    pinMode(pushVibration[0],OUTPUT);
    digitalWrite(pushVibration[0],HIGH);
    }
    if(counterOnOff==3)
    {
    digitalWrite(pushVibration[0],LOW);
    pinMode(pushVibration[0],OUTPUT);
    counterOnOff=0;
    //Serial.print("OFFPush");//send off byte;
    Serial.write('F');
    allOff();
    }
  if(currOnOff==1&&prevOnOff==0)
  {
    prevOnOff=1;
  }
}

void checkPinstateRed()
{
   currRed=digitalRead(switches[1]);
  //Serial.print(currRed);  
  if(currRed==0&&prevRed==1)                                                         
  {
    prevRed=0;
    counterRed++;
  }
   if(counterRed==1)
    {
      counterRed++;
  //  Serial.print("ONRed");
    Serial.write('r');
    }//send on byte
    if(counterRed==2)
    {
    pinMode(pushVibration[1],OUTPUT);
    digitalWrite(pushVibration[1],HIGH);
    }
    if(counterRed==3)
    {
    digitalWrite(pushVibration[1],LOW);
    pinMode(pushVibration[1],INPUT);
    counterRed=0;
    //Serial.print("OFFRed");//send off byte;
    Serial.write('R');
    switchOffPushVibration();
    switchOffNavigationVibration();
    }
  if(currRed==1&&prevRed==0)
  {
    prevRed=1;
  }
  
}

void checkPinstateGreen()
{
   currGreen=digitalRead(switches[2]);
  //Serial.print(currRed);  
  if(currGreen==0&&prevGreen==1)                                                         
  {
    prevGreen=0;
    counterGreen++;
  }
   if(counterGreen==1)
    {
      counterGreen++;
  //  Serial.print("ONRed");
    Serial.write('g');
    }//send on byte
    if(counterGreen==2)
    {
    pinMode(pushVibration[2],OUTPUT);
    digitalWrite(pushVibration[2],HIGH);
    }
    if(counterGreen==3)
    {
    digitalWrite(pushVibration[2],LOW);
    pinMode(pushVibration[2],INPUT);
    counterGreen=0;
    //Serial.print("OFFRed");//send off byte;
    Serial.write('G');
    switchOffPushVibration();
    switchOffNavigationVibration();
    }
  if(currGreen==1&&prevGreen==0)
  {
    prevGreen=1;
  }
}

void checkPinstateBlue()
{
   currBlue=digitalRead(switches[3]);
  //Serial.print(currRed);  
  if(currBlue==0&&prevBlue==1)                                                         
  {
    prevBlue=0;
    counterBlue++;
  }
   if(counterBlue==1)
    {
      counterBlue++;
  //  Serial.print("ONRed");
    Serial.write('b');
    }//send on byte
    if(counterBlue==2)
    {
    pinMode(pushVibration[3],OUTPUT);
    digitalWrite(pushVibration[3],HIGH);
    }
    if(counterBlue==3)
    {
    digitalWrite(pushVibration[3],LOW);
    pinMode(pushVibration[3],INPUT);
    counterBlue=0;
    //Serial.print("OFFRed");//send off byte;
    Serial.write('B');
    switchOffPushVibration();
    switchOffNavigationVibration();
    }
  if(currBlue==1&&prevBlue==0)
  {
    prevBlue=1;
  }
}


void navigationVibrations()
{
  if(Serial.available()>0)
  {
    readByte = Serial.read();
    if(readByte=='u')
    {
      pinMode(navigationVibration[1],INPUT);
      pinMode(navigationVibration[2],INPUT);
      pinMode(navigationVibration[3],INPUT);
      pinMode(navigationVibration[0],OUTPUT);
      digitalWrite(navigationVibration[0],HIGH);
      //pinMode(navigationVibration[0],INPUT);
    }
    else if (readByte=='r')
    {
      pinMode(navigationVibration[0],INPUT);
      pinMode(navigationVibration[2],INPUT);
      pinMode(navigationVibration[3],INPUT);
      pinMode(navigationVibration[1],OUTPUT);
      digitalWrite(navigationVibration[1],HIGH);
      //pinMode(navigationVibration[1],INPUT);
    }
    else if (readByte=='d')
    {
      pinMode(navigationVibration[0],INPUT);
      pinMode(navigationVibration[1],INPUT);
      pinMode(navigationVibration[3],INPUT);
      pinMode(navigationVibration[2],OUTPUT);
      digitalWrite(navigationVibration[2],HIGH);
      //pinMode(navigationVibration[2],INPUT);
    }
    else if (readByte=='l')
    {
            pinMode(navigationVibration[0],INPUT);
            pinMode(navigationVibration[1],INPUT);
            pinMode(navigationVibration[2],INPUT);
            pinMode(navigationVibration[3],OUTPUT);
            digitalWrite(navigationVibration[3],HIGH);
      //pinMode(navigationVibration[3],INPUT);
    }
    else if (readByte=='x')
    {
      switchOffNavigationVibration();
    }
  }
}

void allNavigationVibrationOn()
{
  if(Serial.available()>0)
  {
    readByte=Serial.read();
  }
  if(readByte=='X')
  {
    for (int i=0;i<pinSize_nv;i++)
    {
      pinMode(navigationVibration[i],OUTPUT);
      digitalWrite(navigationVibration[i],HIGH);
    }
  }
}
void setup()
{
  Serial.begin(9600);
  allOff();
}

void loop()
{
 checkPinstateOnOff();
 if(digitalRead(pushVibration[0])==1)
 {
   checkPinstateRed(); 
   checkPinstateGreen();
   checkPinstateBlue();
}
navigationVibrations();
allNavigationVibrationOn();
}
