/*
 *  TextureIO.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "TextureIO.h"

#include "Image.h"



/*
GLshort loadPVRTC(const char* filename, GLshort size, GLshort type){	
	NSString* path = [[NSBundle mainBundle] pathForResource:[NSString stringWithCString:filename] ofType:@"pvr4"];
	NSData* texData = [[NSData alloc] initWithContentsOfFile:path];	
	if(texData == NULL)
		return -1;
	
	GLuint texName;
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, type);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, type);
	
	//GLshort s = TEX_SIZE[size][X];
	GLshort s = 64;
		
	glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, s, s, 0, s*s/2, [texData bytes]);
	[texData release];
	return texName;
}
 */

Image* loadPNG(const char* filename, const Size2d<GLshort>& rs, const Coord2d<double>& os)
{
	printf("Loading %s.png...\n", filename);
	string fn = "../../Textures/";
	fn += filename;
	fn += ".png";
	
	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(fn.c_str(), 0);//Automatocally detects the format(from over 20 formats!)
	FIBITMAP* imagen = FreeImage_Load(formato, fn.c_str());
	
	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);
	
	int w = FreeImage_GetWidth(imagen);
	int h = FreeImage_GetHeight(imagen);
	
	GLubyte* imageData = new GLubyte[4 * w * h];
	char* pixeles = (char*)FreeImage_GetBits(imagen);
	
	//FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).
	for(int j = 0; j < w * h; j++){
		imageData[j*4+0]= pixeles[j*4+2];
		imageData[j*4+1]= pixeles[j*4+1];
		imageData[j*4+2]= pixeles[j*4+0];
		imageData[j*4+3]= pixeles[j*4+3];
	}
	
	//Now generate the OpenGL texture object
	GLuint texName;
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, DRAW_METHOD);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, DRAW_METHOD);
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	
	glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)imageData);
	
	GLenum huboError = glGetError();
	if(huboError)
		cout<< "There was an error loading the texture" << endl;
	
	free(imageData);
	return new Image(Size2d<GLshort>(w, h), rs, texName, os);
}

vector<Image*> loadPNG(const char* filename)
{	
	// Check if tex coord file exists
	printf("Loading %s.txc...\n", filename);
	string fn = "../../Textures/";
	fn += filename;
	fn += ".txc";
	
	ifstream file;
	file.open(fn.c_str());
	
	vector<Image*> imgs;
	if(file.fail()){
		printf("Failed to load %s.txc!\n", filename);
		return imgs;
	}
	
	fn = "../../Textures/";
	fn += filename;
	fn += ".png";
	
	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(fn.c_str(), 0);//Automatocally detects the format(from over 20 formats!)
	FIBITMAP* imagen = FreeImage_Load(formato, fn.c_str());
	
	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);
	
	int w = FreeImage_GetWidth(imagen);
	int h = FreeImage_GetHeight(imagen);
	
	GLubyte* imageData = new GLubyte[4 * w * h];
	char* pixeles = (char*)FreeImage_GetBits(imagen);
	
	//FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).
	for(int j = 0; j < w * h; j++){
		imageData[j*4+0]= pixeles[j*4+2];
		imageData[j*4+1]= pixeles[j*4+1];
		imageData[j*4+2]= pixeles[j*4+0];
		imageData[j*4+3]= pixeles[j*4+3];
	}
	
	
	//Now generate the OpenGL texture object
	GLuint texName;
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, DRAW_METHOD);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, DRAW_METHOD);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	
	
	// Split up the image into subimages
	Size2d<GLshort> s(w, h);
	Size2d<GLshort> tl(0, 0);
	Size2d<GLshort> ts(0, 0);
	
	GLshort curr;
	for(int i = 0; true; i++){
		if(file.eof())
			break;
		
		file >> curr;
		if(curr == 0){
			tl[Y] += ts[Y];
			file >> ts[Y];
			tl[X] = 0;
		}
		else{
			ts[X] = curr;
			imgs.push_back(new Image(s, tl, ts, texName));
			tl[X] += ts[X];
		}
	}
	
	GLenum huboError = glGetError();
	if(huboError)
		cout<< "There was an error loading the texture" << endl;
	
	free(imageData);
	file.close();
	return imgs;
	
}
