#ifndef flasher_h
#define flasher_h


// flasher.h contains the base classe for flashing things on the screen. Basically a two
// frame sprit that repeats.


#include <drawObj.h>
#include <squareWave.h>


// *****************************************************
//                        flasher
// *****************************************************

// flasher is a drawObj that has two states that automatically flip back and forth.
// The default is a two color rectangle changing colors every 1/2 second.

class flasher :	public drawObj,
						public squareWave {

	public:
				flasher(rect* inRect,colorObj* offColor=&black,colorObj* onColor=&red);
				flasher(int inLocX,int inLocY,int inWidth,int inHeight,colorObj* offColor=&black,colorObj* onColor=&red);
					
	virtual	~flasher(void);
	
	virtual	void	setColors(colorObj* onColor,colorObj* offColor);
	virtual	void	drawSelf(void);
	virtual	void	pulseOn(void);                                                   
	virtual	void	pulseOff(void);
	
	protected:
				colorObj		mForeColor;
				colorObj		mBackColor;
				bool			mFlash;
};

#endif
