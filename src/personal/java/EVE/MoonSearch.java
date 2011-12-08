
import java.util.*;
import java.io.*;

public class MoonSearch {

	Scanner scanner;
	FileWriter writer;
	Region region[] = new Region[69];
	Constellation constellation[] = new Constellation[781];
	SolarSystem solarSystem[] = new SolarSystem[5322];
	Moon moon[] = new Moon[336534];
	ComponentCalculator calculator;
	TreeNode constellationRoot, systemRoot;
	
	
	// CONSTRUCTORS
	MoonSearch() throws Exception{
		calculator = new ComponentCalculator();
		constructRegions();
		constructConstellations();
		constructSystems();
		constructMoons();
		insertMinerals();
		insertMoonUsage();
	}
	
	private void constructRegions() throws Exception{
		scanner = new Scanner(new File("data files/regions.txt"));
		scanner.nextLine();
		int temp;
		while(scanner.hasNextLine()){
			temp = scanner.nextInt();
			region[temp - 10000000] = new Region(temp, scanner.nextLine().trim());
		}
	}
	
	private void constructConstellations() throws Exception{
		scanner = new Scanner(new File("data files/constellations.txt"));
		scanner.nextLine();
		int temp;
		while(scanner.hasNextLine()){
			temp = scanner.nextInt();
			region[scanner.nextInt() - 10000000].insert((constellation[temp - 20000000] = new Constellation(temp, scanner.nextLine().trim())));
		}
	}
	
	private void constructSystems() throws Exception{
		scanner = new Scanner(new File("data files/systems.txt"));
		scanner.nextLine();
		int temp;
		while(scanner.hasNextLine()){
			temp = scanner.nextInt();
			constellation[scanner.nextInt() - 20000000].insert((solarSystem[temp - 30000000] = new SolarSystem(temp, scanner.nextLine().trim())));
		}
	}
	
	private void constructMoons() throws Exception{
		scanner = new Scanner(new File("data files/moons.txt"));
		scanner.nextLine();
		int temp;
		while(scanner.hasNextLine()){
			temp = scanner.nextInt();
			solarSystem[scanner.nextInt() - 30000000].insert((moon[temp - 40000000] = new Moon(temp, scanner.nextLine().trim())));
		}
	}	
	
	private void insertMinerals() throws Exception{
		scanner = new Scanner(new File("data files/minerals.txt"));
		scanner.nextLine();
		int temp;
		while(scanner.hasNextInt()){
			temp = scanner.nextInt() - 40000000;
			if(!moon[temp].isUpToDate()){
				moon[temp].insert(scanner.nextInt() - 1);
				moon[temp].insert(scanner.nextInt() - 1);
				moon[temp].insert(scanner.nextInt() - 1);
				moon[temp].insert(scanner.nextInt() - 1);
				moon[temp].setUpToDate(true);
			}
			else
				scanner.nextLine();
		}
	}	
	
	private void insertMoonUsage() throws Exception{
		scanner = new Scanner(new File("data files/moonUsage.txt"));
		while(scanner.hasNextInt())
			moon[scanner.nextInt() - 40000000].setInUse(true);
	}
	
	
	
	// SORTING TOOLS
	public int compare(EVEItem[] array, int index){
		if(array == moon){			
			if(!moon[index].isUpToDate() || moon[index].isInUse())
				return 0;
		}
		else
			array[index].count();		
		array[index].setMatches(0);	
		array[index].setUniqueMatches(0);
		for(int rawIndex = 0; rawIndex < calculator.raw.length; rawIndex++){
			if(calculator.raw[rawIndex].getCountInt() > 0 && array[index].mineralCount[rawIndex] > 0){
				array[index].setUniqueMatches(array[index].getUniqueMatches() + 1);
				if(calculator.raw[rawIndex].getCountInt() < array[index].mineralCount[rawIndex])
					array[index].setMatches(array[index].getMatches() + calculator.raw[rawIndex].getCountInt());
				else
					array[index].setMatches(array[index].getMatches() + array[index].mineralCount[rawIndex]);
			}
		}			
		return array[index].getMatches();
	}

	public void sort(Region currentRegion){
		sortSolarSystems(currentRegion);
		sortConstellations(currentRegion);	
	}
	
	private void sortSolarSystems(Region currentRegion){
		currentRegion.resetCursor();
		currentRegion.head.resetCursor();
		systemRoot = new TreeNode(currentRegion.head.head);
		compare(solarSystem, currentRegion.head.head.getArrayIndex());
		do{				
			while(currentRegion.cursor.cursor.getNext() != currentRegion.cursor.head){
				currentRegion.cursor.cursor = currentRegion.cursor.cursor.getNext();
				compare(solarSystem, currentRegion.cursor.cursor.getArrayIndex());
				sortSolarSystemsSub(currentRegion, systemRoot);
			}
			currentRegion.cursor = currentRegion.cursor.getNext();
			currentRegion.cursor.resetCursor();
		}while(currentRegion.cursor != currentRegion.head);
	}
	
	private void sortSolarSystemsSub(Region currentRegion, TreeNode node){
		if(currentRegion.cursor.cursor.getMatches() != 0){
			SolarSystem nodeElement = (SolarSystem)node.getElement();
			if(currentRegion.cursor.cursor.getMatches() > nodeElement.getMatches()){
				if(node.getLeft() == null)
					node.setLeft(new TreeNode(currentRegion.cursor.cursor));
				else
					sortSolarSystemsSub(currentRegion, node.getLeft());
			}
			else{
				if(node.getRight() == null)
					node.setRight(new TreeNode(currentRegion.cursor.cursor));
				else
					sortSolarSystemsSub(currentRegion, node.getRight());
			}
		}
	}
	
	private void sortConstellations(Region currentRegion){
		currentRegion.resetCursor();
		constellationRoot = new TreeNode(currentRegion.head);
		compare(constellation, currentRegion.head.getArrayIndex());
		while(currentRegion.cursor.getNext() != currentRegion.head){
			currentRegion.cursor = currentRegion.cursor.getNext();
			compare(constellation, currentRegion.cursor.getArrayIndex());
			sortConstellationsSub(currentRegion, constellationRoot);
		}
	}
	
	private void sortConstellationsSub(Region currentRegion, TreeNode node){
		if(currentRegion.cursor.getMatches() != 0){
			Constellation nodeElement = (Constellation)node.getElement();
			if(currentRegion.cursor.getMatches() > nodeElement.getMatches()){
				if(node.getLeft() == null)
					node.setLeft(new TreeNode(currentRegion.cursor));
				else
					sortConstellationsSub(currentRegion, node.getLeft());
			}
			else{
				if(node.getRight() == null)
					node.setRight(new TreeNode(currentRegion.cursor));
				else
					sortConstellationsSub(currentRegion, node.getRight());
			}
		}
	}
	
	
	// DISPLAY TOOLS
	public String showConstellationNames(){
		return show(constellationRoot, true);
	}
	
	public String showSolarSystemNames(){
		return show(systemRoot, true);
	}	

	public String showConstellationNumbers(){
		return show(constellationRoot, false);
	}
	
	public String showSolarSystemNumbers(){
		return show(systemRoot, false);
	}
	
	private String show(TreeNode root, boolean names){
		String temp = "";
		if(names)
			temp = temp + "   ";
		if(root != null){
			EVEItem rootElement = (EVEItem)root.getElement();
			temp = subShow(root.getLeft(), temp, names);
			if(rootElement.getMatches() != 0){
				if(names)
					temp = temp + rootElement.getItemName() + "\n   ";
				else{
					String tempString = "(" + rootElement.getUniqueMatches() + ")   ";
					if(tempString.length() == 6)
						tempString = tempString + "  ";
					temp = temp + tempString + rootElement.getMatches() + "     \n";
				}
			}
			temp = subShow(root.getRight(), temp, names);	
		}
		return temp;
	}
	
	private String subShow(TreeNode node, String temp, boolean names){
		if(node != null){
			EVEItem nodeElement = (EVEItem)node.getElement();
			temp = subShow(node.getLeft(), temp, names);
			if(names)
				temp = temp + nodeElement.getItemName() + "\n   ";
			else{
				String tempString = "(" + nodeElement.getUniqueMatches() + ")   ";
				if(tempString.length() == 6)
					tempString = tempString + "  ";
				temp = temp + tempString + nodeElement.getMatches() + "     \n";
			}
			temp = subShow(node.getRight(), temp, names);				
		}
		return temp;
	}
	
	
	// OTHER METHODS
	public void setMoonUsage(int moonIndex, boolean used) throws Exception{
		scanner = new Scanner(new File("data files/moonUsage.txt"));
		moon[moonIndex].setInUse(used);	
		moon[moonIndex].getParent().count();
		moon[moonIndex].getParent().getParent().count();
		String tempString = "";
		if(used)
			tempString = tempString + moon[moonIndex].getItemID();
		while(scanner.hasNextInt()){
			int tempInt = scanner.nextInt();
			if(tempInt != moon[moonIndex].getItemID())
				tempString = tempString + " " + tempInt;
		}		
		writer = new FileWriter(new File("data files/moonUsage.txt"));
		writer.write(tempString);
		writer.close();
	}
	
	// 40308570 15 	14 	1 	0
	public static void main(String[] args) {
		try{
			MoonSearch search = new MoonSearch();
			System.out.println(search.moon[308551].getItemName());
			System.out.println(search.moon[308551].getParent().getItemName());
			System.out.println(search.moon[308551].getParent().getParent().getItemName());
			System.out.println(search.moon[308551].getParent().getParent().getParent().getItemName());
			search.calculator.raw[0].setCount(14);
			search.calculator.raw[13].setCount(10);
			search.calculator.raw[14].setCount(8);		
		/*
			System.out.println("\n" + search.compare(search.moon,308551));
			for(int i = 0; i < 20; i++){
				System.out.print(search.moon[308551].mineralCount[i] + " ");
			}
			System.out.println("\n" + search.compare(search.solarSystem, 4874));	
			for(int i = 0; i < 20; i++){
				System.out.print(search.solarSystem[4874].mineralCount[i] + " ");
			}	
			System.out.println("\n" + search.compare(search.constellation, 713));	
			for(int i = 0; i < 20; i++){
				System.out.print(search.constellation[713].mineralCount[i] + " ");
			}
		*/
			System.out.println();
			search.sort(search.region[61]);
			System.out.println(search.showConstellationNames());
			System.out.println(search.showConstellationNumbers());
		}
		catch(Exception e){
			System.out.println("Not Found.");
			System.exit(0);
		}
	}
}
