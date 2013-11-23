// Joanthan Chandler
// Main.C

#include "nString.h"

int main(){
	// Testing constructor 1
	nString str1;
	cout << "str1:  " << str1  << "   len:  " << str1.Length() << endl;  // should print nothing
	
	// Testing constructor 3
	nString *str2 = new nString("Testing...");
	cout << "str2:  " << *str2 << "   len:  " << (*str2).Length() << endl;	
	
	// Testing constructor 2
	nString *str3 = new nString(*str2);
	cout << "str3:  " << *str3 << "   len:  " << (*str3).Length() << endl;
	
	// Testing constructor 5
	nString str4;
	str4 = '!';
	cout << "str4:  " << str4 << "   len:  " << str4.Length() <<  endl;
	
	// Testing for memory leaks
	str4 = *str3;
	cout << "str4:  " << str4 << "   len:  " << str4.Length() <<  endl;	

	// Testing Put and constructor 2
	(*str3).Put('3');
	cout << "str2:  " << *str2 <<  "   len:  " << (*str2).Length() <<  endl;		
	cout << "str3:  " << *str3 << "   len:  " << (*str3).Length() << endl;
	
	// Testing input/output
	cout << "Input string 5:  ";
	nString str5;
	cin >> str5;
	cout << "str5:  " << str5 << "   len:  " << str5.Length() << endl;
	
	// Testing +=
	*str2 += *str3;
	cout << "str2:  " << *str2 << "   len:  " << (*str2).Length() << endl;		
	cout << "str3:  " << *str3 << "   len:  " << (*str3).Length() << endl;
	str1 += "I AM TEST 1!";
	cout << "str1:  " << str1  << "   len:  " << str1.Length() << endl;
	
	// Testing Extract()
	char *str = str1.Extract();
	cout << "str1 was:  " << str << endl;
	delete [] str;
	cout << "str1 is:  " << str1  << "   len:  " << str1.Length() << endl; // should print nothing

	delete str2;
	delete str3;

	int i;
	cin >> i;

	return 0;	
}
