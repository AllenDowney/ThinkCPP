#include <iostream>

struct Time {
  int hour, minute;
  double second;

  Time::Time (int hour, int min, double secs);
  Time::Time (double secs);

  void Time::print () const;
  void Time::increment (double secs);
  bool Time::after (const Time& time2) const;
  Time Time::add (const Time& t2) const;

  double Time::convertToSeconds () const;
};

Time::Time (int h, int m, double s)
{
  hour = h;  minute = m;  second = s;
}

Time::Time (double secs)
{
  hour = (int) (secs / 3600.0);
  secs -= hour * 3600.0;
  minute = (int) (secs / 60.0);
  secs -= minute * 60.0;
  second = secs;
}

void Time::print () const
{
  cout << hour << ":" << minute << ":" << second << endl;
}

bool Time::after (const Time& time2) const
{
  if (hour > time2.hour) return true;
  if (hour < time2.hour) return false;

  if (minute > time2.minute) return true;
  if (minute < time2.minute) return false;

  if (second > time2.second) return true;
  return false;
}

void Time::increment (double secs)
{
  second += secs;

  while (second >= 60.0) {
    second -= 60.0;
    minute += 1;
  }
  while (minute >= 60) {
    minute -= 60;
    hour += 1;
  }
}

double Time::convertToSeconds () const
{
  int minutes = hour * 60 + minute;
  double seconds = minutes * 60 + second;
  return seconds;
}

Time Time::add (const Time& t2) const
{
  double seconds = convertToSeconds() + t2.convertToSeconds();
  Time time (seconds);
  return time;
}

void main ()
{
  Time currentTime (9, 14, 30.0);
  currentTime.increment (500.0);
  currentTime.print ();

  Time breadTime (3, 35, 0.0);
  Time doneTime = currentTime.add (breadTime);
  doneTime.print ();

  if (doneTime.after (currentTime)) {
    cout << "The bread will be done after it starts." << endl;
  }
}


