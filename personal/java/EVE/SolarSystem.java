

public class SolarSystem extends EVEItem2<Constellation, SolarSystem, Moon>{
	
	SolarSystem(){
		
	}
	
	SolarSystem(int itemID, String itemName){
		super(itemID, itemName);
	}
	
	public int getArrayIndex(){
		return getItemID() - 30000000;
	}
	
	public void insert(Moon element){
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
			if(!cursor.isInUse() && cursor.isUpToDate()){
				for(int i = 0; i < cursor.mineralCount.length; i++)
					mineralCount[i] = mineralCount[i] + cursor.mineralCount[i];
			}
			cursor = cursor.getNext();
		}while(cursor != head);
	}	
	
	public String getInfo(RawMaterial[] raw){
		String temp = "";
		for(int i = 0; i < mineralCount.length; i++){
			if(mineralCount[i] != 0){
				temp = temp + "    " + raw[i].getName() + ":\t";
				if(raw[i].getName().length() < 12)
					temp = temp + "\t";
				temp = temp + mineralCount[i] + "\n";
			}
		}
		return temp;		
	}
	
	public String getSubInfo(RawMaterial[] raw){
		String temp = "\n\n\nMOON TOTALS:\t\tmoonID\n\n";
		resetCursor();
		do{	
			if(cursor.isUpToDate() && !cursor.isEmpty())
				temp = temp + cursor.getInfo(raw);
			cursor = cursor.getNext();
		}while(cursor != head);
		
		
		return temp;
	}

}
