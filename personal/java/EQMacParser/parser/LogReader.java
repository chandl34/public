package parser;

import java.io.File;
import java.util.Scanner;
import java.util.Vector;

public class LogReader {

	private FightList fightList;
	
	private File file;
	private String filepath;
	private Scanner scan;
	
	private boolean parsing, fileOpen;
	
	private long lastModified;
	private int skip;
	
	public LogReader(){
		fightList = new FightList();
		file = null;	
		scan = null;
		parsing = false;
		fileOpen = false;
		
		new Thread(){
			public void run(){
				parse();
			}			
		}.start();
	}
	
	
	// Synchronized methods
	public synchronized void setParsing(boolean p){
		parsing = p;		
	}
	
	public synchronized void toggleParsing(){
		parsing = !parsing;
	}
	
	public synchronized boolean isParsing(){
		return parsing;
	}
	
	public synchronized void setFileOpen(boolean fo){
		fileOpen = fo;
	}
	
	public synchronized boolean isFileOpen(){
		return fileOpen;
	}

	// Note: separate from main thread
	public void parse(){
		File tempFile;
		String tempStr1, tempStr2;
					
		while(true){
			//------------ CRITICAL SECTION BEGIN ------------//
			while(isParsing()){
				setFileOpen(true);
								
				if(scan.hasNextLine()){				// Read available lines
					tempStr1 = scan.nextLine();
					tempStr2 = scan.nextLine();
					fightList.parseOutput(tempStr1, tempStr2);
					skip += 2;
				}
				else{						
					try{
						Thread.sleep(1000);			// Pause for a second
						tempFile = new File(filepath);
						if(lastModified != tempFile.lastModified()){
							openFile(tempFile);
							for(int i = 0; i < skip; i++)// Skip already read lines
								scan.nextLine();
						}
					}
					catch(Exception e){
						System.out.println("Error reading updated file.");
						file = null;
					}		
				}

				//------------ CRITICAL SECTION END ------------//
				setFileOpen(false);
			}
			
			// Sleep between checks if parsing is active
			try{
				Thread.sleep(1000);			
			}
			catch(Exception e){
				System.out.println("Parsing thread failed to sleep.");
			}
		}	// End while(true)
	}
		
	public String getFileName(){
		if(file == null)
			return "n/a";
		return file.getAbsolutePath();
	}
	
	public void closeFile(){
		setParsing(false);			// stop parsing
		do{							// then wait for it to end
			try{
				Thread.sleep(100);
			}
			catch(Exception e){
				System.out.println("ERROR:  sleep() in closeLogFile()");
			}
		}while(isFileOpen());	
		
		fightList.clear();
		skip = 0;		
	}
	
	public void openFile(File f){
		try{
			if(scan != null)
				scan.close();
			file = f;	
			filepath = file.getAbsolutePath();
			lastModified = file.lastModified();
			scan = new Scanner(file);
						
			System.out.println("Reading " + file.getName() + "...");
			setParsing(true);
		}
		catch(Exception e){
			System.out.println("Error opening file.");
			file = null;
		}	
	}
	
	public String getFightStatus(int i){
		return fightList.getFightStatus(i);
	}

	public Vector<String[]> getData(int i){
		return fightList.getData(i);
	}
	
}
