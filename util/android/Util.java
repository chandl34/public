package com.surgeworks.divineoffice.util;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.reflect.Array;
import java.nio.charset.Charset;
import java.security.Key;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.ConfigurationInfo;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.text.InputType;
import android.util.Base64;
import android.view.Surface;
import android.view.View;
import android.view.ViewGroup;

import com.amazon.geo.mapsv2.util.AmazonMapsRuntimeUtil;
import com.amazon.geo.mapsv2.util.ConnectionResult;

public class Util
{
	// Debug
	public static void showLog(String log)
	{
		Scanner scanner = new Scanner(log);
		while(scanner.hasNextLine())
		{
			String line = scanner.nextLine();
			System.out.println("chandl34 - " + line);
		}

		scanner.close();
	}

	public static String getDebugInfo(Context context)
	{
		String debugInfo = "";
		debugInfo += "App version:  " + getAppName(context) + " " + getAppVersion(context) + "\n";
		debugInfo += "OS version:  Android " + getAndroidVersion() + "\n";
		debugInfo += "Device type:  " + getDeviceType() + "\n";
		debugInfo += "\n\n";
		return debugInfo;
	}
	
	public static String getAppName(Context context)
	{
	    return (String)context.getApplicationInfo().loadLabel(context.getPackageManager());
	}
	
	public static String getAppVersion(Context context)
	{
		try
		{
			return context.getPackageManager().getPackageInfo(context.getPackageName(), 0).versionName;
		}
		catch(Exception e)
		{
			return null;
		}		
	}
	
	public static String getAndroidVersion()
	{
		return Build.VERSION.RELEASE;
	}
	
	public static String getDeviceType()
	{
	    String manufacturer = Build.MANUFACTURER;
	    String model = Build.MODEL;	    
	    if(model.startsWith(manufacturer))
	    {
	    	return capitalize(model);
	    }
	    
	    return capitalize(manufacturer) + " " + capitalize(model);
	}

	public static int getScreenOrientation(Activity activity)
	{
		int rotation = activity.getWindowManager().getDefaultDisplay().getRotation();
		int orientation = activity.getResources().getConfiguration().orientation;
		if(orientation == Configuration.ORIENTATION_PORTRAIT)
		{
			if(rotation == Surface.ROTATION_0 || rotation == Surface.ROTATION_270)
			{
				return ActivityInfo.SCREEN_ORIENTATION_PORTRAIT;
			}
			else
			{
				return ActivityInfo.SCREEN_ORIENTATION_REVERSE_PORTRAIT;
			}
		}
		if(orientation == Configuration.ORIENTATION_LANDSCAPE)
		{
			if(rotation == Surface.ROTATION_0 || rotation == Surface.ROTATION_90)
			{
				return ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;
			}
			else
			{
				return ActivityInfo.SCREEN_ORIENTATION_REVERSE_LANDSCAPE;
			}
		}
		return ActivityInfo.SCREEN_ORIENTATION_UNSPECIFIED;
	}
	
	public static void lockScreenOrientation(Activity activity)
	{
		int orientation = getScreenOrientation(activity);		
		activity.setRequestedOrientation(orientation);
	}

	
	// Device
	public static boolean isFireTV()
	{
		return isAmazonDevice() && android.os.Build.MODEL.startsWith("AFT");
	}

	public static boolean isAmazonDevice()
	{
		return android.os.Build.MANUFACTURER.equalsIgnoreCase("Amazon");
	}

	public static boolean supportsGoogleMaps(Context context)
	{
		try
		{
			context.getPackageManager().getApplicationInfo("com.google.android.apps.maps", 0);

			ActivityManager activityManager = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
			ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
			return configurationInfo.reqGlEsVersion >= 0x20000;
		}
		catch(Exception e)
		{
			return false;
		}
	}

	public static boolean supportsAmazonMaps(Context context)
	{
		return AmazonMapsRuntimeUtil.isAmazonMapsRuntimeAvailable(context) == ConnectionResult.SUCCESS;
	}
	
	
	// Collections
	public static boolean nullOrEmpty(Object collection)
	{
		if(collection == null)
		{
			return true;
		}
		
		if(collection.getClass().isArray())
		{
			return Array.getLength(collection) == 0;
		}
		
		if(collection instanceof String)
		{
			return ((String)collection).isEmpty();
		}
		
		if(collection instanceof Map)
		{
			return ((Map)collection).isEmpty();
		}

		if(collection instanceof Collection)
		{
			return ((Collection)collection).isEmpty();
		}
		
		if(collection instanceof Bundle)
		{
			return ((Bundle)collection).isEmpty();
		}

		return false;
	}
	
	public static Object objectAt(Object collection, int index)
	{
		if(collection.getClass().isArray())
		{	
			return Array.get(collection, index);
		}

		if(collection instanceof List)
		{
			return ((List)collection).get(index);
		}
		
		if(collection instanceof Map)
		{
			collection = ((Map)collection).entrySet();
		}

		if(collection instanceof Collection)
		{
			Object object = null;			
			Iterator iter = ((Collection)collection).iterator();
			for(int i = 0; i <= index; ++i)
			{
				object = iter.next();
			}			
			
			return object;
		}

		return null;
	}

	public static Integer indexOf(Object collection, Object object)
	{
		if(collection.getClass().isArray())
		{			
			collection = Arrays.asList(object);
		}

		if(collection instanceof Map)
		{
			collection = ((Map)collection).keySet();
		}

		if(collection instanceof Collection)
		{			
			Iterator iter = ((Collection)collection).iterator();
			for(int i = 0; iter.hasNext(); ++i)
			{
				Object other = iter.next(); 
				if(object.equals(other))
				{
					return i;
				}
			}			
		}

		return null;
	}
	
	
	// String
	public static String capitalize(String str)
	{
		if(nullOrEmpty(str))
		{
			return str;
		}
		
		char first = str.charAt(0);
		if(Character.isUpperCase(first))
		{
			return str;
		}
		
		return Character.toUpperCase(first) + str.substring(1);
	}
	
	public static String join(String[] array, String delimiter)
	{
		StringBuilder builder = new StringBuilder();

		for(int i = 0; i < array.length; ++i)
		{
			if(i != 0)
			{
				builder.append(delimiter);
			}
			builder.append(array[i]);
		}
		
		return builder.toString();
	}
	
	public static String[] split(String string, String delimiter)
	{
		if(string == null)
		{
			return new String[]{""};
		}
		
		String[] array = string.split(delimiter);
		if(string.endsWith(delimiter))
		{
			ArrayList<String> list = new ArrayList<String>();
			list.addAll(Arrays.asList(array));	
			list.add("");
			array = list.toArray(array);
		}		
		return array;
	}
	
	public static boolean containsIgnoreCase(String string, String search)
	{
		if(string == null || search == null)
		{
			return false;
		}
		
		return string.toLowerCase().contains(search.toLowerCase());
	}
	
	public static int count(String string, String search)
	{
		if(Util.nullOrEmpty(search))
		{
			return 0;
		}
		
		int count = 0;		
		int pos = 0;
		while(pos < string.length())
		{
			int index = string.indexOf(search, pos);
			if(index < 0)
			{
				break;
			}
			
			pos = index + search.length();
			++count;
		}		
		return count;
	}
		
	
	// Casting
	public static long toLong(Object value)
	{
		try
		{
			if(value instanceof Number)
			{
				return ((Number)value).longValue();
			}
			else if(value instanceof String)
			{
				return Long.valueOf((String)value);
			}
		}
		catch(Exception e){}
		
		return 0;
	}

	public static byte[] toByteArray(String value)
	{
		if(value == null)
		{
			return null;
		}		
		
		return value.getBytes(Charset.forName("UTF-8"));
	}
	
	public static byte[] toByteArray(InputStream input) throws IOException
	{
		int length;
		byte[] buffer = new byte[1024]; 		
		ByteArrayOutputStream output = new ByteArrayOutputStream();
		
		while((length = input.read(buffer)) != -1)
		{
			output.write(buffer, 0, length);		
		}
		input.close();
		
		return output.toByteArray();
	}

	public static String toString(InputStream input) throws IOException
	{
		StringBuilder builder = new StringBuilder();
		BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(input, "UTF-8"));
		String line = bufferedReader.readLine();
		while(line != null)
		{
			builder.append(line);
			//builder.append('\n');
			line = bufferedReader.readLine();
		}

		return builder.toString();
	}
		
	public static String fixFormat(String input)
	{
		String output = input.replace("%i", "%d");
		output = output.replace("%@", "%s");
		return output;
	}
	
	
	// Math
	public static int clamp(int value, int min, int max)
	{
		value = Math.max(value, min);
		return Math.min(value, max);
	}
	
	
	// Activity
	public static void restartWithActivity(Activity activity, Intent intent)
	{
		if(!activity.isFinishing())
		{
			intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);	
			intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK); 
			activity.startActivity(intent);
		}		
	}
		
	
	// External
	public static Intent getEmailIntent(Context context, String to, String subject, String body, String purpose)
	{
		return getEmailIntent(context, to, subject, body, purpose, null);
	}
	
	public static Intent getEmailIntent(Context context, String to, String subject, String body, String purpose, ArrayList<Uri> attachments)
	{
		Intent intent = new Intent(Intent.ACTION_SEND_MULTIPLE);
		intent.setType("text/plain");
		
	    intent.putExtra(Intent.EXTRA_EMAIL, new String[]{to});
	    intent.putExtra(Intent.EXTRA_SUBJECT, subject);
	    intent.putExtra(Intent.EXTRA_TEXT, body);	    
	    if(attachments != null)
	    {
	    	intent.putExtra(Intent.EXTRA_STREAM, attachments);
	    }
	    
	    ComponentName emailComponent = getEmailComponent(context);
	    if(emailComponent != null)
	    {
	    	intent.setComponent(emailComponent);
	    	return intent;
	    }	    
	    return Intent.createChooser(intent, purpose);
	}
	
	
	
	private static ComponentName getEmailComponent(Context context)
	{
	    PackageManager pm = context.getPackageManager();

	    Intent intent = new Intent(Intent.ACTION_SENDTO, Uri.parse("mailto:"));
	    List<ResolveInfo> activities = pm.queryIntentActivities(intent, 0);
	    
	    ComponentName emailComponent = null;
	    if(activities.size() == 1)
	    {
	    	ResolveInfo activity = activities.get(0);
    		emailComponent = new ComponentName(activity.activityInfo.packageName, activity.activityInfo.name);
	    }
	    else
	    {
		    for(ResolveInfo activity : activities)
		    {
		    	if(activity.isDefault)
		    	{
		    		emailComponent = new ComponentName(activity.activityInfo.packageName, activity.activityInfo.name);
		    		break;
		    	}
		    }
	    }
	    	    
	    return emailComponent;
	}
	
	public static Intent getPhoneIntent(String number)
	{
		return new Intent(Intent.ACTION_CALL, Uri.parse("tel:" + number));
	}
	
	public static Intent getURLIntent(String url)
	{
		if(!url.startsWith("http://") && !url.startsWith("https://"))
		{
			url = "http://" + url;
		}
		
		return new Intent(Intent.ACTION_VIEW, Uri.parse(url));
	}
	
	public static Intent getAddressIntent(String address)
	{
		address = address.replace(" ", "+");
		address = address.replace("\n", "+");
		String url = "http://maps.google.com/?q=" + address;
		return getURLIntent(url);
	}
	
	
	// Bitmap
	public static byte[] toPNG(Bitmap bitmap)
	{
		ByteArrayOutputStream output = new ByteArrayOutputStream();
		bitmap.compress(Bitmap.CompressFormat.PNG, 100, output);
		return output.toByteArray();
	}
	
	public static byte[] toJPEG(Bitmap bitmap, int compression)
	{		
		ByteArrayOutputStream output = new ByteArrayOutputStream();
		bitmap.compress(Bitmap.CompressFormat.JPEG, compression, output);	
		return output.toByteArray();
	}

	public static Bitmap scaleBitmap(byte[] bytes, int width, int height)
	{
		Bitmap input = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
		return scaleBitmap(input, width, height);
	}
	
	public static Bitmap scaleBitmap(Bitmap input, int width, int height)
	{		
		if(input == null)
		{
			return null;
		}
		
		int divisor = findDivisor(input.getWidth(), input.getHeight(), width, height);
		if(divisor == 1)
		{
			return input;
		}
		return Bitmap.createScaledBitmap(input, input.getWidth() / divisor, input.getHeight() / divisor, false);
	}

	public static Bitmap scaleBitmap(File file, int width, int height)
	{
	    BitmapFactory.Options options = new BitmapFactory.Options();
	    options.inJustDecodeBounds = true;
	    
		BitmapFactory.decodeFile(file.getAbsolutePath(), options);	
	    options.inSampleSize = findDivisor(options.outWidth, options.outHeight, width, height);

	    options.inJustDecodeBounds = false;
	    return BitmapFactory.decodeFile(file.getAbsolutePath(), options);	
	}
	
	private static int findDivisor(int width, int height, int destWidth, int destHeight)
	{
		int divisor = 1;
		while(width / (divisor * 2) > destWidth &&
			height / (divisor * 2) > destHeight)
		{
			divisor *= 2;
		}

		return divisor;
	}
	
	
	// Files
	public static boolean writeFile(Context context, String filePath, byte[] output)
	{
		File file = new File(context.getFilesDir(), filePath);
		return writeFile(context, file, output);
	}
	
	public static boolean writeFile(Context context, File file, byte[] output)
	{
		try
		{
			if(!file.exists())
			{
				File dir = file.getParentFile();
				dir.mkdirs();
			}
			
			FileOutputStream fos = new FileOutputStream(file);
			fos.write(output);
			fos.close();
			
			return true;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return false;
		}
	}

	public static byte[] readFile(Context context, String filePath)
	{
		File file = new File(context.getFilesDir(), filePath);
		return readFile(context, file);
	}
	
	public static byte[] readFile(Context context, File file)
	{
		try
		{
			FileInputStream fis = new FileInputStream(file);
	
			ByteArrayOutputStream out = new ByteArrayOutputStream();
			byte[] buffer = new byte[1024];
			while(true) 
			{
			    int r = fis.read(buffer);
			    if (r == -1) break;
			    out.write(buffer, 0, r);
			}
			fis.close();
			
			return out.toByteArray();
		}
		catch(FileNotFoundException e){}
		catch(Exception e){e.printStackTrace();}
		return null;
	}
	
	public static boolean deleteFile(Context context, String filePath)
	{
		File file = new File(context.getFilesDir(), filePath);
		return deleteFile(context, file);
	}	
	
	public static boolean deleteFile(Context context, File file)
	{
		/*
		if(file.isHidden())
		{
			return false;
		}
		*/
		if(file.isDirectory())
		{
	        String[] children = file.list();
			for(int i = 0; i < children.length; ++i)
			{
	            File temp = new File(file, children[i]);
	            deleteFile(context, temp);
			}
		}
		
		return file.delete(); 
	}
	
	
	// Other
	public static long currentTimeSeconds()
	{
		return System.currentTimeMillis() / 1000;
	}
	
	public static int getInputType(KeyboardType keyboardType, boolean multi)
	{
		switch(keyboardType)
		{
			default:
			case None:
				if(multi)
				{		
					return 	InputType.TYPE_CLASS_TEXT | 						
							InputType.TYPE_TEXT_FLAG_CAP_SENTENCES |
							InputType.TYPE_TEXT_FLAG_MULTI_LINE;
				}
				else
				{
					return 	InputType.TYPE_CLASS_TEXT |
							InputType.TYPE_TEXT_FLAG_CAP_SENTENCES;
				}
				
			case Address:
				return 	InputType.TYPE_CLASS_TEXT | 
						InputType.TYPE_TEXT_FLAG_CAP_SENTENCES |
						InputType.TYPE_TEXT_FLAG_MULTI_LINE | 
						InputType.TYPE_TEXT_VARIATION_POSTAL_ADDRESS;
				
			case Email:
				return  InputType.TYPE_CLASS_TEXT | 
						InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS;
				
			case Phone:
				return InputType.TYPE_CLASS_PHONE;
				
			case URL:
				return 	InputType.TYPE_CLASS_TEXT | 
						InputType.TYPE_TEXT_VARIATION_URI;
		}
	}
	
	public static View getChildWithTag(ViewGroup viewGroup, Object tag)
	{
		for(int i = 0; i < viewGroup.getChildCount(); ++i)
		{
			View child = viewGroup.getChildAt(i);
			if(tag.equals(child.getTag()))
			{
				return child;
			}
		}
		
		return null;
	}
	
	
	// Encryption
	public static byte[] encryptAES256(byte[] bytes, byte[] key)
	{
		try
		{
	        Cipher cipher = Cipher.getInstance("AES");
	        cipher.init(Cipher.ENCRYPT_MODE, getAESKey(key));
	        bytes = cipher.doFinal(bytes);	        
		}
		catch(Exception e){e.printStackTrace();}
		
		return bytes;
	}

	public static byte[] decryptAES256(byte[] bytes, byte[] key)
	{
		try
		{
	        Cipher cipher = Cipher.getInstance("AES");
	        cipher.init(Cipher.DECRYPT_MODE, getAESKey(key));
	        bytes = cipher.doFinal(bytes);		        
		}
		catch(Exception e){e.printStackTrace();}
		
		return bytes;
	}	
	
	public static byte[] md5(byte[] key)
	{
		return hash("md5", key);
	}

	public static byte[] sha256(byte[] key)
	{
		return hash("SHA-256", key);
	}

	public static byte[] hash(String algorithm, byte[] key)
	{
		try
		{
			final MessageDigest digest = MessageDigest.getInstance(algorithm);
			digest.update(key);
			return digest.digest();
		}
		catch(Exception e){e.printStackTrace();}
		
		return null;
	}

	public static Key getAESKey(byte[] key) throws Exception
	{
		return new SecretKeySpec(key, "AES");
	}

	
	// Encoding
	public static String base64ToUtf8(final String base64)
	{
		byte[] utf8 = Base64.decode(base64, Base64.DEFAULT);
		return new String(utf8);
	}
	
	public static String utf8ToBase64(final byte[] utf8)
	{			
		byte[] base64 = Base64.encode(utf8, Base64.DEFAULT);
		return new String(base64);
	}	
}
