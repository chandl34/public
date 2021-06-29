package com.skoop.uniwellkiosk.util;


import android.os.Bundle;

import org.json.JSONArray;
import org.json.JSONObject;


public class JSON
{
    // Accessors
    public static String getString(JSONObject json, String name)
    {
        try
        {
            if(!json.isNull(name))
            {
                return json.getString(name);
            }
        }
        catch(Exception e){}

        return "";
    }


    // Conversion
    public static JSONObject toObject(Bundle bundle)
    {
        JSONObject json = new JSONObject();

        try
        {
            for(String key : bundle.keySet())
            {
                Object value = bundle.get(key);

                if(value != null)
                {
                    if(value.getClass().isArray())
                    {
                        value = toArray((Object[])value);
                    }
                    else if(value instanceof Bundle)
                    {
                        value = toObject((Bundle)value);
                    }
                }

                json.put(key, value);
            }
        }
        catch(Exception e){e.printStackTrace();}

        return json;
    }

    public static JSONArray toArray(Object[] array)
    {
        JSONArray json = new JSONArray();

        try
        {
            for(Object object : array)
            {
                if(object != null)
                {
                    if(object.getClass().isArray())
                    {
                        object = toArray((Object[])object);
                    }
                    else if(object instanceof Bundle)
                    {
                        object = toObject((Bundle)object);
                    }
                }

                json.put(object);
            }
        }
        catch(Exception e){e.printStackTrace();}

        return json;
    }
}
