package override;

import java.io.File;
import java.util.Vector;

public class FileFilter extends javax.swing.filechooser.FileFilter {

	Vector<String> filter;
	
	
	public FileFilter(){
		filter = new Vector<String>();		
	}
	
	
	public boolean accept(File f) {
		if (f.isDirectory()) {
            return true;
        }
		
		
		String extension = f.getName();
		extension = extension.substring(extension.lastIndexOf(".") + 1);		
		if(extension != null){
			for(int i = 0; i < filter.size(); i++){				
				if(filter.get(i).equalsIgnoreCase(extension))
					return true;
			}
		}

		return false;
	}

	public String getDescription() {
		String f = "";
		for(int i = 0; i < filter.size(); i++)
			f += filter.get(i) + " ";		
		return f;
	}
	
	public void addFilter(String f){
		filter.add(f);
	}

}
