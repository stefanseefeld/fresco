#include <Babylon/Babylon.hh>
#include <iostream.h>
#include <iomanip.h>

using namespace Babylon;

int main (int argc, char **argv) {
    UCS4 chars = 0;
    UCS4 undefined = 0;

    Char A(0x0000AC00);
    A.is_defined();

    cout.setf(ios::uppercase);

    for (A = UCS4(0x00000000); A < UCS4(0x00110000); A++) {
	try {
	    if (A.is_defined()) {
		chars++;
		// code value
		cout << hex << setfill('0') << setw(8) << A.value() << ";";
		// Gen_Cat
		switch(A.category()) {
		case CAT_Lu: cout << "Lu;" << flush; break;
		case CAT_Ll: cout << "Ll;" << flush; break;
		case CAT_Lt: cout << "Lt;" << flush; break;
		case CAT_Mn: cout << "Mn;" << flush; break;
		case CAT_Mc: cout << "Mc;" << flush; break;
		case CAT_Me: cout << "Me;" << flush; break;
		case CAT_Nd: cout << "Nd;" << flush; break;
		case CAT_Nl: cout << "Nl;" << flush; break;
		case CAT_No: cout << "No;" << flush; break;
		case CAT_Zs: cout << "Zs;" << flush; break;
		case CAT_Zl: cout << "Zl;" << flush; break;
		case CAT_Zp: cout << "Zp;" << flush; break;
		case CAT_Cc: cout << "Cc;" << flush; break;
		case CAT_Cf: cout << "Cf;" << flush; break;
		case CAT_Cs: cout << "Cs;" << flush; break;
		case CAT_Co: cout << "Co;" << flush; break;
		case CAT_Cn: cout << "Cn;" << flush; break;
		case CAT_Lm: cout << "Lm;" << flush; break;
		case CAT_Lo: cout << "Lo;" << flush; break;
		case CAT_Pc: cout << "Pc;" << flush; break;
		case CAT_Pd: cout << "Pd;" << flush; break;
		case CAT_Ps: cout << "Ps;" << flush; break;
		case CAT_Pe: cout << "Pe;" << flush; break;
		case CAT_Pi: cout << "Pi;" << flush; break;
		case CAT_Pf: cout << "Pf;" << flush; break;
		case CAT_Po: cout << "Po;" << flush; break;
		case CAT_Sm: cout << "Sm;" << flush; break;
		case CAT_Sc: cout << "Sc;" << flush; break;
		case CAT_Sk: cout << "Sk;" << flush; break;
		case CAT_So: cout << "So;" << flush; break;
		default:     cout << "UNDEFINED;" << flush;
		}
		// comp_class
		cout << dec << A.comb_class() << ";" << flush;
		// Bidir_Props
		switch(A.direction()) {
		case BIDIR_L:   cout << "L;" << flush; break;
		case BIDIR_LRE: cout << "LRE;" << flush; break;
		case BIDIR_LRO: cout << "LRO;" << flush; break;
		case BIDIR_R:   cout << "R;" << flush; break;
		case BIDIR_AL:  cout << "AL;" << flush; break;
		case BIDIR_RLE: cout << "RLE;" << flush; break;
		case BIDIR_RLO: cout << "RLO;" << flush; break;
		case BIDIR_PDF: cout << "PDF;" << flush; break;
		case BIDIR_EN:  cout << "EN;" << flush; break;
		case BIDIR_ES:  cout << "ES;" << flush; break;
		case BIDIR_ET:  cout << "ET;" << flush; break;
		case BIDIR_AN:  cout << "AN;" << flush; break;
		case BIDIR_CS:  cout << "CS;" << flush; break;
		case BIDIR_NSM: cout << "NSM;" << flush; break;
		case BIDIR_BN:  cout << "BN;" << flush; break;
		case BIDIR_B:   cout << "B;" << flush; break;
		case BIDIR_S:   cout << "S;" << flush; break;
		case BIDIR_WS:  cout << "WS;" << flush; break;
		case BIDIR_ON:  cout << "ON;" << flush; break;
		default:        cout << "UNDEFINED;" << flush;
		}
		// Char_Decomp_Type
		bool needSpace = 1;
		switch(A.decomp_type()) {
		case DECOMP_NO_DECOMP: cout << "" << flush; needSpace = 0; break;
		case DECOMP_FONT:      cout << "<font>" << flush; break;
		case DECOMP_NOBREAK:   cout << "<noBreak>" << flush; break;
		case DECOMP_INITIAL:   cout << "<initial>" << flush; break;
		case DECOMP_MEDIAL:    cout << "<medial>" << flush; break;
		case DECOMP_FINAL:     cout << "<final>" << flush; break;
		case DECOMP_ISOLATED:  cout << "<isolated>" << flush; break;
		case DECOMP_CIRCLE:    cout << "<circle>" << flush; break;
		case DECOMP_SUPER:     cout << "<super>" << flush; break;
		case DECOMP_SUB:       cout << "<sub>" << flush; break;
		case DECOMP_VERTICAL:  cout << "<vertical>" << flush; break;
		case DECOMP_WIDE:      cout << "<wide>" << flush; break;
		case DECOMP_NARROW:    cout << "<narrow>" << flush; break;
		case DECOMP_SMALL:     cout << "<small>" << flush; break;
		case DECOMP_SQUARE:    cout << "<square>" << flush; break;
		case DECOMP_FRACTION:  cout << "<fraction>" << flush; break;
		case DECOMP_COMPAT:    cout << "<compat>" << flush; break;
		default:               cout << "UNDEFINED" << flush;
		}
		// Decomp String
		{
		    Babylon::String us;
		    us = A.decompose();
		    if (us[0] == A)
			cout << ";" << flush;
		    else {
			if (needSpace) cout << " " << flush;
			for (unsigned long i = 0; i < us.length(); i++) {
			    cout << hex << setfill('0') << setw(4) << us[i].value() << flush;
			    if ( i == ( us.length() - 1 ) )
				cout << ";" << flush;
			    else
				cout << " " << flush;
			}
		    }
		}
		// Dec_Digit_Value
		if (A.is_Decimal_Digit())
		    cout << A.dec_digit_value();
		cout << ";";
		// Digit_Value
		if (A.is_Digit())
		    cout << A.digit_value();
		cout << ";";
		// Numeric_Value
		if (A.is_Numeric())
		    cout << A.numeric_value();
		cout << ";";
		// Is_Mirrored
		if (A.must_mirror()) cout << "Y;" << flush;
		else cout << "N;" << flush;
		// Uppercase
		if (A.uppercase() != A)
		    cout << hex << setfill('0') << setw(8)
			 << A.uppercase().value() << flush;
		cout << ";" << flush;
		// Lowercase
		if (A.lowercase() != A)
		    cout << hex << setfill('0') << setw(8)
			 << A.lowercase().value() << flush;
		cout << ";" << flush;
		// Titlecase
		if (A.titlecase() != A)
		    cout << hex << setfill('0') << setw(8)
			 << A.titlecase().value() << flush;
		cout << ";" << flush;
		// EA_Width
		switch(A.EA_width()) {
		case EA_WIDTH_W:  cout << "EA_WIDTH_W;" << flush; break;
		case EA_WIDTH_F:  cout << "EA_WIDTH_F;" << flush; break;
		case EA_WIDTH_Na: cout << "EA_WIDTH_Na;" << flush; break;
		case EA_WIDTH_H:  cout << "EA_WIDTH_H;" << flush; break;
		case EA_WIDTH_A:  cout << "EA_WIDTH_A;" << flush; break;
		case EA_WIDTH_N:  cout << "EA_WIDTH_N;" << flush; break;
		default:          cout << "UNDEFINED;" << flush;
		}
		// Line_Break
		switch(A.linebreak()) {
		case LB_BK: cout << "LB_BK" << flush; break;
		case LB_CR: cout << "LB_CR" << flush; break;
		case LB_LF: cout << "LB_LF" << flush; break;
		case LB_CM: cout << "LB_CM" << flush; break;
		case LB_SG: cout << "LB_SG" << flush; break;
		case LB_GL: cout << "LB_GL" << flush; break;
		case LB_CB: cout << "LB_CB" << flush; break;
		case LB_SP: cout << "LB_SP" << flush; break;
		case LB_ZW: cout << "LB_ZW" << flush; break;
		case LB_XX: cout << "LB_XX" << flush; break;
		case LB_OP: cout << "LB_OP" << flush; break;
		case LB_CL: cout << "LB_CL" << flush; break;
		case LB_QU: cout << "LB_QU" << flush; break;
		case LB_NS: cout << "LB_NS" << flush; break;
		case LB_EX: cout << "LB_EX" << flush; break;
		case LB_SY: cout << "LB_SY" << flush; break;
		case LB_IS: cout << "LB_IS" << flush; break;
		case LB_PR: cout << "LB_PR" << flush; break;
		case LB_PO: cout << "LB_PO" << flush; break;
		case LB_NU: cout << "LB_NU" << flush; break;
		case LB_AL: cout << "LB_AL" << flush; break;
		case LB_ID: cout << "LB_ID" << flush; break;
		case LB_IN: cout << "LB_IN" << flush; break;
		case LB_HY: cout << "LB_HY" << flush; break;
		case LB_BB: cout << "LB_BB" << flush; break;
		case LB_BA: cout << "LB_BA" << flush; break;
		case LB_SA: cout << "LB_SA" << flush; break;
		case LB_AI: cout << "LB_AI" << flush; break;
		case LB_B2: cout << "LB_B2" << flush; break;
		default:    cout << "UNDEFINED" << flush;
		}
		if (A.is_Zero_width())
		    cout << ";Zero_width";
		if (A.is_Space())
		    cout << ";Space";
		if (A.is_White_space())
		    cout << ";White_space";
		if (A.is_Non_break())
		    cout << ";Non_break";
		if (A.is_ISO_Control())
		    cout << ";ISO_Control";
		if (A.is_Bidi_Control())
		    cout << ";Bidi_Control";
		if (A.is_Join_Control())
		    cout << ";Join_Control";
		if (A.is_Format_Control())
		    cout << ";Format_Control";
		if (A.is_Dash())
		    cout << ";Dash";
		if (A.is_Hyphen())
		    cout << ";Hyphen";
		if (A.is_Punctuation())
		    cout << ";Punctuation";
		if (A.is_Line_Separator())
		    cout << ";Line_Separator";
		if (A.is_Paragraph_Separator())
		    cout << ";Paragraph_Separator";
		if (A.is_Quotation_Mark())
		    cout << ";Quotation_Mark";
		if (A.is_Terminal_Punctuation())
		    cout << ";Terminal_Punctuation";
		if (A.is_Currency_Symbol())
		    cout << ";Currency_Symbol";
		if (A.is_Math())
		    cout << ";Math";
		if (A.is_Paired_Punctuation())
		    cout << ";Paired_Punctuation";
		if (A.is_Left_of_Pair())
		    cout << ";Left_of_Pair";
		if (A.is_Combining())
		    cout << ";Combining";
		if (A.is_Non_spacing())
		    cout << ";Non_spacing";
		if (A.is_Composite())
		    cout << ";Composite";
		if (A.is_Hex_Digit())
		    cout << ";Hex_Digit";
		// if (A.is_Decimal_Digit())
		//     cout << ";Decimal_Digit";
		// if (A.is_Numeric())
		//     cout << ";Numeric";
		if (A.is_Alphabetic())
		    cout << ";Alphabetic";
		if (A.is_Ideographic())
		    cout << ";Ideographic";
		if (A.is_Diacritic())
		    cout << ";Diacritic";
		if (A.is_Extender())
		    cout << ";Extender";
		if (A.is_Identifier_Part())
		    cout << ";Identifier_Part";
		if (A.is_Ignorable_Control())
		    cout << ";Ignorable_Control";
		if (A.is_Bidi_Left_to_Right())
		    cout << ";Bidi_Left_to_Right";
		if (A.is_Bidi_Hebrew_Right_to_Left())
		    cout << ";Bidi_Hebrew_Right_to_Left";
		if (A.is_Bidi_Arabic_Right_to_Left())
		    cout << ";Bidi_Arabic_Right_to_Left";
		if (A.is_Bidi_European_Digit())
		    cout << ";Bidi_European_Digit";
		if (A.is_Bidi_Eur_Num_Separator())
		    cout << ";Bidi_Eur_Num_Separator";
		if (A.is_Bidi_Eur_Num_Terminator())
		    cout << ";Bidi_Eur_Num_Terminator";
		if (A.is_Bidi_Arabic_Digit())
		    cout << ";Bidi_Arabic_Digit";
		if (A.is_Bidi_Common_Separator())
		    cout << ";Bidi_Common_Separator";
		if (A.is_Bidi_Block_Separator())
		    cout << ";Bidi_Block_Separator";
		if (A.is_Bidi_Segment_Separator())
		    cout << ";Bidi_Segment_Separator";
		if (A.is_Bidi_Whitespace())
		    cout << ";Bidi_Whitespace";
		if (A.is_Bidi_Non_spacing_Mark())
		    cout << ";Bidi_Non_spacing_Mark";
		if (A.is_Bidi_Boundary_Neutral())
		    cout << ";Bidi_Boundary_Neutral";
		if (A.is_Bidi_PDF())
		    cout << ";Bidi_PDF";
		if (A.is_Bidi_Embedding_or_Override())
		    cout << ";Bidi_Embedding_or_Override";
		if (A.is_Bidi_Other_Neutral())
		    cout << ";Bidi_Other_Neutral";
		if (A.is_Private_Use())
		    cout << ";Private_Use";
		// if (A.is_Uppercase())
		//    cout << ";Uppercase";
		// if (A.is_Lowercase())
		//    cout << ";Lowercase";
		// if (A.is_Titlecase())
		//     cout << ";Titlecase";
		if (A.is_Low_Surrogate())
		    cout << ";Low_Surrogate";
		if (A.is_High_Surrogate())
		    cout << ";High_Surrogate";
		if (A.is_Private_Use_High_Surrogate())
		    cout << ";Private_Use_High_Surrogate";
		if (A.is_Not_a_Character())
		    cout << ";Not_a_Character";
		if (A.is_Unassigned_Code_Value())
		    cout << ";Unassigned_Code_Value";
		cout << endl;
	    } else if (A.is_Not_a_Character()) undefined++;
	} // try
	catch (Babylon::Block_Error &Except) {
	    cerr << "ERROR: Block_Error -> EXITING" << endl << flush;
	    exit(1);
	} // catch
	catch (Babylon::Undefined_Property &Except) {
	    cerr << "ERROR: Undefined_Property -> EXITING" << endl << flush;
	    exit(2);
	}
    } // for

    cerr << "Number of defined and supported characters: " << chars
	 << endl;
    cerr << "Number of unused characters               : " << undefined
	 << endl;
}
