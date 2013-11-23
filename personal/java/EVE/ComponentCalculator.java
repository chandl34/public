
public class ComponentCalculator{
	
	RawMaterial[] raw = new RawMaterial[20];
	SimpleReaction[] simple = new SimpleReaction[19];
	ComplexReaction[] complex = new ComplexReaction[11];
	Component[] component = new Component[36];
	TreeNode root;
	
	
	// CONSTRUCTORS	
	ComponentCalculator(){
		constructRaw();
		constructSimple();
		constructComplex();
		constructComponents();		    
	}
	
	private void constructRaw(){
		raw[0] = new RawMaterial("Atmospheric Gases");		
		raw[1] = new RawMaterial("Cadmium");
		raw[2] = new RawMaterial("Caesium");
		raw[3] = new RawMaterial("Chromium");
		raw[4] = new RawMaterial("Cobalt");
		raw[5] = new RawMaterial("Dysprosium");
		raw[6] = new RawMaterial("Evaporite Deposits");
		raw[7] = new RawMaterial("Hafnium");
		raw[8] = new RawMaterial("Hydrocarbons");
		raw[9] = new RawMaterial("Mercury");
		raw[10] = new RawMaterial("Neodymium");
		raw[11] = new RawMaterial("Platinum");
		raw[12] = new RawMaterial("Promethium");
		raw[13] = new RawMaterial("Scandium");
		raw[14] = new RawMaterial("Silicates");
		raw[15] = new RawMaterial("Technetium");
		raw[16] = new RawMaterial("Thulium");
		raw[17] = new RawMaterial("Titanium");
		raw[18] = new RawMaterial("Tungsten");		
		raw[19] = new RawMaterial("Vanadium");				
	}
	
	private void constructSimple(){
		simple[0] = new SimpleReaction("Caesarium Cadmide", raw[1], raw[2]);
		simple[1] = new SimpleReaction("Carbon Polymers", raw[8], raw[14]);
		simple[2] = new SimpleReaction("Ceramic Powder", raw[6], raw[14]);
		simple[3] = new SimpleReaction("Crystalline Alloy", raw[1], raw[4]);
		simple[4] = new SimpleReaction("Dysporite", raw[5], raw[9]);
		simple[5] = new SimpleReaction("Fernite Alloy", raw[13], raw[19]);
		simple[6] = new SimpleReaction("Ferrofluid", raw[5], raw[7]);
		simple[7] = new SimpleReaction("Fluxed Condensates", raw[10], raw[16]);
		simple[8] = new SimpleReaction("Hexite", raw[3], raw[11]);
		simple[9] = new SimpleReaction("Hyperflurite", raw[12], raw[19]);
		simple[10] = new SimpleReaction("Neo Mercurite", raw[9], raw[10]);
		simple[11] = new SimpleReaction("Platinum Technite", raw[11], raw[15]);
		simple[12] = new SimpleReaction("Prometium", raw[1], raw[12]);
		simple[13] = new SimpleReaction("Rolled Tungsten Alloy", raw[11], raw[18]);
		simple[14] = new SimpleReaction("Silicon Diborite", raw[6], raw[14]);
		simple[15] = new SimpleReaction("Solerium", raw[2], raw[3]);
		simple[16] = new SimpleReaction("Sulfuric Acid", raw[0], raw[6]);
		simple[17] = new SimpleReaction("Titanium Chromide", raw[3], raw[17]);
		simple[18] = new SimpleReaction("Vanadium Hafnite", raw[7], raw[19]);
	}
	
	private void constructComplex(){
		complex[0] = new ComplexReaction("Crystalline Carbonide", simple[1], simple[3], null, null, 10000);
		complex[1] = new ComplexReaction("Fermionic Condensates", simple[0], simple[4], simple[7], simple[12], 200);
		complex[2] = new ComplexReaction("Fernite Carbide", simple[2], simple[5], null, null, 10000);
		complex[3] = new ComplexReaction("Ferrogel", simple[6], simple[8], simple[9], simple[12], 400);
		complex[4] = new ComplexReaction("Fullerides", simple[1], simple[11], null, null, 3000);
		complex[5] = new ComplexReaction("Hypersynaptic Fibers", simple[4], simple[15], simple[18], null, 750);
		complex[6] = new ComplexReaction("Nanotransistors", simple[10], simple[11], simple[16], null, 1500);
		complex[7] = new ComplexReaction("Phenolic Composites", simple[0], simple[14], simple[18], null, 2200);
		complex[8] = new ComplexReaction("Sylramic Fibers", simple[2], simple[8], null, null, 6000);
		complex[9] = new ComplexReaction("Titanium Carbide", simple[14], simple[17], null, null, 10000);
		complex[10] = new ComplexReaction("Tungsten Carbide", simple[13], simple[16], null, null, 10000);
	}
	
	private void constructComponents(){
		component[0] = new Component("Antimatter Reactor Unit", complex[1], 1, complex[3], 1, complex[10], 11);
		component[1] = new Component("Crystalline Carbonide Armor Plate", complex[0], 54, complex[8], 41, null, 0);
		component[2] = new Component("Deflection Shield Emitter", complex[2], 27, complex[3], 1, complex[8], 11);
		component[3] = new Component("Electrolytic Capacitor Unit", complex[2], 32, complex[4], 20, complex[6], 1);
		component[4] = new Component("EMP Pulse Generator", complex[6], 3, complex[7], 8, complex[10], 27);
		component[5] = new Component("Fernite Carbide Composite Armor Plate", complex[2], 54, complex[8], 41, null, 0);
		component[6] = new Component("Fusion Reactor Unit", complex[0], 11, complex[1], 1, complex[3], 1);
		component[7] = new Component("Fusion Thruster", complex[3], 1, complex[7], 4, complex[10], 16);
		component[8] = new Component("Gravimetric Sensor Cluster", complex[5], 3, complex[6], 1, complex[9], 27);
		component[9] = new Component("Graviton Pulse Generator", complex[6], 3, complex[7], 8, complex[9], 27);
		component[10] = new Component("Graviton Reactor Unit", complex[2], 1, complex[3], 1, complex[9], 11);
		component[11] = new Component("Ion Thruster", complex[0], 16, complex[3], 1, complex[7], 4);
		component[12] = new Component("Laser Focusing Crystals", complex[4], 14, complex[5], 1, complex[10], 38);
		component[13] = new Component("Laser Sensor Cluster", complex[2], 27, complex[5], 3, complex[6], 1);
		component[14] = new Component("Linear Shield Emitter", complex[3], 1, complex[8], 11, complex[10], 27);
		component[15] = new Component("Magnetometric Sensor Cluster", complex[0], 27, complex[5], 3, complex[6], 1);
		component[16] = new Component("Magpulse Thruster", complex[3], 1, complex[7], 4, complex[9], 16);
		component[17] = new Component("Nanoelectrical Microprocessor", complex[6], 7, complex[7], 1, complex[10], 16);
		component[18] = new Component("Nanomechanical Microprocessor", complex[2], 16, complex[6], 7, complex[7], 1);
		component[19] = new Component("Nuclear Pulse Generator", complex[2], 27, complex[6], 3, complex[7], 8);
		component[20] = new Component("Nuclear Reactor Unit", complex[1], 1, complex[2], 11, complex[3], 1);
		component[21] = new Component("Oscillator Capacitor Unit", complex[0], 32, complex[4], 20, complex[6], 1);
		component[22] = new Component("Particle Accelerator Unit", complex[0], 38, complex[4], 14, complex[5], 1);
		component[23] = new Component("Photon Microprocessor", complex[0], 16, complex[6], 7, complex[7], 1);
		component[24] = new Component("Plasma Pulse Generator", complex[0], 27, complex[6], 3, complex[7], 8);
		component[25] = new Component("Plasma Thruster", complex[2], 16, complex[3], 1, complex[7], 4);
		component[26] = new Component("Pulse Shield Emitter", complex[0], 27, complex[3], 1, complex[8], 11);
		component[27] = new Component("Quantum Microprocessor", complex[6], 7, complex[7], 1, complex[9], 16);
		component[28] = new Component("Radar Sensor Cluster", complex[5], 3, complex[6], 1, complex[10], 27);
		component[29] = new Component("Scalar Capacitor Unit", complex[4], 20, complex[6], 1, complex[9], 32);
		component[30] = new Component("Superconductor Rails", complex[4], 14, complex[5], 1, complex[9], 38);
		component[31] = new Component("Sustained Shield Emitter", complex[3], 1, complex[8], 11, complex[9], 27);
		component[32] = new Component("Tesseract Capacitor Unit", complex[4], 20, complex[6], 1, complex[10], 32);
		component[33] = new Component("Thermonuclear Trigger Unit", complex[2], 38, complex[4], 14, complex[5], 1);
		component[34] = new Component("Titanium Diborite Armor Plate", complex[8], 41, complex[9], 54, null, 0);
		component[35] = new Component("Tungsten Carbide Armor Plate", complex[8], 41, complex[10], 54, null, 0);
	}	
	
	private void resetCount(){
		for(int complexIndex = 0; complexIndex < complex.length; complexIndex++)
			complex[complexIndex].setCount(0);
		for(int simpleIndex = 0; simpleIndex < simple.length; simpleIndex++)
			simple[simpleIndex].setCount(0);
		for(int rawIndex = 0; rawIndex < raw.length; rawIndex++)
			raw[rawIndex].setCount(0);		
	}
	
	public void count(int index, double pe){		
		resetCount();
		for(int complexIndex = 0; complexIndex < 3; complexIndex++){
			if(component[index].getComplex(complexIndex) != null){
				component[index].getComplex(complexIndex).setCount(((1 - .05 * pe) * component[index].getComplexCount(complexIndex)));
				for(int simpleIndex = 0; simpleIndex < 4; simpleIndex++){
					if(component[index].getComplex(complexIndex).getSimple(simpleIndex) != null){
						component[index].getComplex(complexIndex).getSimple(simpleIndex).addToCount((1 - .05 * pe) * component[index].getComplex(complexIndex).getCountDouble() * component[index].getComplex(complexIndex).ratio);
						for(int rawIndex = 0; rawIndex < 2; rawIndex++)
							component[index].getComplex(complexIndex).getSimple(simpleIndex).getRaw(rawIndex).addToCount((1 - .05 * pe) * component[index].getComplex(complexIndex).getCountDouble() * component[index].getComplex(complexIndex).ratio * SimpleReaction.RATIO);
					}
				}
			}
		}
	}
	
	public int getTotalUniqueRawCount(){
		int temp = 0;
		for(int i = 0; i < raw.length; i++){
			if(raw[i].getCountInt() > 0)
				temp++;
		}			
		return temp;
	}
	
	public int getTotalRawCount(){
		int temp = 0;
		for(int i = 0; i < raw.length; i++)
			temp = temp + raw[i].getCountInt();
		return temp;
	}
	
	// SORTING TOOLS
	public void sort(Material[] type, int multiplier){
		root = new TreeNode(type[0]);
		for(int i = 0; i < type.length; i++){
			if(type[i].getCountDouble() != 0){
				type[i].setCount(Math.round(type[i].getCountDouble() * multiplier));
				if(type[i].getCountDouble() == 0)
					type[i].addToCount(1);
				sortSub(type, i, root);
			}
		}
	}
	
	private void sortSub(Material[] type, int index, TreeNode node){
		if(index != 0){
			Material rootElement = (Material)node.getElement();
			if(type[index].getCountDouble() > rootElement.getCountDouble()){
				if(node.getLeft() == null)
					node.setLeft(new TreeNode(type[index]));
				else
					sortSub(type, index, node.getLeft());
			}
			else{
				if(node.getRight() == null)
					node.setRight(new TreeNode(type[index]));
				else
					sortSub(type, index, node.getRight());
			}	
		}
	}
	
	
	// DISPLAYS
	public String showRatioNames(){
		return showRatio(true);
	}
	
	public String showRatioNumbers(){
		return showRatio(false);
	}
	
	private String showRatio(boolean names){
		String temp = "";
		if(names)
			temp = temp + "     ";
		if(root != null){
			Material rootElement = (Material)root.getElement();
			temp = subShowRatio(root.getLeft(), temp, names);
			if(rootElement.getCountDouble() != 0){
				if(names)
					temp = temp + rootElement.getName() + "\n     ";
				else
					temp = temp + rootElement.getCountInt() + "\n";
			}
			temp = subShowRatio(root.getRight(), temp, names);	
		}
		return temp;
	}
	
	private String subShowRatio(TreeNode node, String temp, boolean names){
		if(node != null){
			Material nodeElement = (Material)node.getElement();
			temp = subShowRatio(node.getLeft(), temp, names);
			if(names)
				temp = temp + nodeElement.getName() + "\n     ";
			else
				temp = temp + nodeElement.getCountInt() + "\n";
			temp = subShowRatio(node.getRight(), temp, names);				
		}
		return temp;
	}

	public String showMaterials(int index){		
		String temp = "*******Component Blueprint*******\n\n";
		for(int complexIndex = 0; complexIndex < 3; complexIndex++){
			if(component[index].getComplex(complexIndex) != null){
				temp = temp + component[index].getComplex(complexIndex).getName() + "\n";
				for(int simpleIndex = 0; simpleIndex < 4; simpleIndex++){
					if(component[index].getComplex(complexIndex).getSimple(simpleIndex) != null){
						temp = temp + ("          - " + component[index].getComplex(complexIndex).getSimple(simpleIndex).getName() + "\n");
						for(int rawIndex = 0; rawIndex < 2; rawIndex++)
							temp = temp + ("                    -- " + component[index].getComplex(complexIndex).getSimple(simpleIndex).getRaw(rawIndex).getName()) + "\n";
					}
				}
			}
		}
		return temp;
	}
	
	public static void main(String[] args) {
		
	}
	
}
