/*
 *  Font.mm
 *
 *  Created by Jonathan Chandler on 12/9/12.
 *
 */

#include "Font.h"

#include <iostream>


//---- CHAR ----//
Char::Char(char ch, NSString* nFontName, GLshort fSize)
{
	std::string temp;
	temp += ch;
	NSString* nsstr = [[NSString alloc] initWithUTF8String:temp.c_str()];
	
	CGSize stringSize = [nsstr sizeWithFont:[UIFont fontWithName:nFontName size:fSize]];
	
	Texture2D* texData = [[Texture2D alloc] initWithString:nsstr 
														 dimensions:CGSizeMake(stringSize.width, stringSize.height)
													 	 alignment:UITextAlignmentLeft 
														 fontName:nFontName 
														 fontSize:fSize];
	
	_texName = [texData name];
	
	GLshort ws = stringSize.width;
	GLshort hs = stringSize.height;	
	_texVert[0] = ws;		_texVert[1] = 0;
	_texVert[2] = 0;		_texVert[3] = 0;
	_texVert[4] = ws;		_texVert[5] = hs;
	_texVert[6] = 0;		_texVert[7] = hs;
	
	GLfloat wf = stringSize.width / (GLfloat) texData->_width;
	GLfloat hf = stringSize.height / (GLfloat) texData->_height;	
	_texCoord[0] = wf;		_texCoord[1] = hf;
	_texCoord[2] = 0.0f;		_texCoord[3] = hf;
	_texCoord[4] = wf;		_texCoord[5] = 0.0f;
	_texCoord[6] = 0.0f;		_texCoord[7] = 0.0f;
	
	[nsstr release];
	[texData release];
}

Char::~Char()
{
	glDeleteTextures(1, &_texName);
}


GLshort Char::getWidth() const
{
	return _texVert[4];
}

GLshort Char::getHeight() const
{
	return _texVert[5];
}

void Char::draw()
{
	glBindTexture(GL_TEXTURE_2D, _texName);
	glVertexPointer(2, GL_SHORT, 0, _texVert);
	glTexCoordPointer(2, GL_FLOAT, 0, _texCoord);	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	glTranslatef(getWidth(), 0.0f, 0.0f);
}




//---- FONT ----//
Font::Font(const std::string& fontName, GLshort fSize)
{
	NSString* nFontName = [[NSString alloc] initWithUTF8String:fontName.c_str()];	
	
	// Generate all characters
	for(GLshort i = 0; i < CHARS; ++i)
		_char[i] = new Char(i + CHAR_OFFSET, nFontName, fSize);
	
	[nFontName release];
}

Font::~Font()
{
	for(GLshort i = 0; i < CHARS; ++i)
		delete _char[i];
}


void Font::draw(const std::string& str, GLfloat x, GLfloat y, GLshort align)
{
	// Remove these comments, if you have not previously enabled these states
	//	glEnableClientState(GL_VERTEX_ARRAY);
	//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//	glEnable(GL_TEXTURE_2D);	
	
	// Align text
	if(align != ALIGN_LEFT){
		GLshort width = 0;
		for(GLshort i = 0; i < str.size(); ++i)
			width += _char[str[i] - CHAR_OFFSET]->getWidth();
		
		if(align == ALIGN_RIGHT)
			x -= width;
		else 
			x -= width / 2;
	}	
	
	// Draw text
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	for(GLshort i = 0; i < str.size(); ++i)
		_char[str[i] - CHAR_OFFSET]->draw();
}
