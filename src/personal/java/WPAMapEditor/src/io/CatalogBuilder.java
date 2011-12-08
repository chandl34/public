package io;

import javax.media.opengl.GL;

import catalogs.TerrainCatalog;

public class CatalogBuilder {

	public static void buildTerrain(GL gl){
		new TerrainCatalog();
		Loader.loadTerrain(gl, "sea.tsc");
		Loader.loadTerrain(gl, "beach.tsc");
		Loader.loadTerrain(gl, "grass.tsc");
	}
	
}
