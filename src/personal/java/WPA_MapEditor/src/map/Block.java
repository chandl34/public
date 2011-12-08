package map;

import include.Const;

import javax.media.opengl.GL;

import sprites.Sprite;
import catalogs.TerrainCatalog;

public class Block {
	
	private Sprite sprite;
	private int loc[];
	private int offset[];
	private int type, section, flip;
	private int other;
	private int index;
	
	public Block(int x, int y){	
		loc = new int[2];
		loc[0] = x;
		loc[1] = y;
		
		offset = new int[2];
		offset[0] = x*Const.TEX_SIZE[Const.BLOCK_SIZE][0];
		offset[1] = y*Const.TEX_SIZE[Const.BLOCK_SIZE][1];
		type = Const.DEFAULT_TERRAIN;
		other = type;
		section = Const.COMPLETE;
		flip = Math.abs(Const.RANDOM.nextInt())%2;
				
		refresh(true);
	}
	
	public int getLoc(int c){return loc[c];}
	public void setType(int t){type = t;}
	public int getType(){return type;}
	public void setTypes(int m, int o){type = m; other = o;}
	public void setOtherType(int o){other = o;}
	public int getOtherType(){return other;}
	public void setSection(int s){section = s;}
	public int getSection(){return section;}
	public void setIndex(int i){index = i;}
	public int getIndex(){return index;}
	public void setFlip(int f){flip = f;}
	public void setRandomFlip(){flip = Math.abs(Const.RANDOM.nextInt())%2;}
	public int getFlip(){return flip;}
	
	public void refresh(boolean newIndex){
		if(newIndex){
			sprite = TerrainCatalog.getRandomSprite(type, section);
			index = sprite.getIndex();
		}
		else
			sprite = TerrainCatalog.getSprite(type, section, index);
	}
	
	public void draw(GL gl){
		gl.glLoadIdentity();
		gl.glTranslatef(offset[0], -offset[1], 0);
		sprite.draw(gl, flip, Const.BLOCK_SIZE);		
	}
}
