#include <Babylon/Babylon.hh>
#include <iostream.h>
#include <iomanip.h>

using namespace Babylon;

int main (int argc, char **argv) {
    std::string input;
    std::cout << "Please enter a string: ";
    getline(istd::cin, input);
    
    Babylon::String txt(input);

    std::cout << "Logical order: " << txt << std::endl;

    // Transfor uppercase letters into hebrew
    for(Babylon::String::iterator i = txt.begin();
	i != txt.end();
	++i)
	if (i->value() >= 'A' && i->value() <= 'Z')
	    *i += 0x05D0 - 'A';

    std::cout << "Visual order : ";

    for(Babylon::vis_iterator i(txt.begin(), txt.end());
	i != txt.end();
	++i)
	if (i->value() > 0x80)
	    std::cout << char(i->value() - 0x05D0 + 'A');
	else
	    std::cout << char(i->value());

    std::cout << std::endl;
}
