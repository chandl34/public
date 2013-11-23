package bugs;

import java.awt.Rectangle;

import main.FlyGame;

public abstract class Projectile extends AnimatedLabel{

	public Projectile(FlyGame theGame){
		super(theGame);	
		setAlive(false);
	}

	public void initialize(){
		timer = 0;
		setVisible(true);
	}	

	public void sendCursorLocation(Rectangle r){
		cursor = r;
	}

	public void step(){
		if(timer == -1)
			initialize();
		else{
			projectileMovement();
			int px_post = getX() + getHVelocity();
			int py_post = getY() + getVVelocity();
			//Checks if the projectile has gone out of bounds
			if(px_post < 0 || px_post > FlyGame.WIDTH || py_post < 0 || py_post > FlyGame.HEIGHT)
				game.remove(this);
			setLocation(px_post, py_post);
			if(getBounds().intersects(cursor))  //Checks if the cursor is being touched by this
				game.takeDamage();
			animate();
			timer++;
		}
	}

	public abstract void projectileMovement();
}
