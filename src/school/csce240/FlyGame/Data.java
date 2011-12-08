/**
 * Overview:  Handles the saving/loading of User objects
 * 
 * @author Matthew Crocket
 */

import java.io.*;

public class Data {

	private static User u;
	
	/**
	 * Saves User's information to file /battery.sav
	 * <p>
	 * modifies:  changes /battery.sav
	 * <p>
	 * requires:  a != null
	 * @param a User object to save to
	 */
	public static void save(User a){
		if(a == null){
			System.out.println("User was null");
			return;
		}
		ObjectOutputStream outputStream = null;
		String fileName = "battery.sav";
		
		try{
			outputStream = new ObjectOutputStream(new FileOutputStream(fileName));
			outputStream.writeObject(a);
			System.out.println("Records written to file " +fileName);
	        outputStream.close();
	      }catch(IOException ioe){
	    	  System.out.println("Error writing to file "+fileName);
	      }
	}
	
	/**
	 * modifies:
	 * @return User object store in /battery.sav
	 */
	public static User load(){
    	ObjectInputStream inputStream = null;
    	String fileName  = "battery.sav";
		try{
		      inputStream = new ObjectInputStream(new FileInputStream(fileName));
		    	  u = (User)inputStream.readObject();
			}catch(IOException ioe){
				u = new User();
	    	}catch(Exception e){
	    		System.out.println("Other error reading file");
	    		}
	    	return u;
	    }
	
}
