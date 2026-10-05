#include <fontLabel.h>
#include <debug.h>

 
 
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


// This has to be last after all the parmeters for drawing text are set up. Bascally just 
int fontLabel::doJustify(int xLoc) {

	int	offset;
	rect	txtBounds;
	
	switch(justify) {												// Now, depending on how we want to justify this..
		case TEXT_LEFT		: break;								// No change, it's already like this.
		case TEXT_RIGHT	:										// Right justify..
			txtBounds = screen->getTextRect(buff);
			offset = width - txtBounds.width;				// Do the calculation.
			xLoc = xLoc + offset;								// Add the offset.
		break;														//
		case TEXT_CENTER	:										// Right justify..
			txtBounds = screen->getTextRect(buff);
			offset = width - txtBounds.width;				// Do the calculation.
			xLoc = xLoc + offset/2;								// Add the offset.
		break;														//
	}																	//
	return xLoc;
}


void fontLabel::drawSelf(void) {

	int	xLoc;
	int	yLoc;
	
	//screen->drawRect(this,&cyan);							// CYAN for debugging.
	screen->setTextWrap(false);								// we don't use text wrap for anything.
	if (transp) {													// If transparent?						
		screen->setTextColor(&textColor);					// Just print the text, others deal with background.
	} else {															// Else..
		screen->setTextColor(&textColor,&backColor);		// We'll do the solid color background.
	}																	//
	screen->setFont(ourFont);									// Set the font we want to use.
	screen->setTextSize(1);										// Always this for fancy fonts.
	xLoc = x + fontXOffset;										// Offsets for lining it up to where we say it goes.
	yLoc = y + fontYOffset;										// Vertical as well. Now we're pointing at the top left corner..
	xLoc = doJustify(xLoc);										// Do the justify thing.
	screen->setCursor(xLoc,yLoc);								// Start writing here..
	screen->drawText(buff);										// These chars..
	screen->setFont(NULL);										// Recycle the font RAM.
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
	
	aRect.insetRect(-2);							// Some values, like '3' overlap a little.
	screen->fillRect(&aRect,&backColor);	// Erase the value.
	//screen->drawRect(&aRect,&green);		// GREEN for debugging.
	screen->setTextWrap(false);				// Wrap is not a good plan ever.
	screen->setTextColor(&textColor);		// Already erased, use transparent.
	screen->setFont(ourFont);					// Load our font.
	screen->setTextSize(1);						// Does it need this? I don't know.
	xLoc = x + fontXOffset;						// Offsets for funky font tweaks.
	yLoc = y + fontYOffset;						//
	xLoc = doJustify(xLoc);						// Do the justify thing.
	screen->setCursor(xLoc,yLoc);				// Point to this location.. 
	screen->drawText(buff);						// And draw!
	screen->setFont(NULL);						// Unload the fons data.
}


