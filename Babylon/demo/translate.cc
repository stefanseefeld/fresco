// This progran is to check wether the translation from and
// to Babylon::String works.

#include <Babylon/Babylon.hh>
#include <Warsaw/Types.hh>

int main (int argc, char * argv) {
    Unistring us;
    Babylon::String bs("TEST-STRING");

    cout << bs << endl;

    us = translate(bs);

    Babylon::String bs2 = translate(us);
    
    cout << bs2 << endl;
}
