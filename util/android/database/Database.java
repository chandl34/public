package com.skoop.uniwellkiosk.util.database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.DatabaseUtils;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import com.skoop.uniwellkiosk.util.Util;

import java.io.Closeable;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class Database
extends SQLiteOpenHelper
implements Closeable
{
    //---- CONSTANTS
    public enum SQLMethod
    {
        Insert,
        Update,
        Delete
    }

    public static final String DATABASE_NAME = "company.project.sqlite";
	private static final int DATABASE_VERSION = 1;
	
	
	//---- MEMBERS
    private static Lock _mutex = new ReentrantLock();
	private SQLiteDatabase _db;

	
	//---- SETUP
	public Database(Context context)
	{
		super(context, DATABASE_NAME, null, DATABASE_VERSION);

        _mutex.lock();
        _db = getWritableDatabase();
        _db.beginTransaction();
	}

	@Override
	public void onCreate(SQLiteDatabase db){}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion){}


	//---- Closeable
    @Override
    public void close()
    {
        _db.setTransactionSuccessful();
        _db.endTransaction();
        _db.close();
        _mutex.unlock();
    }


	//---- METHODS
    private boolean sqlExecute(String query)
    {
        return sqlExecute(query, true);
    }

	private boolean sqlExecute(String query, boolean showError)
	{
		try
		{
			_db.execSQL(query);
			return true;
		}
		catch(Exception e)
        {
            if(showError)
            {
                e.printStackTrace();
            }
        }
		return false;
	}
	
	private Cursor sqlQuery(String query)
	{
		try
		{
			return _db.rawQuery(query, null);
		}
		catch(Exception e){e.printStackTrace();}
		return null;
	}

	public boolean sqlCreate(String table, List<DatabaseColumn> columnList)
	{
	    String query = String.format("CREATE TABLE IF NOT EXISTS %s", table);
        if(!Util.nullOrEmpty(columnList))
        {
            List<String> stringList = new ArrayList<>();
            for(DatabaseColumn column : columnList)
            {
                stringList.add(column.toString());
            }

            String columns = Util.join(stringList, ", ");
            query += " (" + columns + ")";
        }
	    
	    return sqlExecute(query);
	}

	public boolean sqlAlter(String table, DatabaseColumn column)
	{
        String query = String.format("ALTER TABLE %s ADD %s", table, column);
        return sqlExecute(query, false);
	}

	public boolean sqlDrop(String table)
	{
	    String query = String.format("DROP TABLE IF EXISTS %s", table);
	    return sqlExecute(query);
	}

    public List<ContentValues> sqlSelect(String query)
    {
        Cursor cursor = sqlQuery(query);

        List list = new ArrayList();
        if(cursor != null)
        {
            for(int i = 0; i < cursor.getCount(); ++i)
            {
                cursor.moveToNext();

                ContentValues data = new ContentValues();
                DatabaseUtils.cursorRowToContentValues(cursor, data);

                list.add(data);
            }
            cursor.close();
        }

        return list;
    }

	public List<ContentValues> sqlSelect(String table, String[] columns, String clause)
	{
		String columns_ = "*";
		if(!Util.nullOrEmpty(columns))
		{
			columns_ = Util.join(columns, ", ");
		}

		if(clause == null)
        {
            clause = "";
        }

	    String query = String.format("SELECT %s FROM %s %s", columns_, table, clause);
	    return sqlSelect(query);
	}

	public long sqlCount(String table, String clause)
    {
        if(clause == null)
        {
            clause = "";
        }

        String query = String.format("SELECT COUNT(*) FROM %s %s", table, clause);
        Cursor cursor = sqlQuery(query);

        long count = 0;
        if(cursor != null && cursor.getCount() > 0)
        {
            cursor.moveToFirst();
            count = cursor.getInt(0);
        }

        cursor.close();

        return count;
    }

    public long sqlInsert(String table, ContentValues values)
    {
        return _db.insert(table, null, values);
    }

	public boolean sqlUpdate(String table, ContentValues values, String clause)
	{
        if(clause == null)
        {
            clause = "";
        }

        String updateClause = getUpdateClause(values);
        String query = String.format("UPDATE %s SET %s %s", table, updateClause, clause);

        return sqlExecute(query);
	}

    private String getUpdateClause(ContentValues values)
    {
        List<String> updateList = new ArrayList<>();

        for(String key : values.keySet())
        {
            String value = values.getAsString(key);
            value = value.replace("'", "''");

            String update = String.format("%s='%s'", key, value);
            updateList.add(update);
        }

        return Util.join(updateList, ", ");
    }

	public boolean sqlDelete(String table, String clause)
	{
        if(clause == null)
        {
            clause = "";
        }

        String query = String.format("DELETE FROM %s %s", table, clause);
        return sqlExecute(query);
	}
}
