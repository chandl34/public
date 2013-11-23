package data;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class Data {

	private static User u;

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
