package window.menu;

import java.io.File;


public class FileFilter extends javax.swing.filechooser.FileFilter{

	private String extension;
	
	public FileFilter(String ext){
		extension = ext;
	}
	
	public boolean accept(File e){
		return e.getName().substring(e.getName().lastIndexOf('.')+1).equals(extension);
	}

	public String getDescription(){		
		return extension;
	}

}
