

public class ComplexReaction extends Material{
	
	private SimpleReaction simple[] = new SimpleReaction[4];
	private int produced;
	public double ratio;
	
	ComplexReaction(String name, SimpleReaction simple1, SimpleReaction simple2, SimpleReaction simple3, SimpleReaction simple4, int produced){
		setName(name);
		simple[0] = simple1;
		simple[1] = simple2;
		simple[2] = simple3;
		simple[3] = simple4;
		this.produced = produced;
		ratio = (double)SimpleReaction.NUM_OF_MATERIALS/produced;
	}
		
	public SimpleReaction getSimple(int index){
		return simple[index];
	}
	
	public int getProduced(){
		return produced;
	}
	
}
