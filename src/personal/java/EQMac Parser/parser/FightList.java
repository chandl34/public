package parser;

import java.util.Scanner;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.Vector;

import ui.main.MainWindow;

public class FightList {

	private Vector<String> fightName;
	private Vector<Fight> fight;

	private TreeSet<String> fightWord;
	private TreeMap<String, Integer> monthMap;

	private int year, month, day, hour, minute, second;
	private String fighter, enemy;
	private int damage;

	private int oldestActive;

	private Scanner scan;


	public FightList(){
		fightName = new Vector<String>();
		fight = new Vector<Fight>();
		oldestActive = -1;

		fightWord = new TreeSet<String>();
		fightWord.add("hits");
		fightWord.add("crushes");
		fightWord.add("slashes");
		fightWord.add("pierces");
		fightWord.add("slices");
		fightWord.add("bites");
		fightWord.add("gores");
		fightWord.add("punches");
		fightWord.add("bashes");
		fightWord.add("slams");
		fightWord.add("claws");
		fightWord.add("backstabs");
		fightWord.add("strikes");
		fightWord.add("kicks");
		fightWord.add("mauls");
		fightWord.add("stings");
		fightWord.add("rends");

		monthMap = new TreeMap<String, Integer>();
		monthMap.put("Jan", 1);
		monthMap.put("Feb", 2);
		monthMap.put("Mar", 3);
		monthMap.put("Apr", 4);
		monthMap.put("May", 5);
		monthMap.put("Jun", 6);
		monthMap.put("Jul", 7);
		monthMap.put("Aug", 8);
		monthMap.put("Sep", 9);
		monthMap.put("Oct", 10);
		monthMap.put("Nov", 11);
		monthMap.put("Dec", 12);
	}


	private boolean isMeleeDamage(String str){
		return str.contains("damage") && 		// Look for damage
		!str.contains(" non-melee ") &&	// Ignore non-melee damage
		!str.contains(" have ") &&		// Ignore spell messages
		!str.contains(",");	 			// Ignore conversation
	}


	private boolean isFightingWords(String s){
		return fightWord.contains(s);
	}


	public void parseOutput(String str1, String str2){
		if(isMeleeDamage(str2)){				
			scan = new Scanner(str2);
			scan.skip("] ");

			fighter = scan.next();
			String temp = scan.next();

			if(!fighter.equals("You")){
				while(!isFightingWords(temp)){
					fighter += " " + temp;
					//System.out.println(fighter);
					temp = scan.next();
				}
			}

			enemy = scan.next();

			temp = scan.next();
			while(!temp.equals("for")){
				enemy += " " + temp;
				//System.out.println(enemy);
				temp = scan.next();
			}

			if(MainWindow.isFiltered(enemy))
				return;

			damage = scan.nextInt();

			parseDate(str1);

			addInfo();
		}
	}


	private int getMonth(String m){		
		return monthMap.get(m).intValue();
	}


	private void parseDate(String s){	
		scan = new Scanner(s);
		scan.next();  // Skip [DayofWeek

		month = getMonth(scan.next());				
		day = scan.nextInt();

		scan.skip(" ");
		scan.useDelimiter(":");		
		hour = scan.nextInt();
		minute = scan.nextInt();

		scan.skip(":");
		scan.useDelimiter(" ");
		second = scan.nextInt();
		year = scan.nextInt();
	}


	private void addInfo(){
		boolean found = false;

		for(int i = oldestActive; i >= 0; i--){
			if(oldestActive == i &&									// Remove old fights
					fight.get(i).becameInactive(hour, minute, second))
				oldestActive--;
			else if(enemy.equalsIgnoreCase(fightName.get(i))){		// Add to existing fight
				fight.get(i).addInfo(fighter, damage, hour, minute, second, month, day, year);
				found = true;
			}
		}

		if(!found){													// Add new fight
			fightName.add(0, enemy);
			fight.add(0, new Fight(fighter, damage, hour, minute, second, month, day, year));
			oldestActive++;			
			MainWindow.updateList(fightName);
		}
	}


	public void clear() {
		oldestActive = -1;
		fightName.clear();
		fight.clear();		
	}	


	public String getFightStatus(int i){
		return fight.get(i).getStatus();
	}

	public Vector<String[]> getData(int i){
		return fight.get(i).getData();
	}	
}
