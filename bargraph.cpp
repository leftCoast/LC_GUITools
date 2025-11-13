#include <bargraph.h>
#include <colorObj.h>



// *****************************************************
//                     bargraph
// *****************************************************



bargraph::bargraph(rect* inRect,orientation inOrientation)
	: drawObj(inRect) {
	
	ourOrientation	= inOrientation;
}


bargraph::~bargraph(void) {  }



// Given the a value with min & max limits. Calculate the bar rectangle along with the
// background rectangle in pixels.	
void bargraph::setValue(float inVal,float min,float max) {

	mapper	ourMapper;
	int		newValue;
	
	backRect.setRect(this);										// Set default backRect.
	foreRect.setRect(this);										// Set default foreRect.
	switch (ourOrientation) {									// Calculate rects by type..
		case bottomUp	:											// Your standard bottom up graph.
			ourMapper.setValues(min,max,y+height,y);		// Set up the math.
			newValue = round(ourMapper.map(inVal));		// Calculate the top of the bar in pixels.
			backRect.height = newValue - y - 1;
			foreRect.y = newValue;
			foreRect.height = height - backRect.height-1;
		break;
		case leftRight	:
			ourMapper.setValues(min,max,x,x+width);
			newValue = round(ourMapper.map(inVal));
			foreRect.width = newValue - x;
			backRect.x = newValue;
			backRect.width =  width - foreRect.width;
		break;
		case topDown	:
			ourMapper.setValues(min,max,y,y+height);
			newValue = round(ourMapper.map(inVal));
			foreRect.height = newValue - y;
			backRect.height = height-foreRect.height;
			backRect.y = y + foreRect.height;
		break;
		case rightLeft	:
			ourMapper.setValues(min,max,x+width,x);
			newValue = round(ourMapper.map(inVal));
			backRect.width =  newValue - x;
			foreRect.width = width - backRect.width;
			foreRect.x = newValue;
		break;
	}
}



// *****************************************************
//                    colorBargraph
// *****************************************************


colorBargraph::colorBargraph(rect* inRect,colorObj* inBackColor,orientation inOrientation)
	: bargraph(inRect,inOrientation) {
	
	if (inBackColor) {
		backColor.setColor(inBackColor);
		transparent = false;
	} else {
		transparent = true;
	}
	maxVal	= 0;
	minVal	= 0;
	value		= 0;
	empty = true;
}
	

colorBargraph::~colorBargraph(void) {  }
   
   	
void colorBargraph::addColor(double inVal, colorObj* color) {

	
	if (empty) {
		maxVal = inVal;
		minVal = inVal;
		empty = false;
	} else {
		if (inVal>maxVal) maxVal=inVal;
		else if (inVal<minVal) minVal = inVal;
	}
	colorMultiMap::addColor(inVal,color);
	setNeedRefresh();
}


void colorBargraph::clearMap(void) {

	colorMultiMap::clearMap();
	maxVal	= 0;
	minVal	= 0;
	value		= 0;
	empty = true;	
}

	
void colorBargraph::setValue(float inVal) {

	value = inVal;
	bargraph::setValue(inVal,minVal,maxVal);
	if (!empty) {
		setNeedRefresh();
	}
}


void  colorBargraph::drawSelf(void) {

	colorObj	fillColor;
	
	if (!transparent) {
		screen->fillRect(&backRect,&backColor);
	}
	fillColor = map(value);
	screen->fillRect(&foreRect,&fillColor);
}

			