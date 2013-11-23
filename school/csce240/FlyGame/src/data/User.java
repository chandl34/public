package data;

import java.io.Serializable;

public class User implements Serializable{

	private int health;
	private int maxLevel;	

	public User(){
		health = 3;
		maxLevel = 1;
	}

	public User(int a, int b){
		health = a;
		maxLevel = b;
	}

	public void setHealth(int a){
		if(a >= 0 && a <= 6)
			health = a;
		else
			System.out.println("Invalid health value.");
	}

	public int getHealth(){
		return health;
	}

	public void setMaxLevel(int a){
		if(a > 0)
			maxLevel = a;
		else
			System.out.println("Invalid max level value.");
	}

	public int getMaxLevel(){
		return maxLevel;
	}

}
