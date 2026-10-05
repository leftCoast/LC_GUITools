#include <typeFace.h>
#include <debug.h>


// Can't find the one you want? Use the one you're with. IE. This one.
void	defaultTypeFace(label* inLabel) {

	inLabel->setColors(&black,&white);
	inLabel->setTextSize(1);
	inLabel->setPrecision(2);
	inLabel->setJustify(TEXT_LEFT);
}



//****************************************************************************************
// typeFace
//****************************************************************************************


typeFace::typeFace(int inID)
	: linkListObj() {
	
	ourID = inID;
	foreColor.setColor(&black);
	backColor.setColor(&white);
	transperent	= false;
	precision	= 2;
	justify		= TEXT_LEFT;
	useFonts		= false;
	nonFontSize	= 1;
	ourFontPtr	= NULL;
	fontHeight	= 0;
	fontXOffset	= 0;
	fontYOffset	= 0;
}
	
	
typeFace::~typeFace(void) {  }


void typeFace::saveFont(const GFXfont* font,int inHeight,int xOffset,int yOffset) {

	ourFontPtr	= font;
	fontHeight	= inHeight;
	fontXOffset	= xOffset;
	fontYOffset	= yOffset;
}


void typeFace::setTypeFace(label* inLabel) {

	if (transperent) {
		inLabel->setColors(&foreColor);
	} else {
		inLabel->setColors(&foreColor,&backColor);
	}
	inLabel->setTextSize(nonFontSize);
	inLabel->setPrecision(precision);
	inLabel->setJustify(justify);
}


void typeFace::setTypeFace(fontLabel* inLabel) {
	
	setTypeFace((label*)inLabel);													// Do the labels stuff..
	if (useFonts) {																	// If we are actually using fonts..
		inLabel->setTextSize(1);													// I hear fonts want this set to one.
		inLabel->setFont(ourFontPtr,fontHeight,fontXOffset,fontYOffset);
	}
}


void typeFace::setTypeFace(erasableText* inLabel) { 
	
	transperent = false;						// erasableText needs this true. For erasing, silly.
	setTypeFace((fontLabel*)inLabel);	// Do the fontLabel stuff..
}													



void typeFace::setTypeFace(editLabel* inLabel) { 

	setTypeFace((label*)inLabel);	// Today editLabel is ony a label. So just do the label stuff.
}													



//****************************************************************************************
// typeFacePallette
//****************************************************************************************
	
		
typeFacePallette::typeFacePallette(void)
	: linkList() {  }
	
	
typeFacePallette::~typeFacePallette(void) {  }

					 
void typeFacePallette::addTypeFace( typeFace* newtypeFace) {

	if (newtypeFace) {
		addToTop(newtypeFace);
	}
}


typeFace* typeFacePallette::findID(int inID) {

	typeFace* trace;
	
	trace = (typeFace*)getFirst();
	while(trace) {
		if (trace->ourID==inID) {
			return trace;
		}
		trace = trace->getNext();
	}
	return NULL;
}


void typeFacePallette::setTypeFace(label* inLabel,int choice) {

	typeFace* selectTypeFace;
	
	if (inLabel) {
		selectTypeFace = findID(choice);
		if (selectTypeFace) {
			selectTypeFace->setTypeFace(inLabel);
		} else {
			defaultTypeFace(inLabel);
		}
	}
}


void typeFacePallette::setTypeFace(fontLabel* inLabel,int choice) {

	typeFace* selectTypeFace;
	
	if (inLabel) {
		selectTypeFace = findID(choice);
		if (selectTypeFace) {
			selectTypeFace->setTypeFace(inLabel);
		} else {
			defaultTypeFace(inLabel);
		}
	}
}


void typeFacePallette::setTypeFace(erasableText* inLabel,int choice) {

	typeFace* selectTypeFace;
	
	if (inLabel) {
		selectTypeFace = findID(choice);
		if (selectTypeFace) {
			selectTypeFace->setTypeFace(inLabel);
		} else {
			defaultTypeFace(inLabel);
		}
	}
}


void typeFacePallette::setTypeFace(editLabel* inLabel,int choice) {

	typeFace* selectTypeFace;
	
	if (inLabel) {
		selectTypeFace = findID(choice);
		if (selectTypeFace) {
			selectTypeFace->setTypeFace(inLabel);
		} else {
			defaultTypeFace(inLabel);
		}
	}
}

typeFacePallette ourTxtPallette;