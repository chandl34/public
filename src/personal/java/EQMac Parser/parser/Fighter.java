package parser;

public class Fighter {

	private int prevHour, prevMinute, prevSecond;
	private int origHour, origMinute, origSecond;
	private int damage;
	
	
	public Fighter(int dam, int h, int min, int sec) {
		damage = dam;
		origHour = h;
		origMinute = min;
		origSecond = sec;
		prevHour = h;
		prevMinute = min;
		prevSecond = sec;
	}
	

	private int getSeconds(){
		int hour = Math.abs(prevHour - origHour + 24)%24;
		int min = hour*60 + prevMinute - origMinute;
		int sec = min*60 + prevSecond - origSecond;	
		
		return sec;
	}
		
	
	public int getDamage(){
		return damage;
	}
	

	public void addInfo(int dam, int h, int min, int sec) {
		damage += dam;
		prevHour = h;
		prevMinute = min;
		prevSecond = sec;
	}


	public String[] getData(String name){
		int sec = getSeconds();
		String dps = "n/a";
		if(sec > 0)
			dps = "" + (int)((float)damage)/sec;	
		
		String[] data = {name, "" + damage, "" + sec, dps};
		
		return data;
	}

}
