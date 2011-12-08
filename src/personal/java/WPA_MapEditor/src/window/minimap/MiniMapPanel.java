package window.minimap;

import include.Const;

import java.awt.Color;

import javax.media.opengl.GLCanvas;
import javax.swing.BorderFactory;
import javax.swing.JLayeredPane;

import com.sun.opengl.util.Animator;



public class MiniMapPanel  extends JLayeredPane{
	private static View view;
	private static GLCanvas glCanvas;
	

	public MiniMapPanel(){
		setBounds(0, Const.TOOLPANEL_HEIGHT - 1, Const.MINIMAP_SIZE + 8, Const.MINIMAP_SIZE + 8);
		setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(Color.black),
                BorderFactory.createEmptyBorder(5,5,5,5)));

		glCanvas = new GLCanvas(); 
		glCanvas.setBounds(4, 4, Const.MINIMAP_SIZE, Const.MINIMAP_SIZE);
		view = new View();
		glCanvas.addGLEventListener(view);
		glCanvas.setFocusable(false);
		add(glCanvas);
		
		final Animator animator = new Animator(glCanvas); 	
		animator.start(); 
	}
	
}
