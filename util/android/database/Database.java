package com.surgeworks.divineoffice.util.database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class Database
extends SQLiteOpenHelper
{
	//---- CONSTANTS
	private static final String DATABASE_NAME = "company.project.sqlite";
	private static final int DATABASE_VERSION = 1;
	
	
	//---- MEMBERS
	private static Database _instance;
	private SQLiteDatabase _db;

	
	//---- SETUP
	private Database(Context context)
	{
		super(context, DATABASE_NAME, null, DATABASE_VERSION);

		_db = getWritableDatabase();
	}
	
	@Override
	public void onCreate(SQLiteDatabase db){}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion){}
	

	//---- FACTORIES
	public static Database getInstance(Context context)
	{
		if(_instance == null)
		{
			_instance = new Database(context);
		}
		
		return _instance;
	}
	
	
	//---- METHODS
	public SQLiteDatabase open()
	{
		//_mutex.lock();
		//Util.showLog("database open");
		//return getWritableDatabase("password");
		return _db;
	}

	@Override
	public void close()
	{
		/*
		if(_mutex.isHeldByCurrentThread())
		{
			//Util.showLog("database close");
			super.close();
			_mutex.unlock();
		}	
		*/
	}
			
	private boolean sqlQuery(SQLiteDatabase db, String query)	
	{
		try
		{
			db.execSQL(query);
			return true;
		}
		catch(Exception e){e.printStackTrace();}	
		return false;
	}
	
	public Cursor sqlSelect(SQLiteDatabase db, String query)
	{
		//Util.showLog(query);		
		try
		{
			return db.rawQuery(query, null);
		}
		catch(Exception e){e.printStackTrace();}	
		return null;
	}

	public void sqlCreate(SQLiteDatabase db, String table, String keys)	
	{
	    String query = "CREATE TABLE IF NOT EXISTS ";
	    query += table + " (" + keys + ")";
	    
	    sqlQuery(db, query);
	}
	
	public void sqlAlter(SQLiteDatabase db, String table, String column)
	{
		// Check if column exists
		String query = "SELECT " + column + " ";
		query += "FROM " + table;
			
		Cursor cursor = sqlSelect(db, query);
		if(cursor != null)
		{
			cursor.close();
		}
		else
		{
			//Util.showLog("adding:  " + column + " to " + table);
	        query = "ALTER TABLE " + table + " ";
	        query += "ADD " + column + " TEXT";
	        			
	        sqlQuery(db, query);		
		}
	}

	public void sqlDrop(SQLiteDatabase db, String table)
	{
	    String query = "DROP TABLE IF EXISTS " + table;
	    sqlQuery(db, query);
	}

	public Cursor sqlSelect(SQLiteDatabase db, String table, String[] columns, String where)
	{
		String columns_ = "*";
		if(!Util.nullOrEmpty(columns))
		{
			columns_ = Util.join(columns, ", ");
		}
			
	    String query = "SELECT " + columns_ + " FROM " + table + " ";
	    if(!Util.nullOrEmpty(where))
	    {
		    query += "WHERE " + where;
	    }
	    
	    return sqlSelect(db, query);
	}

	public void sqlUpdate(SQLiteDatabase db, String table, ContentValues values, String where)
	{
	    db.update(table, values, where, null);
	}

	public long sqlInsert(SQLiteDatabase db, String table, ContentValues values)
	{
	    return db.insert(table, null, values);
	}

	public boolean sqlDelete(SQLiteDatabase db, String table, String where)
	{
	    return db.delete(table, where, null) > 0;
	}
}
