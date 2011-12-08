package parser;

import java.util.Vector;

import ui.main.MainWindow;

public class Fight {

	private int year, month, day, hour, minute, second;

	private Vector<String> fighterName;
	private Vector<Fighter> fighter;
	
	
	public Fight(String f, int dam, int h, int min, int sec, int mon, int d, int y){
		fighterName = new Vector<String>();
		fighter = new Vector<Fighter>();
		fighterName.add(f);
		fighter.add(new Fighter(dam, h, min, sec));
		hour = h;
		minute = min;
		second = sec;
		month = mon;
		day = d;
		year = y;
	}	
	
	
	private void sortFighters(){
		int index = 0;
		int max;
		Fighter tempFighter;
		String tempFighterName;
		
		for(int sorted = 0; sorted < fighter.size() - 1; sorted++){
			max = 0;
			for(int i = sorted; i < fighter.size(); i++){
				if(fighter.get(i).getDamage() > max){
					index = i;
					max = fighter.get(i).getDamage();
				}
			}
			tempFighter = fighter.get(sorted);
			tempFighterName = fighterName.get(sorted);
			
			fighter.setElementAt(fighter.get(index), sorted);
			fighterName.setElementAt(fighterName.get(index), sorted);
			
			fighter.setElementAt(tempFighter, index);
			fighterName.setElementAt(tempFighterName, index);		
		}
		
	}	
	
	public String getStatus(){				
		String status = "Last recorded time: ";
		
		if(hour < 10)
			status += 0;
		status += hour + ":";
		
		if(minute < 10)
			status += 0;
		status += minute + ":";
		
		if(second < 10)
			status += 0;
		status += second + "  ";
		
		if(month < 10)
			status += 0;
		status += month + "/";
		
		if(day < 10)
			status += 0;
		status += day + "/";
		
		status += year + "\n\n";
		
		return status;			
	}
	

	public void addInfo(String f, int dam, int h, int min, int sec, int mon, int d, int y){
		if(fighterName.contains(f))
			fighter.get(fighterName.indexOf(f)).addInfo(dam, h, min, sec);
		else{
			fighterName.add(f);
			fighter.add(new Fighter(dam, h, min, sec));
		}		
		hour = h;
		minute = min;
		second = sec;
		month = mon;
		day = d;
		year = y;	

		//sortFighters();					// removed from here, may be a mistake				----v
	}
	

	public boolean becameInactive(int h, int min, int sec){	// Note: Could fail in rare cases
		int h1 = Math.abs(h - hour + 24)%24;
		int m1 = h1*60 + min - minute;
		int s1 = m1*60 + sec - second;	
		
		return s1 > MainWindow.getTimeOut();
	}


	public Vector<String[]> getData() {
		sortFighters();						// moved to here, may be a mistake					----^
		Vector<String[]> data = new Vector<String[]>();
		for(int i = 0; i < fighter.size(); i++)
			data.add(fighter.get(i).getData(fighterName.get(i)));	
		return data;
	}
}
