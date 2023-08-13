/** \file fs_lock.h
 *  \brief wrapper around semaphore.h
 *
 *  Contains a synchronized macro to make critical sections.
 *  synchronized {
 *     // critical section
 *  }
 */

#pragma once
#ifndef FS_LOCK_H
#define FS_LOCK_H

#include <semaphore.h>

#include "fs_macros.h"

// macro magic for synchronized sections
// change lock prefix if it conflicts with code
#define SYNC_LOCK_PREFIX __sync_lock_
#define synchronized __synchronized2(__COUNTER__)
#define __synchronized2(lockNo)				\
  fs::semaphore __xcat(SYNC_LOCK_PREFIX,lockNo);	\
  for(__xcat(SYNC_LOCK_PREFIX,lockNo).lock();		\
      __xcat(SYNC_LOCK_PREFIX,lockNo).is_locked();	\
      __xcat(SYNC_LOCK_PREFIX,lockNo).unlock())

namespace fs {
  /// wrapper around semaphore.h
  class semaphore {
  private:
    ::sem_t lock_sem;

  public:
    semaphore() {
      ::sem_init(& lock_sem,0,1);

    }
    semaphore(unsigned int initial_value) {
      ::sem_init(& lock_sem,0,initial_value);
    }
    ~semaphore() {
      sem_destroy(&lock_sem);
    }
    /// try to lock or wait until unlocked
    void lock() {
      ::sem_wait(& lock_sem);

    }
    /// unlock semaphore
    void unlock() {
      ::sem_post(& lock_sem);
    }
    /// returns true if semaphore is locked
    bool is_locked() {
      int v = 0;
      ::sem_getvalue(& lock_sem,& v);
      return (v == 0);
    }
  };
} // namespace fs
#endif // FS_LOCK_H
