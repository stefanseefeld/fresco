#include <Babylon/Babylon.hh>
#include <iostream.h>
#include <iomanip.h>

using namespace Babylon;

int main (int argc, char **argv) {
    std::string input;
    cout << "Please enter a string: ";
    getline(cin, input);
    
    Babylon::String txt(input);

    cout << "Logical order: " << txt << endl;

    // Transfor uppercase letters into hebrew
    for(Babylon::String::iterator i = txt.begin();
	i != txt.end();
	++i)
	if (i->value() >= 'A' && i->value() <= 'Z')
	    *i += 0x05D0 - 'A';

    cout << "Visual order : ";

    for(Babylon::vis_iterator i(txt.begin(), txt.end());
	i != txt.end();
	++i)
	if (i->value() > 0x80)
	    cout << char(i->value() - 0x05D0 + 'A');
	else
	    cout << char(i->value());

    cout << endl;
}
