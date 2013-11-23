

public class Constellation extends EVEItem2<Region, Constellation, SolarSystem>{
	
	Constellation(){
		
	}
	
	Constellation(int itemID, String itemName){
		super(itemID, itemName);
	}
	
	public int getArrayIndex(){
		return getItemID() - 20000000;
	}
	
	public void insert(SolarSystem element){
		if(head == null){
			head = element;
			cursor = head;			
		}
		else{
			while(cursor.getNext() != head)
				cursor = cursor.getNext();		
			cursor.setNext(element);
			cursor = cursor.getNext();			
		}
		cursor.setNext(head);
		cursor.setParent(this);
	}	
	
	public void count(){
		for(int i = 0; i < mineralCount.length; i++){
			mineralCount[i] = 0;
		}
		cursor = head;
		do{
			for(int i = 0; i < cursor.mineralCount.length; i++)
				mineralCount[i] = mineralCount[i] + cursor.mineralCount[i];
			cursor = cursor.getNext();
		}while(cursor != head);
	}	
	
	public String getInfo(RawMaterial[] raw){
		String temp = "CONSTELLATION TOTALS:\n\n";
		
		for(int i = 0; i < mineralCount.length; i++){
			if(mineralCount[i] != 0){
				temp = temp + "  " + raw[i].getName() + ":\t";
				if(raw[i].getName().length() < 13)
					temp = temp + "\t";
				temp = temp + mineralCount[i] + "\n";
			}
		}		
		return temp;
	}
	
	public String getSubInfo(RawMaterial[] raw){
		String temp = "\n\n\nSYSTEM TOTALS:\n\n";
		resetCursor();
		do{	
			if(!cursor.isEmpty())
				temp = temp + "  " + cursor.getItemName() + ":\n" +cursor.getInfo(raw);
			cursor = cursor.getNext();
		}while(cursor != head);
		
		
		return temp;
	}

}
