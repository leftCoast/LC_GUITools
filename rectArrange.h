#ifndef rectArrange_h
#define rectArrange_h

// ***************************************************************************************
//
// Base class for arranging rectangles. The idea here is to extend this to a class that
// will do your favorite arrangement. By inheriting and filling in the arrangeList()
// method.
//
// Pass in the address of a rectangle of your allowed area, along with the spacing limits.
// Then, add all your rectangles using addRect(). By the time they are all added, they'll 
// be arranged by your arrangeList() method. Yes you will need to write that. Then you can
// delete your rectArrange object, if you wish.
//
// This will calculate a few things for you, just in case you need them.
//
// totalRectWidth() - The summation of all your entered rects widths.
// maxWidth() - Gives the total width of all all your rects with maxWSpace between them.
// minWidth() - Gives the total width of all all your rects with minWSpace between them.
// midX - This is the calculated mid point of your area rect's width.
// isOdd - If the number of rects in the list is an odd number.
//
// ***************************************************************************************

#include <lists.h>
#include <baseGraphics.h>


// ******** The rectArrange class to interact with. ********


class rectArrange : public linkList {

	public:
				rectArrange(void);
	virtual	~rectArrange(void);
	
	virtual	void	settings(rect* area,int inMinWSpace=0,int inMaxWSpace=0,int inMinHSpace=0,int inMaxHSpace=0);
	virtual	void	addRect(rect* inRect);
				int	totalRectWidth(void);
				int	maxWidth(void);
				int	minWidth(void);
	virtual	void	arrangeList(void);
		
	protected:
				rect	areaRect;
				int	maxWSpace;
				int	minWSpace;
				int	maxHSpace;
				int	minHSpace;
				int	midX;
				bool	isOdd;
};


// ********  Holds address to the rects in your list. ********


class rectListObj :	public linkListObj {

	public:
				rectListObj(rect* inRect);
	virtual	~rectListObj(void);
	
				rect*	ourRect;
};


#endif
		