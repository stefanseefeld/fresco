#include <Prague/Unicode/Unicode.hh>
#include <iostream.h>
#include <iomanip.h>

using namespace Unicode;

int main (int argc, char **argv) {
  Unicode::Unichar A;
  bool runOverZero = 1;

  cout.setf(ios::uppercase);
  
  for (A = NULL_UNICODE; A > _Unichar(0x0000) || runOverZero; A++) {
    runOverZero = 0;
    try {
      A.GenericCategory(); // breaks the loop for undefined chars
      // code value
      cout << hex << setfill('0') << setw(4) << A.myUnicode()<< ";";
      // Gen_Cat
      switch(A.GenericCategory()) {
      case CAT_Lu: cout << "Lu;"; break;
      case CAT_Ll: cout << "Ll;"; break;
      case CAT_Lt: cout << "Lt;"; break;
      case CAT_Mn: cout << "Mn;"; break;
      case CAT_Mc: cout << "Mc;"; break;
      case CAT_Me: cout << "Me;"; break;
      case CAT_Nd: cout << "Nd;"; break;
      case CAT_Nl: cout << "Nl;"; break;
      case CAT_No: cout << "No;"; break;
      case CAT_Zs: cout << "Zs;"; break;
      case CAT_Zl: cout << "Zl;"; break;
      case CAT_Zp: cout << "Zl;"; break;
      case CAT_Cc: cout << "Cc;"; break;
      case CAT_Cf: cout << "Cf;"; break;
      case CAT_Cs: cout << "Cs;"; break;
      case CAT_Co: cout << "Cs;"; break;
      case CAT_Cn: cout << "Cn;"; break;
      case CAT_Lm: cout << "Lm;"; break;
      case CAT_Lo: cout << "Lo;"; break;
      case CAT_Pc: cout << "Pc;"; break;
      case CAT_Pd: cout << "Pd;"; break;
      case CAT_Ps: cout << "Ps;"; break;
      case CAT_Pe: cout << "Pe;"; break;
      case CAT_Pi: cout << "Pi;"; break;
      case CAT_Pf: cout << "Pf;"; break;
      case CAT_Po: cout << "Po;"; break;
      case CAT_Sm: cout << "Sm;"; break;
      case CAT_Sc: cout << "Sc;"; break;
      case CAT_Sk: cout << "Sk;"; break;
      case CAT_So: cout << "Sc;"; break;
      default:     cout << "UNDEFINED;";
      }
      // comp_class
      cout << A.CanCombClass() << ";";
      // Bidir_Props
      switch(A.Direction()) {
      case BIDIR_L:   cout << "L;"; break;
      case BIDIR_LRE: cout << "LRE;"; break;
      case BIDIR_LRO: cout << "LRO;"; break;
      case BIDIR_R:   cout << "R;"; break;
      case BIDIR_AL:  cout << "AL;"; break;
      case BIDIR_RLE: cout << "RLE;"; break;
      case BIDIR_RLO: cout << "RLO;"; break;
      case BIDIR_PDF: cout << "PDF;"; break;
      case BIDIR_EN:  cout << "EN;"; break;
      case BIDIR_ES:  cout << "ES;"; break;
      case BIDIR_ET:  cout << "ET;"; break;
      case BIDIR_AN:  cout << "AN;"; break;
      case BIDIR_CS:  cout << "CS;"; break;
      case BIDIR_NSM: cout << "NSM;"; break;
      case BIDIR_BN:  cout << "BN;"; break;
      case BIDIR_B:   cout << "B;"; break;
      case BIDIR_S:   cout << "S;"; break;
      case BIDIR_WS:  cout << "WS;"; break;
      case BIDIR_ON:  cout << "ON;"; break;
      default:        cout << "UNDEFINED;";
      }
      // Char_Decomp_Type
      switch(A.DecompType()) {
      case DECOMP_NO_DECOMP: cout << ";"; break;
      case DECOMP_FONT:      cout << "<font>;"; break;
      case DECOMP_NOBREAK:   cout << "<noBreak>;"; break;
      case DECOMP_INITIAL:   cout << "<initial>;"; break;
      case DECOMP_MEDIAL:    cout << "<medial>;"; break;
      case DECOMP_FINAL:     cout << "<final>;"; break;
      case DECOMP_ISOLATED:  cout << "<isolated>;"; break;
      case DECOMP_CIRCLE:    cout << "<circle>;"; break;
      case DECOMP_SUPER:     cout << "<super>;"; break;
      case DECOMP_SUB:       cout << "<sub>;"; break;
      case DECOMP_VERTICAL:  cout << "<vertical>;"; break;
      case DECOMP_WIDE:      cout << "<wide>;"; break;
      case DECOMP_NARROW:    cout << "<narrow>;"; break;
      case DECOMP_SMALL:     cout << "<small>;"; break;
      case DECOMP_SQUARE:    cout << "<square>;"; break;
      case DECOMP_FRACTION:  cout << "<fraction>;"; break;
      case DECOMP_COMPAT:    cout << "<compat>;"; break;
      default:               cout << "UNDEFINED;";
      }
      // Dec_Digit_Value
      try {
	cout << A.DecimalDigitValue() << ";";
      }
      catch(Unicode::UndefinedProperty &Except) {
	cout << ";";
      }
      // Digit_Value
      try {
	cout << A.DigitValue() << ";";
      }
      catch(Unicode::UndefinedProperty &Except) {
	cout << ";";
      }    
      // Numeric_Value
      try {
	cout << A.NumericValue() << ";";
      }
      catch(Unicode::UndefinedProperty &Except) {
	cout << ";";
      }
      // Is_Mirrored
      if (A.MustMirror()) cout << "Y;";
      else cout << "N;";
      // Uppercase
      if ((A.UppercaseEquivalent()).myUnicode() != A.myUnicode())
	cout << hex << setfill('0') << setw(4)
	     << (A.UppercaseEquivalent()).myUnicode();
      cout << ";";
      // Lowercase
      if ((A.LowercaseEquivalent()).myUnicode() != A.myUnicode())
	cout << hex << setfill('0') << setw(4)
	     << (A.LowercaseEquivalent()).myUnicode();
      cout << ";";
      // Titlecase
      if ((A.TitlecaseEquivalent()).myUnicode() != A.myUnicode())
	cout << hex << setfill('0') << setw(4)
	     << (A.TitlecaseEquivalent()).myUnicode();
      cout << ";";
      // EA_Width
      switch(A.EAWidth()) {
      case EA_WIDTH_W:  cout << "EA_WIDTH_W;"; break;
      case EA_WIDTH_F:  cout << "EA_WIDTH_F;"; break;
      case EA_WIDTH_Na: cout << "EA_WIDTH_Na;"; break;
      case EA_WIDTH_H:  cout << "EA_WIDTH_H;"; break;
      case EA_WIDTH_A:  cout << "EA_WIDTH_A;"; break;
      case EA_WIDTH_N:  cout << "EA_WIDTH_N;"; break;
      default:          cout << "UNDEFINED;";
      }
      // Line_Break
      switch(A.LineBreak()) {
      case LB_BK: cout << "LB_BK"; break;
      case LB_CR: cout << "LB_CR"; break;
      case LB_LF: cout << "LB_LF"; break;
      case LB_CM: cout << "LB_CM"; break;
      case LB_SG: cout << "LB_SG"; break;
      case LB_GL: cout << "LB_GL"; break;
      case LB_CB: cout << "LB_CB"; break;
      case LB_SP: cout << "LB_SP"; break;
      case LB_ZW: cout << "LB_ZW"; break;
      case LB_XX: cout << "LB_XX"; break;
      case LB_OP: cout << "LB_OP"; break;
      case LB_CL: cout << "LB_CL"; break;
      case LB_QU: cout << "LB_QU"; break;
      case LB_NS: cout << "LB_NS"; break;
      case LB_EX: cout << "LB_EX"; break;
      case LB_SY: cout << "LB_SY"; break;
      case LB_IS: cout << "LB_IS"; break;
      case LB_PR: cout << "LB_PR"; break;
      case LB_PO: cout << "LB_PO"; break;
      case LB_NU: cout << "LB_NU"; break;
      case LB_AL: cout << "LB_AL"; break;
      case LB_ID: cout << "LB_ID"; break;
      case LB_IN: cout << "LB_IN"; break;
      case LB_HY: cout << "LB_HY"; break;
      case LB_BB: cout << "LB_BB"; break;
      case LB_BA: cout << "LB_BA"; break;
      case LB_SA: cout << "LB_SA"; break;
      case LB_AI: cout << "LB_AI"; break;
      case LB_B2: cout << "LB_B2"; break;
      default:    cout << "UNDEFINED";
      }
      cout << endl;
    }
    catch (Unicode::FileError &Except) {
      cout << "ERROR: "
	   << Except.ErrorFilename << ": "
	   << Except.ErrorMessage << "\n";
    }
    catch (Unicode::UndefinedProperty &Except) {
      //    cout << "ERROR: " << hex << setfill('0') << setw(4)
      //	 << Except.ErrorUC << " has undefined Property ("
      //	 << Except.ErrorProp << ").\n";
    }
    catch (Unicode::BlockError &Except) {
      //    cout << "ERROR: Unicodeblock (" << hex << setfill('0') << setw(4)
      //	 << Except.BlockStart << "-"
      //	 << setfill('0') << setw(4) << Except.BlockEnd << "): "
      //	 << Except.ErrorMessage << "\n";
    }
  }
}
