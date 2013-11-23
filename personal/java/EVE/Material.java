

public abstract class Material {
	private String name;
	private double count;
	
	public String getName(){
		return name;
	}	

	public void setName(String name){
		this.name = name;
	}
	
	public void setCount(double count){
		this.count = count;
	}
	
	public double getCountDouble(){
		return count;
	}
	
	public int getCountInt(){
		return (int)count;
	}
	
	public void addToCount(double count){
		this.count = this.count + count;
	}
}
