package config;

import include.Constant;

import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class Config {
	
	private File configFile;
	private FightFilter fightFilter;
	private int timeout = Constant.DEFAULT_TIMEOUT;
	
	private Scanner scan;
	
	public Config(){		
		configFile = new File("smp.cfg");
		
		if(!configFile.exists())	// Create file if it doesn't exist		
			writeConfigFile();

		scan = null;		
		fightFilter = new FightFilter();	
		
		readConfigFile();		
	}
	
	
	private void readConfigFile(){		
		try{
			scan = new Scanner(configFile);
			
			String label, info;
			int loc;
			while(scan.hasNextLine()){
				info = scan.nextLine();
				loc = info.indexOf('=');
				if(loc > 0){
					label = info.substring(0, loc);
					info = info.substring(loc + 1);				
				
					if(label.equals("TIMEOUT"))
						timeout = Integer.parseInt(info);
					else if(label.equals("FILTERS"))
						fightFilter.setFilters(info);	
				}
			}	
			scan.close();
		}
		catch(Exception e){
			System.out.println("Failed to read configuration file");			
		}		
	}
	
	
	public void writeConfigFile(){
		System.out.println("Building configuration file...");
		
		try{
			FileWriter out = new FileWriter(configFile, false);
			out.write("TIMEOUT=" + timeout + "\nFILTERS=" + fightFilter.getFilters());
			out.close();
		}
		catch(Exception e){
			System.out.println("Build failed");
		}			
	}
	
	
	// Time out
	public void setTimeOut(int t){
		if(t < 0)
			timeout = 0;
		else
			timeout = t;
	}
	
	public int getTimeOut(){
		return timeout;
	}
	
	// Fight filters
	public void setFightFilters(String str){
		fightFilter.setFilters(str);
	}
		
	public String getFightFilters(){
		return fightFilter.getFilters();
	}
		
	public boolean isFiltered(String s){
		return fightFilter.isFiltered(s);
	}
}
