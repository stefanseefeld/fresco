/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA.
 */

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
