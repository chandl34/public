package window.menu;

import io.MapIO;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.JFileChooser;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

import map.LevelMap;
import window.map.View;

public class MenuBar extends JMenuBar implements ActionListener{
	
	private static NewMapPopup newMapPopup;
	private static JMenuItem newMap, save, load;
	private static JFileChooser chooser;
	private static FileFilter map;
	
	public MenuBar(){		
        JMenu menu = new JMenu("File");
        add(menu);       

        newMap = new JMenuItem("New");
        newMap.addActionListener(this);
        menu.add(newMap);
        
        save = new JMenuItem("Save");
        save.addActionListener(this);
        menu.add(save);
        
        load = new JMenuItem("Load");
        load.addActionListener(this);
        menu.add(load);       
                
        newMapPopup = new NewMapPopup();
        
        chooser = new JFileChooser();
        try{
        	File dir = new File("maps");
        	if(dir.exists() || dir.mkdir()) 	       	
        		chooser.setCurrentDirectory(dir);
        }catch(Exception e){}
        map = new FileFilter("map");       
        chooser.setAcceptAllFileFilterUsed(false);
        chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
	}

	public void actionPerformed(ActionEvent e){
		JMenuItem item = (JMenuItem)e.getSource();        
        chooser.setFileFilter(map);

		if(item == newMap)
			newMapPopup.popup();
		else{
			String temp;
			boolean failed = true;
			if(item == save){
				int returnVal = chooser.showSaveDialog(this);
				if (returnVal == JFileChooser.APPROVE_OPTION){
					temp = chooser.getSelectedFile().getName();
					if(temp.charAt(0) != '.'){
						MapIO.saveMap(getFullName(temp));
						failed = false;
					}
				}
			}
			else if(item == load){
				int returnVal = chooser.showOpenDialog(this);
				if (returnVal == JFileChooser.APPROVE_OPTION){
					temp = chooser.getSelectedFile().getName();
					if(temp.charAt(0) != '.'){
						MapIO.loadMap(getFullName(temp));
						failed = false;
					}
				}
			}
			if(failed)
				System.out.println("Operation failed");
		}
	}	
	
	public String getFullName(String fn){
		if(!fn.endsWith("." + chooser.getFileFilter().getDescription()))
			fn += "." + chooser.getFileFilter().getDescription();
		fn = chooser.getCurrentDirectory().getName() + "/" + fn;		
		return fn;
	}
}
