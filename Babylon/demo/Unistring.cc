#include <Babylon/Babylon.hh>
#include <iostream.h>
#include <iomanip.h>

using namespace Babylon;

int main (int argc, char **argv) {
  String ex_a(0x1E0A); // D-dot-above
  String ex_b("D."); // D, dot-above
  ex_b[1] = 0x0307;
  String ex_c("D."); // D-dot-below, dot-above
  ex_c[0] = 0x1E0C; ex_c[1] = 0x0307;
  String ex_d("D."); // D-dot-above, dot-below
  ex_d[0] = 0x1E0A; ex_d[1] = 0x0323;
  String ex_e("D.."); // D, dot-above, dot-below
  ex_e[1] = 0x0307; ex_e[2] = 0x0323;
  String ex_f("D.,."); // D, dot-above, horn, dot-below
  ex_f[1] = 0x0307; ex_f[2] = 0x031B; ex_f[3] = 0x0323;
  String ex_g("E"); // E-macron-grave
  ex_g[0] = 0x1E14;
  String ex_h("E,"); // E-macron, grave
  ex_h[0] = 0x0112; ex_h[1] = 0x0300;
  String ex_i("E."); // E-grave, macron
  ex_i[0] = 0x00C8; ex_i[1] = 0x0304;
  String ex_j(0x212B); // angstrom_sign
  String ex_k("A"); // A-ring
  ex_k[0] = 0x00C5;
  String ex_l("Affin"); // "A,f,f,i,n
  ex_l[0] = 0x00C4;
  String ex_m("Afn"); // "A, ffi, n
  ex_m[0] = 0x00C4; ex_m[1] = 0xFB03;
  String ex_n("Henry IV"); // H, e, n, r, y,  , I, V
  String ex_o("Henry 4"); // H, e, n, r, y, IV
  ex_o[6] = 0x2163;
  String ex_p("G"); // GA
  ex_p[0] = 0x304C;
  String ex_q("KT"); // KA, TEN
  ex_q[0] = 0x304B; ex_q[1] = 0x3099;
  String ex_r("KT"); //HW_KA, HW_TEN
  ex_r[0] = 0xFF76; ex_r[1] = 0xFF9E;
  String ex_s("KT"); // KA, HW_TEN
  ex_s[0] = 0x304B; ex_s[1] = 0xFF9E;
  String ex_t("KT"); // HW_KA, TEN
  ex_t[0] = 0xFF76; ex_t[1] = 0x3099;
  
  String tmp;
  
  tmp = ex_a;
  cerr << "a) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  
  tmp = ex_b;
  cerr << "b) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_c;
  cerr << "c) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_d;
  cerr << "d) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_e;
  cerr << "e) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_f;
  cerr << "f) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_g;
  cerr << "g) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_h;
  cerr << "h) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_i;
  cerr << "i) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_j;
  cerr << "j) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_k;
  cerr << "k) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_l;
  cerr << "l) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_m;
  cerr << "m) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_n;
  cerr << "n) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_o;
  cerr << "o) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_p;
  cerr << "p) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  tmp = ex_q;
  cerr << "q) " << tmp;
  cerr << "\tD:" << (tmp.norm(NORM_D));
  cerr << "\tC:" << (tmp.norm(NORM_C));
  cerr << "\tKD:" << (tmp.norm(NORM_KD));
  cerr << "\tKC:"<< (tmp.norm(NORM_KC)) << endl;
  // Dictionary::instance()->update("/data1/seefelds/Berlin/etc/Unicode/");
  cerr << "#####" << endl;

  tmp  = ex_a;
  tmp += Babylon::String(" ");
  tmp += ex_b;
  tmp += Babylon::String(" ");
  tmp += ex_c;
  tmp += Babylon::String("\n");
  tmp += ex_d;
  tmp += Babylon::String("\n");
  tmp += ex_e;
  tmp += Babylon::String(" ");
  tmp += ex_f;
  tmp += Babylon::String(" ");
  tmp += ex_g;
  tmp += Babylon::String(" ");
  tmp += ex_h;

  tmp.resize(0);
  tmp += Babylon::String("TEST TEXT");
  tmp += Babylon::Char(0x2029);
  tmp += Babylon::String("NEXT LINE");

  cerr << tmp << endl;
  cerr << "Number of glyphs: " << tmp.glyphs() << endl;
  cerr << "These glyphs are:" << endl;
  
  Babylon::String::const_iterator i = tmp.begin();
  while (i != tmp.end()) {
    cerr << (tmp.getGlyph(i)) << endl;
    tmp.nextGlyph(i);
  }

  i = tmp.begin();
  cerr << endl;
  cerr << "The Paragraphs are:" << endl;
  while (i != tmp.end()) {
    cerr << (tmp.getParagraph(i)) << "<<--" << endl;
    tmp.nextParagraph(i);
  }

  cerr << "DONE WITH THE PROGRAM" << endl << flush;
}
