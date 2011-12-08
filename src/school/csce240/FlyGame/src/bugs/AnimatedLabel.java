package bugs;

import java.awt.Rectangle;

import javax.swing.JLabel;

import sound.SoundFXPlayer;

import main.FlyGame;

public abstract class AnimatedLabel extends JLabel{

	private boolean alive;	
	private int velx, vely;	// Vector speed <x, y> components
	private int speed;  // Vector speed
	protected int speedReduction;

	protected boolean stopping, stopped, starting, movesInCircles, attackAnimating;
	protected int lastSwitchedDirections, lastStop;

	//Next few variables only used if movesInCircles = true
	protected double degrees;  //Travel angle, standard (x, y) coordinates with positive y going up
	private static final int RADIUSMAX = 20;
	protected int radius;
	protected boolean goingClockwise;

	protected FlyGame game;	
	protected int timer = -1;
	protected Rectangle cursor;  // Only used if a Projectile or BombOmb
	protected SoundFXPlayer deathSound, fallSound;

	AnimatedLabel(FlyGame theGame){
		super();		
		game = theGame;
	}	

	public void initialize(){
		timer = 0;
		alive = true;
		lastSwitchedDirections = 0;
		lastStop = 0;
		radius = 15;
		if(Math.random() > .5)
			goingClockwise = true;
		else
			goingClockwise = false;
		starting = false;
		stopping = false;
		stopped = false;
		attackAnimating = false;
		speedReduction = 0;

		int x, y;
		velx = vely = (int)Math.round(Math.random() * speed - speed / 2.0); //One of these will be reset below
		if(Math.random() < .5){		
			x = (int)Math.round(Math.random()*(FlyGame.WIDTH - getWidth()));    		
			if(Math.random() > .5){
				y = 0;
				vely = (int)Math.round(Math.sqrt(speed * speed - velx * velx));
			}
			else{
				y = FlyGame.HEIGHT - getHeight();
				vely = -(int)Math.round(Math.sqrt(speed * speed - velx * velx));
			}
		}
		else{
			y = (int)Math.round(Math.random()*(FlyGame.HEIGHT - getHeight()));
			if(Math.random() > .5){
				x = 0;
				velx = (int)Math.round(Math.sqrt(speed * speed - vely * vely));
			}
			else{
				x = FlyGame.WIDTH - getWidth();
				velx = -(int)Math.round(Math.sqrt(speed * speed - vely * vely));
			}
		}    	
		setLocation(x, y);
		setVisible(true);

		degrees = (int)Math.round(Math.toDegrees(Math.atan2(-vely, velx)));

	}

	public void setVelocity(int vx, int vy) {
		velx = vx;
		vely = vy;
	}

	public int getHVelocity() {
		return velx;
	}

	public int getVVelocity() {
		return vely;
	}

	public int getSpeed(){
		return speed;
	}

	public void setSpeed(int i){
		speed = i;
	}

	public void kill(){
		deathSound.play();
		setAlive(false);
	}

	public void setAlive(boolean a){
		alive = a;
	}

	public boolean isAlive(){
		return alive;
	}

	public void horizontalMovement(){
		if(!starting && !stopping && !stopped && (Math.random() < .01 || timer == lastStop + 150)){ //Causes bug to come to a stop
			stopping = true;
			//System.out.println("STOPPING");
		}
		//Can switch directions here
		if(Math.random() < .01 || timer == lastSwitchedDirections + 50){
			velx = -velx;
			lastSwitchedDirections = timer;
		}
		if(timer%6 == 0){			
			if(stopping){
				speedReduction += 5;
				if(speedReduction >= speed){	
					speedReduction = speed;
					stopping = false;
					stopped = true;
					lastStop = timer;
					//System.out.println("STOPPED");
				}
			}
			else if(starting){
				speedReduction -= 4;
				if(speedReduction <= 0){
					speedReduction = 0;
					starting = false;					
					//System.out.println("REGAINING SPEED");
				}
			}	
			if(velx > 0)
				velx = speed - speedReduction;
			else
				velx = -(speed - speedReduction);
		}
	}

	public void homingMovement(){
		velx = (cursor.x + cursor.width / 2) - (getX() + getWidth() / 2);
		vely = (cursor.y + cursor.height / 2) - (getY() + getHeight() / 2);
		double hypotenuse = Math.sqrt((double)velx * velx + vely * vely);
		velx = (int)Math.round(velx / hypotenuse * speed);
		vely = (int)Math.round(vely / hypotenuse * speed);
	}

	public void circularMovement(){
		//Can switch directions here
		if(Math.random() < .01 || timer == lastSwitchedDirections + 100){
			goingClockwise = !goingClockwise;
			lastSwitchedDirections = timer;
		}
		if(!stopping && radius >= 5 && (Math.random() < .001 || timer == lastStop + 500)){ //Causes bug to come to a stop
			stopping = true;
			//System.out.println("STOPPING - AnimatedLabel - " + timer);
		}
		if(timer%6 == 0){
			if(radius < 5 && //Prevents getting shot into a corner when coming out of a tight circle
					(getX() > FlyGame.WIDTH/2 && getY() > FlyGame.HEIGHT/2 && velx <= 0 && vely <= 0) ||
					(getX() > FlyGame.WIDTH/2 && getY() < FlyGame.HEIGHT/2 && velx <= 0 && vely >= 0) ||
					(getX() < FlyGame.WIDTH/2 && getY() > FlyGame.HEIGHT/2 && velx >= 0 && vely <= 0) ||
					(getX() < FlyGame.WIDTH/2 && getY() < FlyGame.HEIGHT/2 && velx >= 0 && vely >= 0)) {
				if(stopped){	
					if(!attackAnimating){
						degrees = (int)Math.round(Math.random() * 360);
						stopped = false;
						starting = true; 
						//System.out.println("STARTING - AnimatedLabel - " + timer);
					}
				}
				else if(!stopping && !starting)
					radius = RADIUSMAX - (int)Math.round(Math.random() * 10);
			}
			if(!stopped){
				if(!starting){
					radius--;
					if(radius <= 0 && stopping){
						radius = 0;
						if(this instanceof Attacker)
							attackAnimating = true;
						stopping = false;
						stopped = true;
						lastStop = timer;
						//System.out.println("STOPPED - AnimatedLabel - " + timer);
					}
				}
				else{
					radius += 2;
					if(radius > RADIUSMAX - 5){
						starting = false;
						//System.out.println("REGAINING SPEED - AnimatedLabel - " + timer);
					}
				}
			}
		}
		//Speed control for a large radius
		double limiter = (4.0 * RADIUSMAX - radius)/(4.0 * RADIUSMAX);
		//Circular movement
		velx = (int)Math.round(limiter * speed * Math.cos(Math.toRadians(degrees)));
		vely = -(int)Math.round(limiter * speed * Math.sin(Math.toRadians(degrees)));
		//Slowing to a stop or expanding slowly
		if(stopped || stopping || starting){
			velx *= ((double)radius)/RADIUSMAX;
			vely *= ((double)radius)/RADIUSMAX;
		}
		if(goingClockwise)
			degrees -= (RADIUSMAX - radius);	  
		else
			degrees += (RADIUSMAX - radius);
	}

	public void step() {  // Checks for if the bug is going out of bounds, then makes a movement step
		int px_post = getX() + velx; 
		int py_post = getY() + vely;

		if(getX() + getWidth() > FlyGame.WIDTH || getX() < 0 ){ // CASE 1
			velx = -velx;
			px_post = getX() + velx;
			switchDirections();
		}
		else if(getX() + getWidth() + velx > FlyGame.WIDTH || getX() + velx < 0 ){ // CASE 2
			velx = -velx;
			px_post = getX();
			switchDirections();
		}	 
		if(getY() + getHeight() > FlyGame.HEIGHT || getY() < 0){ // CASE 1
			vely = -vely;
			py_post = getY() + vely;
			switchDirections();
		}
		else if(getY() + getHeight() + vely > FlyGame.HEIGHT || getY() + vely < 0){ // CASE 2
			vely = -vely;
			py_post = getY();
			switchDirections();
		}			
		setLocation(px_post, py_post);	
	}

	public void deathAnimation(){
		velx = 0;
		vely = 40;
		if(getY() + vely > FlyGame.HEIGHT){
			fallSound.play(); // Sound when they hit the table
			game.remove(this);
		}
		else
			setLocation(getX(), getY() + vely);
	}

	private void switchDirections(){
		if(movesInCircles){
			if(Math.random() > .5){
				goingClockwise = !goingClockwise;	
				lastSwitchedDirections = timer;
			}	 		 	
			degrees -= 180;
			if(Math.random() < .5){
				if(Math.random() < .5){
					radius += (int)Math.round(Math.random() * 5);
					if(radius > RADIUSMAX)
						radius = RADIUSMAX;
				}
				else{
					radius -= (int)Math.round(Math.random() * 5);
					if(radius < 0)
						radius = 0;
				}
			}
		}
		else
			lastSwitchedDirections = timer;
	}

	public abstract void animate();

}
