#include <Wire.h>

//======================================================
//-----------SLAVE CODE---------------------------------
//======================================================

//Specify which pins we're using
#define REDPIN 11
#define GREENPIN 9
#define BLUEPIN 6
#define HEARTPIN 3

//Set up our initial colors
byte red=0,green=0,blue=0;

//We can't use Serial.print inside of the interrupts, so we buffer it to 
// str and print it in the main loop.
String str="";

//Store the last number of bytes, for testing purposes
byte lastNumBytes=0;


void setup(){
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); //set up the interrupt function when the slave gets data
  
  Serial.begin(9600);           // start serial for output

  //set up everything as outputs
  pinMode(HEARTPIN,OUTPUT);
  pinMode(REDPIN,OUTPUT);
  pinMode(BLUEPIN,OUTPUT);
  pinMode(GREENPIN,OUTPUT);

}

void loop(){

  //Check to see if we have data, then print it
  if(str!=""){
    //Print out any data/error messages, and erase the buffer
    Serial.println(str);
    str="";

    //Flip an LED for our debugging. 
    digitalWrite(HEARTPIN,!digitalRead(HEARTPIN));
  }
  
 
  //Write out the values that we get in the interrupt function
  analogWrite(REDPIN,red);
  analogWrite(BLUEPIN, blue);
  analogWrite(GREENPIN,green);

  //put this in here just because. Realistically, it's not needed.
  delay(25);
}


//Will run whenever we are given data
void receiveEvent(int numBytes){
  
  //Make sure we got what we expected from the master
  if(numBytes==3){
    red=Wire.read();
    green=Wire.read();
    blue=Wire.read();
    
    str+="r"+String(red);
    str+=" g"+String(green);
    str+=" b"+String(blue);
  }
  //Something went wrong! 
  //cycle through all available bytes, and put them on the serial terminal
  else{
    byte data;
    str+=String(numBytes);
    str+=" bytes: ";
    while(Wire.available()){
      data=Wire.read();
      str+=String(data);
      str+=" ";
      } 
    }
    
   
}

