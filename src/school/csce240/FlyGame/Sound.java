/**
 * Overview:  Handles the playing and stopping of sound.
 * 
 * @author Matthew Crocket
 */

import java.io.*;
import javax.sound.sampled.*;

public class Sound {

	 private AudioFormat format;
	 private byte[] samples;
	 private SourceDataLine line;	 
	 
	 /**
	  * Initializes Sound file
	  * @param filename filename of sound to be played
	  */
	 public Sound(String filename) {
	        try {
	            AudioInputStream stream = AudioSystem.getAudioInputStream(new File(filename));
	            format = stream.getFormat();
	            samples = getSamples(stream);	            
	        }
	        catch (UnsupportedAudioFileException uafe) {
	        	uafe.printStackTrace();
	        }
	        catch (IOException uafe) {
	        	uafe.printStackTrace();
	        }
	    }
	 
	 /**
	  * Gets samples
	  * @return byte[] samples
	  */
	 public byte[] getSamples() {
	        return samples;
	    }
	 
	 /**
	  * Gets samples from AudioInputStream
	  * <p>
	  * requires:  AudioInputStream != null
	  * @return byte[] samples
	  */
	 private byte[] getSamples(AudioInputStream audioStream) {
		 if(audioStream == null){
			 System.out.println("AudioInputStream is null");
			 return null;
		 }
		 int length = (int)(audioStream.getFrameLength()*format.getFrameSize());

		 byte[] samples = new byte[length];
		 DataInputStream is = new DataInputStream(audioStream);
		 try {is.readFully(samples);
		 		}catch (IOException io) {
		 			io.printStackTrace();
		            }
		return samples;
	 }
	
	 /**
	  * Plays the current Sound
	  */
	 public void play() {
		 ByteArrayInputStream source = new ByteArrayInputStream(getSamples());
		 int bufferSize = format.getFrameSize()*Math.round(format.getSampleRate() / 10);
		 byte[] buffer = new byte[bufferSize];
		 
		 
	     try {
	    	 DataLine.Info info = new DataLine.Info(SourceDataLine.class, format);
	         line = (SourceDataLine)AudioSystem.getLine(info);
	         line.open(format, bufferSize);
	     }catch (LineUnavailableException lue) {
	            lue.printStackTrace();
	            return;
	     }
	     
	     line.start();
	     
	    int numBytesRead = 0;
	    while (numBytesRead != -1) {
	    	numBytesRead = source.read(buffer, 0, buffer.length);
	        if (numBytesRead != -1) {
	           	line.write(buffer, 0, numBytesRead);
	        }
	    }
	 
	     line.drain();
	     line.close();
	 }
	 
	 /**
	  * Stops current Sound file from playing.
	  */
	 public void stop(){
	     line.stop();
	 }
	 
}

