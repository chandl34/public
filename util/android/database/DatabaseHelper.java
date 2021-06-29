package com.skoop.uniwellkiosk.util.database;


import android.content.ContentValues;
import android.content.Context;

import com.skoop.uniwellkiosk.Const.DatabaseKey;
import com.skoop.uniwellkiosk.data.entity.general.DatabaseEntity;
import com.skoop.uniwellkiosk.util.Util;
import com.skoop.uniwellkiosk.util.database.Database.SQLMethod;

import java.util.ArrayList;
import java.util.List;


public class DatabaseHelper
{
	//---- CLASSES
	public interface Callback<T>
	{
		T run(Context context, Database database);
	}


    //---- METHODS
    public static void createTables(Context context, final List<Class<? extends DatabaseEntity>> entityTypes)
    {
        createTables(context, null, entityTypes);
    }

    public static void createTables(Context context, Database database, final List<Class<? extends DatabaseEntity>> entityTypes)
    {
        Callback callback = new Callback()
        {
            @Override
            public Object run(Context context, Database database)
            {
                for(Class<? extends DatabaseEntity> entityType : entityTypes)
                {
                    try
                    {
                        DatabaseEntity entity = entityType.newInstance();

                        database.sqlCreate(entity.getTableName(), entity.getTableColumns());
                    }
                    catch(Exception e)
                    {
                        e.printStackTrace();
                    }
                }

                return null;
            }
        };

        executeDatabase(context, database, callback);
    }

    public static void dropTables(Context context, final List<Class<? extends DatabaseEntity>> entityTypes)
    {
        dropTables(context, null, entityTypes);
    }

    public static void dropTables(Context context, Database database, final List<Class<? extends DatabaseEntity>> entityTypes)
    {
        Callback callback = new Callback()
        {
            @Override
            public Object run(Context context, Database database)
            {
                for(Class<? extends DatabaseEntity> entityType : entityTypes)
                {
                    try
                    {
                        DatabaseEntity entity = entityType.newInstance();

                        database.sqlDrop(entity.getTableName());
                    }
                    catch(Exception e){e.printStackTrace();}
                }

                return null;
            }
        };

        executeDatabase(context, database, callback);
    }

    public static <T extends DatabaseEntity> T load(Context context, Class<T> entityType, String[] columns, String clause)
    {
        return load(context, null, entityType, columns, clause);
    }

    public static <T extends DatabaseEntity> T load(Context context, Database database, Class<T> entityType, String[] columns, String clause)
    {
        List<T> objList = loadList(context, database, entityType, columns, clause);
        if(!Util.nullOrEmpty(objList))
        {
            return objList.get(0);
        }

        return null;
    }

    public static ContentValues load(Context context, String query)
    {
        return load(context, null, query);
    }

    public static ContentValues load(Context context, Database database, String query)
    {
        List<ContentValues> objList = loadList(context, database, query);
        if(!Util.nullOrEmpty(objList))
        {
            return objList.get(0);
        }

        return null;
    }

    public static <T extends DatabaseEntity> List<T> loadList(Context context, Class<T> entityType, String[] columns, String clause)
    {
        return loadList(context, null, entityType, columns, clause);
    }

    public static <T extends DatabaseEntity> List<T> loadList(Context context, Database database, final Class<T> entityType, final String[] columns, final String clause)
    {
        return loadList(context, database, entityType, null, columns, clause);
    }

    public static <T extends DatabaseEntity> List<T> loadList(Context context, Class<T> entityType, final List<Class<? extends DatabaseEntity>> joinedTypes, String[] columns, String clause)
    {
        return loadList(context, null, entityType, joinedTypes, columns, clause);
    }

    public static <T extends DatabaseEntity> List<T> loadList(Context context, Database database, final Class<T> entityType, final List<Class<? extends DatabaseEntity>> joinedTypes, final String[] columns, final String clause)
    {
        Callback callback = new Callback()
        {
            @Override
            public Object run(Context context, Database database)
            {
                try
                {
                    String tables = getTables(entityType, joinedTypes);
                    List<ContentValues> valuesList = database.sqlSelect(tables, columns, clause);
                    List<DatabaseEntity> objList = new ArrayList<>();
                    for(ContentValues values : valuesList)
                    {
                        DatabaseEntity obj = entityType.newInstance();
                        obj.setData(values);
                        objList.add(obj);
                    }

                    return objList;
                }
                catch(Exception e){e.printStackTrace();}

                return null;
            }
        };

        return (List)executeDatabase(context, database, callback);
    }

    public static List<ContentValues> loadList(Context context, String clause)
    {
        return loadList(context, null, clause);
    }

    public static List<ContentValues> loadList(Context context, Database database, final String clause)
    {
        Callback callback = new Callback()
        {
            @Override
            public List<ContentValues> run(Context context, Database database)
            {
                return database.sqlSelect(clause);
            }
        };

        return (List)executeDatabase(context, database, callback);
    }

    public static long count(Context context, Class<? extends DatabaseEntity> entityType, String clause)
    {
        return count(context, null, entityType, clause);
    }

    public static long count(Context context, Database database, final Class<? extends DatabaseEntity> entityType, final String clause)
    {
        Callback callback = new Callback()
        {
            @Override
            public Object run(Context context, Database database)
            {
                try
                {
                    DatabaseEntity entity = entityType.newInstance();

                    return database.sqlCount(entity.getTableName(), clause);
                }
                catch(Exception e){e.printStackTrace();}

                return 0L;
            }
        };

        return (Long)executeDatabase(context, database, callback);
    }

    public static SQLMethod updateDb(Context context, DatabaseEntity entity)
    {
        return updateDb(context, null, entity);
    }

    public static SQLMethod updateDb(Context context, Database database, final DatabaseEntity entity)
    {
        Callback callback = new Callback()
        {
            @Override
            public Object run(Context context, Database database)
            {
                SQLMethod method;

                DatabaseEntity prevEntity = load(context, database, entity.getClass(), new String[]{DatabaseKey.LOCAL_ID}, entity.getWhereClause());

                entity.setModifyTime(System.currentTimeMillis());
                if(prevEntity == null)
                {
                    entity.setCreateTime(entity.getModifyTime());

                    long localID = database.sqlInsert(entity.getTableName(), entity.getChanges());
                    entity.setLocalID(localID);

                    method = SQLMethod.Insert;
                }
                else
                {
                    entity.setLocalID(prevEntity.getLocalID());
                    database.sqlUpdate(entity.getTableName(), entity.getChanges(), entity.getWhereClause());

                    method = SQLMethod.Update;
                }

                entity.onUpdate(context);

                return method;
            }
        };

        return (SQLMethod)executeDatabase(context, database, callback);
    }

    public static void deleteFromDb(Context context, DatabaseEntity entity)
    {
        deleteFromDb(context, null, entity);
    }

    public static void deleteFromDb(Context context, Database database, final DatabaseEntity entity)
    {
        Callback callback = new Callback()
        {
            @Override
            public Object run(Context context, Database database)
            {
                if(database.sqlDelete(entity.getTableName(), entity.getWhereClause()))
                {
                    entity.onDelete(context);
                }

                return null;
            }
        };

        executeDatabase(context, database, callback);
    }

    public static void deleteFromDb(Context context, final Class<? extends DatabaseEntity> entityType, String clause)
    {
        deleteFromDb(context, null, entityType, clause);
    }

    public static void deleteFromDb(Context context, Database database, final Class<? extends DatabaseEntity> entityType, final String clause)
    {
        Callback callback = new Callback()
        {
            @Override
            public Object run(Context context, Database database)
            {
                try
                {
                    DatabaseEntity entity = entityType.newInstance();

                    database.sqlDelete(entity.getTableName(), clause);
                }
                catch(Exception e){e.printStackTrace();}

                return null;
            }
        };

        executeDatabase(context, database, callback);
    }

    private static <T> T executeDatabase(Context context, Database database, Callback<T> callback)
    {
        boolean temp = database == null;
        if(temp)
        {
            database = new Database(context);
        }

        T object = callback.run(context, database);

        if(temp)
        {
            database.close();
        }

        return object;
    }

    private static String getTables(Class<? extends DatabaseEntity> entityType, List<Class<? extends DatabaseEntity>> joinedTypes)
    {
        try
        {
            DatabaseEntity entity = entityType.newInstance();
            if(Util.nullOrEmpty(joinedTypes))
            {
                return entity.getTableName();
            }

            List<String> tableList = new ArrayList<>();
            tableList.add(entity.getTableName());
            for(Class<? extends DatabaseEntity> joinedType : joinedTypes)
            {
                DatabaseEntity joined = joinedType.newInstance();
                tableList.add(joined.getTableName());
            }

            return Util.join(tableList, ", ");
        }
        catch(Exception e){e.printStackTrace();}

        return null;
    }
}
