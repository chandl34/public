package window.map;

import include.Const;

import java.awt.event.AdjustmentEvent;
import java.awt.event.AdjustmentListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import javax.swing.JScrollBar;

import map.MapEditor;

public class MouseInput implements MouseListener, MouseMotionListener, AdjustmentListener{

	private int oldX = 0, oldY = 0;
	private boolean disabled = true;;

	public void mouseClicked(MouseEvent e){}

	public void mouseEntered(MouseEvent e){
		disabled = false;
	}

	public void mouseExited(MouseEvent e){
		disabled = true;
	}

	public void mousePressed(MouseEvent e){
		mouseMoved(e);
		if(!disabled){
			if(e.getButton() == MouseEvent.BUTTON3)
				MapEditor.toggleType();
			if(e.getButton() == MouseEvent.BUTTON1 || e.getButton() == 0){
				if(e.getButton() == MouseEvent.BUTTON1 ||
						(e.getButton() == 0 && (oldX != Cursor.blockX || oldY != Cursor.blockY)))
					MapEditor.insertType(Cursor.blockX, Cursor.blockY);
				oldX = Cursor.blockX;
				oldY = Cursor.blockY;
			}
		}
	}

	public void mouseReleased(MouseEvent e){}

	public void mouseDragged(MouseEvent e) {
		mousePressed(e);
	}

	public void mouseMoved(MouseEvent e) {	
		if(!disabled){				
			int x = Cursor.getMapLoc(0, e.getX());
			int y = Cursor.getMapLoc(1, e.getY());

			Cursor.blockX = x/Const.TEX_SIZE[Const.BLOCK_SIZE][0];
			Cursor.blockY = y/Const.TEX_SIZE[Const.BLOCK_SIZE][1];

			int remX = x%Const.TEX_SIZE[Const.BLOCK_SIZE][0];		
			int remY = y%Const.TEX_SIZE[Const.BLOCK_SIZE][1];	

			if((Cursor.blockX + Cursor.blockY)%2 == 0){ //Even gridBlocks own 
				if(remY + 0.5f*remX > 32){ // Centered at current gridBlock's pixel translation
					Cursor.blockX++;
					Cursor.blockY++;
				}
			}
			else{
				if(remY - 0.5f*remX > 0)
					Cursor.blockY++;
				else
					Cursor.blockX++;

			}	
		}
	}

	public void adjustmentValueChanged(AdjustmentEvent e) {
		JScrollBar jBar = (JScrollBar)e.getSource();

		if(jBar.getVisibleAmount() == 100)
			return;
		
		int c = 1;
		if(jBar == MapPanel.hBar)
			c = 0;
		
		float range = jBar.getMaximum() - jBar.getVisibleAmount();
		
		float temp = jBar.getValue()/range;
		temp *= Camera.getBound(c);
		Camera.setPan(c, (int)temp);
	}	
}
