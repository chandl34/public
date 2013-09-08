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

Image* loadPNG(const char* filename, const Size2d<GLshort>& rs)
{
	printf("Loading %s.png...\n", filename);
	NSString* path = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:filename] ofType:@"png"];
	NSData* texData = [[NSData alloc] initWithContentsOfFile:path];
	UIImage* image = [[UIImage alloc] initWithData:texData];
	if(image == nil){
		printf("Failed to load %s.png!\n", filename);
		return NULL;
	}
	
	GLuint width = CGImageGetWidth(image.CGImage);
	GLuint height = CGImageGetHeight(image.CGImage);
	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	void* imageData = malloc(height*width*4);
	CGContextRef context = CGBitmapContextCreate(imageData, width, height, 8, 4*width, colorSpace, 
																kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
	CGColorSpaceRelease(colorSpace);
	CGContextClearRect(context, CGRectMake(0, 0, width, height));
	CGContextDrawImage(context, CGRectMake(0, 0, width, height), image.CGImage);
	
	GLuint texName;
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, DRAW_METHOD);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, DRAW_METHOD);	
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	
	CGContextRelease(context);
	
	free(imageData);
	[image release];
	[texData release];
	return new Image(texName, Size2d<GLshort>(width, height), rs);
}


vector<Image*> loadPNG(const char* filename){	
	vector<Image*> imgs;
	
	// Check if tex coord file exists
	printf("Loading %s.txc...\n", filename);
	NSString* txcpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:filename] ofType:@"txc"];
	
	ifstream file;
	file.open([txcpath UTF8String]);
	
	if(file.fail()){
		printf("Failed to load %s.txc!\n", filename);
		return imgs;
	}
	
	// Check if png exists
	printf("Loading %s.png...\n", filename);
	NSString* imgpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:filename] ofType:@"png"];
    NSData* texData = [[NSData alloc] initWithContentsOfFile:imgpath];
    UIImage* image = [[UIImage alloc] initWithData:texData];
    if(image == nil){
		printf("Failed to load %s.png!\n", filename);
		return imgs;
	}
	
	// Load texture into OpenGL and get texName
    GLuint width = CGImageGetWidth(image.CGImage);
    GLuint height = CGImageGetHeight(image.CGImage);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    void* imageData = malloc(height*width*4);
    CGContextRef context = CGBitmapContextCreate(imageData, width, height, 8, 4*width, colorSpace, 
												 kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpace);
    CGContextClearRect(context, CGRectMake(0, 0, width, height));
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), image.CGImage);
	
	GLuint texName;
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, DRAW_METHOD);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, DRAW_METHOD);	
	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	
    CGContextRelease(context);
	
    free(imageData);
    [image release];
    [texData release];
	
	
	Size2d<GLshort> s(width, height);	
	Size2d<GLshort> rs(0, 0);
	Coord2d<GLshort> os(0, 0);	
	
	GLshort temp;	
	for(int i = 0; true; ++i){
		if(file.eof())
			break;
		
		file >> temp;
		if(temp == 0){
			os[Y] += rs[Y];
			file >> rs[Y];
			os[X] = 0;
		}
		else{
			rs[X] = temp;
			imgs.push_back(new Image(texName, s, rs, os));	
			os[X] += rs[X];		
		}
	}	
	
	file.close();
	return imgs;
}

