/*
 *  Font.h
 *
 *  Created by Jonathan Chandler on 12/9/12.
 *
 */

#ifndef FONT_H_
#define FONT_H_

#import "texture2d.h"
#include <string>


const int CHARS = 95;
const int CHAR_OFFSET = 32;
enum{ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT};


class Char{
public:
	Char(char, NSString*, GLshort = 12);
	~Char();
	
	GLshort getWidth() const;
	GLshort getHeight() const;
	
	void draw();
	
private:
	GLuint _texName;
	GLshort _texVert[8];
	GLfloat _texCoord[8];
};


class Font{
public:
	Font(const std::string& = "Helvetica", GLshort = 12);
	~Font();
	
	void draw(const std::string&, GLfloat = 0.0f, GLfloat = 0.0f, GLshort = ALIGN_LEFT);
	
private:	
	Char* _char[CHARS];
};

#endif
