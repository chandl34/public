/*
 *  LevelMapThreading.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelMap.h"



void LevelMap::sendToBackground(ViewArgs& va)
{
	pthread_mutex_lock(&_mutex);
	_bgActive = true;
	
	_viewArgs = va;
	
	pthread_cond_signal(&_cond);	
	pthread_mutex_unlock(&_mutex);
}

void* LevelMap::backgroundThread(void*)
{
	//printf("Thread created\n");
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	while(true){
		pthread_mutex_lock(&_mutex);
		
		while(!_bgActive){
			//printf("Thread blocked\n");
			pthread_cond_wait(&_cond, &_mutex);
		}		
		//printf("Thread awake\n");
		_bgActive = false;
		
		if(_bgKill){
			pthread_mutex_unlock(&_mutex);
			break;			
		}
		
		View* v = new View();
		v->findLOS(_viewArgs.gb, _viewArgs.dir, _viewArgs.reason, _viewArgs.kneeling);
		_viewArgs.unit->setBackupView(v);
		
		pthread_mutex_unlock(&_mutex);
	}
	
	//printf("Thread exiting\n");
	[pool release];
	pthread_exit(NULL);
}

