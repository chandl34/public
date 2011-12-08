package window.map;

import include.Const;
import io.Loader;

import javax.media.opengl.GL;

import sprites.Sprite;

public class Guide {

	Sprite sprite;
	int pan[] = {0, 0};
	static int scroll[] = {0, 0};
	int bound[] = {	
			(Const.GL_SIZE - Const.TEX_SIZE[Const.GUIDE_SIZE][0])/2,
			(Const.GL_SIZE - Const.TEX_SIZE[Const.GUIDE_SIZE][1])/2,
	};
	
	public Guide(GL gl){
		sprite = Loader.loadImage(gl, "guide.png");
		sprite.setBlend(true);
	}
	
	public static int getScroll(int c){
		return scroll[c];
	}
	
	public static void setScroll(int c, int p){
		scroll[c] = p;
	}
	
	private void setPan(int c, int p){
		if(p < -bound[c]){
			pan[c] = -bound[c];		
			Camera.setPan(c, Camera.getPan(c) + scroll[c]);
			MapPanel.adjustScrollBar(c);
		}
		else if(p > bound[c]){
			pan[c] = bound[c];
			Camera.setPan(c, Camera.getPan(c) + scroll[c]);
			MapPanel.adjustScrollBar(c);
		}
		else
			pan[c] = p;
	}
	
	public void draw(GL gl){
		gl.glMatrixMode(GL.GL_PROJECTION);
		gl.glLoadIdentity();			
		gl.glOrtho(-Const.GL_BOUND, Const.GL_BOUND, 
				-Const.GL_BOUND, Const.GL_BOUND, -1.0f, 1.0f);
		gl.glTranslatef(0, 0, 0);
		
		gl.glMatrixMode(GL.GL_MODELVIEW);
		gl.glLoadIdentity();
		setPan(0, pan[0] + scroll[0]);
		setPan(1, pan[1] + scroll[1]);
		gl.glTranslatef(pan[0], -pan[1], 0);
		sprite.draw(gl, 0);	
	}
}
