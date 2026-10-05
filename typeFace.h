#ifndef typeFace_h
#define typeFace_h

#include <lists.h>
#include <fontLabel.h>
#include <editLabel.h>


class typeFace	: public linkListObj {

	public:
					typeFace(int inID);
		virtual	~typeFace(void);

					void	saveFont(const GFXfont* font,int inHeight,int xOffset,int yOffset);
					void	setTypeFace(label* inLabel);
					void	setTypeFace(fontLabel* inLabel);
					void	setTypeFace(erasableText* inLabel);
					void	setTypeFace(editLabel* inLabel);
	
					int				ourID;
					colorObj			foreColor;
					colorObj			backColor;
					bool				transperant;
					int				precision;		// How many after the decimal point.
					int				justify;
					bool				useFonts;
					int				nonFontSize;
					const GFXfont*	ourFontPtr;			// Our font if we're using one.
					int				fontHeight;
					int				fontXOffset;
					int				fontYOffset;
};
	
		
class typeFacePallette	: public linkList {

	public:
				typeFacePallette(void);
				~typeFacePallette(void);
					 
	virtual	void			addTypeFace(typeFace* newtypeFace);
	virtual	typeFace*	typeFacePallette::findID(int inID);				 
	virtual	void			setTypeFace(label* inLabel,int choice);
	virtual	void			setTypeFace(fontLabel* inLabel,int choice);
	virtual	void			setTypeFace(erasableText* inLabel,int choice);
	virtual	void			setTypeFace(editLabel* inLabel,int choice);
};
	
				
extern typeFacePallette ourTxtPallette;

	
#endif