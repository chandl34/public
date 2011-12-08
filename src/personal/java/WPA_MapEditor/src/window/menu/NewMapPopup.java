package window.menu;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;

import map.LevelMap;
import window.Window;
import window.map.View;

public class NewMapPopup extends JFrame implements ActionListener{

	private static JLayeredPane contentPane;
	private static JComboBox width, height;
	private static JButton ok;
	private static String[] option = {"64", "96", "128"};
	
	
	public NewMapPopup(){
		setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		setResizable(false);

		contentPane = new JLayeredPane();
		contentPane.setOpaque(true); 
		setContentPane(contentPane);	
		setPreferredSize(new Dimension(124, 100));
		
		JLabel label = new JLabel("    Width     Height");
		label.setBounds(4, 0, 104, 20);
		contentPane.add(label);
		
		width = new JComboBox(option);
		width.setBounds(8, 20, 48, 20);
		contentPane.add(width);	
		
		height = new JComboBox(option);	
		height.setBounds(60, 20, 48, 20);
		contentPane.add(height);
		
		ok = new JButton("OK");
		ok.setBounds(21, 44, 80, 20);
		ok.addActionListener(this);
		contentPane.add(ok);	
		
		pack();	
	}
	
	public void popup(){
		setLocation(Window.frame.getX() + 64, Window.frame.getY() + 64);
		setVisible(true);
	}

	public void actionPerformed(ActionEvent e) {
		int w = Integer.parseInt(option[width.getSelectedIndex()]);
		int h = Integer.parseInt(option[height.getSelectedIndex()]);
		View.setLevelMap(new LevelMap(w, h));	
		setVisible(false);		
	}
}
