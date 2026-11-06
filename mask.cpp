#include <mask.h>
#include <debug.h>


mask* gMask = NULL;

// *************************************
//     The -tiny- mask base class.
// *************************************


mask::mask(void) { setInverse(false); }
mask::~mask(void) {  }

void mask::setInverse(bool inInverse) { inverse = inInverse; }
masktype	mask::checkRect(rect* inRect) { return unMasked; }
masktype	mask::checkRect(int x,int y,int w,int h) { return unMasked; }
bool mask::checkPixel(int x,int y) { return true; }



// *************************************
//     The simple maskRect class.
// *************************************


maskRect::maskRect(rect* inRect)
	: mask(),
	rect(inRect) { }

	
maskRect::maskRect(int inX, int inY, int inWidth,int inHeight)
	: mask(),
	rect(inX,inY,inWidth,inHeight) { }
	
	
maskRect::~maskRect(void) { }

/*
masktype	maskRect::checkRect(rect* inRect) {
		
	if (inRect->isSubRectOf(this)) {
		if (inverse) {
			return unMasked;
		} else {
			return totalMasked;
		}
	} else if (inRect->overlap(this)) {
		return partialMasked;
	} else {
		if (inverse) {
			return totalMasked;
		} else {
			return unMasked;
		}
	}
}


masktype	maskRect::checkRect(int x,int y,int w,int h) {

	rect	inRect;
	
	inRect.setRect(x,y,w,h);
	return checkRect(&inRect);
}


bool maskRect::checkPixel(int x,int y) {
	
	bool	answer;
	Serial.print("MASK : ");
	Serial.print(this->x);
	Serial.print(",");
	Serial.print(this->y);
	Serial.print("\tpt x,y : ");
	Serial.print(x);
	Serial.print(",");
	Serial.println(y);
	if (inverse) 
		answer = !inRect(x,y);
	else
		answer = inRect(x,y);
	Serial.println(answer);
	return answer;
}
*/

bool maskRect::checkPixel(int x,int y) {

	if (inverse) {
		
		/*
		if (this->inRect(x,y)) {
			Serial.print("pt x,y : ");
			Serial.print(x);
			Serial.print(",");
			Serial.print(y);
			Serial.print(" is in ");
			Serial.print(this->x);
			Serial.print(" .. ");
			Serial.print(this->x + this->width);
			Serial.print(",");
			Serial.print(this->y);
			Serial.print(" .. ");
			Serial.println(this->y + this->height);
		}
		*/
		return this->inRect(x,y);
	} else {
		return !this->inRect(x,y);
	}
}