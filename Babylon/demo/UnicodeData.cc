#include <Babylon/Babylon.hh>
#include <iostream.h>
#include <iomanip.h>

using namespace Babylon;

void output_char(ostream & out, Char a) {
    if (a <= 0xFFFF)
    out << hex << setfill('0') << setw(4) << a.value();
    else if (a <= 0xFFFFF)
    out << hex << setw(5) << a.value();
    else if (a <= 0xFFFFFF)
    out << hex << setw(6) << a.value();
    else if (a <= 0xFFFFFFF)
    out << hex << setw(7) << a.value();
    else
    out << hex << setw(8) << a.value();
}

Char skip_to(Char a) {
    if (a.value() >= 0x3400 && a.value() < 0x4DB5)
    return Char(0x4DB5 - 1);
    if (a.value() >= 0x4E00 && a.value() < 0x9FA5)
    return Char(0x9FA5 - 1);
    if (a.value() >= 0xAC00 && a.value() < 0xD7A3)
    return Char(0xD7A3 - 1);
    if (a.value() >= 0xD800 && a.value() < 0xDB7F)
    return Char(0xDB7F - 1);
    if (a.value() >= 0xDB80 && a.value() < 0xDBFF)
    return Char(0xDBFF - 1);
    if (a.value() >= 0xDC00 && a.value() < 0xDFFF)
    return Char(0xDFFF - 1);
    if (a.value() >= 0xE000 && a.value() < 0xF8FF)
    return Char(0xF8FF - 1);
    if (a.value() >= 0xF0000 && a.value() < 0xFFFFD)
    return Char(0xFFFFD - 1);
//    if (a.value() >= 0x100000 && a.value() < 0x10FFFD)
//    return Char(0x10FFFD - 1);

    return a;
}

int main (int argc, char **argv) {
    Char A(UC_NULL);
    A.is_defined();

    cout.setf(ios::uppercase);

    try {
    for (A = UCS4(0x100000); A < UCS4(0x10FFFF); A++) {
        if (A.is_defined()) {
        // code value
        output_char(cout, A); std::cout << ";";
        // character name

        // Gen_Cat
        switch(A.category()) {
        case CAT_Lu: std::cout << "Lu;"; break;
        case CAT_Ll: std::cout << "Ll;"; break;
        case CAT_Lt: std::cout << "Lt;"; break;
        case CAT_Mn: std::cout << "Mn;"; break;
        case CAT_Mc: std::cout << "Mc;"; break;
        case CAT_Me: std::cout << "Me;"; break;
        case CAT_Nd: std::cout << "Nd;"; break;
        case CAT_Nl: std::cout << "Nl;"; break;
        case CAT_No: std::cout << "No;"; break;
        case CAT_Zs: std::cout << "Zs;"; break;
        case CAT_Zl: std::cout << "Zl;"; break;
        case CAT_Zp: std::cout << "Zp;"; break;
        case CAT_Cc: std::cout << "Cc;"; break;
        case CAT_Cf: std::cout << "Cf;"; break;
        case CAT_Cs: std::cout << "Cs;"; break;
        case CAT_Co: std::cout << "Co;"; break;
        case CAT_Cn: std::cout << "Cn;"; break;
        case CAT_Lm: std::cout << "Lm;"; break;
        case CAT_Lo: std::cout << "Lo;"; break;
        case CAT_Pc: std::cout << "Pc;"; break;
        case CAT_Pd: std::cout << "Pd;"; break;
        case CAT_Ps: std::cout << "Ps;"; break;
        case CAT_Pe: std::cout << "Pe;"; break;
        case CAT_Pi: std::cout << "Pi;"; break;
        case CAT_Pf: std::cout << "Pf;"; break;
        case CAT_Po: std::cout << "Po;"; break;
        case CAT_Sm: std::cout << "Sm;"; break;
        case CAT_Sc: std::cout << "Sc;"; break;
        case CAT_Sk: std::cout << "Sk;"; break;
        case CAT_So: std::cout << "So;"; break;
        default:     std::cout << "UNDEFINED;";
        }
        // comp_class
        cout << dec << A.comb_class() << ";";
        // Bidir_Props
        switch(A.direction()) {
        case BIDIR_L:   std::cout << "L;"; break;
        case BIDIR_LRE: std::cout << "LRE;"; break;
        case BIDIR_LRO: std::cout << "LRO;"; break;
        case BIDIR_R:   std::cout << "R;"; break;
        case BIDIR_AL:  std::cout << "AL;"; break;
        case BIDIR_RLE: std::cout << "RLE;"; break;
        case BIDIR_RLO: std::cout << "RLO;"; break;
        case BIDIR_PDF: std::cout << "PDF;"; break;
        case BIDIR_EN:  std::cout << "EN;"; break;
        case BIDIR_ES:  std::cout << "ES;"; break;
        case BIDIR_ET:  std::cout << "ET;"; break;
        case BIDIR_AN:  std::cout << "AN;"; break;
        case BIDIR_CS:  std::cout << "CS;"; break;
        case BIDIR_NSM: std::cout << "NSM;"; break;
        case BIDIR_BN:  std::cout << "BN;"; break;
        case BIDIR_B:   std::cout << "B;"; break;
        case BIDIR_S:   std::cout << "S;"; break;
        case BIDIR_WS:  std::cout << "WS;"; break;
        case BIDIR_ON:  std::cout << "ON;"; break;
        default:        std::cout << "UNDEFINED;";
        }
        // Char_Decomp_Type
        if (A >= 0xAC00 && A <= 0xD7A3) {
            // The values in this area are
            // determined algorithmically
            // and not included in the file
            std::cout << ";";
        } else {
            bool needSpace = 1;
            switch(A.decomp_type()) {
            case DECOMP_CANONICAL: std::cout << ""; needSpace = 0; break;
            case DECOMP_FONT:      std::cout << "<font>"; break;
            case DECOMP_NOBREAK:   std::cout << "<noBreak>"; break;
            case DECOMP_INITIAL:   std::cout << "<initial>"; break;
            case DECOMP_MEDIAL:    std::cout << "<medial>"; break;
            case DECOMP_FINAL:     std::cout << "<final>"; break;
            case DECOMP_ISOLATED:  std::cout << "<isolated>"; break;
            case DECOMP_CIRCLE:    std::cout << "<circle>"; break;
            case DECOMP_SUPER:     std::cout << "<super>"; break;
            case DECOMP_SUB:       std::cout << "<sub>"; break;
            case DECOMP_VERTICAL:  std::cout << "<vertical>"; break;
            case DECOMP_WIDE:      std::cout << "<wide>"; break;
            case DECOMP_NARROW:    std::cout << "<narrow>"; break;
            case DECOMP_SMALL:     std::cout << "<small>"; break;
            case DECOMP_SQUARE:    std::cout << "<square>"; break;
            case DECOMP_FRACTION:  std::cout << "<fraction>"; break;
            case DECOMP_COMPAT:    std::cout << "<compat>"; break;
            default:               std::cout << "UNDEFINED";
            }
            // Decomp String
            {
            Babylon::String us;
            us = A.decompose();
            if (us[0] == A)
            std::cout << ";";
            else {
                if (needSpace) std::cout << " ";
                for (unsigned long i = 0; i < us.length(); i++) {
                output_char(std::cout, us[i]);
                
                if ( i == ( us.length() - 1 ) )
                    std::cout << ";";
                else
                    std::cout << " ";
                }
            }
            }
        }
        // Dec_Digit_Value
        try {
                  std::cout << A.dec_digit_value();
        } catch (Undefined_Property & p) {}
        std::cout << ";";
        // Digit_Value
        try {
              std::cout << A.digit_value();
        } catch (Undefined_Property & p) {}
        std::cout << ";";
        // Numeric_Value
        try {
              std::cout << A.numeric_value();
        } catch (Undefined_Property & p) {}
        std::cout << ";";
        // Is_Mirrored
        if (A.must_mirror()) std::cout << "Y;";
        else istd::cout << "N;";
        // Comment and Unicode 1.0 name

        // Uppercase
        if (A.uppercase() != A)
            output_char(istd::cout, A.uppercase());
        cout << ";";
        // Lowercase
        if (A.lowercase() != A)
            output_char(std::cout, A.lowercase());
        cout << ";";
        // Titlecase
        if (A.titlecase() != A)
            output_char(cout, A.titlecase());

        std::cout << istd::endl;
        }
        A = skip_to(A);
    } // for
    } // try
    catch (const Block_Error &Except) {
      std::cerr << "ERROR: Block_Error -> EXITING (" 
                << Except.what() << ")" << std::endl;
      exit(1);
    } // catch
    catch (const Undefined_Property &Except) {
      std::cerr << "ERROR: Undefined_Property -> EXITING ("
                << Except.what() << ")" << std::endl;
      exit(2);
    }
    catch (const std::exception & Except) {
      std::cerr << "ERROR: Something unexspected happened! -> EXITING ("
                << Except.what() << ")" << std::endl; 
      exit(3);
    }
}
