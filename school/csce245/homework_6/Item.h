#ifndef _ITEM_H_
#define _ITEM_H_

#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

class Item {
 		int t;
  	public:
	        Item() : t(0) {}
       		Item(int i): t(i) {}
        	virtual ~Item() {}
        	int getTime() const {return t;}
        	void setTime(int i) {t = i;}
        	int getKey() const {return t;}
        	virtual bool doit(int i) = 0;
};
#endif
