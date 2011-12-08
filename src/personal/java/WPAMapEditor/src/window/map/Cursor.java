package window.map;

import include.Const;
import io.Loader;

import javax.media.opengl.GL;

import sprites.Sprite;

public class Cursor {

	protected static int blockX, blockY;
	private Sprite sprite;
	private int offset[] = {
			-Const.TEX_SIZE[Const.BLOCK_SIZE][0]/2,
			Const.TEX_SIZE[Const.BLOCK_SIZE][1]/2,
	};

	public Cursor(GL gl){
		sprite = Loader.loadImage(gl, "selectBox.png");
		sprite.setBlend(true);
	}
	
	public static int getMapLoc(int c, int a){
		return Math.round(a*Const.GL_SIZE/Const.MAP_SIZE) + Camera.getPan(c);
	}
	
	public void draw(GL gl){
		gl.glLoadIdentity();
		gl.glTranslatef(blockX*Const.TEX_SIZE[Const.BLOCK_SIZE][0] + offset[0], 
				-blockY*Const.TEX_SIZE[Const.BLOCK_SIZE][1] + offset[1], 0);
		sprite.draw(gl, 0);
	}	
}
