package ui.main;

import include.Constant;

import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.util.Vector;

import javax.swing.JLayeredPane;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextPane;

import override.TableModel;

public class DataPane extends JLayeredPane implements ComponentListener {
	
	private JTable table;
	private TableModel tableModel;
	private JTextPane statusPane;
	private JScrollPane dataPane;
	
	
	public DataPane(){
		addComponentListener(this);
		
		statusPane = new JTextPane();
		statusPane.setFocusable(false);
		add(statusPane);		
		
		dataPane = new JScrollPane();
		
		tableModel = new TableModel();
		tableModel.addColumn("Name");
		tableModel.addColumn("Damage");
		tableModel.addColumn("Seconds");
		tableModel.addColumn("DPS");
					
		table = new JTable(tableModel);
		table.setFocusable(false);
		table.getTableHeader().setReorderingAllowed(false);
		
		add(dataPane);
	}
	
	
	public void updateData(Vector<String[]> data){
		while(tableModel.getRowCount() > 0)
			tableModel.removeRow(0);
		if(data != null){
			for(int i = 0; i < data.size(); i++)
				tableModel.addRow(data.get(i));
		}
	}	

	
	public void setStatus(String s){
		statusPane.setText(s);
	}


	public void componentResized(ComponentEvent e){
		statusPane.setBounds(0, 0, getWidth(), Constant.STATUS_HEIGHT);
		dataPane.setBounds(0, Constant.STATUS_HEIGHT, getWidth(), getHeight() - Constant.STATUS_HEIGHT);
		dataPane.setViewportView(table);
	}
	
	public void componentMoved(ComponentEvent e){}
	public void componentShown(ComponentEvent e){}
	public void componentHidden(ComponentEvent e){}
}
