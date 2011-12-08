package io;

import java.io.File;
import java.io.FileOutputStream;
import java.util.Scanner;

import map.Block;
import map.IsoBlock;
import map.LevelMap;
import map.MapEditor;
import window.map.View;

public class MapIO {
	
	public static void saveMap(String filename){
		try{			
			FileOutputStream out = new FileOutputStream(filename, false);
			int temp;
			int x = LevelMap.getSize(0);
			int y = LevelMap.getSize(1);
			temp = x*1000 + y;
			
			out.write((Integer.toHexString(temp) + " ").getBytes());

			Block b;
			for(int i = 0; i < x; i++){
				for(int j = 0; j < y; j++){	
					b = LevelMap.getBlock(i, j);
					temp = b.getIndex()*10;
					temp += b.getFlip();	
					out.write(((Integer.toHexString(temp) + " ").getBytes()));
				}
			}			
			IsoBlock ib;
			for(int i = 0; i < x + 1; i++){
				for(int j = 0; j < y + 1; j++){	
					ib = LevelMap.getIsoBlock(i, j);
					if(ib != null){
						temp = ib.getType()*100000;
						temp += ib.getOtherType()*10000;
						temp += ib.getCorner(0)*1000;
						temp += ib.getCorner(1)*100;
						temp += ib.getCorner(2)*10;
						temp += ib.getCorner(3);
						out.write(((Integer.toHexString(temp) + " ").getBytes()));
					}
				}
			}		

			out.close();
			System.out.println("File saved to " + filename);			
		}catch(Exception e){System.out.println("File failed to save.");}
	}	
	
	public static void loadMap(String filename){
		try{			
			Scanner in = new Scanner(new File(filename));
			
			int temp = Integer.valueOf(in.next(), 16);
			int x = temp/1000;
			int y = temp%1000;
			
			View.setLevelMap(null);
			LevelMap map = new LevelMap(x*2, y);
			
			Block b;
			for(int i = 0; i < x; i++){
				for(int j = 0; j < y; j++){				
					b = LevelMap.getBlock(i, j);
					temp = Integer.valueOf(in.next(), 16);	
					b.setIndex(temp/10);
					b.setFlip(temp%10);
				}				
			}
			IsoBlock ib;
			for(int i = 0; i < x + 1; i++){
				for(int j = 0; j < y + 1; j++){				
					ib = LevelMap.getIsoBlock(i, j);
					if(ib != null){
						temp = Integer.valueOf(in.next(), 16);	
						ib.setType(temp/100000);
						temp %= 100000;
						ib.setOtherType(temp/10000);
						temp %= 10000;
						ib.setCorner(0, temp/1000);
						temp %= 1000;
						ib.setCorner(1, temp/100);
						temp %= 100;
						ib.setCorner(2, temp/10);
						ib.setCorner(3, temp%10);
					}
				}				
			}
			
			MapEditor.refreshAll();

			in.close();
			View.setLevelMap(map);
			System.out.println("Loaded " + filename);			
		}catch(Exception e){System.out.println("Failed to load " + filename);}
	}	
	
}