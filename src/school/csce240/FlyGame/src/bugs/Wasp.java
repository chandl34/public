package bugs;

import javax.swing.ImageIcon;

import sound.SoundFXPlayer;

import main.FlyGame;

public class Wasp extends Attacker{

	private ImageIcon icon[] = {
			new ImageIcon("icons/monsters/Wasp/normal1.GIF"),  // 96 x 64
			new ImageIcon("icons/monsters/Wasp/normal2.GIF"),	
			new ImageIcon("icons/monsters/BlueFly/attack1.GIF"),
			new ImageIcon("icons/monsters/BlueFly/attack2.GIF")
	};

	public Wasp(FlyGame theGame){
		super(theGame);
		setSpeed(20);
		setIcon(icon[1]);
		setSize(96, 64);	
		movesInCircles = false;		
		attackSound = new SoundFXPlayer("audio/soundFX/waspAttack.mp3");
		deathSound = new SoundFXPlayer("audio/soundFX/waspDeath.mp3");
		fallSound = new SoundFXPlayer("audio/soundFX/waspFall.mp3");
	}

	public void animate(){
		if(!attackAnimating) // Normal animation
			setIcon(icon[timer%2]);
		else
			setIcon(icon[timer%2 + 2]);
	}

	public void attackerMovement(){
		if(timer%3 == 0){
			if(attackAnimating){
				if(lastStop == timer - 24){ 		
					attackSound.play();                                                                     
					game.createGnat(this);						    			
				}			
				else if(lastStop == timer - 27) 	                                             
					game.createGnat(this);		
				else if(lastStop == timer - 30)                                              
					game.createGnat(this);			
				else if(lastStop == timer - 33){
					attackAnimating = false;
					stopped = false;
					starting = true; 
					//System.out.println("STARTING");
				}
			}
			else if(stopped){  //Start attacking when stopped
				attackAnimating = true;
				//System.out.println("BEGINNING ATTACK");
			}
		}
		horizontalMovement();
	}

	public void initialize(){ //Specialized initialization for wasps
		timer = 0;
		lastStop = 0;
		speedReduction = 0;
		setAlive(true);
		starting = false;
		stopping = true;
		stopped = false;
		attackAnimating = false;

		//Randomizing starting location
		int x, y = (int)Math.round(Math.random()*(FlyGame.HEIGHT - getHeight()) * 2 / 3 + FlyGame.HEIGHT / 6);
		if(Math.random() > .5){
			setVelocity(getSpeed(), 0);
			x = 0;
		}
		else{
			x = FlyGame.WIDTH - getWidth();
			setVelocity(-getSpeed(), 0);		
		}
		setLocation(x, y);
		setVisible(true);
	}

}
