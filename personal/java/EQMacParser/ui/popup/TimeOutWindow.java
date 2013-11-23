package ui.popup;

import include.Constant;

import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JLayeredPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

import ui.main.MainWindow;


public class TimeOutWindow extends JFrame implements ActionListener{	

	private JLayeredPane contentPane;
	private JTextField textField;
	
	public TimeOutWindow(){				
		setTitle("");
		setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		setPreferredSize(new Dimension(0, 
									   Constant.TIMEOUT_HEIGHT + 22));
		setResizable(false);		

		contentPane = new JLayeredPane();
		contentPane.setOpaque(true); 		
		setContentPane(contentPane);	

		JTextArea textArea = new JTextArea("Set timeout:");
		textArea.setBounds(5, 7, 70, 20);		
		textArea.setEditable(false);
		textArea.setFocusable(false);
		textArea.setOpaque(false);
		contentPane.add(textArea);
		
		textField = new JTextField("" + MainWindow.getTimeOut());	
		textField.setBounds(75, 5, 45, 20);	
		textField.addActionListener(this);
		contentPane.add(textField);
				
		pack();		
	}

	public void actionPerformed(ActionEvent e){
		String txt = textField.getText();
		
		try{
			int temp = Integer.parseInt(txt);
			if(temp != MainWindow.getTimeOut())
				MainWindow.setTimeOut(temp);
		}
		catch(Exception exc){	
			Toolkit.getDefaultToolkit().beep();			
		}
		
		textField.setText("" + MainWindow.getTimeOut());
		setVisible(false);
	}

}
