package bugs;

import sound.SoundFXPlayer;
import main.FlyGame;

public abstract class Attacker extends AnimatedLabel{

	protected SoundFXPlayer attackSound;

	public Attacker(FlyGame theGame){
		super(theGame);	
	}	

	public void step(){
		if(timer == -1)
			initialize();
		if(!isAlive())
			deathAnimation();
		else{
			attackerMovement();
			super.step();   	
			animate();
			timer++;    	
		}
	}

	public abstract void attackerMovement();
	
}
