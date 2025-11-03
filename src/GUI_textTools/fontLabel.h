#ifndef fontLabel_h
#define fontLabel_h

#include "label.h"
#include <Fonts/FreeSansOblique24pt7b.h>
#include <Fonts/FreeSansBoldOblique24pt7b.h>
#include <Fonts/FreeSansBoldOblique12pt7b.h>
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSansOblique9pt7b.h>


#define AFF_SANS_BOLD_24_OB	&FreeSansBoldOblique24pt7b,45,-12
#define AFF_SANS_BOLD_12_OB	&FreeSansBoldOblique12pt7b,24,-6
#define AFF_SANS_BOLD_9_OB		&FreeSansBoldOblique9pt7b,18,-5
#define AFF_SANS_9_OB			&FreeSansOblique9pt7b,18,-5
#define AFF_MONO_12				&FreeMono12pt7b,20,-6
#define AFF_MONO_9				&FreeMono9pt7b,17,-3


class fontLabel : public label {

	public:
				fontLabel(void);
				fontLabel(rect* inRect);
				fontLabel(int inX, int inY, int inW,int inH);
	virtual	~fontLabel(void);
				
				void	setFont(const GFXfont* font,int yOffset);
				void	setFont(const GFXfont* font,int inHeight,int yOffset);
	virtual	void  drawSelf(void);
	
				GFXfont*	ourFont;		// Our font.
				int		fontOffset;
};


#endif
