#include <Babylon/Babylon.hh>
#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>
short int chars[0x10000];
int main(int argc, char **argv)
{
	int chars_count = 0;
	for (int i = 1; i < 0x10000; i ++) {
		Babylon::Char c  = i;
		try {
			c.is_lowercase();
			chars[chars_count ++ ] = i;
//			cout << hex << i << endl;
		} catch (Babylon::UndefinedProperty c) {
		}
	}
	cout << chars_count << " valid characters" << endl;
	int count = 0;
	int undef_count = 0;
	for (int i = 1; i < 10000000; i ++) {
		//Use next string if you want to test only for defined chars
		//Babylon::Char c  = chars[rand() % chars_count];

		//Use next string if you want to test arbitrary chars
		Babylon::Char c  = rand(); 
		try {
		if (c.is_lowercase())
				count ++;
		} catch (Babylon::UndefinedProperty c) {undef_count++;}
	}
	cout << "Lowercase characters found " << count << endl
		<< "Undefined characters found " << undef_count << endl;
}
