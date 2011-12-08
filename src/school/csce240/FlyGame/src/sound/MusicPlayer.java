package sound;

import java.io.File;
import java.util.Map;

import javazoom.jlgui.basicplayer.BasicController;
import javazoom.jlgui.basicplayer.BasicPlayer;
import javazoom.jlgui.basicplayer.BasicPlayerEvent;
import javazoom.jlgui.basicplayer.BasicPlayerException;
import javazoom.jlgui.basicplayer.BasicPlayerListener;

public class MusicPlayer implements BasicPlayerListener{

	private BasicPlayer player;

	private int levelNumber;

	private boolean looping, introPlaying;

	private File intro[] = {
			null,
			new File("audio/music/levelOneIntro.mp3"),
			new File("audio/music/levelTwoIntro.mp3"),
			new File("audio/music/levelThreeIntro.mp3")
	};

	private File music[] = {
			new File("audio/music/titleMusic.mp3"),
			new File("audio/music/levelOneMusic.mp3"),
			new File("audio/music/levelTwoMusic.mp3"),
			new File("audio/music/levelThreeMusic.mp3")
	};

	private File theme[] = {
			new File("audio/theme/gameOver.mp3"),
			new File("audio/theme/levelComplete.mp3")	
	};

	public MusicPlayer(){
		player = new BasicPlayer();
		player.addBasicPlayerListener(this);
		looping = false;	
		introPlaying = false;
	}

	public void playGameOverTheme(){
		try{
			player.open(theme[0]);
			player.play();
		}catch(BasicPlayerException bpe){}
	}

	public void playLevelCompleteTheme(){
		try{
			player.open(theme[1]);
			player.play();
		}catch(BasicPlayerException bpe){}
	}

	public void playLevelMusic(int level){
		levelNumber = level;
		if(levelNumber == 0){
			loop();
			return;
		}
		introPlaying = true;
		try{
			player.open(intro[levelNumber]);
			player.play();
		}catch(BasicPlayerException bpe){}
	}

	private void loop(){
		looping = true;
		try{
			player.open(music[levelNumber]);
			player.play();
		}catch(BasicPlayerException bpe){}
	}	

	public void stop(){
		looping = false;
		try{
			player.stop();
		}catch(BasicPlayerException bpe){}
	}

	public void stateUpdated(BasicPlayerEvent event) {
		if(event.getCode() == 3){
			if(introPlaying){
				introPlaying = false;
				loop();				
			}
			else if(looping){
				try{
					player.play();
				}catch(BasicPlayerException bpe){}
			}
		}
	}

	// Unimplemented
	public void setController(BasicController controller){}
	public void opened(Object stream, Map properties) {}
	public void progress(int bytesread, long microseconds, byte[] pcmdata, Map properties) {}

}
