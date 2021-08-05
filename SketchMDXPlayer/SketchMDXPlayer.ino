/*
	SketchMDXPlayer	v0.31
	author:ISH
*/
// #include	"YM2151.h"
#include "YM2414.h"
#include	"IO.h"
#include	"MMLParser.h"
#include	"MDXParser.h"

IO				io;
MDXParser		mdx;

int32_t		waittime=0;
uint32_t		proctime=0;

void setup()
{
Serial.begin(9600);
	io.Init();
	YM2414.begin();
	YM2414.write(0x09, 0x00);
	YM2414.write(0x0F, 0x00);
	YM2414.write(0x1C, 0x00);
	YM2414.write(0x1E, 0x00);
	YM2414.write(0x0A, 0x04);
	YM2414.write(0x14, 0x70);
	YM2414.write(0x15, 0x01);
	mdx.Setup(0x2800);
	mdx.Elapse(0);
}

void loop()
{
	waittime = mdx.ClockToMicroSec(1);
	waittime -= proctime;
	while(waittime > 0){
		if(waittime > 16383){
			delayMicroseconds(16383);
			waittime -= 16383;
		} else {
			delayMicroseconds(waittime);
			waittime = 0;
		}
	}
	proctime = micros();
	mdx.Elapse(1);
	proctime = micros() - proctime;
}
