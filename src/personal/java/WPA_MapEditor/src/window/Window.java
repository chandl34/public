package window;


import include.Const;

import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JLayeredPane;

import window.map.MapPanel;
import window.menu.MenuBar;
import window.minimap.MiniMapPanel;
import window.tool.ToolPanel;


public class Window {	
	public static JFrame frame;
	private static JLayeredPane contentPane;
	private static MapPanel mapPanel;
	private static MiniMapPanel miniMapPanel;
	private static ToolPanel toolPanel;
	private static MenuBar menuBar;
	private static KeyboardInput keyInput;
	
	
	public static void createAndShowGUI() {
		frame = new JFrame("When Pirates Attack! - Map Editor");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false);

		contentPane = new JLayeredPane();
		contentPane.setOpaque(true); 
		frame.setContentPane(contentPane);	
		frame.setPreferredSize(new Dimension(
				Const.WINDOW_WIDTH, 
				Const.WINDOW_HEIGHT));
		
		keyInput = new KeyboardInput();
		frame.addKeyListener(keyInput);

		menuBar = new MenuBar();
		frame.setJMenuBar(menuBar);
		
		toolPanel = new ToolPanel();
		contentPane.add(toolPanel);	
		
		mapPanel = new MapPanel();
		contentPane.add(mapPanel);

		miniMapPanel = new MiniMapPanel();
		contentPane.add(miniMapPanel);
	
		frame.pack();
		frame.setVisible(true); 
	}
}
