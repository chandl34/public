package bugs;

import javax.swing.ImageIcon;

import sound.SoundFXPlayer;

import main.FlyGame;

public class SmallFly extends AnimatedLabel{

	private ImageIcon icon[] = {
			new ImageIcon("icons/monsters/SmallFly/ani1.GIF"),  // 52 x 32
			new ImageIcon("icons/monsters/SmallFly/ani2.GIF") 	// 52 x 32	
	};

	public SmallFly(FlyGame theGame){
		super(theGame);
		setSpeed(30);
		setIcon(icon[1]);
		setSize(52, 32);
		movesInCircles = true;
		deathSound = new SoundFXPlayer("audio/soundFX/smallFlyDeath.mp3");
		fallSound = new SoundFXPlayer("audio/soundFX/smallFlyFall.mp3");
	}

	public void step(){
		if(timer == -1)
			initialize();
		if(!isAlive())
			deathAnimation();
		else{
			if(timer >= 10)
				circularMovement();
			super.step();
			animate();
			timer++;
		}
	}
	
	public void animate(){
		setIcon(icon[timer%2]);
	}

}
