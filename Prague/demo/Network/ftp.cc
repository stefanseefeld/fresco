#include <Prague/Network/ftp.hh>
#include <unistd.h>

using namespace Prague;

int main (int argc, char **argv)
{
  if (argc != 4)
    {
      cerr << "Usage : " << argv[0] << " hostname user filename\n";
      return 1;
    }
  ftp f(&cout);

  f->connect(argv[1]);
  cerr << "#" << endl;
  f->get_response();
  cerr << "#" << endl;
  // set access 
  f->user(argv[2]);
  cerr << "#" << endl;
  f->passwd(getpass("passwd: "));
  cerr << "#" << endl;
  // get help
  f->help();
  cerr << "#" << endl;
  // set representation type to image
  f->rep_type(ftp::rt_image);
  cerr << "#" << endl;
  // list the home directory
  f->list();
  cerr << "#" << endl;
  // quit
  f->quit();
}
    
