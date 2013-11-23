package bugs;

import javax.swing.ImageIcon;

import sound.SoundFXPlayer;

import main.FlyGame;

public class BlueFly extends Attacker{

	private ImageIcon icon[] = {
			new ImageIcon("icons/monsters/BlueFly/ani1.GIF"),  // 64 x 60
			new ImageIcon("icons/monsters/BlueFly/ani2.GIF"),	
			new ImageIcon("icons/monsters/BlueFly/attack1.GIF"),
			new ImageIcon("icons/monsters/BlueFly/attack2.GIF")
	};

	public BlueFly(FlyGame theGame){
		super(theGame);
		setSpeed(30);
		setIcon(icon[2]);
		setSize(64, 60);
		movesInCircles = true;
		attackSound = new SoundFXPlayer("audio/soundFX/blueFlyAttack.mp3");
		deathSound = new SoundFXPlayer("audio/soundFX/blueFlyDeath.mp3");
		fallSound = new SoundFXPlayer("audio/soundFX/blueFlyFall.mp3");
	}

	public void animate(){
		if(!attackAnimating) // Normal animation
			setIcon(icon[timer%2]);
		else
			setIcon(icon[timer%2 + 2]);
	}	

	public void attackerMovement(){
		if(timer >= 10){			
			if(!stopping && !stopped && Math.random() < .01){  // Gives an additional chance of stopping (so a shot may be taken)
				stopping = true;
				//System.out.println("STOPPING - BlueFly - " + timer);
			}
			if(timer%6 == 0){
				if(!attackAnimating){
					if(stopping){
						radius -= 5;   // Gives an additional reduction to radius for a quick stop
						if(radius <= 0){
							attackAnimating = true;
							radius = 0;
							stopping = false;
							stopped = true;
							lastStop = timer;
							//System.out.println("STOPPED - BlueFly - " + timer);
						}
					}
					else if(starting)  // Gives an additional boost to radius
						radius++;
				}
				else{
					if(lastStop == timer - 24){
						attackSound.play();                                             
						game.createBlueShots(this);				
					}	
					else if(lastStop == timer - 30)
						attackAnimating = false;
				}
			}
			circularMovement();
		}
	}
}