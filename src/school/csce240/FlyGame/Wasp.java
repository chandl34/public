/**
 * Wasp object
 * 
 * @author James Liu
 */

import javax.swing.ImageIcon;

public class Wasp extends AnimatedThing{

	private ImageIcon icon[] = {
			new ImageIcon("icons/monsters/Wasp/normal1.GIF"),  // 96 x 64
			new ImageIcon("icons/monsters/Wasp/normal2.GIF")
	};
	
	private boolean attackAnimating = false;
		
	/**
	 * Initializes Wasp
	 * @param label AnimatedLabel this Wasp is connected to
	 */
    public Wasp(AnimatedLabel label) {
    	super(label);
    	setSpeed(35);
		aLabel.setIcon(icon[1]);
		aLabel.setSize(96, 64);		
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
    				aLabel.createGnats();
    			}
    		}
    		//Animation    	
    		//if(!attackAnimating){ // Normal animation
    			aLabel.setIcon(icon[timer%2]);
    		//}
    		//else{
    		//	if(timer%2 == 0)
    		//		aLabel.setIcon(img3);
    		//	else
    		//		aLabel.setIcon(img4); 
    		//}
    		timer++;    		
   	 	}
    } 
}
