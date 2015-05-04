#pragma once


//---- CONSTANTS
const static UIViewAutoresizing UIViewAutoresizingFlexibleSize = (UIViewAutoresizingFlexibleWidth |
                                                                  UIViewAutoresizingFlexibleHeight);
const static UIViewAutoresizing UIViewAutoresizingFlexibleVertical = (UIViewAutoresizingFlexibleTopMargin |
                                                                      UIViewAutoresizingFlexibleBottomMargin);
const static UIViewAutoresizing UIViewAutoresizingFlexibleHorizontal = (UIViewAutoresizingFlexibleLeftMargin |
                                                                        UIViewAutoresizingFlexibleRightMargin);
const static UIViewAutoresizing UIViewAutoresizingFlexibleAll = (UIViewAutoresizingFlexibleSize |
                                                                 UIViewAutoresizingFlexibleVertical |
                                                                 UIViewAutoresizingFlexibleHorizontal);

const static double EPSILON = 0.0000001;



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

- (void)removeSubviews;

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
// Array
@interface NSArray(Custom)

- (id)objectTagged:(NSInteger)tag;

@end


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
- (NSString*)toBase64;
- (NSString*)fromBase64;

@end



//--- FILES
// FileManager
@interface NSFileManager(Custom)

+ (NSArray*)filesInDir:(NSString*)dirPath;

@end


// Files
NSString* documentsFilePath(NSString* fileName);
NSString* resourcesFilePath(NSString* fileName);
NSString* fileExtension(NSString* fileName);

BOOL createDirectory(NSString* filePath);
BOOL deleteFile(NSString* filePath);



//---- OTHER
// Error
@interface NSError(Custom)

+ (NSError*)withDescription:(NSString*)description;

@end

// NSTimer
@interface NSTimer(Custom)

+ (NSTimer*)timerWithTimeInterval:(NSTimeInterval)timeInterval block:(void (^)())block repeats:(BOOL)repeats;
+ (NSTimer*)scheduledTimerWithTimeInterval:(NSTimeInterval)timeInterval block:(void (^)())block repeats:(BOOL)repeats;

@end


// Validation
BOOL null(id obj);
BOOL nullOrEmpty(id obj);


// System
double currentTime();
CGFloat pixelSize();


// Math
BOOL equals(double a, double b);
double clamp(double value, double min, double max);
int32_t bytesToInt(Byte* b);
CGSize aspectFit(CGSize limit, CGSize size);
