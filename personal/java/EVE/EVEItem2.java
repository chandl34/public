

public class EVEItem2<A, B, C> extends EVEItem<A, B>{
	public C head, cursor;
	
	EVEItem2(){
		
	}
	
	EVEItem2(int itemID, String itemName){
		super(itemID, itemName);
	}
	
	public void resetCursor(){
		cursor = head;
	}
	
	public void insert(C element){}
	
}
