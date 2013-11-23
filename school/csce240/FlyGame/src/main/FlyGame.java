package main;

import java.awt.Dimension;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.ArrayList;

import javax.swing.ImageIcon;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;

import sound.MusicPlayer;
import sound.SoundFXPlayer;
import bugs.AnimatedLabel;
import bugs.BlueFly;
import bugs.BlueShot;
import bugs.Gnat;
import bugs.Projectile;
import bugs.SmallFly;
import bugs.Wasp;
import data.Data;
import data.User;

public class FlyGame extends JLayeredPane
implements MouseMotionListener, 
MouseListener{

	//Rainbow cursor icons (for animation) - size() = 6
	private ImageIcon rainbowCursorIcon[] = {
			new ImageIcon("icons/cursors/rainbowcursor/1.GIF"), 
			new ImageIcon("icons/cursors/rainbowcursor/2.GIF"), 
			new ImageIcon("icons/cursors/rainbowcursor/3.GIF"), 
			new ImageIcon("icons/cursors/rainbowcursor/4.GIF"), 
			new ImageIcon("icons/cursors/rainbowcursor/5.GIF"), 
			new ImageIcon("icons/cursors/rainbowcursor/6.GIF") 
	};

	//flySwatter icons (for animation)
	private ImageIcon swatterIcon[] = {
			new ImageIcon("icons/cursors/flyswatter/still.GIF"),
			new ImageIcon("icons/cursors/flyswatter/ani1.GIF"),
			new ImageIcon("icons/cursors/flyswatter/ani3.GIF"),
			new ImageIcon("icons/cursors/flyswatter/ani2scaled(yellow).GIF"),
			new ImageIcon("icons/cursors/flyswatter/ani2scaled(red).GIF")
	};

	//Backgrounds for the three levels
	private ImageIcon backgroundIcon[] = {
			new ImageIcon("icons/backgrounds/title.PNG"),
			new ImageIcon("icons/backgrounds/bg1.PNG"),
			new ImageIcon("icons/backgrounds/bg2.PNG"),
			new ImageIcon("icons/backgrounds/bg1.PNG")
	};

	private ImageIcon hurtHandIcon[] = {
			new ImageIcon("icons/cursors/hurthand/hurt1.GIF"),  // Maintains size with flySwatter
			new ImageIcon("icons/cursors/hurthand/hurt2.GIF"),  // Maintains size with flySwatter
			new ImageIcon("icons/cursors/hurthand/hurt3.GIF")   // 112x176, must be shifted 8 pixels left
	};

	//Image for health
	private ImageIcon healthHandIcon = new ImageIcon("icons/display/hand/lifebar.GIF");

	//Numbers for counter - size() = 10
	private ImageIcon counterIcon[] = {
			new ImageIcon("icons/display/count/zero.GIF"),
			new ImageIcon("icons/display/count/one.GIF"),
			new ImageIcon("icons/display/count/two.GIF"),
			new ImageIcon("icons/display/count/three.GIF"),
			new ImageIcon("icons/display/count/four.GIF"),
			new ImageIcon("icons/display/count/five.GIF"),
			new ImageIcon("icons/display/count/six.GIF"),
			new ImageIcon("icons/display/count/seven.GIF"),
			new ImageIcon("icons/display/count/eight.GIF"),
			new ImageIcon("icons/display/count/nine.GIF")
	};	

	private JLabel counterLabel[] = {// Labels for bug counter
			new JLabel(),
			new JLabel(),
			new JLabel()
	};

	private JLabel backgroundLabel = new JLabel(backgroundIcon[0]);    
	private JLabel menuCursorLabel = new JLabel(rainbowCursorIcon[0]);
	private JLabel gameCursorLabel = new JLabel(swatterIcon[0]);

	//Health hands - size() = 6
	private JLabel healthHandLabel[] = {
			new JLabel(healthHandIcon),
			new JLabel(healthHandIcon),
			new JLabel(healthHandIcon),
			new JLabel(healthHandIcon),
			new JLabel(healthHandIcon),
			new JLabel(healthHandIcon),
	};    

	private MusicPlayer music = new MusicPlayer();
	private SoundFXPlayer attackSound = new SoundFXPlayer("audio/soundFX/miss.mp3");
	private SoundFXPlayer hurtSound = new SoundFXPlayer("audio/soundFX/hurt.mp3");
	private SoundFXPlayer healthSound = new SoundFXPlayer("audio/soundFX/health.mp3");

	//Contains all animated creatures
	private ArrayList<AnimatedLabel> aLabel = new ArrayList<AnimatedLabel>();

	//User - contains user information
	private User user = Data.load();

	private Rectangle hitBox = new Rectangle(0, 0, SWATTERWIDTH, 92);

	//Adjustments to put pointer in middle of cursor
	private static final int XFUDGE = 32, YFUDGE = 80;
	private static final int SWATTERWIDTH = 64, SWATTERHEIGHT = 160; 

	private static Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize(); 
	public static final int WIDTH = 896, HEIGHT = 768; 	

	public static final int SMALLFLY = 0;
	public static final int BLUEFLY = 1;
	public static final int BLUESHOT1 = 2;
	public static final int BLUESHOT2 = 3;
	public static final int BLUESHOT3 = 4;
	public static final int BLUESHOT4 = 5;
	public static final int WASP = 6;
	public static final int GNAT = 7;

	//Game info	
	private int currentLevel = 0;
	private int timer;       // Timer = used to time bug appearances
	private int toBeKilled;  // Bugs to be killed before level is over - should stay at 100
	private int onScreen;    // Number of bugs on screen - is limited by level
	private boolean gameOver;	
	private boolean onTitleScreen = true;
	private boolean ableToAttack = true;

	//Keeps track of Threads to prevent repeats    
	private boolean menuCursorLabelAnimating = false;
	private boolean gameCursorLabelAnimating = false;
	private boolean hurtAnimating = false;

	public FlyGame(){
		setPreferredSize(new Dimension(WIDTH, HEIGHT));
		addMouseMotionListener(this);
		addMouseListener(this);

		//Make the cursor disappear
		setCursor(Toolkit.getDefaultToolkit().createCustomCursor(new ImageIcon("icons/cursors/blank.GIF").getImage(), new Point(16, 16), "Blank"));        

		//Set up menuCursorLabel
		menuCursorLabel.setBounds(WIDTH/2, HEIGHT/2, 32, 32);
		add(menuCursorLabel);

		//Set up gameCursor
		gameCursorLabel.setBounds(WIDTH/2 - XFUDGE, HEIGHT/2 - YFUDGE, SWATTERWIDTH, SWATTERHEIGHT);
		gameCursorLabel.setVisible(false); //Doesn't show up until game starts
		add(gameCursorLabel);

		//Setting up healthHandLabels
		for(int i = 0; i < healthHandLabel.length; i++){
			healthHandLabel[i].setBounds(640 + 64 * (i % 3), 8 + 64 * (i / (healthHandLabel.length / 2)), 48, 52);
			healthHandLabel[i].setVisible(false);
			add(healthHandLabel[i]);
		}

		//Setup counter labels
		for(int i = 0; i < counterLabel.length; i++){
			counterLabel[i].setBounds(320 + 64 * i, 0, 64, 64);
			counterLabel[i].setVisible(false);  
			add(counterLabel[i]);
		}

		//Create the background image
		backgroundLabel.setBounds(0, 0, WIDTH, HEIGHT);   	
		add(backgroundLabel);   

		music.playLevelMusic(0);

	}   

	public void createBug(int bug){
		AnimatedLabel temp = null;
		if(bug == SMALLFLY)
			temp = new SmallFly(this);
		else if(bug == BLUEFLY)
			temp = new BlueFly(this);
		else if(bug == WASP)
			temp = new Wasp(this);
		temp.setVisible(false);
		aLabel.add(temp);  
		sendCursorLocation(temp);  // Tells certain bugs where you are
		add(temp);  
		moveToBack(backgroundLabel);
	}

	public void createGnat(AnimatedLabel label){    	
		AnimatedLabel temp;
		temp = new Gnat(GNAT, this);
		sendCursorLocation(temp);  // Tells certain bugs where you are
		aLabel.add(temp);
		add(temp);
		temp.setLocation(label.getX() + (label.getWidth() - temp.getWidth()) / 2, 
				label.getY() + (label.getHeight() - temp.getHeight()) / 2);    	

		moveToBack(backgroundLabel);
	}

	public void createBlueShots(AnimatedLabel label){    
		AnimatedLabel temp;
		for(int i = 0; i < 4; i++){
			if(i == 0)
				temp = new BlueShot(BLUESHOT1, this);  // TOP LEFT
			else if(i == 1)
				temp = new BlueShot(BLUESHOT2, this);  // TOP RIGHT
			else if(i == 2)
				temp = new BlueShot(BLUESHOT3, this);  // BOTTOM RIGHT
			else
				temp = new BlueShot(BLUESHOT4, this);  // BOTTOM LEFT

			sendCursorLocation(temp);  // Tells certain bugs where you are
			aLabel.add(temp);
			add(temp);
			temp.setLocation(label.getX() + (label.getWidth() - temp.getWidth()) / 2, 
					label.getY() + (label.getHeight() - temp.getHeight()) / 2);    	
		}
		moveToBack(backgroundLabel);
	}

	public void remove(AnimatedLabel label){
		label.setVisible(false);
		super.remove(label);
		aLabel.remove(label);
	}    

	public void clearScreen(){
		gameCursorLabel.setVisible(false);
		for(int i = 0; i < counterLabel.length; i++)
			counterLabel[i].setVisible(false);
		while(aLabel.size() > 0)
			remove(aLabel.get(0)); 
		try{
			Thread.currentThread().sleep(2000);
		}catch(Exception e){}
	}       

	public void takeDamage(){
		if(!hurtAnimating){
			if(user.getHealth() == 0)
				gameOver = true;
			else{
				hurtAnimating = true;
				user.setHealth(user.getHealth() - 1);
				healthHandLabel[user.getHealth()].setVisible(false);
				hurtAnimation();
			}
		}
	}    

	public void gameOver(){ 
		gameOver = false;
		System.out.println("Game Over");    	
		music.stop();
		clearScreen();
		user.setHealth(3);
		playLevel(currentLevel);
	}

	public void playLevel(int level){   //Run the game
		System.out.println("Starting level " + level);
		onTitleScreen = false;		
		toBeKilled = 100;   //Game is intended to be run at 100
		timer = 0;
		onScreen = 0;

		//Updates level information and saves to User
		currentLevel = level;
		if(currentLevel > user.getMaxLevel())
			user.setMaxLevel(currentLevel);
		Data.save(user);

		//Making appropriate adjustments to game screen
		backgroundLabel.setIcon(backgroundIcon[(currentLevel - 1)%3 + 1]);	

		counterLabel[0].setIcon(counterIcon[1]);
		counterLabel[1].setIcon(counterIcon[0]);
		counterLabel[2].setIcon(counterIcon[0]);		

		for(int i = 0; i < counterLabel.length; i++)
			counterLabel[i].setVisible(true);
		for(int i = 0; i < user.getHealth(); i++)   // Adjust health hands accordingly
			healthHandLabel[i].setVisible(true);

		//Switch to game cursor
		menuCursorLabel.setVisible(false);
		gameCursorLabel.setVisible(true);		

		new Thread(new Runnable(){
			public void run(){
				try{  
					Thread.currentThread().sleep(500);
					music.playLevelMusic((currentLevel - 1)%3 + 1);  // First three songs continuously looped
					Thread.currentThread().sleep(2500);
					while(toBeKilled > 0){	//Level is over when all are dead   
						if(gameOver){
							gameOver();
							return;
						}
						if(onScreen < 2 * ((currentLevel - 1)%3 + 1) && timer > 10 && (onScreen%20 != toBeKilled%20 || onScreen == 0)){  //Limits number on screen and when they appear
							onScreen++;
							timer = (int)Math.round(Math.random() * 5);

							if(toBeKilled > 80)
								createBug(SMALLFLY);
							else if(toBeKilled > 60){
								if(Math.random() > .6)
									createBug(SMALLFLY);
								else
									createBug(BLUEFLY);
							}
							else if(toBeKilled > 40){
								if(Math.random() > .6)
									createBug(SMALLFLY);
								else
									createBug(WASP);
							}
							else if(toBeKilled > 20){
								createBug(BLUEFLY);
							}
							else{
								if(Math.random() > .5)
									createBug(WASP);
								else
									createBug(BLUEFLY);
							}													
						}     			
						for(int j = 0; j < aLabel.size(); j++)
							aLabel.get(j).step();        		
						Thread.currentThread().sleep(40);						
						timer++;
					} 
				}catch(Exception exc){}	
				if(!gameOver){
					System.out.println("Level beaten.  Moving to next level.");
					music.stop();				
					clearScreen();
					playLevel(currentLevel + 1);
				}
			}			
		}).start();
	}    

	public void mouseMoved(MouseEvent e) {
		gameCursorLabel.setLocation(e.getX()-XFUDGE, e.getY()-YFUDGE);
		hitBox.setLocation(gameCursorLabel.getLocation());
		menuCursorLabel.setLocation(e.getX(), e.getY());
		for(int i = 0; i < aLabel.size(); i++)
			sendCursorLocation(aLabel.get(i));  // Tells certain bugs where you are
		if(onTitleScreen){ //When game is not running, the cursors are directly on pointer
			//Checks if mouse is over a box
			if((e.getX() >= 55 && e.getX() <= 55 + 54 && e.getY() >= 695 && e.getY() <= 695 + 61) || 
					(e.getX() >= 725 && e.getX() <= 725 + 54 && e.getY() >= 695 && e.getY() <= 695 + 61))
				rainbowCursorAnimation();
			else
				menuCursorLabelAnimating = false;
		}
	}	

	public void mouseDragged(MouseEvent e) {    	
		gameCursorLabel.setLocation(e.getX()-XFUDGE, e.getY()-YFUDGE);
		hitBox.setLocation(gameCursorLabel.getLocation());
		menuCursorLabel.setLocation(e.getX(), e.getY());
		for(int i = 0; i < aLabel.size(); i++)
			sendCursorLocation(aLabel.get(i));  // Tells certain bugs where you are
	}    

	public void mousePressed(MouseEvent e){
		if(onTitleScreen){ //Game is not currently playing
			//Title screen buttons are 54 x 61
			//Mouse is clicking load button - at point (55, 695)
			if(e.getX() >= 55 && e.getX() <= 55 + 54 && e.getY() >= 695 && e.getY() <= 695 + 61){
				System.out.println("Load feature accessed.");
				music.stop();
				playLevel(user.getMaxLevel());
			}
			//Mouse is clicking new game button - at point (725, 695)
			else if(e.getX() >= 725 && e.getX() <= 725 + 54 && e.getY() >= 695 && e.getY() <= 695 + 61){
				music.stop();
				user.setHealth(3);
				playLevel(1);  
			}
		}
		else if(!gameCursorLabelAnimating && ableToAttack && !gameOver)  //Attack sequence
			swatAnimation();
	}    

	public void sendCursorLocation(AnimatedLabel label){
		if(label instanceof Projectile)
			((Projectile)label).sendCursorLocation(gameCursorLabel.getBounds());
	}

	private void rainbowCursorAnimation(){
		//Animates if not already doing so
		if(!menuCursorLabelAnimating){  
			menuCursorLabelAnimating = true;
			new Thread(new Runnable(){
				public void run(){
					try{        					
						while(menuCursorLabelAnimating){
							for(int j = 1; j < 6; j++){
								menuCursorLabel.setIcon(rainbowCursorIcon[j]);
								Thread.currentThread().sleep(50);
							}
							menuCursorLabel.setIcon(rainbowCursorIcon[0]);
						}
					}catch(Exception exc){}
				}
			}).start();
		}
	}

	private void swatAnimation(){  //Also handles hit tests and updating kill information
		gameCursorLabelAnimating = true;
		new Thread(new Runnable(){
			public void run(){
				try{
					boolean hit = false;					
					for(int j = 0; j < 4; j++){
						if(j == 0)
							gameCursorLabel.setIcon(swatterIcon[1]);
						else if(j == 1)
							gameCursorLabel.setIcon(swatterIcon[2]);				
						else if(j == 2){							
							for(int i = 0; i < aLabel.size(); i++){  	//HitBox only contains top 92 pixels
								if(hitBox.intersects(aLabel.get(i).getBounds()) && aLabel.get(i).isAlive()){
									if(!hit){
										hit = true;
										gameCursorLabel.setIcon(swatterIcon[3]);
										gameCursorLabel.setSize(SWATTERWIDTH + 60, SWATTERHEIGHT); //Is more wide and has to be moved over					    				
										gameCursorLabel.setLocation(gameCursorLabel.getX() - 30, gameCursorLabel.getY());
										hitBox.setLocation(gameCursorLabel.getLocation());
									}    									
									toBeKilled--;  //Change counter numbers
									//Remove unwanted numbers first
									if(toBeKilled == 99)
										counterLabel[0].setVisible(false);
									else if(toBeKilled == 9)
										counterLabel[1].setVisible(false);    								
									else if(toBeKilled == 0)
										counterLabel[2].setVisible(false);
									if(toBeKilled%10 == 9)
										counterLabel[1].setIcon(counterIcon[toBeKilled/10]);    								
									counterLabel[2].setIcon(counterIcon[toBeKilled%10]);   								

									onScreen--;  //Allows more bugs to enter
									timer = 0;   //Resets time to create pause between bug appearances
									aLabel.get(i).kill();  //Send kill request for death animation					    			
								}
							}    								
							if(!hit)
								attackSound.play();
						}	
						else if(j == 3 && hit)
							gameCursorLabel.setIcon(swatterIcon[4]);    					
						Thread.currentThread().sleep(50);
					}
					gameCursorLabel.setIcon(swatterIcon[0]);
					gameCursorLabel.setSize(SWATTERWIDTH, SWATTERHEIGHT);
					if(hit){  //Moves back to original position if necessary
						gameCursorLabel.setLocation(gameCursorLabel.getX() + 30, gameCursorLabel.getY());
						hitBox.setLocation(gameCursorLabel.getLocation());
					}
					gameCursorLabelAnimating = false;
				}catch(Exception exc){}
			}
		}).start();   //End of main Thread
	}

	private void hurtAnimation(){
		new Thread(new Runnable(){
			public void run(){
				try{ 
					ableToAttack = false;
					hurtSound.play();
					for(int i = 0; i < 2; i++){
						gameCursorLabel.setIcon(hurtHandIcon[i]);
						Thread.currentThread().sleep(125);
					}
					gameCursorLabel.setIcon(hurtHandIcon[2]);
					gameCursorLabel.setBounds(gameCursorLabel.getX() - 8, gameCursorLabel.getY(), 112, 176);
					Thread.currentThread().sleep(1000);
					gameCursorLabel.setBounds(gameCursorLabel.getX() + 8, gameCursorLabel.getY(), SWATTERWIDTH, SWATTERHEIGHT);
					for(int i = 1; i >= 0; i--){
						gameCursorLabel.setIcon(hurtHandIcon[i]);
						Thread.currentThread().sleep(125);
					}	
					gameCursorLabel.setIcon(swatterIcon[0]);
					ableToAttack = true;
					for(int i = 0; i < 70; i++){
						if(i%2 == 0)
							gameCursorLabel.setVisible(false);
						else
							gameCursorLabel.setVisible(true);
						Thread.currentThread().sleep(50);
					}    					
					hurtAnimating = false;
				}catch(Exception e){}
			}			
		}).start();
	}

	/**
	 * Create the GUI and show it.  For thread safety,
	 * this method should be invoked from the
	 * event-dispatching thread.
	 */
	private static void createAndShowGUI() {
		//Create and set up the window.
		JFrame frame = new JFrame("Mario Paint?");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  
		frame.setResizable(false);
		frame.setAlwaysOnTop(true);   

		//Create and set up the content pane.
		JComponent newContentPane = new FlyGame();
		newContentPane.setOpaque(true); //content panes must be opaque
		frame.setContentPane(newContentPane);

		//Display the window.
		frame.pack();
		frame.setVisible(true);        
	}

	public static void main(String[] args) {
		//Schedule a job for the event-dispatching thread:
		//creating and showing this application's GUI.
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {  
				createAndShowGUI();
			}
		});
	}	

	public void mouseReleased(MouseEvent e){}
	public void mouseClicked(MouseEvent e){}
	public void mouseEntered(MouseEvent e){}
	public void mouseExited(MouseEvent e){}

}