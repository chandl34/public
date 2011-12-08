package include;


import map.LevelMap;



public class ConstAssist {
		
	public static int getTexSize(int x, int y){
		for(int i = 0; i < Const.TEXTURE_SIZES; i++){
			if(x == Const.TEX_SIZE[i][0] && y == Const.TEX_SIZE[i][1])
				return i;
		}		
		return -1;
	}	
	
	public static int getBlocksPerScreen(int c){
		return Const.GL_SIZE/Const.TEX_SIZE[Const.BLOCK_SIZE][c];		
	}
	
	public static int getMiniMapSize(int c){
		return LevelMap.getPixelSize(c)/2;
	}
}
