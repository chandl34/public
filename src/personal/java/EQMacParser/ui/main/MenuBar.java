package ui.main;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JCheckBoxMenuItem;
import javax.swing.JFileChooser;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

import override.FileFilter;

public class MenuBar extends JMenuBar 
					 implements ActionListener {
	
	private JMenuItem open, filter, timeOut;
	private JCheckBoxMenuItem parse;
	
	private JFileChooser fc;
	
	
	public MenuBar(){
		JMenu menu = new JMenu("File");
		add(menu);
		
		open = new JMenuItem("Open");
		open.addActionListener(this);
        menu.add(open);   

        menu.addSeparator();
        
        parse = new JCheckBoxMenuItem("Parse");
		parse.addActionListener(this);
		parse.setEnabled(false);
        menu.add(parse);
        
        
		JMenu options = new JMenu("Options");
		add(options);
        
        filter = new JMenuItem("Filter");
        filter.addActionListener(this);
        options.add(filter);   

        timeOut = new JMenuItem("Timeout");
        timeOut.addActionListener(this);
        options.add(timeOut);   
        
        
        // Add .txt filter for Open menu option
        fc = new JFileChooser();
        FileFilter ff = new FileFilter();
        ff.addFilter("txt");
        fc.setAcceptAllFileFilterUsed(false);
        fc.setFileFilter(ff);
	}

	
	public void actionPerformed(ActionEvent e) {
		JMenuItem source = (JMenuItem)e.getSource();
		if(source == open){
			if(fc.showOpenDialog(this) == JFileChooser.APPROVE_OPTION){
				parse.setEnabled(true);
				parse.setState(true);
				MainWindow.openNewLogFile(fc.getSelectedFile());
			}
		}
		else if(source == parse)
			MainWindow.toggleParsing();
		else if(source == filter)
			MainWindow.showFilterWindow();
		else if(source == timeOut)
			MainWindow.showTimeOutWindow();
	}
	
}
