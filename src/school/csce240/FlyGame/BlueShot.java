/**
 * Overview:  BlueShot object
 * 
 * @author James Liu
 */
import javax.swing.ImageIcon;

public class BlueShot extends AnimatedThing {

	private ImageIcon icon[] = {
		new ImageIcon("icons/monsters/BlueShot/fireball1.GIF"),
		new ImageIcon("icons/monsters/BlueShot/fireball2.GIF"),
		new ImageIcon("icons/monsters/BlueShot/fireball3.GIF")
	};
	
	/**
	 * Creates BlueShot
	 * @param shotDir Determines direction of shot
	 * @param label AnimatedLabel this blue shot is connected to
	 */
    public BlueShot(int shotDir, AnimatedLabel label) {
    	super(label);  
    	setAlive(false); // Set to dead so they cannot be hit
    	setSpeed(15);
    	if(shotDir == FlyGame.BLUESHOT1)  // TOP LEFT
    		setVelocity(-getSpeed(), -getSpeed());
    	else if(shotDir == FlyGame.BLUESHOT2)  // TOP RIGHT
    		setVelocity(getSpeed(), -getSpeed());
    	else if(shotDir == FlyGame.BLUESHOT3)  // BOTTOM RIGHT
    		setVelocity(getSpeed(), getSpeed());
    	else  // BOTTOM LEFT
    		setVelocity(-getSpeed(), getSpeed());
		aLabel.setIcon(icon[2]);
		aLabel.setSize(32, 32);
    }
    
    /**
     * Causes one step of animation, changes icons depending time
     */
    public void step(){
    	int px_post = aLabel.getX() + getHVelocity();
    	int py_post = aLabel.getY() + getVVelocity();
    	if(px_post < 0 || px_post + aLabel.getWidth() > FlyGame.WIDTH || py_post < 0 || py_post + aLabel.getHeight() > FlyGame.HEIGHT)
    		aLabel.remove();
    	aLabel.setLocation(px_post, py_post);
    	if(aLabel.hitTest(targetX, targetY, FlyGame.SWATTERWIDTH, FlyGame.SWATTERHEIGHT))  //Checks if the cursor is being touched by this
    		aLabel.causeDamage();
    	//Animation
    	aLabel.setIcon(icon[timer%3]);
    		
    	timer++;
    } 
    
}
