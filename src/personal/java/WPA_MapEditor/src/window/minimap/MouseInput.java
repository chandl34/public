package window.minimap;

import include.Const;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import map.LevelMap;
import window.map.Camera;


public class MouseInput implements MouseListener, MouseMotionListener{

	private boolean disabled = true;

	public void mouseClicked(MouseEvent e){}

	public void mouseEntered(MouseEvent e){
		disabled = false;
	}

	public void mouseExited(MouseEvent e){
		disabled = true;
	}

	public void mousePressed(MouseEvent e){
		if(!disabled){
			int x = Cursor.getMapLoc(0, e.getX()) - Const.GL_BOUND;
			int y = Cursor.getMapLoc(1, e.getY()) - Const.GL_BOUND;
			x -= (LevelMap.getLargestPixelSize() - LevelMap.getPixelSize(0))/2;
			y -= (LevelMap.getLargestPixelSize() - LevelMap.getPixelSize(1))/2;
			Camera.setPan(0, x);
			Camera.setPan(1, y);
			
		//	Window.adjustScrollBar(0);
		//	Window.adjustScrollBar(1);
		}
	}

	public void mouseReleased(MouseEvent e){}

	public void mouseDragged(MouseEvent e) {
		mousePressed(e);
	}

	public void mouseMoved(MouseEvent e) {}
}
