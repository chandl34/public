package ui.main;

import java.util.Vector;

import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;


public class ListPane extends JScrollPane 
					  implements ListSelectionListener {
		
	private JList jList;
	
	
	public ListPane(){					
		jList = new JList();
		jList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);   
		jList.addListSelectionListener(this);
		setViewportView(jList);				
	}

	
	public void valueChanged(ListSelectionEvent e) {		
	//	if(!e.getValueIsAdjusting()){
			JList list = (JList)e.getSource();
			MainWindow.selectFight(list.getSelectedIndex());
	//	}
	}
	
	
	public void updateList(Vector<String> s){
		jList.removeAll();							// Using this removeAll() seems to prevent it from bugging out
		if(s != null)
			jList.setListData(s);						// but who knows?
	}
	
}
