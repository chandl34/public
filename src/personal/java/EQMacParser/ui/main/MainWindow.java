package ui.main;


import include.Constant;

import java.awt.Dimension;
import java.awt.Point;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.io.File;
import java.util.Vector;

import javax.swing.JFrame;
import javax.swing.JSplitPane;
import javax.swing.UIManager;

import parser.LogReader;
import ui.popup.FilterWindow;
import ui.popup.TimeOutWindow;
import config.Config;



public class MainWindow implements ComponentListener {
	private static int selected;	
	private static Config config;
	private static LogReader reader;	
	private static File logFile;
	
	private static JFrame frame;
	private static JSplitPane contentPane;

	private static MenuBar menuBar;
	private static ListPane listPane;	
	private static DataPane dataPane;

	private static TimeOutWindow timeOutWindow;
	private static FilterWindow filterWindow;	
		
		
	public void createAndShowGUI() {
		System.out.println("Loading configuration file...");
		config = new Config();
		reader = new LogReader();	
		logFile = null;
		selected = -1;	
		
		try{
			UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
		}
		catch(Exception e){
			System.out.println("Failed to change LookAndFeel");
		}
			
			
		frame = new JFrame("Shlammo!'s EQMac Melee Parser");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//frame.setResizable(false);

		contentPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
		contentPane.setOpaque(true); 		
		contentPane.setDividerSize(4);
		contentPane.setDividerLocation(Constant.LIST_WIDTH);
		frame.setContentPane(contentPane);	
		frame.setPreferredSize(new Dimension(
				Constant.WINDOW_WIDTH, 
				Constant.WINDOW_HEIGHT));
		frame.addComponentListener(this);
				
		menuBar = new MenuBar();
		frame.setJMenuBar(menuBar);
		
		listPane = new ListPane();
		contentPane.setLeftComponent(listPane);	
		
		dataPane = new DataPane();
		updateStatus();
		contentPane.setRightComponent(dataPane);	

		timeOutWindow = new TimeOutWindow();
		filterWindow = new FilterWindow();
		
		frame.pack();
		frame.setVisible(true); 
	}

	// Update the parsing status pane
	private static void updateStatus(){
		String status = (" Log file:  " + reader.getFileName() + "\n Parsing:  ");
		if(!reader.isParsing())
			status += "in";
		status += "active\n\n ";
		
		if(selected > -1)
			status += reader.getFightStatus(selected);
		
		dataPane.setStatus(status);		
	}

	// Shows selected fight's data table
	private static void showData(){
		if(selected > -1)
			dataPane.updateData(reader.getData(selected));
		else
			dataPane.updateData(null);
	}
	
	// Select fight from fight list
	public static void selectFight(int i){
		if(selected != i){
			selected = i;
			showData();
		}
		updateStatus();
	}
			
	
	//---- METHODS INTERACTING WITH PARSING THREAD ----//

	public static void openNewLogFile(File f){
		updateList(null);
		closeLogFile();
		openLogFile(f);
	}
	
	
	private static void closeLogFile(){
		logFile = null;
		reader.closeFile();
	}
	
	// Sets the log file
	private static void openLogFile(File f){	
		logFile = f;				
		reader.openFile(logFile);			// update file
		selectFight(-1);					// clean up
	}
	
	// Reload log file to show new data
	private static void reloadLogFile(){
		updateList(null);
		if(logFile != null)
			openLogFile(logFile);
	}
	
	// Write to config file and reload
	private static void writeConfigFile(){
		config.writeConfigFile();
		reloadLogFile();
	}
	
	
		
	// Toggles parsing
	public static void toggleParsing(){
		reader.toggleParsing();
		updateStatus();		
	}
	
	// Updates the fight list
	public static void updateList(Vector<String> s){
		listPane.updateList(s);
	}
	
		// Get fight filters
	public static String getFightFilters(){
		return config.getFightFilters();
	}	

	// Set fight filters
	public static void setFightFilters(String str){
		reader.closeFile();
		config.setFightFilters(str);
		writeConfigFile();
	}	

	// Gets fight timout
	public static int getTimeOut(){
		return config.getTimeOut();
	}
	
	// Sets delay for fights
	public static void setTimeOut(int s){
		reader.closeFile();
		config.setTimeOut(s);
		writeConfigFile();
	}
		
	// Finds if a name is filtered
	public static boolean isFiltered(String s){
		return config.isFiltered(s);
	}
		
	// Show delay window so users can set fight delay
	public static void showTimeOutWindow(){
		timeOutWindow.setLocation(new Point(frame.getX() + 40, frame.getY() + 60));
		timeOutWindow.setVisible(true);
	}		
		
	// Show filter window so users can add filters
	public static void showFilterWindow(){
		filterWindow.setLocation(new Point(frame.getX() + 40, frame.getY() + 60));
		filterWindow.setVisible(true);
	}

	
	public void componentResized(ComponentEvent e){
		int width = contentPane.getDividerLocation();
		listPane.setBounds(1, 
						   1, 
						   width - 1, 
						   contentPane.getHeight() - 1);
		dataPane.setBounds(width + contentPane.getDividerSize(), 
						   1, 
						   contentPane.getWidth() - width - contentPane.getDividerSize(), 
						   contentPane.getHeight() - 1);
	}

	public void componentMoved(ComponentEvent e){}
	public void componentShown(ComponentEvent e){}
	public void componentHidden(ComponentEvent e){}		
}
