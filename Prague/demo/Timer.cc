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

class TimerAction : public Timer::Notifier
{
public:
  TimerAction(const char **s, const char *c) : song(s), color(c), line(0) {}
  virtual void notify() { cout << color << song[line % 6] << endl; line++;}
private:
  const char **song;
  const char  *color;
  short line;
};

Timer *timer1;
Timer *timer2;

class Exit : public Signal::Notifier
{
public:
  virtual void notify(int)
    {
      timer1->stop();
      timer2->stop();
      cout << "\033[0m";
    }
};

int main (int argc, char **argv)
{
  Exit *exit = new Exit;
  Signal::set(Signal::interrupt, exit);
  TimerAction *song1 = new TimerAction(text1, "\033[31m");
  TimerAction *song2 = new TimerAction(text2, "\033[32m");
  timer1 = new Timer(song1);
  timer2 = new Timer(song2);
  /*
   * execute the action repeatedly every 1000 milliseconds
   */
  timer1->start(1000, true);
  timer2->start(1000, true);
  while (1);
}
