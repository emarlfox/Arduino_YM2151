#include <arduino.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include  "Common.h"
#include  "YM2414.h"

#define	DIRECT_IO

YM2414_Class	YM2414;

YM2414_Class::YM2414_Class()
{
}

void YM2414_Class::initLFO()
{
	write(0x1B, (1 << 4));
}

const char KeyCodeTable[] PROGMEM= {
	0x00,0x01,0x02,0x04,0x05,0x06,0x08,0x09,
	0x0a,0x0c,0x0d,0x0e,0x10,0x11,0x12,0x14,
	0x15,0x16,0x18,0x19,0x1a,0x1c,0x1d,0x1e,
	0x20,0x21,0x22,0x24,0x25,0x26,0x28,0x29,
	0x2a,0x2c,0x2d,0x2e,0x30,0x31,0x32,0x34,
	0x35,0x36,0x38,0x39,0x3a,0x3c,0x3d,0x3e,
	0x40,0x41,0x42,0x44,0x45,0x46,0x48,0x49,
	0x4a,0x4c,0x4d,0x4e,0x50,0x51,0x52,0x54,
	0x55,0x56,0x58,0x59,0x5a,0x5c,0x5d,0x5e,
	0x60,0x61,0x62,0x64,0x65,0x66,0x68,0x69,
	0x6a,0x6c,0x6d,0x6e,0x70,0x71,0x72,0x74,
	0x75,0x76,0x78,0x79,0x7a,0x7c,0x7d,0x7e,
};

/*! 音程を設定する
	\param ch				設定するチャンネル
	\param keycode			オクターブ0のD#を0とした音階、D# E F F# G G# A A# B (オクターブ1) C C# D....と並ぶ
	\param kf				音階微調整、64で1音分上がる。
 */
void YM2414_Class::setTone(uint8_t ch,uint8_t keycode,int16_t kf){
	int16_t	offset_kf = (kf & 0x3f);
	int16_t	offset_note = keycode + (kf >> 6);
	if(offset_note < 0)offset_note=0;
	if(offset_note > 0xbf)offset_note=0xbf;

	RegKFMONO[ch] = (offset_kf << 2) | RegKFMONO[ch] & 3;
    RegKC[ch] = pgm_read_byte_near(KeyCodeTable + offset_note) | RegKC[ch] & 0x80;
	
	write(0x30 + ch, RegKFMONO[ch]);
	write(0x28 + ch, RegKC[ch]);
}

void YM2414_Class::setPanpot(uint8_t ch,uint8_t pan)
{
    // // 1 = left, 2 = right, 3 = L+R
    RegFLCON[ch] = ((pan & 0x03) << 6) | (RegFLCON[ch] & 0x3F);
    write(0x20+ch, RegFLCON[ch]);

	RegKFMONO[ch] = (pan & 0x03) | (RegKFMONO[ch] & 0xFE);
	// RegKFMONO[ch] = (0 & 0x03) | (RegKFMONO[ch] & 0xFE);
	write(0x30 + ch, RegKFMONO[ch]);

    RegKC[ch] = ((pan & 0x01) << 7) | (RegKC[ch] & 0xFE);
    write(0x28 + ch, RegKC[ch]);

    // if ( pan & )
    // write(0x20+ch,
	// 	(pan<<6) | (RegFLCON[ch] ));
}
