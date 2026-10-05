#include <rectObj.h>


rectObj::rectObj(rect* inRect)
	: drawObj(inRect) {

	color.setColor(&white);
}
	

rectObj::~rectObj(void) {  }

	
void rectObj::setColor(colorObj* inColor) {
  
  color.setColor(inColor);
  needRefresh = true;
}


void rectObj::drawSelf() { screen->drawRect(this,&color); }

