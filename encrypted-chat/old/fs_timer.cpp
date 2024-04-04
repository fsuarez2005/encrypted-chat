
#include "fs_timer.h"

namespace fs {
  inline time_t total_days(time_t seconds) {
    return (seconds/(24*60*60)); 
  }
  inline time_t total_hours(time_t seconds) {
    return (seconds/(60*60));
  }
  inline time_t minutes(time_t seconds) {
    return (seconds/60)%60;
  }
  // -------------------------------------------
  void chrono::start() {
    if (gettimeofday(&start_time,NULL) < 0) {
      perror(NULL);
      exit(1);
    }
  }
  // -------------------------------------------
  void chrono::stop() {
    if (gettimeofday(&end_time,NULL) < 0) {
      perror(NULL);
      exit(1);
    }
  }
  // -------------------------------------------
  void chrono::recalculate() {
    stop(); // set end time
    timersub(&end_time,&start_time,&elapsed_time);
  }
  // -------------------------------------------
  void chrono::reset() {
    start_time.tv_sec = 0;
    start_time.tv_usec = 0;

    end_time.tv_sec = 0;
    end_time.tv_usec = 0;

    elapsed_time.tv_sec = 0;
    elapsed_time.tv_usec = 0;
  }
  // -------------------------------------------
  time_t chrono::get_days() {
    recalculate();
    return total_days(elapsed_time.tv_sec);
  }
  // -------------------------------------------
  time_t chrono::get_hours() {
    recalculate();
    return total_hours(elapsed_time.tv_sec);
  }
  // -------------------------------------------
  time_t chrono::get_minutes() {
    recalculate();
    return minutes(elapsed_time.tv_sec);
  }
  // -------------------------------------------
  time_t chrono::get_seconds() {
    recalculate();
    return elapsed_time.tv_sec;
  }
  // -------------------------------------------
  suseconds_t chrono::get_microseconds() {
    recalculate();
    return elapsed_time.tv_usec;
  }
  // -------------------------------------------
  suseconds_t chrono::get_milliseconds() {
    recalculate();
    // 1 ms = 1000 us
    return (elapsed_time.tv_usec / 1000);
  }
} // namespace fs

