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
	//screen->drawRect(this,&cyan);
	screen->drawText(buff);
	screen->setFont(NULL);
}
	


// ******************************  erasableText   ******************************


erasableText::erasableText(void)
	: fontLabel() { }
	
	
erasableText::erasableText(rect* inRect)
	: fontLabel(inRect) { }
	
	
erasableText::erasableText(int inX, int inY, int inW,int inH)
	: fontLabel(inX,inY,inW,inH) { }
	
	
erasableText::~erasableText(void) { }

	
void erasableText::drawSelf(void) {
	
	rect	aRect(this);
	int	xLoc;
	int	yLoc;
	
	screen->fillRect(&aRect,&backColor);	// Erase the value.
	//screen->drawRect(&aRect,&green);		// GREEN for debugging.
	screen->setTextWrap(false);				// Wrap is not a good plan ever.
	screen->setTextColor(&textColor);		// Already erased, use transparent.
	screen->setFont(ourFont);					// Load our font.
	screen->setTextSize(1);						// Does it need this? I don't know.
	xLoc = x + fontXOffset;						// Offsets for funky font tweaks.
	yLoc = y + fontYOffset;						//
	screen->setCursor(xLoc,yLoc);				// Point to this location.. 
	screen->drawText(buff);						// And draw!
	screen->setFont(NULL);						// Unload the fons data.
}


