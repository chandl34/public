/**
 * Overview:  Handles the animation of bugs
 * 
 * @author Jonathan Chandler
 * @author James Liu
 */

public abstract class AnimatedThing{

  private boolean alive;	
  private int velx;
  private int vely;	
  protected AnimatedLabel aLabel;
  private int speed;
  private double degrees = 0;
  protected int timer = 0;
  protected static final int INCREMENTMAX = 30;
  protected int increment = (int)Math.round((Math.random() * (INCREMENTMAX - 3)));
  private boolean goingClockwise;
  private int whenSwitchedDirections = 0;
  protected int targetX;
  protected int targetY;
  protected Sound deathSound;
	
  /**
   * Initializes an AnimatedThing
   * @param label AnimatedLabel this AnimatedThing is connected to
   */
  public AnimatedThing(AnimatedLabel label) {
	aLabel = label;
    alive = true;
    if(Math.random() > .5)
    	goingClockwise = true;
    else
    	goingClockwise = false;    		
  } // end AnimatedThing

  /**
   * Sets location of cursor's top left corner
   * <p>
   * modifies:  sets targetX and targetY 
   * @param x Top-left corner of cursor
   * @param y Top-left corner of cursor
   */
  public void setTargetLocation(int x, int y){
	  targetX = x;
	  targetY = y;
  }
  
  /**
   * Sets vertical and horizontal velocities
   * <p>
   * modifies:  sets velx and vely
   * @param vx  new velocity in x direction
   * @param vy  new velocity in y direction
   */
  public void setVelocity(int vx, int vy) {
	  velx = vx;
	  vely = vy;
  } // end setVelocity

  /**
   * Returns horizontal velocity
   * @return velx
   */
  public int getHVelocity() {
    return velx;
  } // end getHVelocity

  /**
   * Returns vertical velocity
   * @return vely
   */
  public int getVVelocity() {
    return vely;
  }
  
  /**
   * Returns speed
   * @return speed
   */
  public int getSpeed(){
	  return speed;
  }
  
  /**
   * Sets speed
   * @param i new speed
   */
  public void setSpeed(int i){
	  speed = i;
  }
  
  /**
   * Causes bug to move in a circular pattern of varying sizes
   * <p>
   * modifies:  degrees, velx, vely, whenSwitchedDirections, goingClockwise, increment
   */
  public void circularMovement(){
	  //Very small chance of switching directions or changing increment
	  if(Math.random() < .02){
		  goingClockwise = !goingClockwise;
		  whenSwitchedDirections = timer;			
	  }
	  //Switch directions if you've been going one way for too long
	  if(timer == whenSwitchedDirections + 100){
		  goingClockwise = !goingClockwise;
		  whenSwitchedDirections = timer;
	  }
	  //Counterclockwise
	  if(!goingClockwise){
		  velx = (int)Math.round(((INCREMENTMAX - increment)/((double)INCREMENTMAX)) * speed * Math.cos(Math.toRadians(degrees)));
		  vely = (int)Math.round(((INCREMENTMAX - increment)/((double)INCREMENTMAX)) * speed * Math.sin(Math.toRadians(degrees)));
	  }//Clockwise
	  else{
		  velx = (int)Math.round(((INCREMENTMAX - increment)/((double)INCREMENTMAX)) * speed * Math.sin(Math.toRadians(degrees)));
		  vely = (int)Math.round(((INCREMENTMAX - increment)/((double)INCREMENTMAX)) * speed * Math.cos(Math.toRadians(degrees)));
	  }
	  if(timer%6 == 0){  //Completely stopped
		  if(increment > INCREMENTMAX){ //Increment is getting too large, making circle too small			  
			  //Prevents getting sent towards walls when increment switches back to 0 or 5
			  if(aLabel.getX() > FlyGame.WIDTH/2 && aLabel.getY() > FlyGame.HEIGHT/2){
				  if(velx <= 0 || vely <= 0)
					  increment = (int)Math.round(Math.random() * 5);
			  }		  
			  else if(aLabel.getX() > FlyGame.WIDTH/2 && aLabel.getY() < FlyGame.HEIGHT/2){
				  if(velx <= 0 || vely >= 0)
					  increment = (int)Math.round(Math.random() * 5);
			  }
			  else if(aLabel.getX() < FlyGame.WIDTH/2 && aLabel.getY() > FlyGame.HEIGHT/2){
				  if(velx >= 0 || vely <= 0)
					  increment = (int)Math.round(Math.random() * 5);
			  }
			  else{
				  if(velx >= 0 || vely >= 0)
					  increment = (int)Math.round(Math.random() * 5);
			  }
		  }
		  increment++;  //Decrease the size of the circle
	  }
	  degrees += increment;	  
  }

  /**
   * Handles a single step of animation, prevents moving out of bounds
   * <p>
   * modifies: velx, vely, degrees, goingClockwise, whenSwitchedDirection, aLabel.getLocation()
   */
  public void step() {
	 if(timer == 0){
		 int initialVelX = 0;
		 int initialVelY = 0;
		 if(aLabel.getX() == 0)  //Is on left wall
			 initialVelX = speed;
		 else if(aLabel.getY() == 0)  //Is on top wall
			 initialVelY = speed;
		 else if(aLabel.getX() == FlyGame.WIDTH - aLabel.getWidth()) //Is on right wall
			 initialVelX = -speed;
		 else  //Is on bottom wall
			 initialVelY = -speed;  			
		 setVelocity(initialVelX, initialVelY);
		 try{
			 Thread.currentThread().sleep(50);
		 }catch(Exception e){}
	 }
	 else{
		 int px_post, py_post;
		 if(isAlive()){
			 px_post = aLabel.getX() + velx; 
			 py_post = aLabel.getY() + vely;
		 
			 if(aLabel.getX() + aLabel.getWidth() > FlyGame.WIDTH || aLabel.getX() < 0 ){ // CASE 1
				 velx = -velx;
				 px_post = aLabel.getX() + velx;
				 degrees -= 180;
			 	 if(Math.random() > .5){
			 		goingClockwise = !goingClockwise;
			 		whenSwitchedDirections = timer;
			 	}	 	
			 }
			 else if(aLabel.getX() + aLabel.getWidth() + velx > FlyGame.WIDTH || aLabel.getX() + velx < 0 ){ // CASE 2
				 velx = -velx;
				 px_post = aLabel.getX();
				 degrees -= 180;
				 if(Math.random() > .5){
					 goingClockwise = !goingClockwise;
					 whenSwitchedDirections = timer;
				 }	 	
			 }	 
			 if(aLabel.getY() + aLabel.getHeight() > FlyGame.HEIGHT || aLabel.getY() < 0){ // CASE 1
				 vely = -vely;
				 py_post = aLabel.getY() + vely;
				 degrees -= 180;
				 if(Math.random() > .5){
					 goingClockwise = !goingClockwise;
					 whenSwitchedDirections = timer;
				 }	 	
			 }
			 else if(aLabel.getY() + aLabel.getHeight() + vely > FlyGame.HEIGHT || aLabel.getY() + vely < 0){ // CASE 2
				 vely = -vely;	 		
				 py_post = aLabel.getY();
				 degrees -= 180;
				 if(Math.random() > .5){
					 goingClockwise = !goingClockwise;
					 whenSwitchedDirections = timer;
				 }	 	
			 }
		 }
		 else{  // Death animation
			 velx = 0;
			 vely = 40;
			 px_post = aLabel.getX();
			 py_post = aLabel.getY() + vely;
			 if(py_post > FlyGame.HEIGHT)
				 aLabel.remove();
		 }
		 aLabel.setLocation(px_post, py_post);	
	 }
} // end step
  
  /**
   * Causes death animation to start.  Plays death sound.
   * <p>
   * modifies:  Sets alive to false
   */
  public void kill(){
	  new Thread(new Runnable(){
			public void run(){
				try{ 
					deathSound.play();
				}catch(Exception e){}
			}
	  }).start();
	  setAlive(false);
  }
  
  /**
   * Sets alive state
   * @param a true if alive, false if dead
   */
   public void setAlive(boolean a){
	   alive = a;
   }
   
   /**
    * Returns alive state
    * @return true if alive, false if dead
    */
   public boolean isAlive(){
	   return alive;
   }
  
} // end AnimatedThing
