#include <Wire.h>
#include <math.h>

//======================================================
//-----------MASTER CODE---------------------------------
//======================================================
void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
}

#define RESOLUTION 64 
#define PERIOD  2000 //milliseconds
byte red=0;
byte green=0;
byte blue=0;
float theta=0;
void loop()
{
  theta=(theta+PI/RESOLUTION);
  if(theta>2*PI)theta-=2*PI;

  //Create some fun patterns  
  red=128+sin(theta)*127;
  
  green=128+cos(theta)*127;

  blue=128+sin(theta*1.5)*127;

  //Send it to the slaaaaave
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(red);        
  Wire.write(green);              
  Wire.write(blue);              
  Wire.endTransmission();    // stop transmitting

  //wait however long we need to to hit our period
  delay(PERIOD/RESOLUTION);
  
}
//will run whenever we are asked to write data
void receiveRequest(){}

