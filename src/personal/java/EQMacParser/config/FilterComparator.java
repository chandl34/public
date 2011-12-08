package config;

import java.util.Comparator;

public class FilterComparator implements Comparator<String> {

	public int compare(String s1, String s2){
		if(s1.contains(s2))
			return 0;
		return s1.compareTo(s2);
	}	
}
