#ifndef rectObj_h
#define rectObj_h

#include <drawObj.h>

// This just frames a rect in your choice of colors. Want to fill the rect? See colorRect.
class rectObj : public drawObj {

	public:
				rectObj(rect* inRect);
	virtual	~rectObj(void);
	
				void	setColor(colorObj* inColor);
	virtual	void	drawSelf();
  
  				colorObj	color;
};

#endif