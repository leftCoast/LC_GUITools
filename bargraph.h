#ifndef bargraph_h
#define bargraph_h

#include <colorObj.h>
#include <drawObj.h>


// *****************************************************
//                     bargraph
// *****************************************************

// The bargraph class is a drawObj that can take in a value with min & max limits.
// From these, calculate the two necessary rectangles for drawing a bar graph. The
// foreground rectangle and the background rectangle. And, it can do this for all four
// directions of bar graph. (See enum below.)
// 
// The actual drawing of the bar graph is left up to whatever class inherits this one. For
// example, colorBargraph below.


enum orientation {
	bottomUp,
	leftRight,
	topDown,
	rightLeft
};


class bargraph :	public drawObj {

public:
				bargraph(rect* inRect,orientation inOrientation);
	virtual	~bargraph(void);
	
				void	setValue(float inValue,float min,float max);
	
				orientation	ourOrientation;
				rect			backRect;
				rect			foreRect;
};



// *****************************************************
//                    colorBargraph
// *****************************************************

// A solid color bar graph that can change color as a function of input value. The bar
// color is regulated by adding (value,color) pairs using the addColor() method. The min
// and max values are set by the min & max values of the added data pairs.
//
// NOTE : The colors are managed by the colorMultiMap class. See colorObj from baseTools
// for more info.


class colorBargraph :	public bargraph,
								public colorMultiMap {
	public:
				colorBargraph(rect* inRect,colorObj* inBackColor=&black,orientation inOrientation=bottomUp);
	virtual	~colorBargraph(void);
	
	virtual	void	addColor(double inX, colorObj* color);
				void	clearMap(void);
				void	setValue(float inVal);
	virtual	void	drawSelf(void);
	
   			colorObj		backColor;
   			bool			transparent;
				float			minVal;
				float			maxVal;
				float			value;
				bool			empty;
};


#endif