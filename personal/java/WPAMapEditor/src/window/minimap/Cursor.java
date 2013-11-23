package window.minimap;

import include.Const;

import javax.media.opengl.GL;

import map.LevelMap;
import sprites.Sprite;

public class Cursor {
	protected static int blockX, blockY;
	private Sprite sprite;
	private int offset[] = {
			-Const.TEX_SIZE[Const.BLOCK_SIZE][0]/2,
			Const.TEX_SIZE[Const.BLOCK_SIZE][1]/2,
	};

	public Cursor(GL gl){
		sprite = new Sprite(Const.S_1024_1024);
		sprite.setBlend(true);
	}
	
	public static int getMapLoc(int c, int a){			
		return Math.round(a*LevelMap.getLargestPixelSize()/Const.MINIMAP_SIZE);
	}
	
	public void draw(GL gl){
		gl.glTranslatef(blockX*Const.TEX_SIZE[Const.BLOCK_SIZE][0] + offset[0] + Const.GL_BOUND, 
				-blockY*Const.TEX_SIZE[Const.BLOCK_SIZE][1] + offset[1] - Const.GL_BOUND, 0);
		sprite.draw(gl, 0);
	}	
}
