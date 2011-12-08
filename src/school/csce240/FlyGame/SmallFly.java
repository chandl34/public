/**
 * Overview:  Handles the animation and behavior of SmallFlies
 * 
 * @author Jonathan Chandler
 */

import javax.swing.ImageIcon;

public class SmallFly extends AnimatedThing {

	private ImageIcon icon[] = {
		new ImageIcon("icons/monsters/SmallFly/ani1.GIF"),  // 52 x 32
		new ImageIcon("icons/monsters/SmallFly/ani2.GIF") 	// 52 x 32	
	};
	
	/**
	 * Initializes a SmallFly to be part of label
	 * @param label Animated label that this SmallFly belongs to
	 */
    public SmallFly(AnimatedLabel label) {
    	super(label);
    	setSpeed(50);
		aLabel.setIcon(icon[1]);
		aLabel.setSize(52, 32);
		deathSound = new Sound("sounds/smallFlyDeath.wav");
    }
    
    /**
     * Animates the movement of a SmallFly
     * modifies:  timer is increased to allow different activity
     *            at different times in the animation.  Icon changes
     *            to represent animation.
     */
    public void step(){
    	circularMovement();
    	super.step();
    	
    	//Animation
    	if(isAlive()){
    		aLabel.setIcon(icon[timer%2]);
    		timer++;
   	 	}
    } 

} // end SmallFly
