/*Laatste goede werking hoogste waarde uit Array
 * Voor Arduino micro or leonardo and analog sensor PT19
  Connection:

    VCC -> 3V3 or 5V
    GND -> GND
    A0 ->  Annalog output PT19 to A0 arduino

*/


#include <Keyboard.h>
#include <limits.h>

 
const int numReadings = 8;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;     



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



int sensorPin = A11;
int max_v = INT_MIN;
int max_i = 0;

//----------------------------------------------------------------------------------

void setup(){

  Serial.begin(115200);
  Keyboard.begin();

 luxMem1=220;
 luxMem2=370;
 luxMem3=560;
 luxMem4=800;
 luxMem5=1050;
 luxMem6=1350;
 luxMem7=1630;
 luxMem8=1925;
    
        

 for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
 

}




//----------------Begin main loop---------------------------------------------------------------------------------------


void loop() {


    if (Serial.available() > 0) {
            // read the incoming byte:
          incomingByte = Serial.read();

            if (incomingByte == 104) {   //ascii h    toon dit helpmenu
                   Serial.write(12);                                     //clear the screen for Putty
                   Serial.println("*****************************************");
                   Serial.println("** Optical input controller versie 1.0 **");
                   Serial.println("**   (c) Nov 2020 R D'Arcangelo.       **"); 
                   Serial.println("**  8 channel optical input switches.  **"); 
                   Serial.println("**      Bedrijf: Radboud/Donders.      **");
                   Serial.println("*****************************************");
                   Serial.println(" ");
                   Serial.println("Press C for Calibrate !!");
                   Serial.println("Press R for vieuw values !!");
                   Serial.println("Press K for Dataout as Keyboard !!");
                   Serial.println("Press S for Dataout as Serial !!");
                   Serial.println();
                   return;
            }

            if (incomingByte == 114) {                         // ascii r  Ga naar vieuw channels calibrate");
                  Serial.println(" ");
                  Serial.print("Channel 1  ");
                  Serial.println(luxMem1);
                  Serial.print("Channel 2  ");  
                  Serial.println(luxMem2);
                  Serial.print("Channel 3  ");
                  Serial.println(luxMem3);  
                  Serial.print("Channel 4  ");
                  Serial.println(luxMem4); 
                  Serial.print("Channel 5  "); 
                  Serial.println(luxMem5);  
                  Serial.print("Channel 6  ");
                  Serial.println(luxMem6); 
                  Serial.print("Channel 7  ");
                  Serial.println(luxMem7); 
                  Serial.print("Channel 8  "); 
                  Serial.println(luxMem8);                       
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
                  return;
                 }
                 

           if (incomingByte == 115) {                         //  s  data serial output);  
                     Serial.println("Serial set as output..!");
                     Serieel=true;
                     Keybord=false;           
                  return;
                 }

                 
                 
        }

 
//---------------------------channel filter----------------------------------------------


//lux = analogRead(sensorPin); 


// subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] =  analogRead(sensorPin);     // lightMeter.readLightLevel();   //analogRead(sensorPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  delay(1);

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:  
    readIndex = 0;
   }

  // calculate the average:
   average = total / numReadings;
  // send it to the computer as ASCII digits
 // Serial.println(average);

     //  lux=average;

 
 for ( int i = 0; i < sizeof(readings)/sizeof(readings[0]); i++ )
  {
    if ( readings[i] > max_v )       // get highest value from array
    delay(2);
    {
      max_v = readings[i];
      max_i = i;
   }
  }
 
       lux=max_v;
   
  
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
     


if ((luxMem1 - lux -test1 > -30) && (luxMem1 - lux-test1 < 30) && TTeller==0){ 
           test1 = lux-luxMem1;
          if (lux > 1){       
              luxMem1=lux;                        //button1
            } 
       if (Keybord==true){
           Keyboard.press('1');     
         }
       if (Serieel==true){
           Serial.print("1  ");
           Serial.print(lux);
           Serial.print(" ");
           Serial.println(lux-luxMem1);
         }     
        lux=0;
        max_v=0; 
        TTeller=0;     
}


   
if ((luxMem2 - lux-test2 > -30) && (luxMem2 - lux-test2  <30)&& TTeller==0){  
           test2 = lux-luxMem2;   
         if (lux > 1){            
              luxMem2=lux;                       //button2
         }      
       if (Keybord==true){
           Keyboard.press('2');     
         }
       if (Serieel==true){
           Serial.print("2  ");
           Serial.print(lux);
           Serial.print(" ");
           Serial.println(lux-luxMem2);
         }      
           lux=0;
           max_v=0;
           TTeller=0;
}

  
if ((luxMem3 - lux -test3 > -40) && (luxMem3 - lux-test3 < 40)&& TTeller==0){
           test3 = lux-luxMem3;  
          if (lux > 1){    
             luxMem3=lux;                        //button3
          }   
       if (Keybord==true){
           Keyboard.press('3');     
         }
       if (Serieel==true){
           Serial.print("3  ");
           Serial.print(lux);
           Serial.print(" ");
           Serial.println(lux-luxMem3);
         }      
          lux=0;
          max_v=0;
          TTeller=0;
 }

  
if ((luxMem4 - lux-test4 > -50) && (luxMem4 - lux-test4  < 50)&& TTeller==0){ 
           test4 = lux-luxMem4;
          if (lux > 1){  
            luxMem4=lux;                         //button4
          }
       if (Keybord==true){
           Keyboard.press('4');     
         }
       if (Serieel==true){
           Serial.print("4  ");
           Serial.print(lux);
           Serial.print(" ");
           Serial.println(lux-luxMem4);
         }      
          lux=0;
          max_v=0;
          TTeller=0;
}
  
if ((luxMem5 - lux-test5 > -50) && (luxMem5 - lux-test5 < 50)&& TTeller==0){
          test5 = lux-luxMem5;
        if (lux > 1){  
          luxMem5=lux;                         //button5
        }
       if (Keybord==true){
           Keyboard.press('5');     
         }
       if (Serieel==true){
           Serial.print("5  ");
           Serial.print(lux);
           Serial.print(" ");
           Serial.println(lux-luxMem5);
         }      
         lux=0;
         max_v=0;
         TTeller=0;
}

if ((luxMem6 - lux-test6 > -50) && (luxMem6 - lux-test6  < 50)&& TTeller==0){
          test6 = lux-luxMem6;
         if (lux > 1){  
            luxMem6=lux;                        //button6
         }
      if (Keybord==true){
           Keyboard.press('6');     
         }
       if (Serieel==true){
           Serial.print("6  ");
           Serial.print(lux);
           Serial.print(" ");
           Serial.println(lux-luxMem6);
         }      
         lux=0;
         max_v=0;
         TTeller=0;
}

 if ((luxMem7 - lux-test7  > -60) && (luxMem7 - lux-test7 < 60)&& TTeller==0){
           test7 = lux-luxMem7;
           if (lux > 1){  
             luxMem7=lux;                         //button7
           }
      if (Keybord==true){
           Keyboard.press('7');     
         }
       if (Serieel==true){
           Serial.print("7  ");
           Serial.print(lux);
           Serial.print(" ");
           Serial.println(lux-luxMem7);
         }      
          lux=0;
          max_v=0;
          TTeller=0;
}


  if ((luxMem8 - lux-test8 > -90) && (luxMem8 - lux-test8  < 90)&& TTeller==0){ 
            test8 = lux-luxMem8;
           if (lux > 1){  
             luxMem8=lux;                        //button8
            }
       if (Keybord==true){
           Keyboard.press('8');     
         }
       if (Serieel==true){
           Serial.print("8  ");
           Serial.print(lux);
           Serial.print(" ");
           Serial.println(lux-luxMem8);
         }      
            lux=0;
            max_v=0;
            TTeller=0;
      }

}


//----------------------end main loop------------------------------------------------------------------------







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
         Serial.println("Calibrate Done !!"); //loslaten knop 4
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
           luxMem1=lux;
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
           luxMem2=lux;
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
           luxMem3=lux;
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
           luxMem4=lux;
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
           luxMem5=lux;
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
           luxMem6=lux;
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
           luxMem7=lux;
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
           luxMem8=lux;
           Serial.println("Release Button..!");
           Gem=0;
           Teller=15; 
         }      
       }


//------------------------------einde 5...8.------------------------------------------  
       delay(100);     
     goto repaet;
}
