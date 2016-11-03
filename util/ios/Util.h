//
//  Util.h
//  Template-iOS
//
//  Created by Jonathan Chandler on 8/7/15.
//  Copyright (c) 2015 chandl34. All rights reserved.
//

//---- CONSTANTS
const static UIViewAutoresizing UIViewAutoresizingFlexibleSize = (UIViewAutoresizingFlexibleWidth |
                                                                  UIViewAutoresizingFlexibleHeight);
const static UIViewAutoresizing UIViewAutoresizingFlexibleVertical = (UIViewAutoresizingFlexibleTopMargin |
                                                                      UIViewAutoresizingFlexibleBottomMargin);
const static UIViewAutoresizing UIViewAutoresizingFlexibleHorizontal = (UIViewAutoresizingFlexibleLeftMargin |
                                                                        UIViewAutoresizingFlexibleRightMargin);


//---- VIEWS
// View
@interface UIView(Custom)

@property (nonatomic) CGFloat x;
@property (nonatomic) CGFloat y;
@property (nonatomic) CGPoint origin;

@property (nonatomic) CGFloat width;
@property (nonatomic) CGFloat height;
@property (nonatomic) CGSize size;

@property (nonatomic) CGFloat right;
@property (nonatomic) CGFloat bottom;

+ (UIView*)withColor:(UIColor*)color;

- (void)removeSubviews;
- (UIView*)subviewWithTag:(NSInteger)tag;
- (UIView*)subviewWithClass:(Class)klass;

@end


// ImageView
@interface UIImageView(Custom)

+ (UIImageView*)withImage:(UIImage*)image;

@end


// Button
@interface UIButton(Custom)

+ (UIButton*)withImage:(UIImage*)image;

@end


// TableView
@interface UITableView(Custom)

- (CGFloat)calculateHeight;

@end



//---- COLLECTIONS
// Dictionary
@interface NSDictionary(Custom)

- (NSString*)json;
- (NSString*)xml;

@end



//---- DATA
// Color
@interface UIColor(Custom)

+ (UIColor*)withRGBHex:(UInt32)hex;
+ (UIColor*)withARGBHex:(UInt32)hex;

@end


// Image
@interface UIImage(Custom)

@property (nonatomic, readonly) CGFloat width;
@property (nonatomic, readonly) CGFloat height;

+ (UIImage*)imageNamed:(NSString*)name tinted:(BOOL)tinted;
+ (UIImage*)withColor:(UIColor*)color;
+ (UIImage*)withColor:(UIColor*)color size:(CGSize)size;

- (UIImage*)squareImage:(BOOL)cropBorders;
- (UIImage*)scaleImage:(CGFloat)scale;
- (UIImage*)resizeImage:(CGSize)size;
- (UIImage*)cropImage:(CGRect)rect;
- (UIImage*)maskImage:(UIImage*)maskImage;
- (UIImage*)overlayImage:(UIImage*)overlayImage;
- (UIImage*)rotateImage:(CGFloat)degrees;

@end


// String
@interface NSString(Custom)

- (BOOL)contains:(NSString*)str;
- (NSString*)trim;

- (NSString*)pluralize:(NSString*)plural count:(NSInteger)count;

- (id)json;
- (NSString*)xml;

- (NSString*)toBase64;
- (NSString*)fromBase64;

@end


// Number
@interface NSNumber(Custom)

- (NSString*)xml;

@end


// Data
@interface NSData(Custom)

+ (NSData*)readFile:(NSString*)filePath;
- (BOOL)writeFile:(NSString*)filePath;

- (NSString*)string;
- (id)json;

- (NSString*)toBase64;
- (NSString*)fromBase64;
- (NSString*)hex;

@end



//--- FILES
// FileManager
@interface NSFileManager(Custom)

+ (NSArray*)filesInDir:(NSString*)dirPath;

@end


// Files
NSString* documentsFilePath(NSString* fileName);
NSString* cachesFilePath(NSString* fileName);
NSString* resourcesFilePath(NSString* fileName);
NSString* fileExtension(NSString* fileName);

BOOL createDirectory(NSString* filePath);
BOOL deleteFile(NSString* filePath);



//---- OTHER
// Error
@interface NSError(Custom)

+ (NSError*)withDescription:(NSString*)description;
+ (NSError*)withDescription:(NSString*)description code:(NSInteger)code;

@end

// NSTimer
@interface NSTimer(Custom)

+ (NSTimer*)timerWithTimeInterval:(NSTimeInterval)timeInterval block:(void (^)())block repeats:(BOOL)repeats;
+ (NSTimer*)scheduledTimerWithTimeInterval:(NSTimeInterval)timeInterval block:(void (^)())block repeats:(BOOL)repeats;

@end


// Validation
BOOL null(id obj);
BOOL nullOrEmpty(id obj);
id nullToNil(id obj);


// System
NSTimeInterval currentTime();
CGFloat pixelSize();


// Math
BOOL equals(double a, double b);
double clamp(double value, double min, double max);
double degreesToRadians(double degrees);
double radiansToDegrees(double radians);
int32_t bytesToInt(Byte* b);
CGSize aspectFit(CGSize limit, CGSize size);
UInt32 invertRGB(UInt32 hex);
UInt32 invertARGB(UInt32 hex);

