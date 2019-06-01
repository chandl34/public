#!/usr/bin/env python3

import argparse
import mysql.connector
import os
import json


#---- METHODS
def db_connect(host, port, user, password):
    config = {"host": host, "port": port, "user": user, "password": password}
    db = mysql.connector.connect(**config)
    return db

def import_runs(directory, db):
    cursor = db.cursor()
    
    query = "SELECT MAX(timestamp) FROM slay_the_spire.run";
    cursor.execute(query)
    result = cursor.fetchone()
    last_timestamp = result[0]
    
    count = 0
    for root, dirs, files in os.walk(directory):
        for name in files:
            path = os.path.join(root, name)
            
            filename, file_extension = os.path.splitext(path)
            if file_extension != ".run":
                continue
            
            timestamp, file_extension = os.path.splitext(name)
            if last_timestamp >= int(timestamp):
               continue
            
            import_run(path, cursor)
            count = count + 1

    if count == 0:
        print("No new runs to import")
    else:
        db.commit()

def import_run(path, cursor):
    with open(path) as f:
        data = json.load(f)
        
        if data["is_daily"]:
            return
        
        print("Importing data from", path)
        
        play_id = data["play_id"]
        timestamp = data["timestamp"]
        ascension_level = data["ascension_level"]
        victory = data["victory"]
        floor_reached = data["floor_reached"]
        character = data["character_chosen"]
        
        query = ("REPLACE INTO slay_the_spire.run "
                 "SET play_id=%s, timestamp=%s, ascension_level=%s, victory=%s, floor_reached=%s, character_id="
                 "(SELECT id FROM slay_the_spire.character WHERE name=%s)")
        cursor.execute(query, (play_id, timestamp, ascension_level, victory, floor_reached, character))


#---- BODY
parser = argparse.ArgumentParser()

parser.add_argument("--host", dest="host")
parser.add_argument("--port", dest="port")
parser.add_argument("--user", dest="user")
parser.add_argument("--password", dest="password")
parser.add_argument("--directory", dest="directory")

args = parser.parse_args()
host = args.host if args.host else "127.0.0.1"
port = args.port if args.port else 3306

db = db_connect(host, port, args.user, args.password)
import_runs(args.directory, db)
