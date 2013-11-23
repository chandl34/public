// Jonathan Chandler
// nString.C

#include "nString.h"

// CONSTRUCTORS //
nString::nString(){
	size = 1;
	len = 0;
	data = new char[size];
	data[len] = '\0';
}

nString::nString(const nString & a){
	*this = a;	
	data[len] = '\0';
}

nString::nString(const char * zstr){
	*this = zstr;
	data[len] = '\0';
}

//copy constructor to get n bytes from str, n < the length of str
//if n is 0 or > length of str, copy the whole str
nString::nString(const char * str, size_t n){
	for(len = 0; str[len] != '\0'; len++); 	// finding length
	if(n > 0 && n <= len)
		len = n;							// resetting length to n if it is within bounds 
	size = len + 1;
	data = new char[size];
	memcpy(data, str, len);			
	data[len] = '\0';	
}


// Destructor
nString::~nString(){
	delete [] data;	
}

// Assignment and modification operators
nString & nString::operator=(const nString & right){
	if(*this != right){
		delete[] data;
		len = right.len;
		if(size <= len)						// expanding if necessary
			size = len + 25;		
		data = new char[size];
		memcpy(data, right.data, len);
	}
	return *this;
}

nString & nString::operator=(const char * zstr){
	if(data != zstr){
		delete [] data;
		for(len = 0; zstr[len] != '\0'; len++);
		size = len + 1;
		data = new char[size];
		memcpy(data, zstr, len);
	}
	return *this;
}

nString & nString::operator=(const char c){
	delete [] data;
	size = 2;
	len = 1;
	data = new char[size];
	data[0] = c;
	data[1] = '\0';
	return *this;	
}

nString & nString::operator+=(const nString & right){
	for(int i = 0; right.data[i] != '\0'; i++)
		Put(right.data[i]);
	return *this;	
}

nString & nString::operator+=(const char * zstr){
	for(int i = 0; zstr[i] != '\0'; i++)
		Put(zstr[i]);
	return *this;	
}

nString & nString::operator+=(const char c){
	Put(c);
	return *this;	
}

// Put a char at the end of data, can be used by operators "+=", ">>"
// and function "Extract"
size_t nString::Put(const char c){
	if(len + 1 >= size){
		char *temp = new char[len + 25];
		memcpy(temp, data, len);
		delete [] data;
		data = temp;	
	}		
	data[len] = c;
	len++;
	data[len] = '\0';
	return 0; // ???
}

// set len to 0
void nString::Clear(void){
	len = 0;	
	data[len] = '\0';
}

//put a '\0' at the end of data, then init to len=0, ziez=1, and create
//a new array with this size.
//function shoudl return the address of the old character array
char * nString::Extract(void){
	char *temp = data;
	data = new char[1];	
	size = 1;				
	Clear();
	return temp;	
}

// index operator,l if idx over bound, return '\0'
char nString::operator[](size_t idx) const{
	if(idx >= len)
		return '\0';
	return data[idx];	
}

//overloaded << operator, simliar to the Print function
//implemented for the last project
ostream& operator<<(ostream& out, const nString & astr){
	for(int i = 0; astr.data[i] != '\0'; i++){
		out << astr.data[i];
	}
	return out;
}

//>> operator, similar to the Read function in the previous project
//you strill need to loop to get char one by one, until you encounter
//'\n or EOF
istream& operator>>(istream& in, nString & astr){
	char temp = in.get();
	while(temp != EOF && temp != '\n'){
		astr.Put(temp);
		temp = in.get();
	}
	return in;
}
