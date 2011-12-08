package ui.popup;

import include.Constant;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLayeredPane;
import javax.swing.JScrollPane;
import javax.swing.JTextPane;

import ui.main.MainWindow;


public class FilterWindow extends JFrame implements ActionListener{

	private JLayeredPane contentPane;
	private JScrollPane scrollPane;
	private JTextPane textPane;
	private JButton saveButton;
		
	
	public FilterWindow(){				
		setTitle("Filters (seperate by spaces)");
		setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		setPreferredSize(new Dimension(Constant.FILTER_WIDTH, 
									   Constant.FILTER_HEIGHT + 22));
		setResizable(false);		

		contentPane = new JLayeredPane();
		contentPane.setOpaque(true); 		
		setContentPane(contentPane);	
		
		textPane = new JTextPane();		
		scrollPane = new JScrollPane(textPane,
									 JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
									 JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);	
		scrollPane.setBounds(0, 0, Constant.FILTER_WIDTH, Constant.FILTER_TEXT_HEIGHT);	
		contentPane.add(scrollPane);
		
		saveButton = new JButton("Save");
		saveButton.setBounds(0, 
							 Constant.FILTER_TEXT_HEIGHT, 
							 Constant.FILTER_WIDTH, 
							 Constant.FILTER_HEIGHT - Constant.FILTER_TEXT_HEIGHT);
		saveButton.addActionListener(this);
		contentPane.add(saveButton);
		
		pack();
		
		textPane.setText(MainWindow.getFightFilters());
	}
	
	
	public void actionPerformed(ActionEvent e) {
		JButton jb = (JButton)e.getSource();
		if(jb == saveButton){			
			if(!textPane.getText().equals(MainWindow.getFightFilters())){
				MainWindow.setFightFilters(textPane.getText());
				textPane.setText(MainWindow.getFightFilters());				
			}			
			setVisible(false);
		}
	}	
}
