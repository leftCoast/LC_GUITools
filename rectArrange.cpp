#include <rectArrange.h>


// ******** The rectArrange class to interact with. ********


rectArrange::rectArrange(void) 
	: linkList() {
	
	areaRect.setRect(0,0,0,0);
	maxWSpace	= 0;
	minWSpace	= 0;
	maxHSpace	= 0;
	minHSpace	= 0;
	midX			= 0;
	isOdd			= true;
}


rectArrange::~rectArrange(void) { }
	

void rectArrange::settings(rect* area,int inMinWSpace,int inMaxWSpace,int inMinHSpace,int inMaxHSpace) {

	areaRect.setRect(area);
	maxWSpace	= inMaxWSpace;
	minWSpace	= inMinWSpace;
	maxHSpace	= inMaxHSpace;
	minHSpace	= inMinHSpace;
	midX			= round((areaRect.width/2.0)+areaRect.x);
	isOdd			= (bool)(getCount()%2);
}

	
void rectArrange::addRect(rect* inRect) {

	rectListObj*	newItem;
	
	if (inRect) {
		newItem = new rectListObj(inRect);
		if (newItem) {
			addToEnd(newItem);
			arrangeList();
		}
	}
}


// Width of all the rects in the list. Just the rects, no spaces.
int rectArrange::totalRectWidth(void) {
	
	int				totalWidth;
	rectListObj*	trace;
	
	totalWidth = 0;													// Zero is a good staring point.
	trace = (rectListObj*)getFirst();                     // Grab the first one on the list.
	while(trace) {                                        // For every rect we can find..
		totalWidth = totalWidth + trace->ourRect->width;	// Add it's width to the total.
		trace = (rectListObj*)trace->getNext();				// Hop to the next rect on the list.
	}																		//
	return totalWidth;												// Hand the total back to Mrs user.
}


// How wide can we stretch these?
int rectArrange::maxWidth(void) { return ((getCount()-1) * maxWSpace)+totalRectWidth(); }     
	
	
// How much can we scrunch these?
int rectArrange::minWidth(void) { return ((getCount()-1) * minWSpace)+totalRectWidth(); }
	
			
// User fills this one in to arrange their rects.				
void rectArrange::arrangeList(void) { }




// *****  Holds address to the rects in your list. *****


rectListObj::rectListObj(rect* inRect) { ourRect = inRect; }

	
rectListObj::~rectListObj(void) {  }
	
	
