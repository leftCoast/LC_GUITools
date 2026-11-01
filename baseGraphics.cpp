#include <baseGraphics.h>
#include <math.h>



#define DEF_LOC_X  16    // Just anything so the user can see something.
#define DEF_LOC_Y  16
#define DEF_SIZE_X 16
#define DEF_SIZE_Y 16

/*
void printPoint(point* inPt,char* name) {

	Serial.print(name);
   Serial.print("\t: ");
   Serial.print(inPt->x);
   Serial.print(F(", "));
   Serial.println(inPt->y);
}
*/

// Basically "How wide is this?".
int	xDistance(point ptA,point ptB) { return ptB.x - ptA.x; }


// And this tells us how tall it is.
int	yDistance(point ptA,point ptB) { return ptB.y - ptA.y; }


// How far are these points apart?
float distance(point ptA,point ptB) {
	
	float xDist;
	float yDist;
	float widthSq;
	float heighSq;
	
	xDist = xDistance(ptA,ptB);
	yDist = yDistance(ptA,ptB);
	widthSq = xDist * xDist;
	heighSq = yDist * yDist;
	return sqrt(widthSq + heighSq);
}


// This does the straight trig. calcualtion.
float calcAngle(float deltaX,float deltaY) {

   float rad;

   if (deltaX==0) {
      if (deltaY>0) return 90;
      if (deltaY<0) return 270;
      if (deltaY==0) return NAN;
   } else if (deltaY==0) {
      if (deltaX>0)  return 0;
      else if (deltaX<0) return 180;
   }
   if (deltaX>0 && deltaY>0) {					// quad 1
      rad = atan(deltaY/deltaX);					// 
   } else if (deltaX>0 && deltaY<0) {			// quad 4
      rad = (2*M_PI) + atan(deltaY/deltaX);	//
   } else if (deltaX<0 && deltaY>0) {			// quad 2
      rad = M_PI + atan(deltaY/deltaX);		//
   } else {												// quad 3
       rad = M_PI + atan(deltaY/deltaX);		//
   }														//
   return(rad * 180/M_PI);							// Return the result as degrees from East. CCW.
}

	
// Gives angle in degrees from 3 O'clock counter clockwise. (Like trig stuff.) The
// backwards y values must be dealt with here.
float angle(point ptA,point ptB) {
	
	float deltaX;
	float deltaY;
	
	deltaX = xDistance(ptA,ptB);		// Do the X thing.
	deltaY = -yDistance(ptA,ptB);		// Do the Y thing, but reverese it.
	return calcAngle(deltaX,deltaY);	// Pass in the calcualted deltas.
}


// Rotate around the x.y axis. From current x,y location, angle (radians).
// BUT this is only using ints so the accuracy is somewhat lacking.
point	rotate(point ptA,float angle) {

	point	res;
	float	mag;
	
	mag = sqrt((ptA.x * ptA.x) + (ptA.y * ptA.y));
	res.x = round(mag * cos(acos(ptA.x/mag)+angle));
	res.y = round(mag * sin(asin(ptA.y/mag)+angle));
	return res;
}



// ***************************************************************
// Base class for a rectangle. 
// ***************************************************************


// Default constructor gives default rectangle.
rect::rect(void) {
   
   setLocation(DEF_LOC_X,DEF_LOC_Y);
   setSize(DEF_SIZE_X,DEF_SIZE_Y);
 }
 

// Set "our" rect to match this one. Given a non-NULL address.
rect::rect(rect* inRect) { if (inRect) setRect(inRect); }


// Set "our" rect to these values.
rect::rect(int inX, int inY, int inWidth,int inHeight) { setRect(inX,inY,inWidth,inHeight); }


 // Nothing to recycle so nothing to do.
rect::~rect(void) { }
 

// Move to here.. 
void  rect::setLocation(int inX, int inY) {
  
  x = inX;
  y = inY;
}


// Make us "this big"!
void  rect::setSize(int inWidth,int inHeight) {

  width = inWidth;
  height = inHeight;
}


// Copy the rect at this address and make us like that one. Unless it's NULL..
void rect::setRect(rect* inRect) {
  
	if (inRect) {										// Check for sanity. Dey crazy!
		setLocation(inRect->x,inRect->y);		// Set the location.
		setSize(inRect->width,inRect->height);	// Set the size.
	}
}


// Make us span two points.
void rect::setRect(point* inPt1,point* inPt2) {

	if (inPt1 && inPt2) {										// Check if dey crazy..
		int locX = min(inPt1->x,inPt2->x);					// Find left side.
		int locY = min(inPt1->y,inPt2->y);					// Find top.
		int width = abs((int)inPt1->x-(int)inPt2->x);	// Width
		int height = abs((int)inPt1->y-(int)inPt2->y);	// Height.
		setLocation(locX,locY);									// Set location.
		setSize(width,height);									// Set size.
	}
}


// Here's where we set ourselves to the four rect values.
void rect::setRect(int inX, int inY, int inWidth,int inHeight) {

	setLocation(inX,inY);
   setSize(inWidth,inHeight);
}


// Add these offsets to your location.
void rect::moveRect(int dX,int dY) {
	
	x = x + dX;		// Bump x.
	y = y + dY;		// Bump y.
}
	

// Make us bigger or smaller by "this much" around our center point. Positive values make
// us smaller, Negative value make us bigger. Why is this? Because this started as a way
// to make rects smaller. and I couldn't find a word I liked that was the opposite of
// inset.		
void rect::insetRect(int inset) {

	x = x + inset;						// Move x "this much".
	y = y + inset;						// Move y "this much".
	width = width - (2*inset);		// Resize width by twice as much.
	height = height - (2*inset);	// Resize height by twice as much.
}
          	
 
// Become the enclosing rect of yourself and this rect.
void  rect::addRect(rect* inRect) {

	rect	result(this);
	
	if (inRect)	{													// If we got a rect.. Never trust 'em.
		result.x			= min(x,inRect->x);					// X would be the minimum of ours && inRect's x values.
		result.y			= min(y,inRect->y);					// Y would be the minimum of ours && inRect's y values.
		if (maxX()>inRect->maxX()) {							// If our max x is larger that inRect's max x..
			result.width = maxX() - result.x;				// Then width would be Our max x minus result's x value.
		} else {														// Else, if our max x is NOT larger than BinRect's max x..
			result.width = inRect->maxX() - result.x;		// Then width would be inRect's max x minus the resulting x value.
		}																// 
		if (maxY()>inRect->maxY()) {							// If our max y is larger that inRect's max y..
			result.height = maxY() - result.y;				// Then height would be our max y minus result's y value.
		} else {														// Else, if our max Y is NOT larger than inRect's max Y..
			result.height = inRect->maxY() - result.y;	// Then width would be inRect's max y minus the resulting y value.
		}																//
	}																	//
	setRect(&result);												// All done. Set ourselves to match this new calcualted rect result.
} 

 
 // A group of methods for finding our extents.       	
int rect::maxX(void) { return(x + width); }
int rect::maxY(void)  { return(y + height); }
int rect::minX(void) { return(x); }
int rect::minY(void)  { return(y); }


// Using the extent methods is this location inside us?
bool rect::inRect(int inX, int inY) {

  return(
  inX >= minX() &&
  inX <= maxX() &&
  inY >= minY() &&
  inY <= maxY()
  );
}


// Or we can say "Is this point inside us?".
bool rect::inRect(point* inPoint) {

	if (inPoint) {										// Sanity..
		return inRect(inPoint->x,inPoint->y);	// Ok, return the result of the "inRect() with values" method.
	}														//
	return false;										// Caught a NULL huh? Return false. NULLS ain't in nobody!
}


// Ok corner is an enum. So lets figure out the point they want and hand that back.
point rect::getCorner(rectPt corner) {

	point	tempPt;
	
	switch(corner) {					// Let's see what corner we got here..
		case topLeftPt :				// Top left.
			tempPt.x = x;				// Set up the temp point with the values.
			tempPt.y = y;				// Yeah, both of them.
		break;							// And we're done here.
		case topRightPt :				// Top right.
			tempPt.x = x + width;	// Again calcualted the values.
			tempPt.y = y;				// Un huh..
		break;							// And done.
		case bottomLeftPt :			// These two..
			tempPt.x = x;				// You'll have to figure out..
			tempPt.y = y + height;	// On your own.
		break;							// Again all done.
		case bottomRightPt :			// Last possible chpice.
			tempPt.x = x + width;	// Calcualte.
			tempPt.y = y + height;	// Enough!
		break;							// Done.
	}										//
	return tempPt;						// Return the reult of our labors.
}


// Are we touching this passed in rectangle? We do this by looking at every way we can say
// it's not true;
bool rect::overlap(rect* checkRect) {

	if (checkRect) {											// Watch 'em! They pass NULLs for fun!
		if(maxX()<checkRect->minX()) return false;	// It's to our right? False.
		if(minX()>checkRect->maxX()) return false;	// It's to our left? False.
		if(maxY()<checkRect->minY()) return false;	// Its below us? False.
		if(minY()>checkRect->maxY()) return false;	// It's above us? False.
		return true;											// So if none of these are false? It's true.
	}																//
	return false;												// Well, unless those Bozo's pass up a NULL pointer.
}


// Are we contained in this passed in rectangle?
bool rect::isSubRectOf(rect* checkRect) {
	
	point tr;
	point tl;
	point br;
	point bl;
	
	if (checkRect) {							// Again, check your inputs..
		tr = getCorner(topRightPt);		// Let's lcate our corner points.
		tl = getCorner(topLeftPt);			// Next..
		br = getCorner(bottomRightPt);	// Again..
		bl = getCorner(bottomLeftPt);		// Yes, all four.
		return checkRect->inRect(&tr)		// And we return..
				&& checkRect->inRect(&tl)	// If all their points..
				&& checkRect->inRect(&br)	// are inside..
				&& checkRect->inRect(&bl);	// Us.
	}												// Unless we got a NULL?
	return false;								// In this case nothing is not inside us.
}


// Are we identical to this rect?
bool rect::isSameAs(rect* checkRect) {

	if (checkRect) {												// Always check inputs.
		if (x != checkRect->x)				return false;	// If any 									
		if (y != checkRect->y)				return false;	// of these
		if (width != checkRect->width)	return false;	// are false	
		if (height != checkRect->height)	return false;	// It ain't.
		return true;												// true.
	}																	//
	return false;													// And no, we aint' NULL either.
}	


// Lets say you have a set of points and want a rectangle that spans them all. Here's the
// way to do just that. Create your rect, call startBoundsRec() then pass in all the
// points. using addBoundsPt() Either points or x,y values. When done, you will have a
// rect that spans all these points.

// Clear a rect to start the recording process. The point you start with needs to be the
// location of this rect.
void rect::startBoundsRec(void) {

	x			= x;
	y			= y;
	width		= 0;
	height	= 0;
}


// Add in data as a point.
void rect::addBoundsPt(point* inPt)  {

	if (inPt) {								// Again, check for NULL pointers.
		addBoundsPt(inPt->x,inPt->y);	// Add a point.
	}											// Don't add NULL points. Because there's no point!
}
 
 
// Add in data as x,y values.      	
void rect::addBoundsPt(int x,int y) {

	int	dif;
	
	if (!inRect(x,y)) {				// If an x,y location is NOT in our rect..
		if (x>maxX()) {				// If it's to our right?
			dif = x - maxX();			// By how much?
			width = width + dif;		// Add that much to our width.
		} else if (x<minX()) {		// Else if it's to our left?
			dif = minX() - x;			// Again, calcualte how much.
			width = width + dif;		// Add that to our width.
			x = x;						// And move our left side to match.
		}									//
		if (y>maxY()) {				// Alright, is it below us?
			dif = y - maxY();			// if so, by how much.
			height = height + dif;	// Add the differenc to our height.
		} else if (y<minY()) {		// Else is it's above us..
			dif = minY() - y;			// Calculate the difference.
			height = height + dif;	// Add it to our height.
			y = y;						// And move our y location to that position.
		}									//
	}										//
}


/*
// HANDY for tracing issues through the drawing code.
void rect::printRect(char* label) {

	Serial.print(label);
	Serial.print(F("x:"));Serial.print(x);Serial.print(F(" "));
	Serial.print(F("y:"));Serial.print(y);Serial.print(F(" "));
	Serial.print(F("w:"));Serial.print(width);Serial.print(F(" "));
	Serial.print(F("h:"));Serial.println(height);
}
*/


