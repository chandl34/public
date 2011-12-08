package window.map;

import include.Const;


public class Camera{
	private static int pan[] = {0, 0};
	private static int bound[] = new int[2];	
	
	public static void setPan(int c, int p){
		if(p < 0)
			pan[c] = 0;		
		else if(p > bound[c])
			pan[c] = bound[c];
		else
			pan[c] = p;
		pan[c] -= pan[c]%2;
	}
	
	public static int getPan(int c){
		return pan[c];
	}
	
	public static void setBounds(int x, int y){
		bound[0] = x - Const.GL_SIZE;
		bound[1] = y - Const.GL_SIZE;
	}
	
	public static int getBound(int c){
		return bound[c];
	}
}