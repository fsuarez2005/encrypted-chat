/** \file fs_timer.h
 **  \brief chronograph
 **/

#pragma once
#ifndef FS_TIMER_H
#define FS_TIMER_H

#include <cmath>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <sys/time.h>

namespace fs {

  /// converts seconds to days in broken down time
  inline time_t total_days(time_t seconds);

  /// converts seconds to hours in broken down time
  inline time_t total_hours(time_t seconds);

  /// converts seconds to seconds in broken down time
  inline time_t minutes(time_t seconds);

  /// chronograph / timer
  class chrono {
  private:
    // struct timeval {
    //   time_t      tv_sec;     /* seconds */
    //   suseconds_t tv_usec;    /* microseconds */
    // };

    struct timeval start_time;
    struct timeval end_time;
    struct timeval elapsed_time;

  public:
    /// sets start time
    void start();

    /// sets end time
    void stop();

    /// sets start time, end time, and elapsed time to zero
    void reset();

    /// recalculates the elapsed time;
    void recalculate();

    /// returns numbers of days
    time_t get_days();

    /// returns numbers of hours
    time_t get_hours();

    /// returns numbers of minutes
    time_t get_minutes();

    /// returns numbers of seconds
    time_t get_seconds();

    /// returns numbers of microseconds
    suseconds_t get_microseconds();

    /// returns numbers of milliseconds
    suseconds_t get_milliseconds();

  };
} // namespace fs
#endif // FS_TIMER_H
