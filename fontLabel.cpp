#include <fontLabel.h>
 
 
fontLabel::fontLabel(void)
	: label() {

	fontXOffset	= 0;
	fontYOffset	= 0;
}


fontLabel::fontLabel(int inX, int inY, int inWidth,int inHeight)
	: label(inX,inY,inWidth,inHeight) {
	
	fontXOffset	= 0;
	fontYOffset	= 0;
  }


fontLabel::fontLabel(rect* inRect)
  : label(inRect->x,inRect->y,inRect->width,inRect->height) {
	
	fontXOffset	= 0;
	fontYOffset	= 0;
  }
  
  
fontLabel::~fontLabel(void) {  }


void fontLabel::setFont(const GFXfont* font,int yOffset) {
	
	ourFont		= font;
	fontYOffset = yOffset;
	setNeedRefresh();
}


void fontLabel::setFont(const GFXfont* font,int inHeight,int yOffset) {
	
	ourFont		= font;
	height		= inHeight;		
	fontYOffset	= yOffset;
	setNeedRefresh();
}


void fontLabel::setFont(const GFXfont* font,int inHeight,int xOffset,int yOffset) {
	
	ourFont		= font;
	height		= inHeight;		
	fontXOffset	= xOffset;
	fontYOffset	= yOffset;
	setNeedRefresh();
}


void fontLabel::drawSelf(void) {

	int	xLoc;
	int	yLoc;
	
	screen->setTextWrap(false);
	if (transp) {
		screen->setTextColor(&textColor);
	} else {
		screen->setTextColor(&textColor,&backColor);
	}
	screen->setFont(ourFont);
	screen->setTextSize(1);
	xLoc = x + fontXOffset;
	yLoc = y + fontYOffset;
	screen->setCursor(xLoc,yLoc);
	screen->drawText(buff);
	//screen->drawRect(this,&blue);
	screen->setFont(NULL);
}
	
/*
void fontLabel::drawSelf(void) {

	rect	bounds;
	int	yLoc;
	int	offset;
	
	screen->setTextWrap(false);
	screen->setTextColor(&textColor);
	screen->setFont(ourFont);
	screen->setTextSize(1);
	yLoc = y+height+fontYOffset;
	bounds = screen->getTextRect(buff);
	switch(justify) {
		case TEXT_RIGHT	:
			offset = (width-bounds.width)+fontXOffset;
		break;
		case TEXT_LEFT		:
			offset = 0+fontXOffset;
		break;
		case TEXT_CENTER	:
			offset = (width-bounds.width)+fontXOffset;
			offset = offset/2;
		break;
		default 				:
			offset = 0;
		break;
	}
	screen->setCursor(x+offset,yLoc);
	screen->drawText(buff);
	screen->drawRect(this,&red);
	screen->setFont(NULL);
}
*/