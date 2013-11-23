

public class Component extends Material{
	
	private ComplexReaction complex[] = new ComplexReaction[3];
	private double complexCount[] = new double[3];
	
	Component(String name, ComplexReaction complex1, int num_complex1, ComplexReaction complex2, int num_complex2, ComplexReaction complex3, int num_complex3){
		setName(name);
		complex[0] = complex1;
		complexCount[0] = num_complex1 ;
		complex[1] = complex2;
		complexCount[1] = num_complex2;
		complex[2] = complex3;
		complexCount[2] = num_complex3;
	}
	
	public ComplexReaction getComplex(int index){
		return complex[index];
	}
	
	public double getComplexCount(int index){
		return complexCount[index];
	}
	
}
