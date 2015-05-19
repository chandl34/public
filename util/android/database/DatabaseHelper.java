package com.surgeworks.divineoffice.util.database;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.DatabaseUtils;
import android.database.sqlite.SQLiteDatabase;

public class DatabaseHelper
{
	//---- CLASSES
	public interface Callback
	{
		public Object run(Context context, Database database, SQLiteDatabase db);
	}
	
	
	//---- FACTORIES
	public static DatabaseEntity load(Context context, Class<?> entityType, final String[] columns, String where)
	{		
		return load(context, null, entityType, columns, where);
	}
	
	public static DatabaseEntity load(Context context, SQLiteDatabase db, Class<?> entityType, final String[] columns, String where)
	{
		List<?> list = loadList(context, db, entityType, columns, where);
		if(list.isEmpty())
		{
			return null;
		}
		
		return (DatabaseEntity)list.get(0);
	}

	public static List<?> loadList(Context context, final Class<?> entityType, final String[] columns, String where)
	{
		return loadList(context, null, entityType, columns, where);
	}

	public static List<?> loadList(Context context, SQLiteDatabase db, final Class<?> entityType, final String[] columns, final String where)
	{
		Callback callback = new Callback()
		{
			@Override
			public Object run(Context context, Database database, SQLiteDatabase db)
			{
				List<DatabaseEntity> list = new ArrayList<DatabaseEntity>();
				try
				{
					DatabaseEntity structure = (DatabaseEntity)entityType.newInstance();			
					Cursor cursor = database.sqlSelect(db, structure.getTableName(), columns, where);
					for(int i = 0; i < cursor.getCount(); ++i)
					{
						cursor.moveToNext();
						
						ContentValues data = new ContentValues();
						DatabaseUtils.cursorRowToContentValues(cursor, data);
						
						DatabaseEntity entity = (DatabaseEntity)entityType.newInstance();
						entity.loadFromData(data);
						list.add(entity);
					}
					cursor.close();
				}
				catch(Exception e)
				{
					e.printStackTrace();
				}		
				
				return list;
			}
		};
		
		return (List<?>)openCloseHelper(context, db, callback);
	}

	public static int count(Context context, final Class<?> entityType, String where)
	{
		return count(context, null, entityType, where);
	}
	
	public static int count(Context context, SQLiteDatabase db, final Class<?> entityType, final String where)
	{
		Callback callback = new Callback()
		{
			@Override
			public Object run(Context context, Database database, SQLiteDatabase db)
			{
				try
				{
					DatabaseEntity entity = (DatabaseEntity)entityType.newInstance();	
					String[] columns = {Key.LOCAL_ID};
					Cursor cursor = database.sqlSelect(db, entity.getTableName(), columns, where);	
					int count = cursor.getCount();
					cursor.close();
					return count;
				}
				catch(Exception e)
				{
					e.printStackTrace();
				}	
				
				return 0;
			}
		};	

		return (Integer)openCloseHelper(context, db, callback);
	}
	
	
	//---- METHODS
	public static void createTables(Context context, final List<Class<?>> entityTypes)
	{
		Callback callback = new Callback()
		{
			@Override
			public Object run(Context context, Database database, SQLiteDatabase db)
			{
				for(int i = 0; i < entityTypes.size(); ++i)
				{
					try
					{
						Class<?> entityType = entityTypes.get(i);
						DatabaseEntity entity = (DatabaseEntity)entityType.newInstance();
						
						database.sqlCreate(db, entity.getTableName(), entity.getTableKeys());
						
						List<String> columns = entity.getTableColumns();
						Iterator<String> iter = columns.iterator();						
						while(iter.hasNext())
						{
							String column = iter.next();
							database.sqlAlter(db, entity.getTableName(), column);
						}
					}
					catch(Exception e)
					{
						e.printStackTrace();
					}									
				}
				
				return null;	
			}
		};
		
		openCloseHelper(context, null, callback);
	}

	public static void clearTables(Context context, final List<Class<?>> entityTypes)
	{
		Callback callback = new Callback()
		{
			@Override
			public Object run(Context context, Database database, SQLiteDatabase db)
			{
				for(int i = 0; i < entityTypes.size(); ++i)
				{
					try
					{
						Class<?> entityType = entityTypes.get(i);
						DatabaseEntity entity = (DatabaseEntity)entityType.newInstance();
						
						database.sqlDelete(db, entity.getTableName(), null);
					}
					catch(Exception e)
					{
						e.printStackTrace();
					}									
				}
				
				return null;	
			}
		};
		
		openCloseHelper(context, null, callback);
	}
		
	public static SQLMethod updateDb(Context context, final DatabaseEntity entity)
	{
		return updateDb(context, null, entity);
	}	
	
	public static SQLMethod updateDb(Context context, SQLiteDatabase db, final DatabaseEntity entity)
	{
		Callback callback = new Callback()
		{
			@Override
			public Object run(Context context, Database database, SQLiteDatabase db)
			{
				SQLMethod method = null;
				
				int count = count(context, db, entity.getClass(), entity.getWhereClause());
				if(count > 0)
				{
					database.sqlUpdate(db, entity.getTableName(), entity.getChanges(), entity.getWhereClause());
					if(entity.getLocalID() == 0)
					{
						Cursor cursor = database.sqlSelect(db, entity.getTableName(), new String[]{Key.LOCAL_ID}, entity.getWhereClause());
						cursor.moveToFirst();
						long localID = cursor.getInt(cursor.getColumnIndex(Key.LOCAL_ID));
						entity.setLocalID(localID);
						cursor.close();
					}
					
					method = SQLMethod.Update;
				}
				else
				{
					long localID = database.sqlInsert(db, entity.getTableName(), entity.getChanges());
					entity.setLocalID(localID);
					
					method = SQLMethod.Insert;
				}

				entity.onUpdate(context, db);
				
				return method;
			}
		};

		return (SQLMethod)openCloseHelper(context, db, callback);
	}

	public static void deleteFromDb(Context context, final DatabaseEntity entity)
	{
		deleteFromDb(context, null, entity);
	}	
	
	public static void deleteFromDb(Context context, SQLiteDatabase db, final DatabaseEntity entity)
	{
		Callback callback = new Callback()
		{
			@Override
			public Object run(Context context, Database database, SQLiteDatabase db)
			{
				if(database.sqlDelete(db, entity.getTableName(), entity.getWhereClause()))
				{
					entity.onDeletion(context, db);
				}
				else
				{
					Util.showLog("COULD NOT DELETE");
				}
				return null;
			}
		};
		
		openCloseHelper(context, db, callback);
	}
	
	private static Object openCloseHelper(Context context, SQLiteDatabase db, Callback callback)
	{
		Database database = Database.getInstance(context);		
		Object object = null;
				
		boolean keepOpen = true;
		if(db == null)
		{
			keepOpen = false;
			db = database.open();
		}
		
		object = callback.run(context, database, db);

		if(!keepOpen)
		{
			database.close();
		}
				
		return object;
	}
}
