#include <Prague/Unicode/Unicode.hh>
#include <iostream.h>
#include <iomanip.h>

using namespace Unicode;

int main (int argc, char **argv) {
  Unistring US("Test!");
  Unistring::iterator i;

  for (i = US.begin(); i != US.end(); i++)
    cout << *i << " ";

  i = US.begin();

  cout << endl << "GenericCategory(" << *i << "): "
       << i->GenericCategory() << endl;

  *i = 0x1000;

  for (i = US.begin(); i != US.end(); i++)
    cout << *i << " ";
  
  cout << endl << "DOME!" << endl;
}
