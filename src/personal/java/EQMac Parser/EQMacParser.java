import ui.main.MainWindow;


public class EQMacParser {

	public static void main(String[] args) {
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {	
				MainWindow mw = new MainWindow();
				mw.createAndShowGUI();
			}
		});		
	}

}
