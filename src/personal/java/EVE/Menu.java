import java.awt.*;

import javax.swing.*;

import java.awt.event.*;

public class Menu extends JFrame implements ActionListener{
	JFrame searchFrame, moonUsageFrame;
	JTextField searchField, moonUsageField;
	JButton setUsed, setNotUsed;
	MoonSearch search;
	JMenuItem openSearch, setUsage;
	JTextArea bpText, ratioNameText, ratioNumberText, constellationNameText, constellationNumberText, systemNameText, systemNumberText;
	JTextArea searchText, moonUsageText;
	String ratioName, ratioNumber;
	JComboBox componentBox, peBox, regionBox;	
	double pe;
	int component, regionIndex;
	
	Menu(String title){
		super(title);
	}
	
	private void createMoonUsageWindow(){
		moonUsageFrame = new JFrame("Moon Availability");
		moonUsageFrame.setLayout(new BorderLayout());
		moonUsageFrame.setLocation(new Point(80, 80));
		moonUsageFrame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		moonUsageFrame.setResizable(false);
		
		moonUsageText = new JTextArea();
		moonUsageText.setText("          Enter moonID to set availability");
		moonUsageText.setEditable(false);
		moonUsageFrame.add(moonUsageText, "North");
		
		moonUsageField = new JTextField(6);
		moonUsageFrame.add(moonUsageField, "West");
		
		setUsed = new JButton("in use");
		setUsed.addActionListener(this);
		moonUsageFrame.add(setUsed, "Center");
		
		setNotUsed = new JButton("not in use");
		setNotUsed.addActionListener(this);
		moonUsageFrame.add(setNotUsed, "East");
		
		moonUsageFrame.setVisible(true);
		moonUsageFrame.pack();
	}
	
	private void createSearchWindow() {
		searchFrame = new JFrame("Constellation and Solar System Search");
		searchFrame.setLayout(new BorderLayout());
		searchFrame.setLocation(new Point(40, 40));		
		searchFrame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		searchFrame.setResizable(false);
		
		searchText = new JTextArea(15, 25);
		searchText.setEditable(false);
		searchText.setText("\n\n\n\n\n   Enter exact Constellation or SolarSystem name.");
		
		JScrollPane scrollPane = new JScrollPane(searchText,
				JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
				JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		searchFrame.add(scrollPane, "North");
		
		JLabel textFieldLabel = new JLabel("Search:  ");
		searchFrame.add(textFieldLabel, "West");
		
		searchField = new JTextField();
		searchField.addActionListener(this);
		searchFrame.add(searchField, "Center");
		
		searchFrame.setVisible(true);
		searchFrame.pack();
	}
	    
	public void actionPerformed(ActionEvent e) {
        JComboBox cb = new JComboBox();
        JTextField tf = new JTextField();
        JMenuItem mi = new JMenuItem();
        JButton jb = new JButton();
        if(e.getSource().getClass().equals(cb.getClass())){
        	cb = (JComboBox)e.getSource();
        	if(cb.equals(componentBox))
        		component = cb.getSelectedIndex();
        	else if(cb.equals(peBox))
        		pe = cb.getSelectedIndex();   
        	else if(cb.equals(regionBox)){
        		for(int i = 1; i < search.region.length; i++){
        			if(search.region[i] != null && search.region[i].getItemName().equals(cb.getSelectedItem())){
        				regionIndex = search.region[i].getItemID() - 10000000;
        				break;
        			}
        		}
        	}
        	bpText.setText(search.calculator.showMaterials(component));
        	search.calculator.count(component, pe);
        	search.calculator.sort(search.calculator.raw, 10);
        	ratioName = "******Materials Per Component***\n\n- Raw\n" + search.calculator.showRatioNames();
        	ratioNumber = "***\n\n\n" + search.calculator.showRatioNumbers();
        
        	search.calculator.sort(search.calculator.simple, 10);
        	ratioName = ratioName + "\n- Simple\n" + search.calculator.showRatioNames();
        	ratioNumber = ratioNumber + "\n\n" + search.calculator.showRatioNumbers();
        
        	search.calculator.sort(search.calculator.complex, 1);
        	ratioName = ratioName + "\n- Complex\n" + search.calculator.showRatioNames();
        	ratioNumber = ratioNumber + "\n\n" + search.calculator.showRatioNumbers();
        
        	ratioNameText.setText(ratioName);
        	ratioNumberText.setText(ratioNumber);
        
        	search.sort(search.region[regionIndex]);
        
        
        	String tempString = "(" + search.calculator.getTotalUniqueRawCount() + ")   ";
        	if(tempString.length() == 6)
        		tempString = tempString + "  ";
        	constellationNameText.setText("*******Constellation Ma\n\nMatches Needed:" + "\n" + search.showConstellationNames());
        	constellationNumberText.setText("tches*******\n\n" + tempString + search.calculator.getTotalRawCount() + "\n" + search.showConstellationNumbers());
        
        	tempString = "(" + search.calculator.getTotalUniqueRawCount() + ")   ";
        	if(tempString.length() == 6)
        		tempString = tempString + "  ";
        	systemNameText.setText("******Solar System Ma\n\nMatches Needed:" + "\n" + search.showSolarSystemNames());
        	systemNumberText.setText("tches******\n\n" + tempString + search.calculator.getTotalRawCount() + "\n" + search.showSolarSystemNumbers());
        }
        else if(e.getSource().getClass().equals(tf.getClass())){
        	tf = (JTextField)e.getSource();
        	if(tf.equals(searchField)){
        		for(int constellationIndex = 0; constellationIndex < search.constellation.length; constellationIndex++){
        			if(search.constellation[constellationIndex] != null){
        				if(tf.getText().trim().equalsIgnoreCase(search.constellation[constellationIndex].getItemName())){
        					searchText.setText(search.constellation[constellationIndex].getInfo(search.calculator.raw) + search.constellation[constellationIndex].getSubInfo(search.calculator.raw));
        					return;
        				}
        			}
        		}
        		for(int systemIndex = 0; systemIndex < search.solarSystem.length; systemIndex++){
        			if(search.solarSystem[systemIndex] != null){
        				if(tf.getText().trim().equalsIgnoreCase(search.solarSystem[systemIndex].getItemName())){
        					searchText.setText("SYSTEM TOTALS:\n\n" + search.solarSystem[systemIndex].getInfo(search.calculator.raw) + search.solarSystem[systemIndex].getSubInfo(search.calculator.raw));
        					return;
        				}
        			}
        		}
        		searchText.setText("\n\n\n\n\n   Enter exact Constellation or SolarSystem name." +
        				"\n\n\n            Constellation\\SolarSystem not found!");
        	}
        }
        else if(e.getSource().getClass().equals(mi.getClass())){
        	mi = (JMenuItem)e.getSource();
        	if(mi.equals(openSearch)){
        		if(!searchFrame.isShowing())
        			createSearchWindow();
        		else
        			searchFrame.toFront();
        	}
        	else if(mi.equals(setUsage)){
        		if(!moonUsageFrame.isShowing())
        			createMoonUsageWindow();
        		else
        			moonUsageFrame.toFront();        		
        	}
        }
        else if(e.getSource().getClass().equals(jb.getClass())){
        	jb = (JButton)e.getSource();
        	if(jb.equals(setUsed) || jb.equals(setNotUsed)){
        		int temp = 0;
        		try{
        			temp = Integer.parseInt(moonUsageField.getText().trim()) - 40000000;        		
        		}catch(Exception exc){}
        		if(temp > 336533 || temp < 666 || search.moon[temp] == null)
        			moonUsageText.setText("                         Invalid moonID");    
        		else if(jb.equals(setUsed)){
        			moonUsageText.setText("         " + search.moon[temp].getItemName() + " set used");
        			try{search.setMoonUsage(temp, true);}catch(Exception exc){}
        		}       
        		else{
        			moonUsageText.setText("         " + search.moon[temp].getItemName() + " set available"); 
        			try{search.setMoonUsage(temp, false);}catch(Exception exc){}
        		}
        	}        	
        }
	}	
	
	private void createAndShowGUI() throws Exception{
		search = new MoonSearch();		
		
        //Set up the window.
		setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        setResizable(false);        
                
        searchFrame = new JFrame();
        moonUsageFrame = new JFrame();
        
        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Main");
        
        openSearch = new JMenuItem("Open search window");
        openSearch.addActionListener(this);
        menu.add(openSearch);
        
        setUsage = new JMenuItem("Set moon availability");
        setUsage.addActionListener(this);
        menu.add(setUsage);
        
        menuBar.add(menu);
        
        setJMenuBar(menuBar);
        
        //Set up text area
        bpText = new JTextArea();
        bpText.setEditable(false);
        bpText.setText(search.calculator.showMaterials(0));
        bpText.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(Color.black),
                BorderFactory.createEmptyBorder(5,5,5,5)));
        
        JPanel ratioPanel = new JPanel(new BorderLayout());
        ratioPanel.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(Color.black),
                BorderFactory.createEmptyBorder(5,5,5,5)));
        
        component = 0;
        pe = 5;        
        search.calculator.count(component, pe);        
        
        ratioNameText = new JTextArea();
        ratioNameText.setEditable(false);
        ratioNumberText = new JTextArea();
        ratioNumberText.setEditable(false);
        
        search.calculator.sort(search.calculator.raw, 10);
        ratioName = "******Materials Per Component***\n\n- Raw\n" + search.calculator.showRatioNames();
        ratioNumber = "***\n\n\n" + search.calculator.showRatioNumbers();
        
        search.calculator.sort(search.calculator.simple, 10);
        ratioName = ratioName + "\n- Simple\n" + search.calculator.showRatioNames();
        ratioNumber = ratioNumber + "\n\n" + search.calculator.showRatioNumbers();
        
        search.calculator.sort(search.calculator.complex, 1);
        ratioName = ratioName + "\n- Complex\n" + search.calculator.showRatioNames();
        ratioNumber = ratioNumber + "\n\n" + search.calculator.showRatioNumbers();
        
        ratioNameText.setText(ratioName);
        ratioNumberText.setText(ratioNumber);
        ratioPanel.add(ratioNameText, "Center");
        ratioPanel.add(ratioNumberText, "East");
        
        regionIndex = 61;
        search.sort(search.region[regionIndex]);
        
        JPanel constellationPanel = new JPanel(new BorderLayout());
        constellationPanel.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(Color.black),
                BorderFactory.createEmptyBorder(5,5,5,5)));        
        
        constellationNameText = new JTextArea();
        constellationNameText.setEditable(false);
        constellationNumberText = new JTextArea();
        constellationNumberText.setEditable(false);
        
        String tempString = "(" + search.calculator.getTotalUniqueRawCount() + ")   ";
		if(tempString.length() == 6)
			tempString = tempString + "  ";
        constellationNameText.setText("*******Constellation Ma\n\nMatches Needed:" + "\n" + search.showConstellationNames());
        constellationNumberText.setText("tches*******\n\n" + tempString + search.calculator.getTotalRawCount() + "\n" + search.showConstellationNumbers());
        constellationPanel.add(constellationNameText, "Center");
        constellationPanel.add(constellationNumberText, "East");
        
        JPanel systemPanel = new JPanel(new BorderLayout());
        systemPanel.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(Color.black),
                BorderFactory.createEmptyBorder(5,5,5,5)));        
        
        systemNameText = new JTextArea();
        systemNameText.setEditable(false);
        systemNumberText = new JTextArea();
        systemNumberText.setEditable(false);
        
        tempString = "(" + search.calculator.getTotalUniqueRawCount() + ")   ";
		if(tempString.length() == 6)
			tempString = tempString + "  ";
        systemNameText.setText("******Solar System Ma\n\nMatches Needed:" + "\n" + search.showSolarSystemNames());
        systemNumberText.setText("tches******\n\n" + tempString + search.calculator.getTotalRawCount() + "\n" + search.showSolarSystemNumbers());
        systemPanel.add(systemNameText, "Center");
        systemPanel.add(systemNumberText, "East");
        
        JPanel areaPanel = new JPanel(new BorderLayout());
        areaPanel.add(constellationPanel, "Center");
        areaPanel.add(systemPanel, "East");
        
        //Set up drop boxes
        JPanel boxPanel = new JPanel(new FlowLayout());
        boxPanel.setBorder(BorderFactory.createLineBorder(Color.black));        
        
        JLabel componentBoxLabel = new JLabel("Component: ");
        boxPanel.add(componentBoxLabel);
        
        String[] compList = new String[36];
        for(int i = 0; i < 36; i++)
        	compList[i] = search.calculator.component[i].getName();        
  		componentBox = new JComboBox(compList);
        componentBox.addActionListener(this);
        boxPanel.add(componentBox);
        
        JLabel peBoxLabel = new JLabel("               Production Efficiency: ");
        boxPanel.add(peBoxLabel);
        
        String[] peList = new String[6];
        for(int i = 0; i < 6; i++)
        	peList[i] = "" + i;  
        peBox = new JComboBox(peList);
        peBox.setSelectedIndex(5);
        peBox.addActionListener(this);
        boxPanel.add(peBox);
        
        JLabel regionBoxLabel = new JLabel("               Region: ");
        boxPanel.add(regionBoxLabel);
        
        String[] regionList = new String[66];
        int stringIndex = 0;
        for(int i = 0; i < 69; i++){
        	if(search.region[i] != null){
        		regionList[stringIndex] = search.region[i].getItemName();
        		stringIndex++;
        	}
        }
        regionBox = new JComboBox(regionList);
        regionBox.setSelectedIndex(58);
        regionBox.addActionListener(this);
        boxPanel.add(regionBox);
        	
        //Compile the frame
        add(bpText, "West");
        add(ratioPanel, "Center");
        add(areaPanel, "East");
        add(boxPanel, "South");
        pack();        
    }    
	
	public static void main(String[] args) {
        //Schedule a job for the event-dispatching thread:
        //creating and showing this application's GUI.   	
    	
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
            	try{
            		Menu menu = new Menu("Component Calculator");
            		menu.createAndShowGUI();
            	}
            	catch(Exception e){
            		System.out.println("File Not Found.");
            		System.exit(0);
            	}
            }
        });
    }
}
