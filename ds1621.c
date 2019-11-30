//**************************************************************
//   ******** FUNCTIONS FOR DS1621 TEMP SENSOR  *******
//**************************************************************
//Controller:	ATmega8 (1Mhz Crystal)
//Compiler:		ICCAVR
//Author:		CC Dharmani, Chennai (India)
//			www.dharmanitech.com
//Date:			Sep 2008
//**************************************************************
#include "ds1621.h"
#include "i2c_routines.h"
#include <string.h>

unsigned char tempDisplay[] = "+xx.x";

//******************************************************************
//Function to send command
//******************************************************************    
void ds1621_init()
{
  unsigned char errorStatus, data;
  
  errorStatus = i2c_start();
   if(errorStatus == 1)
   {
   	 i2c_stop();
  	 return;
   } 
   
   errorStatus = i2c_sendAddress(DS1621_W);
   
   if(errorStatus == 1)
   {
  	 i2c_stop();
  	 return;
   } 
   
   errorStatus = i2c_sendData(ACCESS_CONFIG);
   if(errorStatus == 1)
   {
  	 i2c_stop();
  	 return;
   } 
   
   errorStatus = i2c_sendData(0x03);   //commmand to set o/ppolarity high, single shot conversion
   if(errorStatus == 1)
   {
  	 i2c_stop();
	 return;
   } 

   i2c_stop();
}

//******************************************************************
//Function to send command
//******************************************************************    
void ds1621_sendCommand(unsigned char command)
{
  unsigned char errorStatus, i, data;
  
  errorStatus = i2c_start();
   if(errorStatus == 1)
   {
   	 i2c_stop();
	 return;
   } 
   
   errorStatus = i2c_sendAddress(DS1621_W);
   
   if(errorStatus == 1)
   {
	 i2c_stop();
	 return;
   } 
   
   errorStatus = i2c_sendData(command);
   if(errorStatus == 1)
   {
	 i2c_stop();
	 return;
   } 

   i2c_stop();
}

//******************************************************************
//Function to read 
//******************************************************************    

unsigned char ds1621_readValue(unsigned char value)
{
  unsigned char errorStatus, data;
  
  errorStatus = i2c_start();
   if(errorStatus == 1)
   {
   	 i2c_stop();
	 return (0);
   } 
   
   errorStatus = i2c_sendAddress(DS1621_W);
   
   if(errorStatus == 1)
   {
	 i2c_stop();
	 return (0);
   } 
   
   errorStatus = i2c_sendData(value);
   if(errorStatus == 1)
   {
	 i2c_stop();
	 return (0);
   } 

    errorStatus = i2c_repeatStart();
   if(errorStatus == 1)
   {
   	 i2c_stop();
	 return (0);
   } 
   
    errorStatus = i2c_sendAddress(DS1621_R);
   
   if(errorStatus == 1)
   {
	 i2c_stop();
	 return (0);
   } 
 
   data = i2c_receiveData_NACK(); 
   
   i2c_stop();
   
   return (data);
}	  

//******************************************************************
//Function to read 
//******************************************************************    
signed char getTemperature(void)
{ 
  ds1621_sendCommand ( START_CONVERT );
  
  _delay_ms(1000);
  
  return ds1621_readValue ( READ_TEMP );
}