#include <Prague/Unicode/Unicode.hh>
#include <iostream.h>
#include <iomanip.h>

using namespace Unicode;

int main (int argc, char **argv) {
  String us("Test!");
  String::iterator i;

  for (i = us.begin(); i != us.end(); i++)
    cout << *i << " ";

  i = us.begin();

  cout << endl << "category(" << *i << "): "
       << i->category() << endl;

  *i = 0x1000;

  for (i = us.begin(); i != us.end(); i++)
    cout << *i << " ";
  
  cout << endl << "DOME!" << endl;
}
