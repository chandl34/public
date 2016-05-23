#import "Util.h"

//---- VIEWS
// View
@implementation UIView(Custom)

- (CGFloat)x
{
    return self.frame.origin.x;
}

- (void)setX:(CGFloat)x
{
    [self setOrigin:CGPointMake(x, self.y)];
}

- (CGFloat)y
{
    return self.frame.origin.y;
}

- (void)setY:(CGFloat)y
{
    [self setOrigin:CGPointMake(self.x, y)];
}

- (CGPoint)origin
{
    return self.frame.origin;
}

- (void)setOrigin:(CGPoint)point
{
    [self setFrame:CGRectMake(point.x, point.y, self.width, self.height)];
}

- (CGFloat)width
{
    return self.frame.size.width;
}

- (void)setWidth:(CGFloat)width
{
    [self setSize:CGSizeMake(width, self.height)];
}

- (CGFloat)height
{
    return self.frame.size.height;
}

- (void)setHeight:(CGFloat)height
{
    [self setSize:CGSizeMake(self.width, height)];
}

- (CGSize)size
{
    return self.frame.size;
}

- (void)setSize:(CGSize)size
{
    [self setFrame:CGRectMake(self.x, self.y, size.width, size.height)];
}

- (CGFloat)right
{
    return [self x] + [self width];
}

- (void)setRight:(CGFloat)right
{
    self.x = right - self.width;
}

- (CGFloat)bottom
{
    return [self y] + [self height];
}

- (void)setBottom:(CGFloat)bottom
{
    self.y = bottom - self.height;
}

- (void)removeSubviews
{
    NSArray* subviews = self.subviews;
    for(UIView* subview in subviews)
    {
        [subview removeFromSuperview];
    }
}

- (UIView*)subviewTagged:(NSInteger)tag
{
    for(UIView* view in self.subviews)
    {
        if(view.tag == tag)
        {
            return view;
        }
    }
    
    return nil;
}

@end


// ImageView
@implementation UIImageView(Custom)

+ (UIImageView*)withImage:(UIImage*)image
{
    UIImageView* imageView = [[UIImageView alloc] initWithImage:image];
    imageView.size = image.size;
    
    return imageView;
}

@end


// Button
@implementation UIButton(Custom)

+ (UIButton*)withImage:(UIImage*)image
{
    UIButton* button = [[UIButton alloc] init];
    button.size = image.size;
    
    [button setImage:image forState:UIControlStateNormal];
    
    return button;
}

@end


// TableView
@implementation UITableView(Custom)

- (CGFloat)calculateHeight
{
    CGFloat height = 0;
    for(int i = 0; i < [self.dataSource numberOfSectionsInTableView:self]; ++i)
    {
        height += [self.delegate tableView:self heightForHeaderInSection:i];
        for(int j = 0; j < [self.dataSource tableView:self numberOfRowsInSection:i]; ++j)
        {
            NSIndexPath* indexPath = [NSIndexPath indexPathForRow:j inSection:i];
            height += [self.delegate tableView:self heightForRowAtIndexPath:indexPath];
        }
        height += [self.delegate tableView:self heightForFooterInSection:i];
    }
    return height;
}

@end



//---- COLLECTIONS
// Dictionary
@implementation NSDictionary(Custom)

- (NSString*)json
{
    NSError* error;
    NSData* data = [NSJSONSerialization dataWithJSONObject:self options:0 error:&error];
    if(error)
    {
        return nil;
    }
    
    return [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
}

- (NSString*)xml  // NOTE:  implementation incomplete
{
    NSString* xml = @"";
    
    NSArray* keys = [self allKeys];
    NSArray* values = [self allValues];
    for(int i = 0; i < [self count]; ++i)
    {
        id value = [values objectAtIndex:i];
        
        if([value respondsToSelector:@selector(xml)])
        {
            NSString* key = [keys objectAtIndex:i];
            xml = [NSString stringWithFormat:@"%@<%@>", xml, key];
            xml = [xml stringByAppendingString:[value xml]];
            xml = [NSString stringWithFormat:@"%@</%@>", xml, key];
        }
    }
    
    return xml;
}

@end



//---- DATA
// Color
@implementation UIColor(Custom)

+ (UIColor*)withRGBHex:(UInt32)hex
{
    return [self withARGBHex:(hex & 0xFFFFFFFF) + 0xFF000000];
}

+ (UIColor*)withARGBHex:(UInt32)hex
{
    int a = (hex >> 24) & 0xFF;
    int r = (hex >> 16) & 0xFF;
    int g = (hex >> 8) & 0xFF;
    int b = (hex) & 0xFF;
    
    return [UIColor colorWithRed:r / 255.0f
                           green:g / 255.0f
                            blue:b / 255.0f
                           alpha:a / 255.0f];
}

@end


// Image
@implementation UIImage(Custom)

- (CGFloat)width
{
    return self.size.width;
}

- (CGFloat)height
{
    return self.size.height;
}

+ (UIImage*)imageNamed:(NSString *)name tinted:(BOOL)tinted
{
    UIImage* image = [UIImage imageNamed:name];
    if(tinted)
    {
        return [image imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    }
    return image;
}

+ (UIImage *)withColor:(UIColor*)color
{
    return [self withColor:color size:CGSizeMake(1, 1)];
}

+ (UIImage *)withColor:(UIColor*)color size:(CGSize)size
{
    CGRect rect = CGRectMake(0.0f, 0.0f, size.width, size.height);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    
    UIImage* image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
}

- (UIImage*)squareImage:(BOOL)cropBorders
{
    if(equals(self.width, self.height))
    {
        return self;
    }
    
    CGFloat dim;
    if(cropBorders)
    {
        dim = fminf(self.width, self.height);
    }
    else
    {
        dim = fmaxf(self.width, self.height);
    }
    
    CGFloat x = (dim - self.width) / 2;
    CGFloat y = (dim - self.height) / 2;
    CGSize squareSize = CGSizeMake(dim, dim);
    
    UIGraphicsBeginImageContextWithOptions(squareSize, NO, 0.0);
    [self drawInRect:CGRectMake(x, y, self.width, self.height)];
    UIImage* newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return newImage;
}

- (UIImage*)scaleImage:(CGFloat)scale
{
    CGSize size = CGSizeMake(self.width * scale, self.height * scale);
    return [self resizeImage:size];
}

- (UIImage*)resizeImage:(CGSize)size
{
    UIGraphicsBeginImageContextWithOptions(size, NO, 0.0);
    [self drawInRect:CGRectMake(0, 0, size.width, size.height)];
    UIImage* newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return newImage;
}

- (UIImage*)cropImage:(CGRect)rect
{
    CGImageRef imageRef = CGImageCreateWithImageInRect([self CGImage], rect);
    UIImage* newImage = [UIImage imageWithCGImage:imageRef];
    CGImageRelease(imageRef);
    return newImage;
}

- (UIImage*)maskImage:(UIImage*)maskImage
{
    CGImageRef maskRef = maskImage.CGImage;
    
    CGImageRef mask = CGImageMaskCreate(CGImageGetWidth(maskRef),
                                        CGImageGetHeight(maskRef),
                                        CGImageGetBitsPerComponent(maskRef),
                                        CGImageGetBitsPerPixel(maskRef),
                                        CGImageGetBytesPerRow(maskRef),
                                        CGImageGetDataProvider(maskRef), NULL, false);
    
    CGImageRef maskedImageRef = CGImageCreateWithMask([self CGImage], mask);
    UIImage* maskedImage = [UIImage imageWithCGImage:maskedImageRef];
    
    CGImageRelease(mask);
    CGImageRelease(maskedImageRef);
    
    return maskedImage;
}

- (UIImage*)overlayImage:(UIImage*)overlayImage
{
    UIGraphicsBeginImageContext(self.size);
    [self drawInRect:CGRectMake(0, 0, self.width, self.height)];
    [overlayImage drawInRect:CGRectMake(0, 0, self.width, self.height)];
    UIImage* overlayedImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return overlayedImage;
}

- (UIImage*)rotateImage:(CGFloat)degrees
{
    UIView* view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.size.width, self.size.height)];
    view.transform = CGAffineTransformMakeRotation(degrees * M_PI / 180);
    
    UIGraphicsBeginImageContext(view.size);
    CGContextRef bitmap = UIGraphicsGetCurrentContext();
    
    CGContextTranslateCTM(bitmap, view.width / 2, view.height / 2);
    CGContextRotateCTM(bitmap, (degrees * M_PI / 180));
    
    CGContextScaleCTM(bitmap, 1.0, -1.0);
    CGContextDrawImage(bitmap, CGRectMake(-self.width / 2, -self.height / 2, self.width, self.height), [self CGImage]);
    
    UIImage* newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
}

@end


// String
@implementation NSString(Custom)

- (BOOL)contains:(NSString*)str
{
    return [self rangeOfString:str].location != NSNotFound;
}

- (NSString*)trim
{
    return [self stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
}

- (NSString*)pluralize:(NSString*)plural count:(NSInteger)count
{
    if(count == 1)
    {
        return self;
    }
    
    return plural;
}

- (id)json
{
    NSData* data = [self dataUsingEncoding:NSUTF8StringEncoding];
    return [data json];
}

- (NSString*)xml
{
    return self;
}

- (NSString*)toBase64
{
    NSData* data = [self dataUsingEncoding:NSUTF8StringEncoding];
    return [data toBase64];
}

- (NSString*)fromBase64
{
    NSData* data = [[NSData alloc] initWithBase64EncodedString:self
                                                       options:NSDataBase64DecodingIgnoreUnknownCharacters];
    return [data string];
}

@end


// Number
@implementation NSNumber(Custom)

- (NSString*)xml
{
    return [self stringValue];
}

@end


// Data
@implementation NSData(Custom)

+ (NSData*)readFile:(NSString*)filePath
{
    return [[NSData alloc] initWithContentsOfFile:filePath];
}

- (BOOL)writeFile:(NSString*)filePath
{
    createDirectory(filePath);
    
    NSError* error;
    [self writeToFile:filePath options:NSDataWritingAtomic error:&error];
    
    return error == nil;
}

- (NSString*)string
{
    return [[NSString alloc] initWithData:self encoding:NSUTF8StringEncoding];
}

- (id)json
{
    return [NSJSONSerialization JSONObjectWithData:self options:kNilOptions error:nil];
}

- (NSString*)toBase64
{
    return [self base64EncodedStringWithOptions:NSDataBase64Encoding64CharacterLineLength];
}

- (NSString*)fromBase64
{
    NSData* data = [[NSData alloc] initWithBase64EncodedData:self
                                                     options:NSDataBase64DecodingIgnoreUnknownCharacters];
    return [data string];
}

@end



//--- FILES
// FileManager
@implementation NSFileManager(Custom)

+ (NSArray*)filesInDir:(NSString*)dirPath
{
    NSError* error;
    NSFileManager* filemanager = [NSFileManager defaultManager];
    NSArray* contents = [filemanager contentsOfDirectoryAtPath:dirPath error:&error];
    if(error)
    {
        return nil;
    }
    
    NSMutableArray* files = [NSMutableArray array];
    for(int i = 0; i < [contents count]; ++i)
    {
        NSString* filePath = [dirPath stringByAppendingPathComponent:[contents objectAtIndex:i]];
        
        BOOL isDir;
        if([filemanager fileExistsAtPath:filePath isDirectory:&isDir] && !isDir)
        {
            [files addObject:filePath];
        }
    }
    
    return files;
}

@end


// Files
NSString* documentsFilePath(NSString* fileName)
{
    NSURL* url = [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory
                                                         inDomains:NSUserDomainMask] firstObject];
    return [url URLByAppendingPathComponent:fileName].path;
}

NSString* cachesFilePath(NSString* fileName)
{
    NSURL* url = [[[NSFileManager defaultManager] URLsForDirectory:NSCachesDirectory
                                                         inDomains:NSUserDomainMask] firstObject];
    return [url URLByAppendingPathComponent:fileName].path;
}

NSString* resourcesFilePath(NSString* fileName)
{
    NSURL* url = [[NSBundle mainBundle] resourceURL];
    return [url URLByAppendingPathComponent:fileName].path;
}

NSString* fileExtension(NSString* fileName)
{
    NSArray* components = [fileName componentsSeparatedByString:@"."];
    return [components lastObject];
}

BOOL createDirectory(NSString* filePath)
{
    NSError* error;
    NSRange range = [filePath rangeOfString:@"/" options:NSBackwardsSearch];
    if(range.length > 0)
    {
        NSString* dir = [filePath substringToIndex:range.location + range.length];
        
        NSFileManager* mgr = [NSFileManager defaultManager];
        if(![mgr fileExistsAtPath:dir])
        {
            [mgr createDirectoryAtPath:dir withIntermediateDirectories:YES attributes:nil error:&error];
        }
    }
    
    return error == nil;
}

BOOL deleteFile(NSString* filePath)
{
    NSError* error = nil;
    [[NSFileManager defaultManager] removeItemAtPath:filePath error:&error];
    return error == nil;
}



//---- OTHER
// Error
@implementation NSError(Custom)

+ (NSError*)withDescription:(NSString*)description
{
    NSDictionary* userInfo = @{NSLocalizedDescriptionKey : description};
    return [NSError errorWithDomain:[[NSBundle mainBundle] bundleIdentifier]
                               code:0
                           userInfo:userInfo];
}

@end


// NSTimer
@implementation NSTimer(Custom)

+ (NSTimer*)timerWithTimeInterval:(NSTimeInterval)timeInterval block:(void (^)())block repeats:(BOOL)repeats
{
    NSTimer* timer = [self timerWithTimeInterval:timeInterval
                                          target:self
                                        selector:@selector(run:)
                                        userInfo:block
                                         repeats:repeats];
    
    return timer;
}

+ (NSTimer*)scheduledTimerWithTimeInterval:(NSTimeInterval)timeInterval block:(void (^)())block repeats:(BOOL)repeats
{
    NSTimer* timer = [self scheduledTimerWithTimeInterval:timeInterval
                                                   target:self
                                                 selector:@selector(run:)
                                                 userInfo:block
                                                  repeats:repeats];
    return timer;
}

+ (void)run:(NSTimer*)timer;
{
    if([timer userInfo])
    {
        void (^block)() = (void (^)())[timer userInfo];
        block();
    }
}

@end


// Validation
BOOL null(id obj)
{
    return obj == nil || [obj isKindOfClass:[NSNull class]];
}

BOOL nullOrEmpty(id obj)
{
    if([obj respondsToSelector:@selector(count)])
    {
        return obj == nil || [obj count] == 0;
    }
    
    if([obj respondsToSelector:@selector(length)])
    {
        return obj == nil || [obj length] == 0;
    }
    
    return null(obj);
}


// System
NSTimeInterval currentTime()
{
    return [[NSDate date] timeIntervalSince1970];
}

CGFloat pixelSize()
{
    return 1.0f / [UIScreen mainScreen].scale;
}


// Math
BOOL equals(double a, double b)
{
    return a > b - FLT_MIN && a < b + FLT_MIN;
}

double clamp(double value, double min, double max)
{
    value = fmax(min, value);
    value = fmin(max, value);
    return value;
}

int32_t bytesToInt(Byte* b)
{
    return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
}

CGSize aspectFit(CGSize limit, CGSize size)
{
    float sizeRatio = size.width / size.height;
    float limitRatio = limit.width / limit.height;
    
    float min = fminf(limit.width, limit.height);
    float max = fmaxf(limit.width, limit.height);
    
    if(equals(limit.width, limit.height))
    {
        if(sizeRatio > 1)
        {
            size.width = max;
            size.height = max / sizeRatio;
        }
        else
        {
            size.width = max * sizeRatio;
            size.height = max;
        }
    }
    else
    {
        BOOL acuteRatio =
        (sizeRatio < 1 && limitRatio < 1 && sizeRatio < limitRatio) ||
        (sizeRatio > 1 && limitRatio > 1 && sizeRatio > limitRatio);
        
        if(limit.width > limit.height)
        {
            if(acuteRatio)
            {
                size.width = max;
                size.height = max / sizeRatio;
            }
            else
            {
                size.width = min * sizeRatio;
                size.height = min;
            }
        }
        else
        {
            if(acuteRatio)
            {
                size.width = max * sizeRatio;
                size.height = max;
            }
            else
            {
                size.width = min;
                size.height = min / sizeRatio;
            }
        }
    }
    
    return size;
}
