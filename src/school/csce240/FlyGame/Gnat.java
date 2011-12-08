/**
 * Gnat object
 * 
 * @author James Liu
 */

import javax.swing.ImageIcon;

public class Gnat extends AnimatedThing {

	private ImageIcon icon[] = {
			new ImageIcon("icons/monsters/Gnat/gnat1.GIF"),  // 28 x 20
			new ImageIcon("icons/monsters/Gnat/gnat2.GIF"),	
			new ImageIcon("icons/monsters/Gnat/gnat3.GIF")
	};
	private int compass = 0;
	private int startStep = 0;
	
	/**
	 * Initializes Gnat
	 * @param gnatIniStep Determines Gnats initial movement
	 * @param label AnimatedLabel this Gnat is connected to
	 */
	public Gnat(int gnatIniStep, AnimatedLabel label) {
    	super(label);  
    	setAlive(false); // Set to dead so they cannot be hit
    	setSpeed(25);
    	aLabel.setIcon(icon[2]);
		aLabel.setSize(28, 20);
		startStep = gnatIniStep;
	}
    
	/**
     * Causes one step of animation, changes icons depending time
     */
    public void step(){

    	int px_post = aLabel.getX() + getHVelocity();
    	int py_post = aLabel.getY() + getVVelocity();
    	
    	if(timer < 23)
    	{
    		py_post = py_post+3;
    	}
    	else if(timer < 43)
    	{
    		if(startStep == FlyGame.GNAT1)
    		{    			
    			py_post = py_post+3;
    		}
    		else if(startStep == FlyGame.GNAT2)
    		{    			
    			px_post = px_post+4;
    			py_post = py_post+1;
    		}
    		else
    		{    			
    			px_post = px_post-4;
    			py_post = py_post+1;
    		}
    	}
    	
    	else if(timer < 70){
    		
    		
    		if(0 > targetX - px_post && 0 > targetY - py_post)
    		{
    			px_post = px_post - getSpeed();
    			py_post = py_post - getSpeed();
    			compass = 1;
    		}
    		else if(0 == targetX - px_post && 0 > targetY - py_post)
    		{
    			py_post = py_post - getSpeed();
    			compass = 2;
    		}
    		else if(0 < targetX - px_post && 0 > targetY - py_post)
    		{
    			px_post = px_post + getSpeed();
    			py_post = py_post - getSpeed();
    			compass = 3;
    		}
    		else if(0 < targetX - px_post && 0 == targetY - py_post)
    		{
    			px_post = px_post + getSpeed();
    			compass = 4;
    		}
    		else if(0 < targetX - px_post && 0 < targetY - py_post)
    		{
    			px_post = px_post + getSpeed();
    			py_post = py_post + getSpeed();
    			compass = 5;
    		}
    		else if(0 == targetX - px_post && 0 < targetY - py_post)
    		{
    			py_post = py_post + getSpeed();
    			compass = 6;
    		}
    		else if(0 > targetX - px_post && 0 < targetY - py_post)
    		{
    			px_post = px_post - getSpeed();
    			py_post = py_post + getSpeed();
    			compass = 7;
    		}
    		else
    		{
    			px_post = px_post - getSpeed();
    			compass = 8;
    		}
    	}
    	else{
    		
    		if(compass == 1){
    			px_post = px_post - getSpeed() - 10;
    			py_post = py_post - getSpeed() - 10;
    		}
    		else if(compass == 2){
    			py_post = py_post - getSpeed() - 10;
    		}
    		else if(compass == 3){
    			px_post = px_post + getSpeed() + 10;
    			py_post = py_post - getSpeed() - 10;
    		}
    		else if(compass == 4){
    			py_post = px_post + getSpeed() + 10;
    		}
    		else if(compass == 5){
    			px_post = px_post + getSpeed() + 10;
    			py_post = py_post + getSpeed() + 10;
    		}
    		else if(compass == 6){
    			py_post = py_post + getSpeed() + 10;
    		}
    		else if(compass == 7){
    			px_post = px_post - getSpeed() - 10;
    			py_post = py_post + getSpeed() + 10;
    		}
    		else{
    			py_post = px_post - getSpeed() - 10;
    		}
    	}
    	
    	if(px_post < 0 || px_post + aLabel.getWidth() > FlyGame.WIDTH || py_post < 0 || py_post + aLabel.getHeight() > FlyGame.HEIGHT)
    		aLabel.remove();
    	aLabel.setLocation(px_post, py_post);
    	if(aLabel.hitTest(targetX, targetY, FlyGame.SWATTERWIDTH, FlyGame.SWATTERHEIGHT))  //Checks if the cursor is being touched by this
    		{
    			aLabel.causeDamage();
    			//aLabel.remove();
    		}
    	//Animation
    	if(timer%4 == 0)
    		aLabel.setIcon(icon[1]);
    	else if(timer%4 == 1)
    		aLabel.setIcon(icon[0]);		
    	else if(timer%4 == 2)
    		aLabel.setIcon(icon[1]);
    	else
    		aLabel.setIcon(icon[2]);
    		
    	timer++;
    } 

}
