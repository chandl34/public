

public class SimpleReaction extends Material{

	private RawMaterial raw[] = new RawMaterial[2];
	public static final int PRODUCED = 200;
	public static final int NUM_OF_MATERIALS = 100;
	public static final double RATIO = (double)RawMaterial.NUM_OF_MATERIALS/PRODUCED;
	
	
	SimpleReaction(String name, RawMaterial raw1, RawMaterial raw2){
		setName(name);
		raw[0] = raw1;
		raw[1] = raw2;
	}

	public RawMaterial getRaw(int index){
		return raw[index];
	}
}
