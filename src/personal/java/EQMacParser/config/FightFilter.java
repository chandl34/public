package config;

import java.util.Iterator;
import java.util.Scanner;
import java.util.TreeSet;

public class FightFilter {

	private TreeSet<String> filter;
		
	
	public FightFilter(){		
		filter = new TreeSet<String>(new FilterComparator());
	}
	

	public void setFilters(String str){
		filter.clear();
		Scanner scan = new Scanner(str);
		
		String temp;
		while(scan.hasNext()){
			temp = scan.next();
			filter.add(temp);			
		}
	}
	
	
	public String getFilters(){
		String str = "";
		Iterator<String> iter = filter.iterator();
		while(iter.hasNext())
			str += iter.next() + " ";
		return str;
	}
	
	
	public boolean isFiltered(String s){
		return filter.contains(s);
	}	
	
}
