package sound;

import java.io.File;

import javazoom.jlgui.basicplayer.BasicPlayer;
import javazoom.jlgui.basicplayer.BasicPlayerException;

public class SoundFXPlayer{

	private BasicPlayer player = new BasicPlayer();
	
	public SoundFXPlayer(String sound){
		try{
			player.open(new File(sound));
		}catch(BasicPlayerException bpe){}
	}
	
	public void play(){
		try{
			if(player.getStatus() == BasicPlayer.PLAYING)
				return;		
			player.play();
		}catch(BasicPlayerException bpe){}
	}

}
