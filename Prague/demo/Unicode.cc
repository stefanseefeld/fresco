#include <Prague/Unicode/Unicode.hh>
#include <iostream.h>
#include <iomanip.h>

int main (int argc, char **argv) {
  Unicode::Unichar A( Unicode::_Unichar(10) );

  try {
    cout << "Unicode Test:" << A.GenericCategory() << "\n";
  }
  catch (Unicode::FileError &Except) {
    cout << "ERROR: "
	 << Except.ErrorFilename << ": "
	 << Except.ErrorMessage << "\n";
  }
  catch (Unicode::UndefinedUnichar &Except ) {
    cout << "ERROR: " << hex << setfill('0') << setw(4)
	 << Except.ErrorUC << " undefined!\n";
  }
  catch (Unicode::UndefinedUnicharProperty &Except) {
    cout << "ERROR: " << hex << setfill('0') << setw(4)
	 << Except.ErrorUC << " has undefined Property ("
	 << Except.ErrorProp << ").\n";
  }
  catch (Unicode::UnicodeBlockError &Except) {
    cout << "ERROR: Unicodeblock (" << hex << setfill('0') << setw(4)
	 << Except.BlockStart << "-"
	 << setfill('0') << setw(4) << Except.BlockEnd << "): "
	 << Except.ErrorMessage << "\n";
  }
  
  Unicode::Unichar B( Unicode::_Unichar(250) );
  try {
    cout << "Unicode Test:" << B.GenericCategory() << "\n";
  }
  catch (Unicode::FileError &Except) {
    cout << "ERROR: "
	 << Except.ErrorFilename << ": "
	 << Except.ErrorMessage << "\n";
  }
  catch (Unicode::UndefinedUnichar &Except ) {
    cout << "ERROR: " << hex << setfill('0') << setw(4)
	 << Except.ErrorUC << " undefined!\n";
  }
  catch (Unicode::UndefinedUnicharProperty &Except) {
    cout << "ERROR: " << hex << setfill('0') << setw(4)
	 << Except.ErrorUC << " has undefined Property ("
	 << Except.ErrorProp << ").\n";
  }
  catch (Unicode::UnicodeBlockError &Except) {
    cout << "ERROR: Unicodeblock (" << hex << setfill('0') << setw(4)
	 << Except.BlockStart << "-"
	 << setfill('0') << setw(4) << Except.BlockEnd << "): "
	 << Except.ErrorMessage << "\n";
  }
}
