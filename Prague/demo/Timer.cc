#include <Prague/Sys/Signal.hh>
#include <Prague/Sys/Timer.hh>

using namespace Prague;

const char *text1[] = {"Heut' kommt der Hans zu mir,",
		       "Freut sich die Lies'.",
		       "Kommt er aber \"uber Oberammergau,",
		       "Oder aber \"uber Unterammergau,",
		       "Ob er aber \"uberhaupt nicht kommt,",
		       "Ist nicht gewiss."};
const char *text2[] = {"C-A-F-F-E-E,",
		       "Trink nicht so viel Kaffee.",
		       "Nicht f\"ur Kinder dieser T\"urkentrank,",
		       "Schw\"acht die Nerven, macht dich schwach und krank.",
		       "Sei doch kein Muselman,",
		       "Der das nicht lassen kann."};

class Singer : public Timer::Notifier
{
public:
  Singer(const char **s, const char *c) : song(s), color(c), line(0) {}
  virtual void notify() { cout << color << song[line % 6] << endl; line++;}
private:
  const char **song;
  const char  *color;
  short line;
};

class Exit : public Signal::Notifier
{
public:
  virtual void notify(int)
    {
      Timer::cancel();
      cout << "\033[0m";
    }
};

int main (int argc, char **argv)
{
  Exit *exit = new Exit;
  Signal::set(Signal::interrupt, exit);
  Singer *bass = new Singer(text1, "\033[31m");
  Singer *soprano = new Singer(text2, "\033[32m");
  Timer *timer1 = new Timer(bass);
  Timer *timer2 = new Timer(soprano);
  /*
   * start the Timer queue
   */
  Timer::run();
  /*
   * execute the action repeatedly every 1000 milliseconds
   */
  timer1->start(Time::currentTime(), 1000);
  timer2->start(Time::currentTime(), 1000);
  while (Timer::active()) sleep(1);
}
