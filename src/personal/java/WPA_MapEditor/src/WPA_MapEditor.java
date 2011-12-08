
import include.Const;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

import window.Window;


public class WPA_MapEditor {	

	public static void extractLibraries(){		
		int os = -1, arch = -1;
		String temp = System.getProperty("os.name");
		System.out.println(temp);
		if(temp.startsWith("Windows"))
			os = Const.WINDOWS;		
		else if(temp.startsWith("Linux"))
			os = Const.LINUX;
		else if(temp.startsWith("Mac"))
			os = Const.MACOSX;
		
		temp = System.getProperty("os.arch");
		System.out.println(temp);
		if(temp.startsWith("x86") || temp.startsWith("i386"))
			arch = Const.I386;		
		else if(temp.startsWith("amd 64"))
			arch = Const.AMD64;
		
		String basePath = "/libraries/" + Const.OS_NAME[os] + "/" + Const.ARCHITECTURE[arch] + "/";
		String remPath = "";
		
		byte bytes[] = new byte[10000];
		for(int i = 0; i < Const.LIBRARIES_NEEDED; i++){
			try{				
				remPath = Const.LIBRARY[i] + Const.EXTENSION[os];
				if(os != Const.WINDOWS)
					remPath = "lib" + remPath;
				
				InputStream in = Window.class.getResourceAsStream(basePath + remPath);

				boolean createFile = true;
				File test = new File(remPath);
				if(test.exists()){
					if(test.length() == in.available())
						createFile = false;
				}
				
				if(createFile){		
					System.out.println("Building " + remPath + "...");
					test = new File(basePath + remPath);
					FileOutputStream out = new FileOutputStream(new File(remPath), false);
					
					int done = in.read(bytes);
					while(done != -1){
						out.write(bytes, 0, done);
						done = in.read(bytes);
					}
					in.close();
					out.close();		
				}
			}catch(Exception e){System.out.println("Could not " + basePath + remPath);}
		}
	}
		
	public static void main(String[] args) {
		extractLibraries();		
		System.out.println("Loading window...");
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				Window.createAndShowGUI();
			}
		});
	}

}
