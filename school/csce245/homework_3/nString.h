// Jonathan Chandler
// nString.h

#ifndef NSTRING_H_
#define NSTRING_H_

#include <stddef.h>
#include <memory.h>
#include <iostream>
using namespace std;

class nString{
	public:
		// Constructors
		nString();		
		nString(const nString & a);
		nString(const char * zstr);
		
		//copy constructor to get n bytes from str, n < the length of str
		//if n is 0 or > length of str, copy the whole str
		nString(const char * str, size_t n);

		// Destructor
		~nString();

		// Assignment and modification operators
		nString & operator=(const nString & right);
		nString & operator=(const char * zstr);
		nString & operator=(const char c);
		nString & operator+=(const nString & right);
		nString & operator+=(const char * zstr);
		nString & operator+=(const char c);

		// Put a char at the end of data, can be used by operators "+=", ">>"
		// and function "Extract"
		size_t Put(const char c);
		
		// set len to 0
		void Clear(void);

		//put a '\0' at the end of data, then init to len=0, ziez=1, and create
		//a new array with this size.
		//function shoudl return the address of the old character array
		char * Extract(void);

		// index operator,l if idx over bound, return '\0'
		char operator[](size_t idx) const;

		//get the lenght of the nString
		size_t Length() const { return len; }

		// nString comparison
		bool operator== (const nString & rhs) const {
			if (len!=rhs.len) return false;
			return memcmp(data, rhs.data, len)==0;
		}

		bool operator!= (const nString & rhs) const {
			return !(*this==rhs);
		}

		//overloaded << operator, simliar to the Print function
		//implemented for the last project
		friend ostream& operator<<(ostream& out, const nString & astr);

		//>> operator, similar to the Read function in the previous project
		//you strill need to loop to get char one by one, until you encounter
		//'\n or EOF
		friend istream& operator>>(istream& in, nString & astr);

	private:
		size_t len;
		size_t size;
	
		//data, not theStr as we used for the second project
		char * data;

};
#endif
