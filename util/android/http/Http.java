package com.surgeworks.divineoffice.util.http;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.net.SocketTimeoutException;
import java.net.URI;
import java.net.UnknownHostException;

import javax.net.ssl.SSLPeerUnverifiedException;

import org.apache.http.Header;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpDelete;
import org.apache.http.client.methods.HttpEntityEnclosingRequestBase;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpPut;
import org.apache.http.client.methods.HttpRequestBase;
import org.apache.http.entity.ByteArrayEntity;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
import org.json.JSONObject;

import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Pair;
import android.webkit.CookieManager;

public class Http
{
	//---- CONSTANTS
	public static final int DEFAULT_TIMEOUT = 30000; // ms
	public static String MULTIPART_BOUNDARY = "[)===----++++____~__x_Xx__~___~_++++----===(]";
	
	public enum HttpMethod
	{
		Get,
		Post,
		Put,
		Delete
	}

	public enum ContentType
	{
		Form,
		JSON,
		Multipart
	}	
	
	
	//---- CLASSES
	public static class SessionExpiredException
	extends Exception{}
	
	public static class AsyncHttpTask
	extends AsyncTask<HttpRequestBase, Integer, Pair<byte[], Exception>>
	{
		@Override
		protected Pair<byte[], Exception> doInBackground(HttpRequestBase... params)
		{
			if(params.length > 0)
			{
				return sendRequest(params[0]);
			}			
			return null;
		}
	}
	
	
	//---- METHODS
	public static HttpRequestBase
	getHttpGetRequest(String url, Bundle params, Bundle headers)
	{
		return getHttpRequest(url, HttpMethod.Get, ContentType.Form, params, headers);
	}
	
	public static HttpRequestBase 
	getHttpRequest(String url, HttpMethod method, ContentType contentType, Bundle params, Bundle headers)
	{
		try
		{
			HttpRequestBase request = getRequestType(method);
			
			if(request instanceof HttpEntityEnclosingRequestBase)
			{			
				HttpEntity entity = getEntity(contentType, params);
				((HttpEntityEnclosingRequestBase)request).setEntity(entity);
				request.setHeader("Content-Type", getContentType(contentType));
			}
			else if(!Util.nullOrEmpty(params))
			{
				url += "?" + getQuery(params);
			}
			
			request.setURI(new URI(url));
			
			request.setHeader("Is-Device", "1");
			request.setHeader("Cookie", CookieManager.getInstance().getCookie(url));			
			if(headers != null)
			{
				for(String key : headers.keySet())
				{
					request.setHeader(key, headers.getString(key));
				}	
			}
			
			return request;
		}
		catch(Exception e){e.printStackTrace();}	
		return null;
	}
	
	public static Pair<byte[], Exception> sendRequest(HttpRequestBase request)
	{
		HttpParams params = new BasicHttpParams();
		HttpConnectionParams.setConnectionTimeout(params, DEFAULT_TIMEOUT);
		HttpConnectionParams.setSoTimeout(params, DEFAULT_TIMEOUT);		

		DefaultHttpClient client = new DefaultHttpClient(params);
		try
		{
			HttpResponse response = client.execute(request);
			
			Header setCookie = response.getFirstHeader("Set-Cookie");
			if(setCookie != null)
			{
				String url = request.getURI().toString();
				CookieManager.getInstance().setCookie(url, setCookie.getValue());	
			}
			
			HttpEntity entity = response.getEntity();
			InputStream input = entity.getContent();
			
			return new Pair<byte[], Exception>(Util.toByteArray(input), null);
			
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return new Pair<byte[], Exception>(null, e);
		}
	}
	
	private static HttpRequestBase getRequestType(HttpMethod method)
	{
		switch(method)
		{
			case Get:
				return new HttpGet();				
			case Post:
				return new HttpPost();			
			case Put:
				return new HttpPut();		
			case Delete:
				return new HttpDelete();
		}		
		return null;
	}
	
	private static String getContentType(ContentType contentType)
	{
	    switch(contentType)
	    {
	        case Form:
	            return "application/x-www-form-urlencoded";	            
	        case JSON:
	            return "application/json";	            
	        case Multipart:
	            return "multipart/form-data; boundary=" + MULTIPART_BOUNDARY;
	    }
		return null;
	}
	
	private static HttpEntity getEntity(ContentType contentType, Bundle params)
	{
		try
		{
		    switch(contentType)
		    {
		    	case Form:
		    		return new StringEntity(getQuery(params));
		    		
		    	case JSON:
		    		JSONObject json = JSON.toObject(params);
		    		Util.showLog("SENDING:\n" + json.toString());
		    		return new StringEntity(json.toString());
		    		
		    	case Multipart:
		    		return new ByteArrayEntity(getMulitpartData(params));
		    }
		}
		catch(Exception e){e.printStackTrace();}		
		return null;
	}
		
	public static String getQuery(Bundle params)
	{
		StringBuilder builder = new StringBuilder();	
		if(!Util.nullOrEmpty(params))
		{
			for(String key : params.keySet())
			{
				Object entry = params.get(key);
				if(entry != null)
				{
					if(builder.length() > 1)
					{
						builder.append("&");
					}	
					
					builder.append(key + "=" + Uri.encode(entry.toString()));
				}				
			}	
		}
		
		return builder.toString();
	}
	
	private static byte[] getMulitpartData(Bundle params)
	{
		ByteArrayOutputStream output = new ByteArrayOutputStream();

		try
		{
			for(String key : params.keySet())
			{
				Object value = params.get(key);

				Util.showLog(String.format("%s : %s", key, value));

				output.write(String.format("\r\n--%s\r\n", MULTIPART_BOUNDARY).getBytes());			
				if(value instanceof Attachment)
				{
					try
					{
						Attachment attachment = (Attachment)value;
						output.write(String.format("Content-Disposition: form-data; name=\"%s\"; filename=\"%s\"\r\n", key, attachment.getFileName()).getBytes());	
						output.write(String.format("Content-Type: %s\r\n\r\n", Attachment.getMimeTypeName(attachment.getMimeType())).getBytes());
						output.write(attachment.getData());
					} 
					catch(Exception e){e.printStackTrace();}
				}
				else
				{
					output.write(String.format("Content-Disposition: form-data; name=\"%s\"\r\n\r\n%s", key, value).getBytes());	
				}
			}
			output.write(String.format("\r\n--%s--\r\n", MULTIPART_BOUNDARY).getBytes());			
		}
		catch(Exception e){e.printStackTrace();}
		
		return output.toByteArray();
	}
	
	public static JSONObject getJSONResponse(byte[] bytes) throws Exception
	{
		String jsonString = new String(bytes);
		JSONObject json = new JSONObject(jsonString);
		Util.showLog("RESPONSE:\n" + jsonString);
		
		int status = 0;
		if(json.has("status"))
		{
			status = json.getInt("status");
		}
		
		if(status != 200 || json.has("error"))
		{
			if(status == 0 || status == 401)
			{
				throw new SessionExpiredException();
			}
			
			String message = "Unknown server error.";
			if(json.has("error"))
			{
				message = JSON.getString(json, "error");
			}
			throw new Exception(message);
		}
		
		return json;
	}
	
	public static boolean isTimeout(Exception e)
	{
		return 
			e instanceof UnknownHostException || 
			e instanceof SocketTimeoutException || 
			e instanceof SSLPeerUnverifiedException;
	}
}
