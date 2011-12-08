package sprites;


import include.Const;

import javax.media.opengl.GL;

public class Sprite {	
	private int texName;
	private int texSize;
	private float texVert[][];
	private int index;
	private boolean blend = false;
	
	public Sprite(int sT){
		init(-1, 0, 0, sT, sT);
	}
	
	public Sprite(int t, int sT){
		init(t, 0, 0, sT, sT);
	}
	
	public Sprite(int t, int x, int y, int sS, int sT){	
		init(t, x, y, sS, sT);
	}

	private void init(int t, int x, int y, int sS, int sT){
		texName = t;
		texSize = sS;
		
		texVert = new float[2][8];
		float x0 = (float)x / Const.TEX_SIZE[sT][0];	
		float x1 = (float)(x + Const.TEX_SIZE[sS][0]) / Const.TEX_SIZE[sT][0];	
		float y0 = (float)y / Const.TEX_SIZE[sT][1];
		float y1 = (float)(y + Const.TEX_SIZE[sS][1]) / Const.TEX_SIZE[sT][1];
		
		texVert[Const.NOFLIP][0] = x1;			texVert[Const.NOFLIP][1] = y0;
		texVert[Const.NOFLIP][2] = x0;			texVert[Const.NOFLIP][3] = y0;
		texVert[Const.NOFLIP][4] = x1;			texVert[Const.NOFLIP][5] = y1;
		texVert[Const.NOFLIP][6] = x0;			texVert[Const.NOFLIP][7] = y1;
		
		texVert[Const.FLIP][0] = x0;			texVert[Const.FLIP][1] = y0;
		texVert[Const.FLIP][2] = x1;			texVert[Const.FLIP][3] = y0;
		texVert[Const.FLIP][4] = x0;			texVert[Const.FLIP][5] = y1;
		texVert[Const.FLIP][6] = x1;			texVert[Const.FLIP][7] = y1;
	}

	public void setBlend(boolean b){
		blend = b;
	}
	
	public int getIndex(){
		return index;
	}
	
	public void setIndex(int i){
		index = i;
	}
	
	public void setTexSize(int s){
		texSize = s;
	}
	
	public void draw(GL gl, int flipped){
		draw(gl, flipped, texSize);
	}
	
	public void draw(GL gl, int flipped, int tex){
		if(texName == -1)
			gl.glDisable(GL.GL_TEXTURE_2D); 
		else
			gl.glBindTexture(GL.GL_TEXTURE_2D, texName);
		if(blend)
			gl.glEnable(GL.GL_BLEND);
		gl.glBegin(GL.GL_TRIANGLE_STRIP);	
		for(int i = 0; i < 8; i += 2){
			gl.glTexCoord2f(texVert[flipped][i], texVert[flipped][i + 1]);		
			gl.glVertex2f(Const.SPRITE_VERT[tex][i], Const.SPRITE_VERT[tex][i + 1]);
		}
		gl.glEnd();
		if(texName == -1)
			gl.glEnable(GL.GL_TEXTURE_2D);
		if(blend)
			gl.glDisable(GL.GL_BLEND);	
	}
}
