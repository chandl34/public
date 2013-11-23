package io;

import include.ConstAssist;

import java.util.Scanner;

import javax.media.opengl.GL;

import sprites.Sprite;
import catalogs.TerrainCatalog;

import com.sun.opengl.util.texture.TextureData;
import com.sun.opengl.util.texture.TextureIO;

public class Loader {

	private static GL gl;
	
	public static Sprite loadImage(GL g, String filename){
		gl = g;
		int texName = setupTexName();
		TextureData texData = setupTextureData(filename);
		return new Sprite(texName, ConstAssist.getTexSize(texData.getWidth(), texData.getHeight()));
	}
	
	public static void loadTerrain(GL g, String filename){
		try{
			gl = g;
			Scanner reader = new Scanner(Loader.class.getResourceAsStream("/resources/" + filename));
			int texName = setupTexName();
			TextureData texData = setupTextureData(reader.next());
			
			int type = reader.nextInt();
			int section, x, y, s;
			Sprite sprite;
			while(reader.hasNext()){
				section = reader.nextInt();
				x = reader.nextInt();
				y = reader.nextInt();
				s = reader.nextInt();
				sprite = new Sprite(texName, x, y, s, 
						ConstAssist.getTexSize(texData.getWidth(), texData.getHeight()));
				TerrainCatalog.add(type, section, sprite);
			}
			reader.close();
		}catch(Exception e){
			System.out.println("Could not load " + filename);
		}
	}
	
	private static int setupTexName(){
		int texName[] = new int[1];
		gl.glGenTextures(1, texName, 0);
		gl.glBindTexture(GL.GL_TEXTURE_2D, texName[0]);
		return texName[0];
	}
	
	private static TextureData setupTextureData(String filename){
		try{
			TextureData texData = TextureIO.newTextureData(
					Loader.class.getResource("/images/" + filename), false, "png");	
			
			gl.glTexParameteri(GL.GL_TEXTURE_2D, GL.GL_TEXTURE_MIN_FILTER, GL.GL_NEAREST);
			gl.glTexParameteri(GL.GL_TEXTURE_2D, GL.GL_TEXTURE_MAG_FILTER, GL.GL_NEAREST);
			
			gl.glTexImage2D(GL.GL_TEXTURE_2D, 0, texData.getInternalFormat(), 
					texData.getWidth(), texData.getHeight(), 0, texData.getInternalFormat(), 
					texData.getPixelType(), texData.getBuffer());
			return texData;
		}catch(Exception e){
			System.out.println("Could not load " + filename);
		}
		return null;
	}
}
