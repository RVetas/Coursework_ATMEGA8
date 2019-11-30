#define  DS1621_W			0x90
#define  DS1621_R			0x91

#define	 START_CONVERT		0xEE
#define	 STOP_CONVERT		0x22
#define	 READ_TEMP			0xAA
#define	 READ_COUNTER		0xA8
#define	 READ_SLOPE			0xA9
#define  ACCESS_CONFIG		0xAC
#include <util/delay.h>
void ds1621_init ( void );
void ds1621_sendCommand ( unsigned char );
unsigned char ds1621_readValue ( unsigned char );
signed char getTemperature ( void );

