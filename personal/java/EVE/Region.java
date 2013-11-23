

public class Region extends EVEItem2<Universe, Region, Constellation>{
	
	Region(){
		
	}
	
	Region(int itemID, String itemName){
		super(itemID, itemName);
	}
	
	public int getArrayIndex(){
		return getItemID() - 10000000;
	}
	
	public void insert(Constellation element){
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

}
