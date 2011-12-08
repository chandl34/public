/**
 * Overview:  This program attempts to recreate the 
 * 			  flyswatting game from Mario Paint. 
 *            Users play by clicking their mouse on
 *            flies to swat them, while trying not to
 *            get killed by fireballs.  Every 100 kills
 *            leads to a new level, where two more
 *            flies will show up at a time.
 * 
 * @author Jonathan Chandler
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class FlyGame extends JPanel
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
    
	private JLayeredPane layeredPane;
	
	//Sound effects
	private Sound swatSound = new Sound("sounds/swat.wav");
	private Sound blueShotSound = new Sound("sounds/blueshot.wav");
	
	//Level start sound
	private Sound startSound[] = {
			new Sound("sounds/lvl1start.wav"),
			new Sound("sounds/start2.wav"), //FIX LATER
			new Sound("sounds/lvl1start.wav")  //FIX LATER
	};
	
	//Music
	private Sound music[] = {
		new Sound("music/titlebg.wav"),
		new Sound("music/lvl1music.wav"),
		new Sound("music/2ndsong.wav"),
		new Sound("music/lvl1music.wav") // FIX LATER
	};
	private Sound lvl2IntroSound = new Sound("sounds/2ndintro.wav");
	private Sound currentMusic;
	
	//Contains all animated creatures
	private ArrayList<AnimatedLabel> aLabel = new ArrayList<AnimatedLabel>();
    
	//User - contains user information
	private User user = Data.load();
	
	//Adjustments to put pointer in middle of cursor
    private static final int XFUDGE = 32 ;
	//Adjustments to put pointer in middle of cursor
    private static final int YFUDGE = 80 ;
    
    /**
     * Width of the flyswatter.
     */
    public static final int SWATTERWIDTH = 64;   //Size of flySwatter, used very often
    
    /**
     * Height of flyswatter.
     */
    public static final int SWATTERHEIGHT = 160; 
    
    /**
     * Width of the window.
     */
    public static final int WIDTH = 896;
    
    /**
     * Height of the window.
     */
    public static final int HEIGHT = 768; 
    
    /**
     * int value used to create SmallFly in createBug(int) method
     */
    public static final int SMALLFLY = 0;
    
    /**
     * int value used to create BlueFly in createBug(int) method
     */
    public static final int BLUEFLY = 1;
    
    /**
     * int value used to create top-left BlueShot in createBug(int) method
     */
    public static final int BLUESHOT1 = 2;
    
    /**
     * int value used to create top-right BlueShot in createBug(int) method
     */
    public static final int BLUESHOT2 = 3;
    
    /**
     * int value used to create bottom-right BlueShot in createBug(int) method
     */
    public static final int BLUESHOT3 = 4;
    
    /**
     * int value used to create bottom-left BlueShot in createBug(int) method
     */
    public static final int BLUESHOT4 = 5;
	
    /**
     * int value used to create Wasp in createBug(int) method
     */
    public static final int WASP = 6;
    
    /**
     * int value used to create a Gnat in createBug(int) method
     */
    public static final int GNAT1 = 7;
    
    /**
     * int value used to create a Gnat in createBug(int) method
     */
    public static final int GNAT2 = 8;
    
    /**
     * int value used to create a Gnat in createBug(int) method
     */
    public static final int GNAT3 = 9;
    
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
    private boolean damageAnimating = false;
    private boolean musicPlaying = false;
    
   /**
    * Creates JPanel for FlyGame's title screen.  Plays opening music.  
    */ 
    public FlyGame(){    	
    	setPreferredSize(new Dimension(WIDTH, HEIGHT)); //New Dimension made to fix screen size
        setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
        
        //Create and set up the layered pane.
        layeredPane = new JLayeredPane();
        layeredPane.addMouseMotionListener(this);
        layeredPane.addMouseListener(this);

        //Make the cursor disappear
        setCursor(Toolkit.getDefaultToolkit().createCustomCursor(new ImageIcon("icons/cursors/blank.GIF").getImage(), new Point(16, 16), "Blank"));        
        
        //Set up menuCursorLabel
        menuCursorLabel.setBounds(WIDTH/2, HEIGHT/2, 32, 32);
        layeredPane.add(menuCursorLabel);
        
        //Set up gameCursor
        gameCursorLabel.setBounds(WIDTH/2 - XFUDGE, HEIGHT/2 - YFUDGE, SWATTERWIDTH, SWATTERHEIGHT);
        gameCursorLabel.setVisible(false); //Doesn't show up until game starts
        layeredPane.add(gameCursorLabel);
        
        //Setting up healthHandLabels
        for(int i = 0; i < healthHandLabel.length; i++){
        	healthHandLabel[i].setBounds(640 + 64 * (i % 3), 8 + 64 * (i / (healthHandLabel.length / 2)), 48, 52);
        	healthHandLabel[i].setVisible(false);
        	layeredPane.add(healthHandLabel[i]);
        }
       
        //Setup counter labels
        for(int i = 0; i < counterLabel.length; i++){
        	counterLabel[i].setBounds(320 + 64 * i, 0, 64, 64);
        	counterLabel[i].setVisible(false);  
        	layeredPane.add(counterLabel[i]);
        }
                
        //Create the background image
        backgroundLabel.setBounds(0, 0, WIDTH, HEIGHT);   	
        layeredPane.add(backgroundLabel);         
        
        add(layeredPane); 
        
        playMusic();  //Start the title music
    }   
    
    /**
     * Creates a bug at a random location on the wall.
     * <p>
     * modifies:  The bug is added to aLabel and layeredPane.
     * <p>
     * requires:  Bugs will only be created with valid int values.  
     *            Use the provided static final int to make bugs.
     *            Game must be playing for the bugs to be created.
     * @param bug Bug you want to create
     */   
    public void createBug(int bug){  
    	if(bug < SMALLFLY || bug > GNAT3){
    		System.out.println("ERROR - Invalid bug type.  Did not create bug.");
    		return;
    	}
    	if(!onTitleScreen && !gameOver){
    		int x, y;        	
    		AnimatedLabel temp = new AnimatedLabel(bug, this);
    		aLabel.add(temp);  
    	
    		//Randomizing start location
    		double random = Math.random();
    		if(random < .5){    		
    			x = (int)Math.round(Math.random()*(WIDTH - temp.getWidth()));    		
    			if(random > .25)
    				y = 0;
    			else
    				y = HEIGHT - temp.getHeight();
    		}
    		else{
    			y = (int)Math.round(Math.random()*(HEIGHT - temp.getHeight()));
    			if(random > .75)
    				x = 0;
    			else
    				x = WIDTH - temp.getWidth();
    		}    	
    		temp.setLocation(x, y);
    		temp.sendCursorLocation(gameCursorLabel.getX(), gameCursorLabel.getY());  // Tells certain bugs where you are
    		layeredPane.add(temp);  
    		layeredPane.moveToBack(backgroundLabel);
    	}
    }
    
    /**
     * Creates a Gnat below the label
     * <p>
     * modifies:  The Gnats are created inside an AnimatedLabel which 
     *            is added to ArrayList aLabel and JLayeredPanel 
     *            layeredPane.  Cursor location is sent to the AnimatedLabel
     *            which passes it to the AnimatedThing, so that it can hurt
     *            the player.
     * <p>
     * requires:  Game must be playing for the bugs to be created.
     * 			  label must not be null.
     * @param label AnimatedLabel that is creating the wasps
     */
    public void createGnats(AnimatedLabel label){
    	if(label == null){
    		System.out.println("Cannot create BlueShots.  Sender is null.");
    		return;
    	}
    	else if(onTitleScreen || gameOver){
    		System.out.println("BlueShot cannot be made when game is not playing.");
    		return;
    	}
    	AnimatedLabel temp;
    		for(int i = 1; i < 4; i++){
        		if(i == 1)
        			temp = new AnimatedLabel(GNAT1, this);   
        		else if(i == 2)
        			temp = new AnimatedLabel(GNAT2, this);   
        		else
        			temp = new AnimatedLabel(GNAT3, this);     
    		
    		
    		temp.sendCursorLocation(gameCursorLabel.getX(), gameCursorLabel.getY());  // Tells certain bugs where you are
    		aLabel.add(temp);
    		layeredPane.add(temp);
    		temp.setLocation(label.getX() + (label.getWidth() - temp.getWidth()) / 2, 
    				label.getY() + (label.getHeight() - temp.getHeight()) / 2);    	
    	}
    	layeredPane.moveToBack(backgroundLabel);
    }
    
    /**
     * Creates BlueShots that can hurt the player.  Plays BlueShot sound.
     * <p>
     * modifies:  The shots are created inside an AnimatedLabel which 
     *            is added to ArrayList aLabel and JLayeredPanel 
     *            layeredPane.  Cursor location is sent to the AnimatedLabel
     *            which passes it to the AnimatedThing, so that it can hurt
     *            the player.
     * <p>
     * requires:  Game must be playing for the bugs to be created.
     * 			  label must not be null.
     * @param label AnimatedLabel where BlueShot is created
     */    
    public void createBlueShots(AnimatedLabel label){     	
    	if(label == null){
    		System.out.println("Cannot create BlueShots.  Sender is null.");
    		return;
    	}
    	else if(onTitleScreen || gameOver){
    		System.out.println("BlueShot cannot be made when game is not playing.");
    		return;
    	}
    	AnimatedLabel temp;
    	for(int i = 0; i < 4; i++){
    		if(i == 0)
    			temp = new AnimatedLabel(BLUESHOT1, this);  // TOP LEFT
    		else if(i == 1)
    			temp = new AnimatedLabel(BLUESHOT2, this);  // TOP RIGHT
    		else if(i == 2)
    			temp = new AnimatedLabel(BLUESHOT3, this);  // BOTTOM RIGHT
    		else
    			temp = new AnimatedLabel(BLUESHOT4, this);  // BOTTOM LEFT
    		
    		temp.sendCursorLocation(gameCursorLabel.getX(), gameCursorLabel.getY());  // Tells certain bugs where you are
    		aLabel.add(temp);
    		layeredPane.add(temp);
    		temp.setLocation(label.getX() + (label.getWidth() - temp.getWidth()) / 2, 
    				label.getY() + (label.getHeight() - temp.getHeight()) / 2);    	
    	}
    	layeredPane.moveToBack(backgroundLabel);
    	new Thread(new Runnable(){
			public void run(){
				try{ 
					blueShotSound.play();
				}catch(Exception e){}
			}
    	}).start();
    }
    
    /**
     * Removes an AnimatedLabel from the game.
     * <p>
     * modifies:  label is removed from layeredPane and aLabel
     * <p>
     * requires:  label != null
     * @param label AnimatedLabel you want to remove from play
     */
    public void remove(AnimatedLabel label){
    	if(label == null)
    		System.out.println("Could not remove AnimatedLabel.  label is null");
    	else{
    		label.setVisible(false);
    		layeredPane.remove(label);
    		aLabel.remove(label);
    	}
    }    
    
    /**
     * Removes all AnimatedLabels from the game.
     * <p>
     * modifies:  aLabel is emptied and all of its
     *            contents are removed from layeredPane
     * <p>
     * requires:  nothing
     */
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
    
    /**
     * Causes the user to take damage.  Will set gameOver if user dies.  
     * Animates the process and disallows swatting for a few seconds.
     * <p>
     * modifies:  Subtracts from user.getHealth().  Can set gameOver state.
     *            Temporarily changes ableToAttack and the damageAnimating
     *            state.  gameCursorLabel is changed to show animation.
     * <p>
     * requires:  User cannot be in damageAnimating state, meaning you are       
     *            temporarily invulnerable after taking a hit.
     *            Game must be currently playing for this to work.
     */    
    public void takeDamage(){
    	if(onTitleScreen || gameOver)
    		System.out.println("Cannot take damage when game is not playing.");
    	else if(!damageAnimating){
    		if(user.getHealth() == 0)
    			gameOver = true;
    		else{
    			damageAnimating = true;
    			user.setHealth(user.getHealth() - 1);
    			healthHandLabel[user.getHealth()].setVisible(false);
    			new Thread(new Runnable(){
    				public void run(){
    					try{ 
    						ableToAttack = false;
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
    						damageAnimating = false;
    					}catch(Exception e){}
    				}			
    			}).start();
    		}
    	}
    }    

    /**
     * Restarts the current level
     * <p>
     * modifies:  Calls stopMusic() and clearScreen().
     *            Resets user health to 3, then restarts level.
     * <p>           
     * requires:  gameOver state must be set and cannot be on title screen
     */    
    public void gameOver(){ 
    	if(!gameOver || onTitleScreen){
    		System.out.println("Game is not over.");
    		return;
    	}    		
    	gameOver = false;
    	System.out.println("Game Over");    	
    	stopMusic();
    	clearScreen();
    	user.setHealth(3);
    	playLevel(currentLevel);
    }
 
    /**
     * Plays the music for your current level.
     * <p>
     * modifies:  currentMusic is set to currently playing
     *            music.  musicPlaying state is set to true
     * <p>           
     * requires:  nothing
     */    
    public void playMusic(){  
    	if(musicPlaying){
    		System.out.println("ERROR - Music had to be stopped first.  Trying again.");
    		stopMusic();
    		playMusic();
    	}
    	else{
    		System.out.println("Preparing to play level " + ((currentLevel - 1)%3 + 1) + " music");
    		if(currentLevel != 0){
    			currentMusic = startSound[(currentLevel - 1)%3];
    			currentMusic.play();  // Play start music  
    			System.out.println("Playing start music");
    			try{
    				Thread.currentThread().sleep(500);
    			}catch(Exception e){}
    		}
			musicPlaying = true;
    		new Thread(new Runnable(){
    			public void run(){  
    				try{  
    					if(currentLevel == 2 && musicPlaying){
    						currentMusic = lvl2IntroSound;
    						currentMusic.play();
    					}
    		    		currentMusic = music[(currentLevel - 1)%3 + 1];   
    					while(musicPlaying)
    						currentMusic.play();
    					System.out.println("Music did not continue its loop.");
    				}catch(Exception e){}
    			}			
    		}).start();
    	}
    }
    
    /**
     * Stops the currently playing music.
     * <p>
     * modifies:  musicPlaying state is set to false
     *            currentMusic is stopped
     * <p>           
     * requires:  nothing  
     */
    public void stopMusic(){
    	if(!musicPlaying)
    		System.out.println("Music was not currently playing");
    	else{
    		System.out.println("Stopping music");
    		musicPlaying = false;   
    		try{
    			currentMusic.stop();
    		}catch(NullPointerException e){
    			System.out.println("\\\\\\\\\\!!!!!Music could not be stopped.!!!!!/////");
    		}
    	}
    }
    
    /**
     * Loads input level.
     * <p>
     * modifies:  Sets onTitleScreen state to false.  Initializes toBeKilled,
     *            timer, onScreen.  Sets currentLevel, user's max level,
     *            then saves the game.  Current level screen is setup.
     *            Level music starts playing and 100 bugs are created 
     *            at a rate decided by the level.  They are told to animate.
     *            If the user reaches gameOver state, gameOver() is called.
     *            If toBeKilled reaches 0, the level ends, its music starts,
     *            the screen is cleared of garbage, and the next level is loaded. 
     * <p>           
     * requires:  level must be at least 1 
     * @param level level which you want to play
     */    		
    public void playLevel(int level){   //Run the game
    	if(level < 1){
    		System.out.println("Invalid level select.  Exiting.");
    		return;
    	}
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
					playMusic();  // First three songs continuously looped					
					while(toBeKilled > 0){	//Level is over when all are dead   
						if(gameOver){
							gameOver();
							return;
						}
						if(onScreen < 2 * currentLevel && timer > 10 && onScreen != toBeKilled){  //Limits number on screen and when they appear
							onScreen++;
							timer = (int)Math.round(Math.random() * 5);
							
							if(toBeKilled > 80){
								createBug(SMALLFLY);
							}
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
						Thread.currentThread().sleep(50);						
						timer++;
					} 
				}catch(Exception exc){}	
				if(!gameOver){
					System.out.println("Level beaten.  Moving to next level.");
					stopMusic();				
					clearScreen();
					playLevel(currentLevel + 1);
				}
			}			
		}).start();
    }    

    /**
     * Makes CursorLabels follow the cursor.  Animates the cursor when over a button in the title menu.
     * <p>
     * modifies:  gameCursorLabel and menuCursorLabel move with the mouse.
     *            menuCursorLabelAnimating is temporarily altered while it animates.
     *            Sends cursor location to AnimatedLabels so they can attack the user.
     */
    public void mouseMoved(MouseEvent e) {
    	gameCursorLabel.setLocation(e.getX()-XFUDGE, e.getY()-YFUDGE);
    	menuCursorLabel.setLocation(e.getX(), e.getY());
    	for(int i = 0; i < aLabel.size(); i++)
    		aLabel.get(i).sendCursorLocation(gameCursorLabel.getX(), gameCursorLabel.getY());  // Tells certain bugs where you are
    	if(onTitleScreen){ //When game is not running, the cursors are directly on pointer
    		//Checks if mouse is over a box
    		if((e.getX() >= 55 && e.getX() <= 55 + 54 && e.getY() >= 695 && e.getY() <= 695 + 61) || 
    				(e.getX() >= 725 && e.getX() <= 725 + 54 && e.getY() >= 695 && e.getY() <= 695 + 61)){
    			//Animates if not already doing so or hasn't done so recently
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
    		else
    			menuCursorLabelAnimating = false;
    	}
    }	
    
    /**
     * Makes CursorLabels follow the cursor.  Animates the cursor when over a button in the title menu.
     * <p>
     * modifies:  gameCursorLabel and menuCursorLabel move with the mouse.
     *            Sends cursor location to AnimatedLabels so they can attack the user. 
     * <p>
     * requires: nothing
     */
    public void mouseDragged(MouseEvent e) {    	
    	gameCursorLabel.setLocation(e.getX()-XFUDGE, e.getY()-YFUDGE);
    	menuCursorLabel.setLocation(e.getX(), e.getY());
    	for(int i = 0; i < aLabel.size(); i++)
    		aLabel.get(i).sendCursorLocation(gameCursorLabel.getX(), gameCursorLabel.getY());  // Tells certain bugs where you are
    }    
    
    /**
     * Takes all clicking input from users, including using buttons and swatting flies.
     * <p>
     * modifies:  On title screen, can stopMusic, then call playLevel(int).
     *            On game screen, causes gameCursorLabel to animate and check
     *            for  hits.  gameCursorLabelAnimating is temporarily changed
     *            while animation takes place.  Sounds are played depending on
     *            if a hit is made.  toBeKilled, onScreen, counterIcons, and the
     *            timer are changed to represent a kill.  kill() command sent to
     *            AnimatedLabel to force it's death animation.
     * <p>           
     * requires:  nothing          
     */
    public void mousePressed(MouseEvent e){
    	if(onTitleScreen){ //Game is not currently playing
    		//Title screen buttons are 54 x 61
    		//Mouse is clicking load button - at point (55, 695)
    		if(e.getX() >= 55 && e.getX() <= 55 + 54 && e.getY() >= 695 && e.getY() <= 695 + 61){
    			System.out.println("Load feature accessed.");
    			stopMusic();
    			playLevel(user.getMaxLevel());
    		}
    		//Mouse is clicking new game button - at point (725, 695)
    		else if(e.getX() >= 725 && e.getX() <= 725 + 54 && e.getY() >= 695 && e.getY() <= 695 + 61){
    			stopMusic();
    			user.setHealth(3);
    			playLevel(1);  
    		}
    	}
    	else if(!gameCursorLabelAnimating && ableToAttack && !gameOver){  //Attack sequence
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
    								if(aLabel.get(i).hitTest(gameCursorLabel.getX(), gameCursorLabel.getY(), SWATTERWIDTH, 92) && aLabel.get(i).isAlive()){
    									if(!hit){
    										hit = true;
    										gameCursorLabel.setIcon(swatterIcon[3]);
    										gameCursorLabel.setSize(SWATTERWIDTH + 60, SWATTERHEIGHT); //Is more wide and has to be moved over					    				
    										gameCursorLabel.setLocation(gameCursorLabel.getX() - 30, gameCursorLabel.getY());
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
    								if(!hit){
    									new Thread(new Runnable(){
    										public void run(){
    											try{
    												swatSound.play();
    											}catch(Exception exc){}
    										}
    									}).start(); 
    								}
    							}	
    							else if(j == 3 && hit)
    								gameCursorLabel.setIcon(swatterIcon[4]);    					
    							Thread.currentThread().sleep(50);
    						}
    						gameCursorLabel.setIcon(swatterIcon[0]);
    						gameCursorLabel.setSize(SWATTERWIDTH, SWATTERHEIGHT);
    						if(hit)  //Moves back to original position if necessary
    							gameCursorLabel.setLocation(gameCursorLabel.getX() + 30, gameCursorLabel.getY());
        		    		gameCursorLabelAnimating = false;
    					}catch(Exception exc){}
    				}
    		}).start();   //End of main Thread
    	}
    }    

   /**
    * Not implemented.
    */
    public void mouseReleased(MouseEvent e){}
    
    /**
     * Not implemented.
     */
    public void mouseClicked(MouseEvent e){}
    
    /**
     * Not implemented.
     */
    public void mouseEntered(MouseEvent e){}
    
    /**
     * Not implemented.
     */
    public void mouseExited(MouseEvent e){}
    
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
}