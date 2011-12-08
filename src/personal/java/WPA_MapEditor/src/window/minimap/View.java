package window.minimap;

import include.Const;
import include.ConstAssist;
import io.CatalogBuilder;

import javax.media.opengl.GL;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLEventListener;

import map.LevelMap;
import window.map.Camera;

public class View implements GLEventListener{
	private static GL gl;
	
	private static Cursor cursor;
	private static MouseInput mouseInput;
	
	private int size;
	
	private int offset[] = {
			Const.TEX_SIZE[Const.BLOCK_SIZE][0]/2,
			-Const.TEX_SIZE[Const.BLOCK_SIZE][1]/2,
	};
	
	public void display(GLAutoDrawable gLDrawable){
		if(window.map.View.getLevelMap() != null){
			size = LevelMap.getLargestPixelSize()/2;
			
			gl.glClear(GL.GL_COLOR_BUFFER_BIT);	

			gl.glMatrixMode(GL.GL_PROJECTION);
			gl.glLoadIdentity();			
			gl.glOrtho(-size, size, -size, size, -1.0f, 1.0f);
			gl.glTranslatef(-ConstAssist.getMiniMapSize(0) + offset[0], 
					ConstAssist.getMiniMapSize(1) + offset[1], 0);

			gl.glMatrixMode(GL.GL_MODELVIEW);
			gl.glLoadIdentity();
			LevelMap.draw(gl);

			gl.glMatrixMode(GL.GL_MODELVIEW);
			gl.glLoadIdentity();
			gl.glTranslatef(Camera.getPan(0), -Camera.getPan(1), 0);
			cursor.draw(gl);
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
		gl.glColor4f(1, 1, 1, 0.4f);

		gl.glBlendFunc(GL.GL_SRC_ALPHA, GL.GL_ONE_MINUS_SRC_ALPHA);
		gl.glEnable(GL.GL_TEXTURE_2D);
		gl.glDisable(GL.GL_DEPTH_TEST);	
		
		mouseInput = new MouseInput();
		gLDrawable.addMouseListener(mouseInput);
		gLDrawable.addMouseMotionListener(mouseInput);
		
		cursor = new Cursor(gl);
	}
}
