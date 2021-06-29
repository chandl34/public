package com.skoop.uniwellkiosk.util.http;

import android.os.Bundle;
import android.os.Parcel;
import android.os.Parcelable;


public class Attachment
implements Parcelable
{
	//---- CONSTANTS
	private final class Key
	{
		public static final String DATA = "data";
		public static final String FILE_NAME = "fileName";
		public static final String MIME_TYPE = "mimeType";
	}

	public enum MimeType
	{
		JPEG,
		PNG
	}
	
	
	//---- MEMBERS
	private Bundle _data;

	
	//---- SETUP
	public Attachment(byte[] data, String fileName, MimeType mimeType)
	{
		_data = new Bundle();
		_data.putByteArray(Key.DATA, data);
		_data.putString(Key.FILE_NAME, fileName);
		_data.putSerializable(Key.MIME_TYPE, mimeType);
	}
	
	
	//---- METHODS
	public byte[] getData()
	{
		return _data.getByteArray(Key.DATA);
	}
	
	public String getFileName()
	{
		return _data.getString(Key.FILE_NAME);
	}
	
	public MimeType getMimeType()
	{
		return (MimeType)_data.getSerializable(Key.MIME_TYPE);
	}
	
	public static String getMimeTypeName(MimeType mimeType)
	{
		switch(mimeType)
		{
			case JPEG:
				return "image/jpeg";
			case PNG:
				return "image/png";
		}
		return null;
	}
	
	
	//---- Attachment
	@Override
	public int describeContents()
	{
		return 0;
	}

	@Override
	public void writeToParcel(Parcel dest, int flags)
	{
		dest.writeParcelable(_data, flags);
	}
}
