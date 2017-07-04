/*
 * main.cpp
 *
 * Created: 2015-01-13 오후 8:16:49
 *  Author: kkim
 */ 

#include "iot.h"
#include <string.h>
#include <ctype.h>

#define		CLOCK_TIMER			iotTimer::iotcTimer3
#define		TIMEOUT_TIMER		iotTimer::iotcTimer2
#define		SERVO_MOTOR_TIMER	iotTimer::iotcTimer0
#define		UART_TERMINAL		iotUart::iotcUart1
#define		UART_SENSOR			iotUart::iotcUart0
// #define		LED_PORT		PORTB
// #define		EX_KEY			PINB

static iotCharLcd	*CharLcd = (iotCharLcd *) NULL;
static iotDht		*Dht = (iotDht *) NULL;

//-----------------------------------------------------------------------------
//	switch
//-----------------------------------------------------------------------------
// static char				LastKey = 0;
static void
inputKey()
{
/*
	volatile char    key;

	key = ~EX_KEY & 0xc0;
	if(key == LastKey) return;
	LastKey = key;
	iotCharLcd::delay(200);
*/
}

//-----------------------------------------------------------------------------
//	parser
//-----------------------------------------------------------------------------
static void
parseLine(char *s) {
	CharLcd->print(2, 1, s);
	if(iotFpSensor::parseLine(s)) return;
	if(Dht->parseLine(s)) return;
	if(iotServo::parseLine(s)) return;
	if(iotClock::parseLine(s)) return;
	if(iotDustSensor::parseLine(s)) return;
	printf("unknown\n");
}

//-----------------------------------------------------------------------------
//	main -
//-----------------------------------------------------------------------------
int
main(void)
{
	cli();

	// initialize the clock: Jun-17 10:00:00 at row 1 of char LCD.
	iotClock::init(CLOCK_TIMER, 14472000L, (iotCharLcd *) NULL, 1);
	CharLcd = iotClock::getCharLcd();

	// initialize Terminal
	iotTerminal::init(UART_TERMINAL);

	// initialize Finger Print Sensor
	iotFpSensor::init(UART_SENSOR, TIMEOUT_TIMER);	// PORTE

	// initialize Servo Motor
	iotServo::init(iotPin::iotcPB0);			// PORTB: VCC=R, GND=B, PWM=O
	
	sei();

	// use PE0 & PE1 for RX0 & TX0, and PC0 for DHT11
	Dht = new iotDht(iotPin::iotcPC0);				// PORTC
	iotDustSensor::init(iotPin::iotcPF1, iotPin::iotcPF0);	// PORTF

	char	*s;
	while(1) {
		iotClock::processOne();
		CharLcd->processOne();
		iotTerminal::processOne();
		iotFpSensor::processOne();
		if((s = iotTerminal::getLine())) parseLine(s);
		inputKey();
	}
}