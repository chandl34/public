/*
 *  TextureIO.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "TextureIO.h"

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

Image* loadPNG(const char* filename, GLshort rw, GLshort rh){
	printf("Loading %s.png...\n", filename);
	NSString* path = [[NSBundle mainBundle] pathForResource:[NSString stringWithCString:filename] ofType:@"png"];
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
	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	
    CGContextRelease(context);
	
    free(imageData);
    [image release];
    [texData release];
	return new Image(Size2d<GLshort>(width, height), 
					 Size2d<GLshort>(rw, rh), 
					 texName);
}