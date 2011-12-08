/**
 * Overview:  The User class keeps track of player save 
 *            information:  their best level and the health
 *            they had when they entered it.
 *            
 * @author Matthew Crocket 
 */

import java.io.*;

public class User implements Serializable{

	private int health;
	private int maxLevel;	
	
	/**
	 * Initializes User with default values for new games.
	 */
	public User(){
		health = 3;
		maxLevel = 1;
	}
	/**
	 * Initializes User with level and health information.
	 * @param a Health
	 * @param b Max Level
	 */
	public User(int a, int b){
		health = a;
		maxLevel = b;
	}

	/**
	 * Sets health
	 * <p>
	 * modifies:  changes health
	 * <p>
	 * requires:  0 <= a <= 6
	 * @param a health
	 */
	public void setHealth(int a){
		if(a >= 0 && a <= 6)
			health = a;
		else
			System.out.println("Invalid health value.");
	}
	
	/**
	 * Gets health
	 * @return health
	 */
	public int getHealth(){
		return health;
	}
	
	/**
	 * Sets maximum level
	 * <p>
	 * modifies:  changes maxLevel saved
	 * <p>
	 * requires:  0 < a
	 * @param a health
	 */
	public void setMaxLevel(int a){
		if(a > 0)
			maxLevel = a;
		else
			System.out.println("Invalid max level value.");
	}
	
	/**
	 * Gets maximum level
	 * @return maxLevel
	 */
	public int getMaxLevel(){
		return maxLevel;
	}
	
}
