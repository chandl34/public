/**
 * Overview:  Acts as a holder for AnimatedThing objects inside a JLabel
 *            for the purpose of animation by moving JLabels around a
 *            JLayeredPanel.
 *            
 * @author Jonathan Chandler
 * @author James Liu
 */

import javax.swing.*;

public class AnimatedLabel extends JLabel{
	
	private AnimatedThing thing;	
	private FlyGame game;	
	
	/**
	 * Initializes AnimatedLabel with the appropriate type of bug.
	 * @param input Number corresponds to a type of bug.  Found in FlyGame.java as public static final int's. 
	 * @param theGame The game that is currently playing 
	 */
	
	AnimatedLabel(int input, FlyGame theGame){
		super();		
		game = theGame;
		if(input == FlyGame.SMALLFLY)
			thing = new SmallFly(this);
		else if(input == FlyGame.BLUEFLY)
			thing = new BlueFly(this);
		else if(input == FlyGame.BLUESHOT1)
			thing = new BlueShot(FlyGame.BLUESHOT1, this);
		else if(input == FlyGame.BLUESHOT2)
			thing = new BlueShot(FlyGame.BLUESHOT2, this);
		else if(input == FlyGame.BLUESHOT3)
			thing = new BlueShot(FlyGame.BLUESHOT3, this);
		else if(input == FlyGame.BLUESHOT4)
			thing = new BlueShot(FlyGame.BLUESHOT4, this);
		else if(input == FlyGame.WASP)
			thing = new Wasp(this);
		else if(input == FlyGame.GNAT1)
			thing = new Gnat(FlyGame.GNAT1, this);
		else if(input == FlyGame.GNAT2)
			thing = new Gnat(FlyGame.GNAT2, this);
		else if(input == FlyGame.GNAT3)
			thing = new Gnat(FlyGame.GNAT3, this);
    }	
	
	/**
	 * Returns true if this AnimatedLabel contains the Rectangle(x, y, width, height)
	 * <p>
	 * requires: Is only intended for use with the flyswatter and may not work with other Rectangles
	 * @param x Top-left corner of Rectangle
	 * @param y Top-left corner of Rectangle
	 * @param width Width of Rectangle
	 * @param height Height of Rectangle
	 * @return true if flyswatter is over the AnimatedLabel, false if not
	 */
	public boolean hitTest(int x, int y, int width, int height){
		return  ((getX() >= x && getX() <= x + width) &&   // x,y
		  		(getY() >= y && getY() <= y + height)) ||  
		  		((getX() + getWidth() >= x && getX() + getWidth() <= x + width) &&   // x + theWidth, y
		  		(getY() >= y && getY() <= y + height)) ||
		  		((getX() >= x && getX() <= x + width) &&   // x, y + theHeight
		  		(getY() + getHeight() >= y && getY() + getHeight() <= y + height)) ||
		  		((getX() + getWidth() >= x && getLocation().x + getWidth() <= x + width) &&   // x + theWidth, y + theHeight
		  		(getY() + getHeight() >= y && getY() + getHeight() <= y + height)) ||
		  		((getX() + getWidth()/2 >= x && getX() + getWidth()/2 <= x + width) &&  //Test if swatter is in middle
		  		((getY() >= y && getY() <= y + height) || (getY() + getHeight() >= y && 
		  		getY() + getHeight() <= y + height)));
	}
    
	/**
	 * Handles a single step of animation
	 */
    public void step(){    	
    	thing.step();    	
    }
    
    /**
     * Sends location of cursor to AnimatedThing for the purpose of causing damage
     * @param x Top left corner of cursor image
     * @param y Top left corner of cursor image
     */
    public void sendCursorLocation(int x, int y){
    	if(thing.getClass().getName().equals("BlueShot") || thing.getClass().getName().equals("Gnat"))
    		thing.setTargetLocation(x, y);
    }
    
    /**
     * Creates a Gnat
     */
    public void createGnats(){
    	game.createGnats(this);
    }
    
    /**
     * Creates Blue Shots
     */
    public void createBlueShots(){
    	game.createBlueShots(this);
    }
        
    /**
     * Checks if bug is alive
     * @return true if bug is alive, false if not
     */
    public boolean isAlive(){
    	return thing.isAlive();
    }
    
    /**
     * Removes bug from screen
     */
    public void remove(){
    	game.remove(this);
    }
    
    /**
     * Sends request to start bug's kill animation.
     */
    public void kill(){
    	thing.kill();
    }
    
    /**
     * Causes damage to user
     */
    public void causeDamage(){
    	game.takeDamage();
    }
    
}
