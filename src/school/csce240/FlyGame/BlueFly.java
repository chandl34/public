/**
 * Overview:  BlueFly bug
 * 
 * @author Jonathan Chandler
 * @author James Liu
 */

import javax.swing.ImageIcon;

public class BlueFly extends AnimatedThing{
	
	private ImageIcon icon[] = {
		new ImageIcon("icons/monsters/BlueFly/ani1.GIF"),  // 64 x 60
		new ImageIcon("icons/monsters/BlueFly/ani2.GIF"),	
		new ImageIcon("icons/monsters/BlueFly/attack1.GIF"),
		new ImageIcon("icons/monsters/BlueFly/attack2.GIF")
	};
	
	private boolean attackAnimating = false;
		
	/**
	 * Creates BlueFly
	 * @param label AnimatedLabel this blue fly is connected to
	 */
    public BlueFly(AnimatedLabel label) {
    	super(label);
    	setSpeed(35);
		aLabel.setIcon(icon[2]);
		aLabel.setSize(64, 60);
		deathSound = new Sound("sounds/blueFlyDeath.wav");
    }
    
    /**
     * Causes one step of animation, changes icons depending time
     */
    public void step(){
    	circularMovement();  
    	super.step();
    	if(isAlive()){
    		if(timer%6 == 0){  // HAS TO KEEP SAME MODULUS AS ANIMATED THING'S STEP()
    			if(Math.random() < .05 && !attackAnimating){
    				increment = INCREMENTMAX - 4;
    			}
    			if(increment + 3 == INCREMENTMAX)  // Fly is coming to a stop here
    				attackAnimating = true;                      // Extra conditions added to prevent
                                                                 // fly from appearing flashing    		
    			if(increment == INCREMENTMAX){ // Conditions taken from AnimatedThing for when completely stopped
    				attackAnimating = false;
    				aLabel.createBlueShots();
    			}
    		}
    		//Animation    	
    		if(!attackAnimating) // Normal animation
    			aLabel.setIcon(icon[timer%2]);
    		else
    			aLabel.setIcon(icon[timer%2 + 2]);
    		timer++;    		
   	 	}
    } 
}
