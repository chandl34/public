package include;


import java.util.Random;


public class Const {
	//---- OBJECTS ----//
	public static final Random RANDOM = new Random();
	
	
	

	//----   LIBRARY NAMES  ----//
	public static final int WINDOWS = 0;
	public static final int MACOSX = 1;
	public static final int LINUX = 2;

	public static final String OS_NAME[] = {
		"windows", "macosx", "linux"
	};
	
	public static final String EXTENSION[] = {
		".dll", ".jnilib", ".so"
	};
	
	public static final int I386 = 0;
	public static final int AMD64 = 1;
	
	public static final String ARCHITECTURE[] = {
		"i386", "amd64"
	};
	
	public static final int LIBRARIES_NEEDED = 2;
	public static final String LIBRARY[] = {
		"jogl", "jogl_awt"
	};
	
	
	

	//----   MAP SCREEN SIZE  ----//
	public static final int GL_BOUND = 512;
	public static final int GL_SIZE = GL_BOUND*2;
	
	
	

	//----   WINDOW DATA  ----//
	public static final int JAVA_ERROR[] = {6, 32};
	public static final int MENUBAR_HEIGHT = 23;
	public static final int TOOLPANEL_HEIGHT = 64;
	public static final int MINIMAP_SIZE = 96;
	public static final int MAP_SIZE = GL_BOUND;
	public static final int SCROLLBAR_SIZE = 16;
	public static final int WINDOW_WIDTH = MINIMAP_SIZE + MAP_SIZE + SCROLLBAR_SIZE + 16 + JAVA_ERROR[0] - 1;
	public static final int WINDOW_HEIGHT = MENUBAR_HEIGHT + TOOLPANEL_HEIGHT + MAP_SIZE + SCROLLBAR_SIZE + 8 + JAVA_ERROR[1] - 1;
	
	
	

	//----   TERRAIN  ----//
	public static final int LOW = 0;
	public static final int MID = 1;
	public static final int HIGH = 2;
	
	public static final int TERRAIN_TYPES = 3;
	public static final int NONE = -1;
	public static final int SEA = 0;
	public static final int BEACH = 1;
	public static final int GRASS = 1;
	
	public static final int MASTER[] = {
		NONE, SEA, BEACH
	};	
	public static final int DEFAULT_TERRAIN = SEA;
	
	public static final int TERRAIN_SECTIONS = 9;
	public static final int COMPLETE = 0;
	public static final int TOP1 = 1;
	public static final int TOP2 = 2;
	public static final int BOTTOM1 = 3;
	public static final int BOTTOM2 = 4;
	public static final int CORNER = 5;
	public static final int FAT_INNER = 6;
	public static final int SKINNY_INNER = 7;
	public static final int SKINNY = 8;
	
	
	

	//---- BLOCK INFORMATION ----//
	public static final int TOP_LEFT = 0;
	public static final int TOP_RIGHT = 1;	
	public static final int BOTTOM_RIGHT = 2;
	public static final int BOTTOM_LEFT = 3;

	public static final int NOFLIP = 0;
	public static final int FLIP = 1;
	
	public static final int TEXTURE_SIZES = 7;
	public static final int S_32_16 = 0;
	public static final int S_32_32 = 1;
	public static final int S_64_32 = 2;
	public static final int S_128_64 = 3;	
	public static final int S_256_256 = 4;	
	public static final int S_460_272 = 5;
	public static final int S_1024_1024 = 6; // screen size
	public static final int TEX_SIZE[][] = {
		{32, 16},
		{32, 32},
		{64, 32},
		{128, 64},
		{256, 256},
		{460, 272},
		{1024, 1024},
	};
	
	public static final int BLOCK_SIZE = S_32_16;
	public static final int SCREEN_SIZE = S_1024_1024;
	public static final int GUIDE_SIZE = S_460_272;
	
	public static final int SPRITE_VERT[][] = {
		{16, 8,
		-16, 8,
		16, -8,	
		-16, -8,},		
		
		{16, 16,
		-16, 16,
		16, -16,	
		-16, -16,},		

		{32, 16,
		-32, 16,
		32, -16,	
		-32, -16,},	

		{64, 32,
		-64, 32,
		64, -32,	
		-64, -32,},	
		
		{128, 128,
		-128, 128,
		128, -128,	
		-128, -128,},			

		{230, 136,
		-230, 136,
		230, -136,	
		-230, -136,},	
		
		{512, 512,
		-512, 512,
		512, -512,	
		-512, -512,},	
	};	
}
