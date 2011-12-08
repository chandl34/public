package map;

import include.Const;

import javax.media.opengl.GL;

import window.map.Camera;
import window.map.MapPanel;


public class LevelMap {
	
	private static int size[];
	private static int pixelSize[] = new int[2];
	private static Block block[][];
	private static IsoBlock isoBlock[][];
	
	public LevelMap(int w, int h){
		pixelSize[0] = w*Const.TEX_SIZE[Const.BLOCK_SIZE][0]/2;
		pixelSize[1] = h*Const.TEX_SIZE[Const.BLOCK_SIZE][1];
		Camera.setBounds(pixelSize[0], pixelSize[1]);
		MapPanel.resizeScrollBars(pixelSize[0], pixelSize[1]);
		
		size = new int[2];
		size[0] = pixelSize[0]/Const.TEX_SIZE[Const.BLOCK_SIZE][0];
		size[1] = pixelSize[1]/Const.TEX_SIZE[Const.BLOCK_SIZE][1];
				
		block = new Block[size[0]][size[1]];
		for(int i = 0; i < size[0]; i++){
			for(int j = 0; j < size[1]; j++)
				block[i][j] = new Block(i, j);	
		}
		
		isoBlock = new IsoBlock[size[0] + 1][size[1] + 1];
		for(int i = 0; i <= size[0]; i++){
			for(int j = 0; j <= size[1]; j++){
				if((i+j)%2 == 0)
					isoBlock[i][j] = new IsoBlock(i, j);
				else
					isoBlock[i][j] = null;
			}
		}
	}
	
	public static int getSize(int c){
		return size[c];
	}

	public static int getPixelSize(int c){
		return pixelSize[c];
	}
	
	public static int getLargestPixelSize(){
		return Math.max(pixelSize[0], pixelSize[1]);
	}
		
	public static Block getBlock(int i, int j){
		if(i >= 0 && i < size[0] && j >= 0 && j < size[1])
			return block[i][j];
		return null;
	}
	
	public static IsoBlock getIsoBlock(int i, int j){
		if(i >= 0 && i <= size[0] && j >= 0 && j <= size[1])
			return isoBlock[i][j];
		return null;
	}
	
	public static void draw(GL gl){
		for(int i = 0; i < size[0]; i++){
			for(int j = 0; j < size[1]; j++)
				block[i][j].draw(gl);
		}
	}
}
