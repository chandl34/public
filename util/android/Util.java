package com.skoop.uniwellkiosk.util;


import android.Manifest;
import android.app.Activity;
import android.app.Dialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.ComponentName;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Looper;
import android.support.annotation.RequiresPermission;
import android.util.Base64;
import android.view.Surface;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.webkit.CookieManager;
import android.webkit.CookieSyncManager;

import com.skoop.uniwellkiosk.ui.view.UserInteractionWindowCallback;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Array;
import java.net.URL;
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
import java.util.Set;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;


public class Util
{
    // Debug
    public static void showLog(String log)
    {
        if(log == null)
        {
            log = "";
        }

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
        return (String) context.getApplicationInfo().loadLabel(context.getPackageManager());
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

    public static String getPackageName(Context context)
    {
        return context.getPackageName();
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

    public static boolean isEmulator()
    {
        return Build.BRAND.startsWith("generic") || Build.DEVICE.startsWith("generic");
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
            return ((String) collection).isEmpty();
        }

        if(collection instanceof Map)
        {
            return ((Map) collection).isEmpty();
        }

        if(collection instanceof Collection)
        {
            return ((Collection) collection).isEmpty();
        }

        if(collection instanceof Bundle)
        {
            return ((Bundle) collection).isEmpty();
        }

        if(collection instanceof ContentValues)
        {
            return ((ContentValues) collection).size() == 0;
        }

        if(collection instanceof JSONArray)
        {
            return ((JSONArray) collection).length() == 0;
        }

        if(collection instanceof JSONObject)
        {
            return ((JSONObject) collection).length() == 0;
        }

        return false;
    }

    public static int sizeOf(Object collection)
    {
        if(collection == null)
        {
            return 0;
        }

        if(collection.getClass().isArray())
        {
            return Array.getLength(collection);
        }

        if(collection instanceof String)
        {
            return ((String) collection).length();
        }

        if(collection instanceof Map)
        {
            return ((Map) collection).size();
        }

        if(collection instanceof Collection)
        {
            return ((Collection) collection).size();
        }

        if(collection instanceof Bundle)
        {
            return ((Bundle) collection).size();
        }

        if(collection instanceof ContentValues)
        {
            return ((ContentValues) collection).size();
        }

        if(collection instanceof JSONArray)
        {
            return ((JSONArray) collection).length();
        }

        if(collection instanceof JSONObject)
        {
            return ((JSONObject) collection).length();
        }

        return 0;
    }

    public static Object objectAt(Object collection, int index)
    {
        if(collection.getClass().isArray())
        {
            return Array.get(collection, index);
        }

        if(collection instanceof List)
        {
            return ((List) collection).get(index);
        }

        if(collection instanceof Map)
        {
            collection = ((Map) collection).entrySet();
        }

        if(collection instanceof Collection)
        {
            Object object = null;
            Iterator iter = ((Collection) collection).iterator();
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
            collection = ((Map) collection).keySet();
        }

        if(collection instanceof Collection)
        {
            Iterator iter = ((Collection) collection).iterator();
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

    @SafeVarargs
    public static <T> List<T> toList(T... a)
    {
        if(a == null)
        {
            return new ArrayList<>();
        }

        return Arrays.asList(a);
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

    public static String pluralize(String singular, String plural, int count)
    {
        if(count == 1)
        {
            return singular;
        }

        return plural;
    }

    public static String join(List<String> list, String delimiter)
    {
        String[] array = list.toArray(new String[0]);
        return join(array, delimiter);
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

    public static List<String> split(String string, String delimiter)
    {
        if(string == null)
        {
            return new ArrayList<>();
        }

        ArrayList<String> list = new ArrayList<>();
        int pos = string.indexOf(delimiter);
        while(pos >= 0)
        {
            list.add(string.substring(0, pos));
            string = string.substring(pos + delimiter.length());
            pos = string.indexOf(delimiter);
        }
        list.add(string);

        return list;
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

    public static String nullToEmptyString(String string)
    {
        if(string == null)
        {
            return "";
        }

        return string;
    }

    public static String[] wordWrap(String string, int lineLength)
    {
        if(string == null)
        {
            return new String[0];
        }

        List<String> lineList = new ArrayList<>();
        int offset = 0;
        while(offset < string.length())
        {
            if(string.charAt(offset) == ' ')
            {
                ++offset;
                continue;
            }

            int lastIndex = offset + lineLength < string.length() ?
                            string.lastIndexOf(' ', offset + lineLength) :
                            string.length();
            if(lastIndex < offset)
            {
                lastIndex = Math.min(offset + lineLength, string.length());
            }
            String line = string.substring(offset, lastIndex).trim();
            lineList.add(line);

            offset = lastIndex;
        }
        return lineList.toArray(new String[0]);
    }

    public static String fillString(char ch, int length)
    {
        char[] charArray = new char[length];
        Arrays.fill(charArray, ch);
        return new String(charArray);
    }


    // Casting
    public static Integer toInt(Object value)
    {
        return toInt(value, 0);
    }

    public static Integer toInt(Object value, Integer def)
    {
        if(value instanceof Boolean)
        {
            return toInt(((Boolean)value).booleanValue());
        }
        else if(value instanceof Number)
        {
            return ((Number) value).intValue();
        }
        else if(value instanceof String)
        {
            return parseInt((String) value, def);
        }

        return def;
    }

    public static long toLong(Object value)
    {
        return toLong(value, 0);
    }

    public static long toLong(Object value, long def)
    {
        if(value instanceof Number)
        {
            return ((Number) value).longValue();
        }
        else if(value instanceof String)
        {
            return parseLong((String) value, def);
        }

        return def;
    }

    public static float toFloat(Object value)
    {
        return toFloat(value, 0);
    }

    public static float toFloat(Object value, float def)
    {
        if(value instanceof Number)
        {
            return ((Number) value).floatValue();
        }
        else if(value instanceof String)
        {
            return parseFloat((String) value, def);
        }

        return def;
    }

    public static double toDouble(Object value)
    {
        return toDouble(value, 0);
    }

    public static double toDouble(Object value, double def)
    {
        if(value instanceof Number)
        {
            return ((Number) value).doubleValue();
        }
        else if(value instanceof String)
        {
            return parseDouble((String) value, def);
        }

        return def;
    }

    public static boolean toBoolean(Object value)
    {
        return toBoolean(value, false);
    }

    public static boolean toBoolean(Object value, boolean def)
    {
        if(value instanceof Boolean)
        {
            return ((Boolean)value);
        }
        else if(value instanceof Number)
        {
            return ((Number)value).intValue() != 0;
        }
        else if(value instanceof String)
        {
            String string = (String)value;
            try
            {
                Integer integer = Integer.valueOf(string);
                return integer != 0;
            }
            catch(Exception e)
            {
                return string.equalsIgnoreCase("Y")|| string.equalsIgnoreCase("YES")|| parseBoolean(string, def);
            }
        }

        return def;
    }

    public static byte[] toByteArray(String value)
    {
        if(value == null)
        {
            return null;
        }

        return value.getBytes(Charset.forName("UTF-8"));
    }

    public static byte[] toByteArray(InputStream input)
    throws IOException
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

    public static String toString(InputStream input)
    {
        Scanner s = new Scanner(input).useDelimiter("\\A");
        return s.hasNext() ? s.next() : "";
    }

    public static String read(InputStream input)
    throws IOException
    {
        StringBuilder builder = new StringBuilder();
        byte[] buffer = new byte[1024];
        while(input.available() > 0)
        {
            int length = input.read(buffer);
            builder.append(new String(buffer, 0, length));
        }

        if(builder.length() == 0)
        {
            return null;
        }
        return builder.toString();
    }

    public static int toInt(boolean bool)
    {
        return bool ? 1 : 0;
    }

    private static boolean parseBoolean(String string, boolean def)
    {
        try
        {
            return Boolean.parseBoolean(string);
        }
        catch(Exception e){}
        return def;
    }

    private static Integer parseInt(String string, Integer def)
    {
        try
        {
            return Integer.parseInt(string);
        }
        catch(Exception e){}
        return def;
    }

    private static long parseLong(String string, long def)
    {
        try
        {
            return Long.parseLong(string);
        }
        catch(Exception e){}
        return def;
    }

    private static float parseFloat(String string, float def)
    {
        try
        {
            return Float.parseFloat(string);
        }
        catch(Exception e){}
        return def;
    }

    private static double parseDouble(String string, double def)
    {
        try
        {
            return Double.parseDouble(string);
        }
        catch(Exception e){}
        return def;
    }


    // Math
    public static int clamp(int value, int min, int max)
    {
        value = Math.max(value, min);
        return Math.min(value, max);
    }

    public static double clamp(double value, double min, double max)
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


    // View
    public static View getSubviewWithTag(ViewGroup viewGroup, Object tag)
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

    public static void enableUserInteraction(Activity activity, Dialog dialog)
    {
        Window window = dialog.getWindow();
        if(window != null)
        {
            window.setCallback(new UserInteractionWindowCallback(activity, window.getCallback()));
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

    public static Intent getSMSIntent(String number, String body, boolean exitOnSent)
    {
        Intent intent = new Intent(Intent.ACTION_SENDTO);
        intent.setData(Uri.parse("smsto:" + number));
        intent.putExtra("sms_body", body);
        if(Build.VERSION.SDK_INT < Build.VERSION_CODES.JELLY_BEAN_MR2)
        {
            intent.putExtra("exit_on_sent", exitOnSent);  // causes message body to disappear
        }

        return intent;
    }

    public static Intent getAndroidSettingsIntent()
    {
        return new Intent(android.provider.Settings.ACTION_SETTINGS);
    }


    // Bitmap
    public static byte[] toPNG(Bitmap bitmap)
    {
        ByteArrayOutputStream output = new ByteArrayOutputStream();
        bitmap.compress(Bitmap.CompressFormat.PNG, 100, output);
        return output.toByteArray();
    }

    public static byte[] toJPEG(Bitmap bitmap)
    {
        return toJPEG(bitmap, 100);
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
        while(width / (divisor * 2) > destWidth && height / (divisor * 2) > destHeight)
        {
            divisor *= 2;
        }

        return divisor;
    }


    // Files
    public static boolean writeFile(Context context, String filePath, byte[] output)
    {
        File file = new File(context.getFilesDir(), filePath);
        return writeFile(file, output);
    }

    public static boolean writeFile(File file, byte[] output)
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
        return readFile(file);
    }

    public static byte[] readFile(File file)
    {
        try
        {
            FileInputStream fis = new FileInputStream(file);

            ByteArrayOutputStream out = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            while(true)
            {
                int r = fis.read(buffer);
                if(r == -1)
                {
                    break;
                }
                out.write(buffer, 0, r);
            }
            fis.close();

            return out.toByteArray();
        }
        catch(FileNotFoundException e)
        {
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
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
            for(String child : file.list())
            {
                File temp = new File(file, child);
                deleteFile(context, temp);
            }
        }

        return file.delete();
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
        catch(Exception e)
        {
            e.printStackTrace();
        }

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
        catch(Exception e)
        {
            e.printStackTrace();
        }

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
        catch(Exception e)
        {
            e.printStackTrace();
        }

        return null;
    }

    public static Key getAESKey(byte[] key)
    {
        return new SecretKeySpec(key, "AES");
    }


    // Encoding
    public static String decodeBase64(final String base64)
    {
        return decodeBase64(base64, Base64.DEFAULT);
    }

    public static String decodeBase64(final String base64, int flags)
    {
        byte[] utf8 = Base64.decode(base64, flags);
        return new String(utf8);
    }

    public static String encodeBase64(final byte[] utf8)
    {
        return encodeBase64(utf8, Base64.DEFAULT);
    }

    public static String encodeBase64(final byte[] utf8, int flags)
    {
        byte[] base64 = Base64.encode(utf8, flags);
        return new String(base64);
    }


    // Bluetooth
    @RequiresPermission(Manifest.permission.BLUETOOTH)
    public static boolean isBluetoothEnabled()
    {
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        return bluetoothAdapter != null && bluetoothAdapter.isEnabled();
    }

    @RequiresPermission(Manifest.permission.BLUETOOTH)
    public static boolean isBluetoothDiscovering()
    {
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        return bluetoothAdapter != null && bluetoothAdapter.isDiscovering();
    }

    @RequiresPermission(Manifest.permission.BLUETOOTH)
    public static boolean isBluetoothPaired(String deviceID)
    {
        if(nullOrEmpty(deviceID))
        {
            return false;
        }

        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        Set<BluetoothDevice> deviceSet = bluetoothAdapter.getBondedDevices();
        for(BluetoothDevice device : deviceSet)
        {
            if(deviceID.equalsIgnoreCase(device.getAddress()))
            {
                return true;
            }
        }

        return false;
    }


    // Other
    public static void removeAllCookie(Context context)
    {
        CookieSyncManager.createInstance(context);
        CookieManager cookieManager = CookieManager.getInstance();
        cookieManager.removeAllCookie();
    }

    public static String getBasicAuthorizationHeader(String username, String password)
    {
        String orig = String.format("%s:%s", username, password);
        return String.format("Basic %s", encodeBase64(orig.getBytes(), Base64.NO_WRAP));
    }

    public static long currentTimeSeconds()
    {
        return System.currentTimeMillis() / 1000;
    }

    public static float pxToDp(Context context, float px)
    {
        return px / context.getResources().getDisplayMetrics().density;
    }

    public static float dpToPx(Context context, float dp)
    {
        return dp * context.getResources().getDisplayMetrics().density;
    }

    public static boolean isMainThread()
    {
        return Looper.getMainLooper().equals(Looper.myLooper());
    }

    public static void sleep(long millis)
    {
        try
        {
            Thread.sleep(millis);
        }
        catch(InterruptedException e){}
    }

    public static boolean isValidURL(String urlString)
    {
        try
        {
            URL url = new URL(urlString);
            return true;
        }
        catch(Exception e){}

        return false;
    }
}

