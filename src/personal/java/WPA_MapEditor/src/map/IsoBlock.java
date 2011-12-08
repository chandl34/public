package map;

import include.Const;


public class IsoBlock {
	private Block block[];
	private int mainType;
	private int otherType;
	private int section;
	private int corner[];
	private int loc[];


	public IsoBlock(int x, int y){
		mainType = Const.DEFAULT_TERRAIN;
		otherType = mainType;
		section = MapEditor.CENTER;

		loc = new int[2];
		loc[0] = x;
		loc[1] = y;
		
		corner = new int[4];
		for(int i = 0; i < 4; i++)
			corner[i] = otherType;

		block = new Block[4];
		block[Const.TOP_LEFT] = LevelMap.getBlock(x-1, y-1);
		block[Const.TOP_RIGHT] = LevelMap.getBlock(x, y-1);
		block[Const.BOTTOM_RIGHT] = LevelMap.getBlock(x, y);
		block[Const.BOTTOM_LEFT] = LevelMap.getBlock(x-1, y);		
	}

	public void setTerrain(int m, int o, int s){
		mainType = m;
		otherType = o;
		section = s;
	}

	public int getLoc(int c){return loc[c];}
	public Block getBlock(int c){return block[c];}
	public void setType(int m){mainType = m;}
	public int getType(){return mainType;}
	public void setOtherType(int t){otherType = t;}
	public int getOtherType(){return otherType;}
	public void setSection(int s){section = s;}
	public int getSection(){return section;}
	public void setCorner(int c, int h){corner[c] = h;}	
	public int getCorner(int c){return corner[c];}
}
