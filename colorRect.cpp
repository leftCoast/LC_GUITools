#include "colorRect.h"


colorRect::colorRect(void)
	: drawObj(),colorObj() {
	
	setInset(0);
}


colorRect::colorRect(rect* inRect,colorObj* inColor,int inset)
	: drawObj(inRect),colorObj() {
	
	setColor(inColor);
	setInset(inset);
}


colorRect::colorRect(int inLocX,int inLocY,int inWidth,int inHeight,colorObj* inColor,int inset)
  : drawObj(inLocX,inLocY,inWidth,inHeight),colorObj() {
	
	setColor(inColor);
	setInset(inset);
}	

	
colorRect::colorRect(int inLocX, int inLocY, int inWidth,int inHeight,int inset)
  : drawObj(inLocX,inLocY,inWidth,inHeight),
  colorObj(LC_WHITE) { setInset(inset); }
  
  
colorRect::~colorRect(void) { }


void colorRect::setInset(int inset) {

    mInset = inset;
    needRefresh = true;
}


void colorRect::drawSelf(void) {

	colorObj	insetTLColor;
	colorObj	insetBRColor;
	int		ii;

	screen->fillRect(x, y, width, height, (colorObj*)this);
	if (mInset) {
		if (mInset>0) {
			insetTLColor = mixColors(&black,50);
    		insetBRColor = mixColors(&white,50);
    	} else {
    		insetTLColor = mixColors(&white,50);
    		insetBRColor = mixColors(&black,50);
    	}
		for (int i=0;i<abs(mInset);i++) {
			ii = 2*i;
			screen->drawHLine( x+i, y+i,width-(1+ii), &insetTLColor);
			screen->drawVLine( x+i, y+i,height-(1+ii), &insetTLColor);
			screen->drawHLine( x+i, y+height-(1+i), width-(1+ii), &insetBRColor);
			screen->drawVLine( x+width-(1+i), y+1+i, height-(1+ii), &insetBRColor);
		}
	}
}


void colorRect::setColor(byte r,byte g,byte b) {

  colorObj::setColor(r,g,b);
  needRefresh = true;
}


void colorRect::setColor(word color16) {

  colorObj::setColor(color16);
  needRefresh = true;
}


void colorRect::setColor(colorObj* inColor) {

  colorObj::setColor(inColor);
  needRefresh = true;
}


void colorRect::setLocation(int inX, int inY)								{ drawObj::setLocation(inX,inY); setNeedRefresh(); }
void colorRect::setSize(int inWidth,int inHeight)							{ drawObj::setSize(inWidth,inHeight); setNeedRefresh(); }
void colorRect::setRect(rect* inRect)											{ drawObj::setRect(inRect); setNeedRefresh(); }
void colorRect::setRect(point* inPt1,point* inPt2)							{ drawObj::setRect(inPt1,inPt2); setNeedRefresh(); }			
void colorRect::setRect(int inX, int inY, int inWidth,int inHeight)	{ drawObj::setRect(inX,inY,inWidth,inHeight); setNeedRefresh(); }
void colorRect::insetRect(int inset)											{ drawObj::insetRect(inset); setNeedRefresh(); }
void colorRect::addRect(rect* inRect)											{ drawObj::addRect(inRect); setNeedRefresh(); }


