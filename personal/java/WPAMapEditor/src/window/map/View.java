package window.map;

import include.Const;
import io.CatalogBuilder;

import javax.media.opengl.GL;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLEventListener;

import map.LevelMap;

public class View implements GLEventListener{
	private static GL gl;
	
	private static LevelMap levelMap;
	private static Cursor cursor;
	private static Guide guide;
	
	private int offset[] = {
			Const.TEX_SIZE[Const.BLOCK_SIZE][0]/2,
			-Const.TEX_SIZE[Const.BLOCK_SIZE][1]/2,
	};
	
	public static LevelMap getLevelMap(){
		return levelMap;
	}
	
	public static void setLevelMap(LevelMap map){
		levelMap = map;
	}
	
	public void display(GLAutoDrawable gLDrawable){
		if(levelMap != null){
			gl.glClear(GL.GL_COLOR_BUFFER_BIT);	

			gl.glMatrixMode(GL.GL_PROJECTION);
			gl.glLoadIdentity();			
			gl.glOrtho(-Const.GL_BOUND, Const.GL_BOUND, 
					-Const.GL_BOUND, Const.GL_BOUND, -1.0f, 1.0f);
			gl.glTranslatef(-Camera.getPan(0) - Const.GL_BOUND + offset[0], 
					Camera.getPan(1) + Const.GL_BOUND  + offset[1], 0);

			gl.glMatrixMode(GL.GL_MODELVIEW);
			gl.glLoadIdentity();
			LevelMap.draw(gl);
			cursor.draw(gl);

			guide.draw(gl);
		}
	}

	public void reshape(GLAutoDrawable gLDrawable, int x, 
			int y, int width, int height) {}

	public void displayChanged(GLAutoDrawable gLDrawable, 
			boolean modeChanged, boolean deviceChanged){}

	public void init(GLAutoDrawable gLDrawable) {
		gl = gLDrawable.getGL();

		CatalogBuilder.buildTerrain(gl);
				
		gl.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		gl.glColor4f(1, 1, 1, .8f);

		gl.glBlendFunc(GL.GL_SRC_ALPHA, GL.GL_ONE_MINUS_SRC_ALPHA);
		gl.glEnable(GL.GL_TEXTURE_2D);
		gl.glDisable(GL.GL_DEPTH_TEST);	
		
		gLDrawable.addMouseListener(MapPanel.mouseInput);
		gLDrawable.addMouseMotionListener(MapPanel.mouseInput);

		levelMap = new LevelMap(64, 64);	
		cursor = new Cursor(gl);
		guide = new Guide(gl);
	}
}
