package window.tool;

import include.Const;

import java.awt.Color;

import javax.swing.BorderFactory;
import javax.swing.JLayeredPane;
import javax.swing.JMenuBar;

public class ToolPanel extends JLayeredPane{

	public ToolPanel(){
		setBounds(0, 0, Const.WINDOW_WIDTH - Const.JAVA_ERROR[0], Const.TOOLPANEL_HEIGHT);
		setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(Color.black),
                BorderFactory.createEmptyBorder(5,5,5,5)));
	}
}
