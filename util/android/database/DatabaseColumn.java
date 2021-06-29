package com.skoop.uniwellkiosk.util.database;


import java.util.List;


/**
 Created by jmc on 8/3/17.
 */

public class DatabaseColumn
{
    //---- CONSTANTS
    public enum SQLDataType
    {
        SQLNull,
        SQLInteger,
        SQLReal,
        SQLText,
        SQLBlob;

        @Override
        public String toString()
        {
            switch(this)
            {
                default:
                case SQLNull:
                    return "NULL";

                case SQLInteger:
                    return "INTEGER";

                case SQLReal:
                    return "REAL";

                case SQLText:
                    return "TEXT";

                case SQLBlob:
                    return "BLOB";
            }
        }
    }

    public enum SQLProperty
    {
        SQLPrimaryKey,
        SQLAutoincrement;

        @Override
        public String toString()
        {
            switch(this)
            {
                case SQLPrimaryKey:
                    return "PRIMARY KEY";

                case SQLAutoincrement:
                    return "AUTOINCREMENT";
            }

            return null;
        }
    }


    //---- CLASSES
    public static class SQLDefault
    {
        private Object _value;

        public SQLDefault(Object value)
        {
            _value = value;
        }

        @Override
        public String toString()
        {
            return "DEFAULT '" + _value.toString() + "'";
        }
    }


    //---- MEMBERS
    private String _name;
    private SQLDataType _dataType;
    private List<SQLProperty> _propertyList;
    private SQLDefault _default;


    //---- SETUP
    public DatabaseColumn(String name, SQLDataType dataType)
    {
        init(name, dataType, null, null);
    }

    public DatabaseColumn(String name, SQLDataType dataType, List<SQLProperty> propertyList)
    {
        init(name, dataType, propertyList, null);
    }

    public DatabaseColumn(String name, SQLDataType dataType, SQLDefault defaultValue)
    {
        init(name, dataType, null, defaultValue);
    }

    public DatabaseColumn(String name, SQLDataType dataType, List<SQLProperty> propertyList, SQLDefault defaultValue)
    {
        init(name, dataType, propertyList, defaultValue);
    }

    private void init(String name, SQLDataType dataType, List<SQLProperty> propertyList, SQLDefault defaultValue)
    {
        _name = name;
        _dataType = dataType;
        _propertyList = propertyList;
        _default = defaultValue;
    }


    //---- METHODS
    public String getName()
    {
        return _name;
    }

    @Override
    public String toString()
    {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(_name).append(" ").append(_dataType);
        if(_propertyList != null)
        {
            for(SQLProperty property : _propertyList)
            {
                stringBuilder.append(" ").append(property);
            }
        }

        if(_default != null)
        {
            stringBuilder.append(" ").append(_default);
        }

        return stringBuilder.toString();
    }
}
