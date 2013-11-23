package bugs;

import javax.swing.ImageIcon;

import main.FlyGame;

public class Gnat extends Projectile {

	private ImageIcon icon[] = {
			new ImageIcon("icons/monsters/Gnat/gnat1.GIF"),  // 28 x 20
			new ImageIcon("icons/monsters/Gnat/gnat2.GIF"),	
			new ImageIcon("icons/monsters/Gnat/gnat3.GIF")
	};
	
	public Gnat(int gnatIniStep, FlyGame theGame){
		super(theGame);
		setSpeed(20);
		setIcon(icon[2]);
		setSize(28, 20);
	}

	public void animate(){
		if(timer%4 == 0)
			setIcon(icon[1]);
		else if(timer%4 == 1)
			setIcon(icon[0]);		
		else if(timer%4 == 2)
			setIcon(icon[1]);
		else
			setIcon(icon[2]);
	}
	
	public void projectileMovement(){
		if(timer < 54)
			homingMovement();
	}

}
