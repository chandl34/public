package catalogs;


import include.Const;

import java.util.ArrayList;

import sprites.Sprite;


public class TerrainCatalog {
	
	private static ArrayList<ArrayList<ArrayList<Sprite>>> terrain;
	
		
	public TerrainCatalog(){
		terrain = new ArrayList<ArrayList<ArrayList<Sprite>>>();
		for(int i = 0; i < Const.TERRAIN_TYPES; i++){
			terrain.add(new ArrayList<ArrayList<Sprite>>());
			for(int j = 0; j < Const.TERRAIN_SECTIONS; j++)
				terrain.get(i).add(new ArrayList<Sprite>());
		}
	}
	
	public static void add(int t, int s, Sprite tex){
		tex.setIndex(terrain.get(t).get(s).size());
		terrain.get(t).get(s).add(tex);		
	}
	
	public static Sprite getRandomSprite(int t, int s){
		int rand = Math.abs(Const.RANDOM.nextInt())%terrain.get(t).get(s).size();
		return terrain.get(t).get(s).get(rand);
	}
	
	public static Sprite getSprite(int t, int s, int i){
		return terrain.get(t).get(s).get(i);
	}
}
