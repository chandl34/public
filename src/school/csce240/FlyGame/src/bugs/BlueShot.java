package bugs;

import javax.swing.ImageIcon;

import main.FlyGame;

public class BlueShot extends Projectile {

	private ImageIcon icon[] = {
			new ImageIcon("icons/monsters/BlueShot/fireball1.GIF"),
			new ImageIcon("icons/monsters/BlueShot/fireball2.GIF"),
			new ImageIcon("icons/monsters/BlueShot/fireball3.GIF")
	};

	public BlueShot(int shotDir, FlyGame theGame) {
		super(theGame);
		setSpeed(15);
		setIcon(icon[2]);
		setSize(32, 32);
		if(shotDir == FlyGame.BLUESHOT1)  // TOP LEFT
			setVelocity(-getSpeed(), -getSpeed());
		else if(shotDir == FlyGame.BLUESHOT2)  // TOP RIGHT
			setVelocity(getSpeed(), -getSpeed());
		else if(shotDir == FlyGame.BLUESHOT3)  // BOTTOM RIGHT
			setVelocity(getSpeed(), getSpeed());
		else  // BOTTOM LEFT
			setVelocity(-getSpeed(), getSpeed());
	}

	public void animate(){
		setIcon(icon[timer%3]);
	}
	
	public void projectileMovement(){}
	
}
