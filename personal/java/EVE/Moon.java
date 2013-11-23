

public class Moon extends EVEItem<SolarSystem, Moon>{
	private boolean inUse = false;
	private boolean upToDate = false;
	
	Moon(){
		
	}
	
	Moon(int itemID, String itemName){
		super(itemID, itemName);
	}
	
	public int getArrayIndex(){
		return getItemID() - 40000000;
	}
	
	public void insert(int elementIndex){
		if(elementIndex != -1)
			mineralCount[elementIndex]++;
	}
	
	public void setInUse(boolean used){
		inUse = used;
	}
	
	public boolean isInUse(){
		return inUse;
	}
	
	public void setUpToDate(boolean updated){
		upToDate = updated;
	}
	
	public boolean isUpToDate(){
		return upToDate;
	}
	
	public String getInfo(RawMaterial[] raw){
		String temp = "";
		if(isInUse())
			temp = temp + "   !!! IN USE !!!\n";
		temp = temp + "    " + getItemName() + ":\t" + getItemID() + "\n";		
		for(int i = 0; i < mineralCount.length; i++){
			if(mineralCount[i] != 0){
				temp = temp + "      " + raw[i].getName() + ":\t";
				if(raw[i].getName().length() < 11 && i != 10) // (i != 10) prevents Neodymium from breaking the table
					temp = temp + "\t";
				temp = temp + mineralCount[i] + "\n";
			}
		}		
		return temp + "\n";		
	}
}
