#if !defined( YM2414_H_INCLUDED )
#define YM2414_H_INCLUDED
#include "YM2151.h"

class YM2414_Class: public YM2151_Class {
	public:
		YM2414_Class();
		virtual void initLFO();
        virtual void setPanpot(uint8_t ch,uint8_t pan);
		virtual void setTone(uint8_t ch,uint8_t keycode,int16_t kf);

    protected:
		uint8_t	RegKFMONO[8];
		uint8_t RegKC[8];
};

extern YM2414_Class YM2414;
#endif // YM2414_H_INCLUDED