package window.map;

import include.Const;

import java.awt.Color;

import javax.media.opengl.GLCanvas;
import javax.swing.BorderFactory;
import javax.swing.JLayeredPane;
import javax.swing.JScrollBar;

import com.sun.opengl.util.Animator;

public class MapPanel extends JLayeredPane{

	private static View glView;
	private static GLCanvas glCanvas;
	protected static JScrollBar vBar, hBar;	
	protected static MouseInput mouseInput;
	
	public MapPanel(){
		setBounds(
				Const.MINIMAP_SIZE + 8 - 1, Const.TOOLPANEL_HEIGHT - 1, 
				Const.MAP_SIZE + 8 + Const.SCROLLBAR_SIZE, Const.MAP_SIZE + 8 + Const.SCROLLBAR_SIZE);
		setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(Color.black),
                BorderFactory.createEmptyBorder(5,5,5,5)));

		glCanvas = new GLCanvas(); 
		glCanvas.setBounds(4, 4, Const.MAP_SIZE, Const.MAP_SIZE);
		glView = new View();
		glCanvas.addGLEventListener(glView);
		glCanvas.setFocusable(false);
		add(glCanvas);
		
		final Animator animator = new Animator(glCanvas); 	
		animator.start(); 

		mouseInput = new MouseInput();
		
		vBar = new JScrollBar();
		vBar.setBounds(6 + Const.MAP_SIZE, 4, Const.SCROLLBAR_SIZE, Const.MAP_SIZE);
		vBar.addAdjustmentListener(mouseInput);
		add(vBar);
		
		hBar = new JScrollBar();
		hBar.setBounds(4, 6 + Const.MAP_SIZE, Const.MAP_SIZE, Const.SCROLLBAR_SIZE);
		hBar.setOrientation(JScrollBar.HORIZONTAL);
		hBar.addAdjustmentListener(mouseInput);
		add(hBar);
	}
	
	public static void resizeScrollBars(int x, int y){
		float w = ((float)Const.GL_SIZE)/x*100;
		float h = ((float)Const.GL_SIZE)/y*100;
		hBar.setVisibleAmount((int)w);
		vBar.setVisibleAmount((int)h);
	}
	
	public static void adjustScrollBar(int c){	
		JScrollBar jBar = hBar;
		if(c == 1)
			jBar = vBar;
		
		int range = jBar.getMaximum() - jBar.getVisibleAmount();
		
		float p = ((float)Camera.getPan(c))*range/Camera.getBound(c);
		jBar.setValue((int)p);
	}
}
