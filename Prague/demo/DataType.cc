#include <Prague/Sys/DataTypeManager.hh>

using namespace Prague;

int main (int argc, char **argv)
{
  if (argc != 3)
    {
      cerr << "Usage : " << argv[0] << " <database> <file>" << endl;
      exit(-1);
    }
  DataTypeManager types(argv[1]);
  cout << argv[2] << " is of type " << types.match(argv[2]) << endl;
}
