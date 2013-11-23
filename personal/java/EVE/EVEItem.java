

public class EVEItem<A, B> {
	private A parent;
	private B next;
	private int itemID, matches, uniqueMatches;
	private String itemName;
	public int mineralCount[] = new int[20];
	
	EVEItem(){
		
	}
	
	EVEItem(int itemID, String itemName){
		this.itemID = itemID;
		this.itemName = itemName;
	}	

	public String getItemName(){
		return itemName;
	}
	
	public int getItemID(){
		return itemID;
	}
	
	public int getArrayIndex(){
		return itemID;
	}

	public void setMatches(int match){
		matches = match;
	}	
	
	public int getMatches(){
		return matches;
	}	
	
	public void setUniqueMatches(int match){
		uniqueMatches = match;
	}
	
	public int getUniqueMatches(){
		return uniqueMatches;
	}

	public void setNext(B next){
		this.next = next;
	}
	
	public B getNext(){
		return next;
	}		

	public void setParent(A parent){
		this.parent = parent;
	}
	
	public A getParent(){
		return parent;
	}

	public void count(){}
	

	public boolean isEmpty(){
		for(int i = 0; i < mineralCount.length; i++){
			if(mineralCount[i] > 0)
				return false;
		}			
		return true;
	}
	
	
}
