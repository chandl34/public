package map;

import include.Const;

import java.util.HashSet;

public class MapEditor {
	protected static final int FRONT_LEFT = 0;
	protected static final int BACK_RIGHT = 1;
	protected static final int BACK_LEFT = 2;
	protected static final int FRONT_RIGHT = 3;
	protected static final int LEFT = 4;
	protected static final int BACK = 5;
	protected static final int RIGHT = 6;
	protected static final int FRONT = 7;
	protected static final int CENTER = 8;
	protected static final int FRONT_LEFT_INNER = 9;
	protected static final int BACK_RIGHT_INNER = 10;
	protected static final int BACK_LEFT_INNER = 11;
	protected static final int FRONT_RIGHT_INNER = 12;
	protected static final int FRONT_LEFT_AND_BACK_RIGHT = 13;
	protected static final int FRONT_RIGHT_AND_BACK_LEFT = 14;

	protected static final int DIR[][] = {
		{-2, 0},
		{2, 0},
		{0, -2},
		{0, 2},
		{-1, -1},
		{1, -1},
		{1, 1},
		{-1, 1},
	};

	private static int type = Const.GRASS;
	private static HashSet<Block> block = new HashSet<Block>();	
	private static HashSet<IsoBlock> isoBlock = new HashSet<IsoBlock>();	

	public static void toggleType(){
		type = (type+1)%Const.TERRAIN_TYPES;
	}

	public static void setType(int t){
		type = t;
	}

	public static void refreshAll(){
		int x = LevelMap.getSize(0) + 1;
		int y = LevelMap.getSize(1) + 1;
		
		IsoBlock b;
		for(int i = 0; i < x; i++){
			for(int j = 0; j < y; j++){
				b = LevelMap.getIsoBlock(i, j);
				if(b != null)
					refreshTerrain(b);
			}
		}

		for(int i = 0; i < x; i++){
			for(int j = 0; j < y; j++){
				b = LevelMap.getIsoBlock(i, j);
				if(b != null)
					refreshBlocks(b, false);
			}
		}
		
		isoBlock.clear();
		block.clear();
	}
	
	public static void insertType(int i, int j){
		//System.out.println("Block: " + i + " " + j);
		//old school methods first
		setIsoBlockTerrain(i, j, type);	

		Object array[] = isoBlock.toArray();
		for(int c = 0; c < array.length; c++)
			refreshBlocks((IsoBlock)array[c], true);

		isoBlock.clear();
		block.clear();
	}

	static void setIsoBlockTerrain(int i, int j, int t){
		IsoBlock b = LevelMap.getIsoBlock(i, j);	
		if(b != null){
			b.setType(t);
			b.setOtherType(t);	
			for(int x = 0; x < 4; x++)
				b.setCorner(x, t);	
			refreshTerrain(b);	

			setIsoBlockTerrainSub(i, j, t, FRONT);						
			setIsoBlockTerrainSub(i, j, t, BACK);
			setIsoBlockTerrainSub(i, j, t, LEFT);		
			setIsoBlockTerrainSub(i, j, t, RIGHT);		
			setIsoBlockTerrainSub(i, j, t, BACK_LEFT);		
			setIsoBlockTerrainSub(i, j, t, BACK_RIGHT);
			setIsoBlockTerrainSub(i, j, t, FRONT_LEFT);
			setIsoBlockTerrainSub(i, j, t, FRONT_RIGHT);
		}
	}

	static void setIsoBlockTerrainSub(int i, int j, int t, int s){
		i += DIR[s][0];
		j += DIR[s][1];
		IsoBlock b = LevelMap.getIsoBlock(i, j);	
		if(b != null){
			int tMaster = Const.MASTER[t];
			int mainType = b.getType();
			int otherType = b.getOtherType();
			if(t == mainType){
				if(t == otherType)
					return;	
				b.setType(t);
			}
			else if(t == otherType);
			else if(tMaster == mainType && tMaster == otherType)
				b.setOtherType(t);
			else if(Const.MASTER[mainType] == t && Const.MASTER[otherType] == t){
				b.setType(t);
				b.setOtherType(mainType);			
			}
			else{
				boolean isLower = false;
				int temp = Const.MASTER[mainType];
				while(temp != -1){
					if(temp == t){
						isLower = true;
						break;
					}
					temp = Const.MASTER[temp];
				}		
				if(isLower){
					temp = mainType;
					while(Const.MASTER[temp] != t)
						temp = Const.MASTER[temp];
					b.setType(t);
					b.setOtherType(temp);	
					for(int x = 0; x < 4; x++)
						b.setCorner(x, temp);	
				}
				else{
					temp = Const.MASTER[t];
					b.setType(temp);
					b.setOtherType(t);				
					for(int x = 0; x < 4; x++){
						if(b.getCorner(x) != t)
							b.setCorner(x, temp);	
					}									
				}

				switch(s){
				case BACK:
					setIsoBlockTerrainSub(i, j, temp, BACK_LEFT);
					setIsoBlockTerrainSub(i, j, temp, BACK);
					setIsoBlockTerrainSub(i, j, temp, BACK_RIGHT);
					break;
				case FRONT:
					setIsoBlockTerrainSub(i, j, temp, FRONT_LEFT);
					setIsoBlockTerrainSub(i, j, temp, FRONT);
					setIsoBlockTerrainSub(i, j, temp, FRONT_RIGHT);
					break;
				case LEFT:
					setIsoBlockTerrainSub(i, j, temp, FRONT_LEFT);
					setIsoBlockTerrainSub(i, j, temp, LEFT);
					setIsoBlockTerrainSub(i, j, temp, BACK_LEFT);
					break;
				case RIGHT:
					setIsoBlockTerrainSub(i, j, temp, FRONT_RIGHT);
					setIsoBlockTerrainSub(i, j, temp, RIGHT);
					setIsoBlockTerrainSub(i, j, temp, BACK_RIGHT);
					break;					
				case FRONT_LEFT:
					setIsoBlockTerrainSub(i, j, temp, FRONT_LEFT);
					setIsoBlockTerrainSub(i, j, temp, FRONT_RIGHT);
					setIsoBlockTerrainSub(i, j, temp, BACK_LEFT);
					setIsoBlockTerrainSub(i, j, temp, FRONT);	
					setIsoBlockTerrainSub(i, j, temp, LEFT);
					break;
				case FRONT_RIGHT:
					setIsoBlockTerrainSub(i, j, temp, FRONT_RIGHT);
					setIsoBlockTerrainSub(i, j, temp, FRONT_LEFT);
					setIsoBlockTerrainSub(i, j, temp, BACK_RIGHT);
					setIsoBlockTerrainSub(i, j, temp, FRONT);
					setIsoBlockTerrainSub(i, j, temp, RIGHT);
					break;
				case BACK_RIGHT:
					setIsoBlockTerrainSub(i, j, temp, BACK_RIGHT);
					setIsoBlockTerrainSub(i, j, temp, BACK_LEFT);
					setIsoBlockTerrainSub(i, j, temp, FRONT_RIGHT);
					setIsoBlockTerrainSub(i, j, temp, BACK);
					setIsoBlockTerrainSub(i, j, temp, RIGHT);
					break;
				case BACK_LEFT:
					setIsoBlockTerrainSub(i, j, temp, BACK_LEFT);
					setIsoBlockTerrainSub(i, j, temp, FRONT_LEFT);
					setIsoBlockTerrainSub(i, j, temp, BACK_RIGHT);
					setIsoBlockTerrainSub(i, j, temp, LEFT);
					setIsoBlockTerrainSub(i, j, temp, BACK);
					break;

				}
			}	

			if(s == BACK){
				b.setCorner(BACK_RIGHT, t);
				b.setCorner(BACK_LEFT, t);
			}
			else if(s == FRONT){
				b.setCorner(FRONT_RIGHT, t);
				b.setCorner(FRONT_LEFT, t);
			}
			else if(s == RIGHT){
				b.setCorner(FRONT_RIGHT, t);
				b.setCorner(BACK_RIGHT, t);
			}
			else if(s == LEFT){
				b.setCorner(FRONT_LEFT, t);
				b.setCorner(BACK_LEFT, t);
			}
			else
				b.setCorner(s, t);
			refreshTerrain(b);
		}	
	}

	static void refreshTerrain(IsoBlock b){
		isoBlock.add(b);
		if(b.getCorner(BACK_RIGHT) == b.getOtherType()){		
			if(b.getCorner(FRONT_RIGHT) == b.getOtherType()){
				if(b.getCorner(BACK_LEFT) == b.getOtherType()){
					if(b.getCorner(FRONT_LEFT) == b.getOtherType()){ // Block is completely b.getOtherType() now
						b.setType(b.getOtherType());
						b.setSection(CENTER);
						IsoBlock temp;
						for(int i = 4; i <= 7; i++){
							temp = LevelMap.getIsoBlock(
									b.getLoc(0) + DIR[i][0], 
									b.getLoc(1) + DIR[i][1]);							
							if(temp != null)
								isoBlock.add(temp);
						}
					}
					else
						b.setSection(BACK_RIGHT_INNER);
				}
				else{
					if(b.getCorner(FRONT_LEFT) == b.getOtherType())
						b.setSection(FRONT_RIGHT_INNER);
					else
						b.setSection(RIGHT);
				}
			}
			else if(b.getCorner(BACK_LEFT) == b.getOtherType()){
				if(b.getCorner(FRONT_LEFT) == b.getOtherType())
					b.setSection(BACK_LEFT_INNER);
				else
					b.setSection(BACK);			
			}
			else{
				if(b.getCorner(FRONT_LEFT) == b.getOtherType())
					b.setSection(FRONT_LEFT_AND_BACK_RIGHT);		
				else					
					b.setSection(BACK_RIGHT);		
			}
		}	
		else if(b.getCorner(FRONT_LEFT) == b.getOtherType()){
			if(b.getCorner(FRONT_RIGHT) == b.getOtherType()){
				if(b.getCorner(BACK_LEFT) == b.getOtherType())
					b.setSection(FRONT_LEFT_INNER);
				else
					b.setSection(FRONT);	
			}		
			else if(b.getCorner(BACK_LEFT) == b.getOtherType())
				b.setSection(LEFT);
			else
				b.setSection(FRONT_LEFT);
		}
		else if(b.getCorner(FRONT_RIGHT) == b.getOtherType()){
			if(b.getCorner(BACK_LEFT) == b.getOtherType())
				b.setSection(FRONT_RIGHT_AND_BACK_LEFT);	
			else
				b.setSection(FRONT_RIGHT);
		}
		else{ 			
			if(b.getCorner(BACK_LEFT) == b.getType()){			// All other type is wiped out.  Now considers it only mainType
				b.setOtherType(b.getType());
				b.setSection(CENTER);
			}
			else
				b.setSection(BACK_LEFT);
		}
	}	
	
	static void findCorners(IsoBlock b){
		for(int i = 0; i < 4; i++)
			b.setCorner(i, b.getType());
		if(
				b.getSection() == FRONT_LEFT || 
				b.getSection() == FRONT ||
				b.getSection() == LEFT ||
				b.getSection() == FRONT_LEFT_INNER ||
				b.getSection() == FRONT_LEFT_AND_BACK_RIGHT)			
			b.setCorner(FRONT_LEFT, b.getOtherType());
		
		if(b.getSection() == BACK_RIGHT || 
				b.getSection() == BACK ||
				b.getSection() == RIGHT ||
				b.getSection() == BACK_RIGHT_INNER ||
				b.getSection() == FRONT_LEFT_AND_BACK_RIGHT)
			b.setCorner(BACK_RIGHT, b.getOtherType());

		if(b.getSection() == BACK_LEFT || 
				b.getSection() == BACK ||
				b.getSection() == LEFT ||
				b.getSection() == BACK_LEFT_INNER ||
				b.getSection() == FRONT_RIGHT_AND_BACK_LEFT)
			b.setCorner(BACK_LEFT, b.getOtherType());

		if(b.getSection() == FRONT_RIGHT || 
				b.getSection() == FRONT ||
				b.getSection() == RIGHT ||
				b.getSection() == FRONT_RIGHT_INNER ||
				b.getSection() == FRONT_RIGHT_AND_BACK_LEFT)
			b.setCorner(FRONT_RIGHT, b.getOtherType());		
	}
	

	static void refreshBlocks(IsoBlock b, boolean ref){	
		checkSkinny(b, ref);
		checkSkinnyInner(b, ref);
		checkCorner(b, ref);
		checkOthers(b, ref);
	}
	

	static void checkSkinny(IsoBlock b, boolean ref){
		Block bl;
		IsoBlock bTemp;

		if(		b.getSection() == FRONT || 
				b.getSection() == FRONT_RIGHT_INNER || 
				b.getSection() == FRONT_LEFT_INNER || 
				b.getSection() == BACK_RIGHT_INNER){
			bl = b.getBlock(Const.TOP_RIGHT);
			if(bl != null){
				bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[BACK][0], b.getLoc(1) + DIR[BACK][1]);
				if(bTemp != null){
					if(bTemp.getSection() == BACK || bTemp.getSection() == BACK_LEFT_INNER){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.SKINNY);
						bl.setFlip(Const.FLIP);
						bl.refresh(ref);	
					}					
				}	
			}
		}
		if(		b.getSection() == RIGHT || 
				b.getSection() == FRONT_RIGHT_INNER || 
				b.getSection() == FRONT_LEFT_INNER || 
				b.getSection() == BACK_RIGHT_INNER){
			bl = b.getBlock(Const.TOP_LEFT);	
			if(bl != null){
				bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[LEFT][0], b.getLoc(1) + DIR[LEFT][1]);
				if(bTemp != null){
					if(bTemp.getSection() == LEFT || bTemp.getSection() == BACK_LEFT_INNER){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.SKINNY);
						bl.setFlip(Const.NOFLIP);
						bl.refresh(ref);	
					}					
				}	
			}
		}

		if(b.getSection() == BACK || b.getSection() == BACK_LEFT_INNER){
			bl = b.getBlock(Const.BOTTOM_LEFT);	
			if(bl != null){
				bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[FRONT][0], b.getLoc(1) + DIR[FRONT][1]);
				if(bTemp != null){
					if(bTemp.getSection() == FRONT || 
							bTemp.getSection() == FRONT_LEFT_INNER || 
							bTemp.getSection() == FRONT_RIGHT_INNER){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.SKINNY);
						bl.setFlip(Const.FLIP);
						bl.refresh(ref);	
					}					
				}	
			}
		}
		if(b.getSection() == LEFT || b.getSection() == BACK_LEFT_INNER){
			bl = b.getBlock(Const.BOTTOM_RIGHT);	
			if(bl != null){
				bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[RIGHT][0], b.getLoc(1) + DIR[RIGHT][1]);
				if(bTemp != null){
					if(bTemp.getSection() == RIGHT || 
							bTemp.getSection() == FRONT_RIGHT_INNER ||
							bTemp.getSection() == BACK_RIGHT_INNER){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.SKINNY);
						bl.setFlip(Const.NOFLIP);
						bl.refresh(ref);	
					}					
				}	
			}
		}
	}	

	static void checkSkinnyInner(IsoBlock b, boolean ref){
		Block bl;
		IsoBlock bTemp;

		if(b.getSection() == FRONT || b.getSection() == FRONT_LEFT_INNER || b.getSection() == FRONT_RIGHT_INNER){
			bl = b.getBlock(Const.TOP_RIGHT);
			if(bl != null){
				bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[BACK][0], b.getLoc(1) + DIR[BACK][1]);
				if(bTemp != null){
					if(bTemp.getSection() == BACK_RIGHT_INNER){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.SKINNY_INNER);
						bl.setFlip(Const.NOFLIP);
						bl.refresh(ref);	
					}					
				}	
			}
		}
		if(b.getSection() == RIGHT || b.getSection() == BACK_RIGHT_INNER || b.getSection() == FRONT_RIGHT_INNER){
			bl = b.getBlock(Const.TOP_LEFT);	
			if(bl != null){
				bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[LEFT][0], b.getLoc(1) + DIR[LEFT][1]);
				if(bTemp != null){
					if(bTemp.getSection() == FRONT_LEFT_INNER){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.SKINNY_INNER);
						bl.setFlip(Const.FLIP);
						bl.refresh(ref);	
					}					
				}	
			}
		}
		if(b.getSection() == FRONT_LEFT_INNER){
			bl = b.getBlock(Const.BOTTOM_RIGHT);	
			if(bl != null){
				bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[RIGHT][0], b.getLoc(1) + DIR[RIGHT][1]);
				if(bTemp != null){
					if(bTemp.getSection() == RIGHT || 
							bTemp.getSection() == BACK_RIGHT_INNER ||
							bTemp.getSection() == FRONT_RIGHT_INNER){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.SKINNY_INNER);
						bl.setFlip(Const.FLIP);
						bl.refresh(ref);	
					}					
				}	
			}
		}
		if(b.getSection() == BACK_RIGHT_INNER){
			bl = b.getBlock(Const.BOTTOM_LEFT);	
			if(bl != null){
				bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[FRONT][0], b.getLoc(1) + DIR[FRONT][1]);
				if(bTemp != null){
					if(bTemp.getSection() == FRONT || 
							bTemp.getSection() == FRONT_LEFT_INNER ||
							bTemp.getSection() == FRONT_RIGHT_INNER){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.SKINNY_INNER);
						bl.setFlip(Const.NOFLIP);
						bl.refresh(ref);	
					}					
				}	
			}
		}		
	}

	static void checkCorner(IsoBlock b, boolean ref){
		Block bl;
		IsoBlock bTemp;
		int f;
		
		// Corners
		if(b.getSection() == FRONT_LEFT || b.getSection() == FRONT_LEFT_AND_BACK_RIGHT){
			f = Const.NOFLIP;
			bl = b.getBlock(Const.BOTTOM_RIGHT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.CORNER);
				bl.setFlip(f);
				bl.refresh(ref);
			}
			bl = b.getBlock(Const.TOP_RIGHT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.TOP1);
				bl.setFlip(f);
				bl.refresh(ref);
			}
		}
		if(b.getSection() == BACK_RIGHT || b.getSection() == FRONT_LEFT_AND_BACK_RIGHT){
			f = Const.FLIP;
			bl = b.getBlock(Const.BOTTOM_LEFT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.CORNER);
				bl.setFlip(f);
				bl.refresh(ref);
			}
			bl = b.getBlock(Const.TOP_LEFT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.TOP1);
				bl.setFlip(f);
				bl.refresh(ref);
			}
		}

		// Complete areas around corners
		if(b.getSection() == FRONT_LEFT){
			bTemp = LevelMap.getIsoBlock(
					b.getLoc(0) + DIR[FRONT_LEFT][0], 
					b.getLoc(1) + DIR[FRONT_LEFT][1]);
			if(bTemp == null || bTemp.getSection() != FRONT_LEFT){
				bl = b.getBlock(Const.BOTTOM_LEFT);
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(
							b.getLoc(0) + DIR[FRONT][0], 
							b.getLoc(1) + DIR[FRONT][1]);

					if(bTemp == null || 
							(bTemp.getSection() != FRONT &&
									bTemp.getSection() != FRONT_RIGHT_INNER &&
									bTemp.getSection() != FRONT_LEFT_INNER)){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}
				bl = b.getBlock(Const.TOP_LEFT);
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(
							b.getLoc(0) + DIR[LEFT][0], 
							b.getLoc(1) + DIR[LEFT][1]);

					if(bTemp == null || 
							(bTemp.getSection() != LEFT &&
									bTemp.getSection() != BACK_LEFT_INNER &&
									bTemp.getSection() != FRONT_LEFT_INNER)){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}
			}
		}
		if(b.getSection() == BACK_RIGHT){
			bTemp = LevelMap.getIsoBlock(
					b.getLoc(0) + DIR[BACK_RIGHT][0], 
					b.getLoc(1) + DIR[BACK_RIGHT][1]);
			if(bTemp == null || bTemp.getSection() != BACK_RIGHT){
				bl = b.getBlock(Const.BOTTOM_RIGHT);
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(
							b.getLoc(0) + DIR[RIGHT][0], 
							b.getLoc(1) + DIR[RIGHT][1]);

					if(bTemp == null || 
							(bTemp.getSection() != RIGHT &&
									bTemp.getSection() != FRONT_RIGHT_INNER &&
									bTemp.getSection() != BACK_RIGHT_INNER)){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}
				bl = b.getBlock(Const.TOP_RIGHT);
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(
							b.getLoc(0) + DIR[BACK][0], 
							b.getLoc(1) + DIR[BACK][1]);

					if(bTemp == null || 
							(bTemp.getSection() != BACK &&
									bTemp.getSection() != BACK_RIGHT_INNER &&
									bTemp.getSection() != BACK_LEFT_INNER)){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}
			}
		}
		if(b.getSection() == BACK_LEFT){
			bTemp = LevelMap.getIsoBlock(
					b.getLoc(0) + DIR[BACK_LEFT][0], 
					b.getLoc(1) + DIR[BACK_LEFT][1]);
			if(bTemp == null || bTemp.getSection() != BACK_LEFT){
				bl = b.getBlock(Const.TOP_LEFT);
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(
							b.getLoc(0) + DIR[LEFT][0], 
							b.getLoc(1) + DIR[LEFT][1]);
					if(bTemp == null || 
							(bTemp.getSection() != LEFT	&& 
									bTemp.getSection() != FRONT_LEFT_INNER &&
									bTemp.getSection() != BACK_LEFT_INNER)){ 
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}
				bl = b.getBlock(Const.TOP_RIGHT);
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(
							b.getLoc(0) + DIR[BACK][0], 
							b.getLoc(1) + DIR[BACK][1]);

					if(bTemp == null || 
							(bTemp.getSection() != BACK && 
									bTemp.getSection() != BACK_LEFT_INNER &&
									bTemp.getSection() != BACK_RIGHT_INNER)){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}
			}
		}
		if(b.getSection() == FRONT_RIGHT){
			bTemp = LevelMap.getIsoBlock(
					b.getLoc(0) + DIR[FRONT_RIGHT][0], 
					b.getLoc(1) + DIR[FRONT_RIGHT][1]);
			if(bTemp == null || bTemp.getSection() != FRONT_RIGHT){
				bl = b.getBlock(Const.BOTTOM_LEFT);
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(
							b.getLoc(0) + DIR[FRONT][0], 
							b.getLoc(1) + DIR[FRONT][1]);

					if(bTemp == null || 
							(bTemp.getSection() != FRONT &&
									bTemp.getSection() != FRONT_RIGHT_INNER &&
									bTemp.getSection() != FRONT_LEFT_INNER)){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}
				bl = b.getBlock(Const.BOTTOM_RIGHT);				
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(
							b.getLoc(0) + DIR[RIGHT][0], 
							b.getLoc(1) + DIR[RIGHT][1]);

					if(bTemp == null || 
							(bTemp.getSection() != RIGHT &&
									bTemp.getSection() != BACK_RIGHT_INNER &&
									bTemp.getSection() != FRONT_RIGHT_INNER)){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}
			}
		}
	}
	
	static void checkOthers(IsoBlock b, boolean ref){
		Block bl;
		IsoBlock bTemp;
		int f;


		// Centers
		if(b.getSection() == CENTER){
			for(int i = 0; i < 4; i++){
				bl = b.getBlock(i);
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[i+4][0], b.getLoc(1) + DIR[i+4][1]);
					if(bTemp != null && bTemp.getType() == b.getType()){
						block.add(bl);
						bl.setTypes(b.getType(), b.getOtherType());	// both are same
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}
			}
		}

		// Tops
		if(b.getSection() == BACK || b.getSection() == BACK_LEFT_INNER){
			if(b.getSection() == BACK){
				bl = b.getBlock(Const.TOP_RIGHT);
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[BACK][0], b.getLoc(1) + DIR[BACK][1]);
					if(bTemp == null || bTemp.getType() == b.getType()){
						bl.setTypes(b.getType(), b.getOtherType());	// both are same
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}		
			}
			bl = b.getBlock(Const.TOP_LEFT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.TOP1);
				bl.setFlip(Const.FLIP);
				bl.refresh(ref);
			}
			bl = b.getBlock(Const.BOTTOM_LEFT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.TOP2);
				bl.setFlip(Const.NOFLIP);
				bl.refresh(ref);
			}
		}
		if(b.getSection() == LEFT || b.getSection() == BACK_LEFT_INNER){
			if(b.getSection() == LEFT){
				bl = b.getBlock(Const.TOP_LEFT);
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[LEFT][0], b.getLoc(1) + DIR[LEFT][1]);
					if(bTemp == null || bTemp.getType() == b.getType()){
						bl.setTypes(b.getType(), b.getOtherType());	// both are same
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}		
			}
			bl = b.getBlock(Const.TOP_RIGHT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.TOP1);
				bl.setFlip(Const.NOFLIP);
				bl.refresh(ref);
			}
			bl = b.getBlock(Const.BOTTOM_RIGHT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.TOP2);
				bl.setFlip(Const.FLIP);
				bl.refresh(ref);
			}
		}

		// Bottoms
		if(b.getSection() == FRONT || b.getSection() == FRONT_RIGHT_INNER){
			if(b.getSection() == FRONT){
				bl = b.getBlock(Const.BOTTOM_LEFT);
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[FRONT][0], b.getLoc(1) + DIR[FRONT][1]);
					if(bTemp == null || bTemp.getType() == b.getType()){
						bl.setTypes(b.getType(), b.getOtherType());	// both are same
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}		
			}
			bl = b.getBlock(Const.BOTTOM_RIGHT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.BOTTOM1);
				bl.setFlip(Const.NOFLIP);
				bl.refresh(ref);
			}
			bl = b.getBlock(Const.TOP_RIGHT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.BOTTOM2);
				bl.setFlip(Const.FLIP);
				bl.refresh(ref);
			}
		}	
		if(b.getSection() == RIGHT || b.getSection() == FRONT_RIGHT_INNER){
			if(b.getSection() == RIGHT){
				bl = b.getBlock(Const.BOTTOM_RIGHT);
				if(bl != null && !block.contains(bl)){
					bTemp = LevelMap.getIsoBlock(b.getLoc(0) + DIR[RIGHT][0], b.getLoc(1) + DIR[RIGHT][1]);
					if(bTemp == null || bTemp.getType() == b.getType()){
						bl.setTypes(b.getType(), b.getOtherType());	// both are same
						bl.setSection(Const.COMPLETE);
						if(ref)
							bl.setRandomFlip();
						bl.refresh(ref);
					}
				}		
			}
			bl = b.getBlock(Const.BOTTOM_LEFT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.BOTTOM1);
				bl.setFlip(Const.FLIP);
				bl.refresh(ref);
			}
			bl = b.getBlock(Const.TOP_LEFT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.BOTTOM2);
				bl.setFlip(Const.NOFLIP);
				bl.refresh(ref);
			}
		}	

		//Fat Inners or Bottoms
		if(b.getSection() == FRONT_LEFT_INNER){
			f = Const.FLIP;
			bl = b.getBlock(Const.BOTTOM_RIGHT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.FAT_INNER);
				bl.setFlip(f);
				bl.refresh(ref);	
			}		
			bl = b.getBlock(Const.TOP_RIGHT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.BOTTOM2);
				bl.setFlip(f);
				bl.refresh(ref);
			}
		}
		else if(b.getSection() == BACK_RIGHT_INNER){
			f = Const.NOFLIP;
			bl = b.getBlock(Const.BOTTOM_LEFT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.FAT_INNER);
				bl.setFlip(f);
				bl.refresh(ref);
			}
			bl = b.getBlock(Const.TOP_LEFT);
			if(bl != null && !block.contains(bl)){
				block.add(bl);
				bl.setTypes(b.getType(), b.getOtherType());
				bl.setSection(Const.BOTTOM2);
				bl.setFlip(f);
				bl.refresh(ref);
			}
		}
	}
}
