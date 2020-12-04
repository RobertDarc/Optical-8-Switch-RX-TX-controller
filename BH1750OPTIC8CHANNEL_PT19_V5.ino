/*Laatste goede werking hoogste waarde uit Array                         *
 * Voor Arduino micro or leonardo and analog sensor PT19                 *
 * 29-11-2020 range aangepast van -30 30 naar -5 5 deze werkt nu goed.   *
 * Robert D'Arcangelo     V5 gemaakt met select case                                                *
 *************************************************************************
  Connection:

    VCC -> 3V3 or 5V
    GND -> GND
    A11 ->  Annalog input PT19 to A11 arduino

*/

#include <EEPROM.h>
#include <Keyboard.h>
#include <limits.h>




int READings[8];
int READindex=0;
int index = 0 ; 





 
const int numReadings = 5;      // array  for data annalog
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;     

int Trigger = 13;

int MEM1addr = 0;
int MEM2addr = 1;
int MEM3addr = 2;
int MEM4addr = 3;
int MEM5addr = 4;    //eeprom adress   cali
int MEM6addr = 5;
int MEM7addr = 6;
int MEM8addr = 7;

int MEM9addr  = 9;
int MEM10addr = 10;
int MEM11addr = 11;
int MEM12addr = 12;
int MEM13addr = 13;    //eeprom adress   Remap
int MEM14addr = 14;
int MEM15addr = 15;
int MEM16addr = 16;



byte MEM1 = 0;
byte MEM2 = 0;
byte MEM3 = 0;
byte MEM4 = 0;
byte MEM5 = 0;
byte MEM6 = 0;
byte MEM7 = 0;
byte MEM8 = 0;


char CH1=49;
char CH2=50;
char CH3=51;
char CH4=52;
char CH5=53;
char CH6=54;
char CH7=55;
char CH8=56;





long luxC=0;
long luXx=0;
long lux=0;
long luxMem1=0;
long luxMem2=0;
long luxMem3=0;
long luxMem4=0;
long luxMem5=0;
long luxMem6=0;
long luxMem7=0;
long luxMem8=0;


int Teller=0;
int TTeller=0;
bool X=false;
bool Y=false;
bool Keybord=false;
bool Serieel=true;
bool Testmode=false;

int incomingByte = 0;

int myArray[4];
int i=0;
long Gem=0;
long Gemm=0;

int test8=0;
int test7=0;
int test6=0;
int test5=0;
int test4=0;
int test3=0;
int test2=0;
int test1=0;

int selector=0;

int sensorPin = A0;    //light sensor inputpin  leonardo
int max_v = INT_MIN;
int max_i = 0;


int max_min = INT_MAX;
int maxx_i = 0;


//----------------------------------------------------------------------------------

void setup(){

  Serial.begin(115200);
  Keyboard.begin();



MEM1= EEPROM.read(MEM1addr);
luxMem1=MEM1*4;
MEM2= EEPROM.read(MEM2addr);
luxMem2=MEM2*4;
MEM3= EEPROM.read(MEM3addr);
luxMem3=MEM3*4;
MEM4= EEPROM.read(MEM4addr);
luxMem4=MEM4*4;
MEM5= EEPROM.read(MEM5addr);
luxMem5=MEM5*4;
MEM6= EEPROM.read(MEM6addr);
luxMem6=MEM6*4;
MEM7= EEPROM.read(MEM7addr);
luxMem7=MEM7*4;
MEM8= EEPROM.read(MEM8addr);
luxMem8=MEM8*4;


CH1= EEPROM.read(MEM9addr);

CH2= EEPROM.read(MEM10addr);

CH3= EEPROM.read(MEM11addr);

CH4= EEPROM.read(MEM12addr);

CH5= EEPROM.read(MEM13addr);

CH6= EEPROM.read(MEM14addr);

CH7= EEPROM.read(MEM15addr);

CH8= EEPROM.read(MEM16addr);





     

pinMode(Trigger, OUTPUT);


        

 for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
 

}




//----------------Begin main loop---------------------------------------------------------------------------------------


void loop() {


//digitalWrite(Trigger, HIGH);   //Trigger pin 2 HIGH



    if (Serial.available() > 0) {
            // read the incoming byte:
          incomingByte = Serial.read();

           if (incomingByte == 105){   // asci I voor info vb2010 tool
                   Serial.write(12);                                     //clear the screen for Putty      
                   Serial.println("           *****************************************");
                   Serial.println("           ** Optical input controller versie 1.5  **");
                   Serial.println("           **   (c) Nov 2020 R D'Arcangelo.       **"); 
                   Serial.println("           **  8 channel optical input switches.  **"); 
                   Serial.println("           **      Company: Radboud/Donders.  **");
                   Serial.println("           *****************************************"); 
                   Serial.println(" ");
                   Serial.println("Connection ok !!");
                    
           }
        
            if (incomingByte == 104) {   //ascii h    toon dit helpmenu
                   Serial.write(12);                                     //clear the screen for Putty      
                   Serial.println("*****************************************");
                   Serial.println("** Optical input controller versie 1.5 **");
                   Serial.println("**   (c) Nov 2020 R D'Arcangelo.       **"); 
                   Serial.println("**  8 channel optical input switches.  **"); 
                   Serial.println("**      Company: Radboud/Donders.      **");
                   Serial.println("*****************************************");
                   Serial.println(" ");
                   Serial.println("Press C for calibrate !!");
                   Serial.println("Press R for vieuw values !!");
                   Serial.println("Press K for data out as keyboard !!");
                   Serial.println("Press S for data out as serial !!");
                   Serial.println("Press M for remap char to PC !!");
                   Serial.println("Press T for Testmode vieuw !!");
                   Serial.println();
                   return;
            }

            if (incomingByte == 114) {                         // ascii r  Ga naar vieuw channels calibrate");
              
                  Serial.println(" "); 
                  Serial.print("Calibrate 1 = ");   
                  Serial.print(MEM1*4);
                  Serial.print("    ");
                  Serial.print("Pc-char = ");
                  Serial.println(CH1);                 
                  Serial.print("Calibrate 2 = ");  
                  Serial.print(MEM2*4);
                  Serial.print("    ");
                  Serial.print("Pc-char = ");
                  Serial.println(CH2);
                  Serial.print("Calibrate 3 = ");
                  Serial.print(MEM3*4); 
                  Serial.print("   ");
                  Serial.print("Pc-char = ");
                  Serial.println(CH3);                   
                  Serial.print("Calibrate 4 = ");
                  Serial.print(MEM4*4); 
                  Serial.print("   ");
                  Serial.print("Pc-char = ");
                  Serial.println(CH4);                  
                  Serial.print("Calibrate 5 = "); 
                  Serial.print(MEM5*4);
                  Serial.print("   ");
                  Serial.print("Pc-char = ");
                  Serial.println(CH5);                   
                  Serial.print("Calibrate 6 = ");
                  Serial.print(MEM6*4); 
                  Serial.print("   ");
                  Serial.print("Pc-char = ");
                  Serial.println(CH6);                 
                  Serial.print("Calibrate 7 = ");
                  Serial.print(MEM7*4); 
                  Serial.print("   ");
                  Serial.print("Pc-char = ");
                  Serial.println(CH7);                 
                  Serial.print("Calibrate 8 = "); 
                  Serial.print(MEM8*4); 
                  Serial.print("   ");
                  Serial.print("Pc-char = ");
                  Serial.println(CH8); 
                                                              
                  return;
                 }



            if (incomingByte == 99) {                         // ascii c  Ga naar Calibreren);
                  Serial.println("Calibreren..!");  
                  Serial.println("Please press each button one a time.");  
                  Teller=0;   
                  CAL();                
                  return;
                 }
                 
            if (incomingByte == 107) {                         //  k  data keyboard output);  
                   Serial.println("Keyboard set as output..!"); 
                   Keybord=true; 
                   Serieel=false;
                   Testmode=false; 
                  return;
                 }
                 

           if (incomingByte == 115) {                         //  s  data serial output);  
                     Serial.println("Serial set as output..!");
                     Serieel=true;
                     Keybord=false;  
                     Testmode=false;          
                  return;
                 }
                 
          if (incomingByte == 109) {                         //   m  for remap char to PC;  
                     Serial.println("Remap char to Pc..!");
                      REMAP();                        
                    return;
                 }
          if (incomingByte == 116) {                         //   t  for testmode values vieuw;  
                     Serial.println("Testmode activ..!");
                     Serieel=false;
                     Keybord=false;  
                     Testmode=true;                           
                    return;
                 }
                 
                 
        }

 
//---------------------------channel filter----------------------------------------------


//int luxR = analogRead(sensorPin); 
  //readings[0,1,2,3,4,5,6,7]=0;

    // subtract the last reading:
    // total = total - readings[readIndex];
    // read from the sensor:
  readings[readIndex] =  analogRead(sensorPin);     // lightMeter.readLightLevel();   //analogRead(sensorPin);
   // add the reading to the total:
  //  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  delay(1);


 // Serial.print(readings[0]);
 // Serial.print(" ");
 // Serial.print(readings[1]);
 // Serial.print(" ");
 // Serial.print(readings[2]);
 // Serial.println(" ");
 // Serial.print(readings[3]);
 // Serial.print(" ");
 // Serial.print(readings[4]);
 // Serial.print(" ");
  //Serial.print(readings[5]);
 // Serial.print(" ");
 // Serial.print(readings[6]);
 // Serial.print(" ");
 // Serial.print(readings[7]);
 // Serial.println("");
 //*/
  
 
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:  
     readIndex = 0;  
   }

  // calculate the average:
 //  average = total / numReadings;
  // send it to the computer as ASCII digits
 // Serial.println(average);

    //   lux=average;    //gemiddelde uit array     




 //----------------------------------------------------------------------------------------------


//max_v = readings[readIndex];  // just to start it off
//for (byte n = 0; n < 7; n++) {
  // if (readings[n] > max_v) {
      //  max_v = readings[n];
  // }
//}


 for ( int i = 0; i < sizeof(readings)/sizeof(readings[0]); i++ )
  {
    if ( readings[i] > max_v )       // get highest value from array
    delay(2);
    {
      max_v = readings[i];
    //  max_i = i;
      
   }
 }
 
//---------------------------------------------------------------------
       
          lux=max_v;   //hoogste waarde uit array

 
//----------------------array2-----------------------------------------------------------------------


READings[0]=luxMem1-lux;
READings[1]=luxMem2-lux;
READings[2]=luxMem3-lux;
READings[3]=luxMem4-lux;
READings[4]=luxMem5-lux;
READings[5]=luxMem6-lux;
READings[6]=luxMem7-lux;
READings[7]=luxMem8-lux;


             

// for ( int u = 0; u < sizeof(READings)/sizeof(READings[0]); u++ )
 // {
    //if ( READings[u] > max_min )       // get highest value from array
   // delay(2);
   // {
   //   max_min = READings[u];
    //  max_i = i;
      
  // }
   
 //}

//Serial.println(max_min);

            
//-------------------------------------------------------------------



  
   if (lux <1){
          Y=false;       //Loslaten
           Keyboard.releaseAll();  
           lux=0;
           max_v=0;   
  }
   if (lux >0){
         Y=true;       //indrukken
      //  Serial.println(lux);
      
  } 
   if (TTeller==1 && Y==false){  //loslaten knop 
       TTeller=0;     
  }

if (Y==true){ 

               for (byte i = 0; i < 8; i = i+1) {
                       // Serial.println(READings[i]);   
                      //   delay(2);
                   if (READings[i] > -15 && READings[i] < 15){
                  //   if (READings[i] >= -15 && READings[i] <= 15 ){
                       delay(2);
                       //  Serial.println(i);                      
                     selector = i;                                                             

   switch (selector) {
       case 0:
               if (Keybord==true){
                  Keyboard.press(CH1);     
                  }   
              if (Serieel==true){
                 Serial.println(CH1);
                  } 
              if (Testmode==true){
                 Serial.print(CH1);
                 Serial.print(" ");
                 Serial.print(lux);
                 Serial.print(" ");
                // Serial.println(lux-luxMem1);  
                 Serial.println(READings[0]);
                 }                     
                 break;
        case 1:
             if (Keybord==true){
                 Keyboard.press(CH2);   
                 }
             if (Serieel==true){
                 Serial.println(CH2);
                 }
             if (Testmode==true){
                 Serial.print(CH2);
                 Serial.print(" ");
                 Serial.print(lux);
                 Serial.print(" ");
               //  Serial.println(lux-luxMem2); 
                 Serial.println(READings[1]);
                 }      
                 break;
        case 2:
              if (Keybord==true){
                  Keyboard.press(CH3);    
                  }
              if (Serieel==true){
                  Serial.println(CH3);
                  }
              if (Testmode==true){
                  Serial.print(CH3);
                  Serial.print(" ");
                  Serial.print(lux);
                  Serial.print(" ");
                //  Serial.println(lux-luxMem3);
                  Serial.println(READings[2]);
                 }          
                 break;
        case 3:            
             if (Keybord==true){
                  Keyboard.press(CH4);    
                 }
             if (Serieel==true){
                  Serial.println(CH4);
                 }
             if (Testmode==true){
                 Serial.print(CH4);
                 Serial.print(" ");
                 Serial.print(lux);
                 Serial.print(" ");
                // Serial.println(lux-luxMem4);
                 Serial.println(READings[3]);
                 }                                        
                 break;
        case 4: 
             if (Keybord==true){
                 Keyboard.press(CH5);     
                 }
             if (Serieel==true){
                 Serial.println(CH5);
                 }
             if (Testmode==true){
                 Serial.print(CH5);
                 Serial.print(" ");
                 Serial.print(lux);
                 Serial.print(" ");
                // Serial.println(lux-luxMem5);
                 Serial.println(READings[4]);
                 }      
                 break;
        case 5:
              if (Keybord==true){
                 Keyboard.press(CH6);     
                 }
              if (Serieel==true){
                 Serial.println(CH6);
                 }
              if (Testmode==true){
                  Serial.print(CH6);
                  Serial.print(" ");
                  Serial.print(lux);
                  Serial.print(" ");
               //   Serial.println(lux-luxMem6);
                  Serial.println(READings[5]);
                  }          
                  break;
        case 6: 
              if (Keybord==true){
                  Keyboard.press(CH7);     
                  }
              if (Serieel==true){
                  Serial.println(CH7);
                  }
              if (Testmode==true){
                  Serial.print(CH7);
                  Serial.print(" ");
                  Serial.print(lux);
                  Serial.print(" ");
               //   Serial.println(lux-luxMem7);
                  Serial.println(READings[6]);
                  }      
                  break;
       case 7:
              if (Keybord==true){
                  Keyboard.press(CH8);     
                  }
              if (Serieel==true){
                  Serial.println(CH8);
                  }
              if (Testmode==true){
                  Serial.print(CH8);
                  Serial.print(" ");
                  Serial.print(lux);
                  Serial.print(" ");
                 // Serial.println(lux-luxMem8);
                  Serial.println(READings[7]);
                  }                                        
                  break;           
      default:
               // statements
                  break;
                  }    
      
         
         }
          // Serial.println(max_min); 
           }

     }
      
//  Serial.println(lux);


//--------------------------------------------------------------------------------------------------------
 
/*
 if ((luxMem1 - lux  > -10) && (luxMem1 - lux < 10) && TTeller==0)
        { 
          //  test1 = lux-luxMem1;                   
             luxMem1=lux;                 //button1
                     
       if (Keybord==true){
           Keyboard.press(CH1);     
         }   
       if (Serieel==true){
           Serial.println(CH1);
       } 
       if (Testmode==true){
            Serial.print(CH1);
            Serial.print(" ");
            Serial.print(lux);
            Serial.print(" ");
            Serial.println(lux-luxMem1);  
         }     
        lux=0;
        max_v=0; 
        TTeller=0;   
      
}

if ((luxMem2 - lux > -10) && (luxMem2 - lux <10)&& TTeller==0)
       {  
          //  test2 = lux-luxMem2;                            
            luxMem2=lux;                       //button2 
                 
       if (Keybord==true){
           Keyboard.press(CH2);     
         }
       if (Serieel==true){
           Serial.println(CH2);
        }
       if (Testmode==true){
            Serial.print(CH2);
            Serial.print(" ");
            Serial.print(lux);
            Serial.print(" ");
            Serial.println(lux-luxMem2); 
         }      
           lux=0;
           max_v=0;
           TTeller=0;
}
 
if ((luxMem3 - lux -test3 > -10) && (luxMem3 - lux-test3 < 10)&& TTeller==0)
         {
             test3 = lux-luxMem3;               
             luxMem3=lux;                        //button3 
              
       if (Keybord==true){
           Keyboard.press(CH3);     
         }
       if (Serieel==true){
           Serial.println(CH3);
         }
       if (Testmode==true){
            Serial.print(CH3);
            Serial.print(" ");
            Serial.print(lux);
            Serial.print(" ");
            Serial.println(lux-luxMem3);
         }      
          lux=0;
          max_v=0;       
          TTeller=0;
 }

 
if ((luxMem4 - lux-test4 > -10) && (luxMem4 - lux-test4  < 10)&& TTeller==0)
        { 
            test4 = lux-luxMem4;             
            luxMem4=lux;                         //button4
            
       if (Keybord==true){
           Keyboard.press(CH4);     
         }
       if (Serieel==true){
           Serial.println(CH4);
         }
       if (Testmode==true){
            Serial.print(CH4);
            Serial.print(" ");
            Serial.print(lux);
            Serial.print(" ");
            Serial.println(lux-luxMem4);
         }      
          lux=0;
          max_v=0;
          TTeller=0;
}

 
if ((luxMem5 - lux-test5 > -10) && (luxMem5 - lux-test5 < 10)&& TTeller==0)
       {
           test5 = lux-luxMem5;             
           luxMem5=lux;                         //button5
           
       if (Keybord==true){
           Keyboard.press(CH5);     
         }
       if (Serieel==true){
           Serial.println(CH5);
         }
       if (Testmode==true){
            Serial.print(CH5);
            Serial.print(" ");
            Serial.print(lux);
            Serial.print(" ");
            Serial.println(lux-luxMem5);
         }      
         lux=0;
         max_v=0;
         TTeller=0;
}

if ((luxMem6 - lux-test6 > -10) && (luxMem6 - lux-test6  < 10)&& TTeller==0)
       {
            test6 = lux-luxMem6;       
            luxMem6=lux;                        //button6
            
      if (Keybord==true){
           Keyboard.press(CH6);     
         }
       if (Serieel==true){
           Serial.println(CH6);
         }
       if (Testmode==true){
            Serial.print(CH6);
            Serial.print(" ");
            Serial.print(lux);
            Serial.print(" ");
            Serial.println(lux-luxMem6);
         }      
         lux=0;
         max_v=0;
         TTeller=0;
}

 if ((luxMem7 - lux-test7  > -10) && (luxMem7 - lux-test7 < 10)&& TTeller==0)
       {
           test7 = lux-luxMem7;                  
           luxMem7=lux;                         //button7
           
      if (Keybord==true){
           Keyboard.press(CH7);     
         }
       if (Serieel==true){
           Serial.println(CH7);
         }
       if (Testmode==true){
            Serial.print(CH7);
            Serial.print(" ");
            Serial.print(lux);
            Serial.print(" ");
            Serial.println(lux-luxMem7);
         }      
          lux=0;
          max_v=0;
          TTeller=0;
}

 if ((luxMem8 - lux-test8 > -10) && (luxMem8 - lux-test8  < 10)&& TTeller==0)
       { 
            test8 = lux-luxMem8;
            luxMem8=lux;                        //button8
       
       if (Keybord==true){
           Keyboard.press(CH8);     
         }
       if (Serieel==true){
           Serial.println(CH8);
         }
       if (Testmode==true){
           Serial.print(CH8);
           Serial.print(" ");
           Serial.print(lux);
           Serial.print(" ");
           Serial.println(lux-luxMem8);
         }      
            lux=0;
            max_v=0;
            TTeller=0;
      }


//digitalWrite(Trigger, LOW);    //Trigger pin 2 low
//delay(100);
*/
}

//----------------------end main loop------------------------------------------------------------------------


void  REMAP()
{

bool pressed= true;
int count=0;
      Serial.println("");
      Serial.println("Remap function.");
      Serial.println("Select any key from keyboard..!");
Repaet:



 if (Serial.available() > 0) {
            // read the incoming byte:
         incomingByte = Serial.read();

      //  Serial.println(incomingByte);

         if (Serial.available() == 0){
             pressed=true;
           }
         
         if (incomingByte > 0 && pressed==true){
             count++;
             pressed= false;  
             Serial.print("CH"); 
             Serial.print(count);
             Serial.print("=");
         } 

    if (count==1){
                   CH1=incomingByte;
                  Serial.println(CH1);
                  EEPROM.write(MEM9addr, CH1);
    }

    if (count==2){
                   CH2=incomingByte;
                   Serial.println(CH2);
                   EEPROM.write(MEM10addr, CH2);
    }

    if (count==3){
                   CH3=incomingByte;
                  Serial.println(CH3);
                  EEPROM.write(MEM11addr, CH3);
    }
    
    if (count==4){
                   CH4=incomingByte;
                  Serial.println(CH4);
                  EEPROM.write(MEM12addr, CH4);
    }

    if (count==5){
                   CH5=incomingByte;
                  Serial.println(CH5);
                  EEPROM.write(MEM13addr, CH5);
    }

    if (count==6){
                   CH6=incomingByte;
                  Serial.println(CH6);
                  EEPROM.write(MEM14addr, CH6);
    }

    if (count==7){
                   CH7=incomingByte;
                  Serial.println(CH7);
                  EEPROM.write(MEM15addr, CH7);
    }

    if (count==8){
                   CH8=incomingByte;
                  Serial.println(CH8);
                  EEPROM.write(MEM16addr, CH8);
    }
                                           

      if (count==8)
        {
          Serial.println("Remapping finisch..!!");
          count=0; 
          return;
         }       
    }
   goto Repaet;     
}



//------------------------einde remapping------------------------------------------------------------------------------




void CAL()           //calibrate the channels
{

      Serial.println("");
      Serial.println("Press button 1");
      
   repaet: 
      for (i = 0; i <= 4; i++){
           luXx =   analogRead(sensorPin);      //lightMeter.readLightLevel();      
           delay(1);
           Gem=Gem+luXx;
         }    
           lux=(Gem/5);  
           delay(5);    
           Gem=0;
     
     
  if (lux <1){
    X=false;       //Loslaten
  }
   if (lux >1){
    X=true;       //indrukken
  //  Serial.println(lux);
  }

 

      if (Teller==1 && X==false){
       Serial.println("Press button 2");  //loslaten knop 1
       Teller=2;     
     }

     if (Teller==3 && X==false){
       Serial.println("Press button 3");  //loslaten knop 2
       Teller=4;     
     }

      if (Teller==5 && X==false){
       Serial.println("Press button 4"); //loslaten knop 3
       Teller=6;     
     }

   if (Teller==7 && X==false){
       Serial.println("Press button 5"); //loslaten knop 4
       Teller=8;  
     }  
   
//------------------------------einde 1...5.------------------------------------------  

   
      if (Teller==9 && X==false){
         Serial.println("Press button 6");  //loslaten knop 5
         Teller=10;     
     }

     if (Teller==11 && X==false){
         Serial.println("Press button 7");  //loslaten knop 6
         Teller=12;     
     }

      if (Teller==13 && X==false){
          Serial.println("Press button 8"); //loslaten knop 7
          Teller=14;
     } 
     
      if (Teller==15 && X==false){
         Serial.println(" "); //loslaten knop 8
         delay(250);
         Serial.println("Calibrate Done !!"); //loslaten knop 4
           MEM1= EEPROM.read(MEM1addr);
           luxMem1=MEM1*4;      
           MEM2= EEPROM.read(MEM2addr);
           luxMem2=MEM2*4;      
           MEM3= EEPROM.read(MEM3addr);
           luxMem3=MEM3*4;      
           MEM4= EEPROM.read(MEM4addr);
           luxMem4=MEM4*4;      
           MEM5= EEPROM.read(MEM5addr);
           luxMem5=MEM5*4;      
           MEM6= EEPROM.read(MEM6addr);
           luxMem6=MEM6*4;      
           MEM7= EEPROM.read(MEM7addr);
           luxMem7=MEM7*4;      
           MEM8= EEPROM.read(MEM8addr);
           luxMem8=MEM8*4;      
       
       // Serial.println("Write values to EEprom done !!"); //loslaten knop 4
         Teller=16;
         return;
     } 

 
//-------------einde 4 ....8----------------------------------------------------------
 
     if (lux >0 && Teller==0){
          for (int i = 0; i <= 4; i++){
           lux =       analogRead(sensorPin);             // lightMeter.readLightLevel();      // button 1
           delay(100);
           Gem=Gem+lux;
           lux=(Gem/5);  
           delay(5);    
           //Serial.println(lux);
          }
        if (lux > 1){
           Serial.println(lux);
         //  luxMem1=lux*2;
          EEPROM.write(MEM1addr, lux/4);
           Serial.println("Release Button..!");
           Gem=0;
           Teller=1;
        }       
       }


     if (lux >0 && Teller==2){
         for (int i = 0; i <= 4; i++){
       lux =       analogRead(sensorPin);              // lightMeter.readLightLevel();    //button 2
           delay(100);
           Gem=Gem+lux;
           lux=(Gem/5);  
           delay(5);    
          // Serial.println(lux);
         }
        if (lux > 1){
           Serial.println(lux);
         //  luxMem2=lux*2;
         EEPROM.write(MEM2addr, lux/4);
           Serial.println("Release Button..!");
           Gem=0;
           Teller=3;
        }       
       }

    if (lux >0 && Teller==4){
        for (int i = 0; i <= 4; i++){
           lux =    analogRead(sensorPin);               //  lightMeter.readLightLevel();    //button 3
           delay(100);
           Gem=Gem+lux;
           lux=(Gem/5);  
           delay(5);   
          // Serial.println(lux);
         }
         if (lux > 1){
           Serial.println(lux);
          // luxMem3=lux*2;
          EEPROM.write(MEM3addr, lux/4);
           Serial.println("Release Button..!");
           Gem=0;
           Teller=5; 
         }      
       }
       
      if (lux >0 && Teller==6){
         for (int i = 0; i <= 4; i++){
           lux =    analogRead(sensorPin);            // lightMeter.readLightLevel();    //button 4
           delay(100);
           Gem=Gem+lux;
           lux=(Gem/5);  
           delay(5);
         //  Serial.println(lux);
         }
        if (lux > 1){
           Serial.println(lux);
         //  luxMem4=lux*2;
         EEPROM.write(MEM4addr, lux/4);
           Serial.println("Release Button..!");
           Gem=0;
           Teller=7;
        }       
       }

//------------------------------einde 1...4.------------------------------------------  

      if (lux >0 && Teller==8){
           for (int i = 0; i <= 4; i++){
           lux =      analogRead(sensorPin);         //lightMeter.readLightLevel();    //button 5
           delay(100);
           Gem=Gem+lux;
           lux=(Gem/5);  
           delay(5);
         }
         if (lux > 1){
           Serial.println(lux);
       //    luxMem5=lux*2;
          EEPROM.write(MEM5addr, lux/4);
           Serial.println("Release Button..!");
           Gem=0;
           Teller=9; 
         }      
       }

      if (lux >0 && Teller==10){
            for (int i = 0; i <= 4; i++){
           lux =     analogRead(sensorPin);             //lightMeter.readLightLevel();    //button 6
           delay(100);
           Gem=Gem+lux;
           lux=(Gem/5);  
           delay(5);
         }  
         if (lux > 1){
           Serial.println(lux);
         //  luxMem6=lux*2;
          EEPROM.write(MEM6addr, lux/4);
           Serial.println("Release Button..!");
           Gem=0;
           Teller=11;  
         }     
       }

    if (lux >0 && Teller==12){
          for (int i = 0; i <= 4; i++){
           lux =   analogRead(sensorPin);               //lightMeter.readLightLevel();    //button 7
           delay(100);
           Gem=Gem+lux;
           lux=(Gem/5);  
           delay(5);
         }
         if (lux > 1){
           Serial.println(lux);
         //  luxMem7=lux*2;
          EEPROM.write(MEM7addr, lux/4);
           Serial.println("Release Button..!");
           Gem=0;
           Teller=13; 
         }      
       }
       
      if (lux >0 && Teller==14){
          for (int i = 0; i <= 4; i++){
           lux =    analogRead(sensorPin);               //lightMeter.readLightLevel();    //button 8
           delay(100);
           Gem=Gem+lux;
           lux=(Gem/5);  
           delay(5);
         }
         if (lux > 1){
             Serial.println(lux);
         //  luxMem8=lux*2;
         EEPROM.write(MEM8addr, lux/4);        //lux*2-70/4
           Serial.println("Release Button..!");
           Gem=0;
           Teller=15; 
         }      
       }


//------------------------------einde 5...8.------------------------------------------  
       delay(100);     
     goto repaet;
}
