package window;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import window.map.Guide;


public class KeyboardInput implements KeyListener{

	int inc = 1;
	
	public void keyPressed(KeyEvent e) {
		switch(e.getKeyCode()){
		case KeyEvent.VK_LEFT: case 'a': case 'A':
			Guide.setScroll(0, -32);
			break;

		case KeyEvent.VK_DOWN: case 's': case 'S':
			Guide.setScroll(1, 16);			
			break;
			
		case KeyEvent.VK_RIGHT: case 'd': case 'D':
			Guide.setScroll(0, 32);		
			break;

		case KeyEvent.VK_UP: case 'w': case 'W':
			Guide.setScroll(1, -16);			
			break;
		}
	}

	public void keyReleased(KeyEvent e) {
		switch(e.getKeyCode()){
		case KeyEvent.VK_LEFT: case 'a': case 'A':
			if(Guide.getScroll(0) == -32)
				Guide.setScroll(0, 0);
			break;

		case KeyEvent.VK_DOWN: case 's': case 'S':
			if(Guide.getScroll(1) == 16)
				Guide.setScroll(1, 0);			
			break;
			
		case KeyEvent.VK_RIGHT: case 'd': case 'D':
			if(Guide.getScroll(0) == 32)
				Guide.setScroll(0, 0);		
			break;

		case KeyEvent.VK_UP: case 'w': case 'W':
			if(Guide.getScroll(1) == -16)
				Guide.setScroll(1, 0);			
			break;
		}
	}

	public void keyTyped(KeyEvent e) {
		
	}

}
