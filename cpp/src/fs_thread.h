/** \file fs_thread.h
 ** \brief superclass for making thread objects
 **
 ** sample code
 **
 ** class MyThread : public fs::thread {
 ** protected:
 **   virtual void run() {
 **     cout << "This is running in a thread." << endl;
 **   }
 ** };
 **
 ** int
 ** main() {
 **   MyThread m;
 **   m.start();
 **   m.join();
 **
 **   return 0;
 ** }
 **/

#pragma once
#ifndef FS_THREAD_H
#define FS_THREAD_H

#include <pthread.h>

// ========================================================
namespace fs {
  class thread;

  /// struct to pass an object to the callback function
  template <class T>
  struct pthread_create_arg_s {
    T * object;
  };
  // -----------------------------------------
  /// callback function for pthread
  template <class T>
  static void * pthread_create_start(void * arg) {
    struct pthread_create_arg_s<T> * arg_struct = (struct pthread_create_arg_s<T> *) arg;
    T * o = arg_struct->object;

    // calls the member function of the subclassed thread
    o->run();
    return NULL;
  }
  // -----------------------------------------
  /// thread superclass
  class thread {
  private:
    pthread_t thread_id;
    pthread_attr_t thread_attributes;
    bool running;
    struct pthread_create_arg_s<thread> pthread_args;
  protected:
    /// function to redefine that will run in thread
    virtual void run()=0;

  public:
    template <class U> friend void * pthread_create_start(void * arg);
    // -----------------------------------------
    thread() : running(false) {
      pthread_args.object = this;
    }
    ~thread(){
      // exit thread
      pthread_exit(0);
    }
    // -------------------------------------------------
    /// returns thread id
    pthread_t get_thread_id() {
      return thread_id;
    }
    // -------------------------------------------------
    /// starts the thread
    void start() {
      // prevent multiple runs
      if (running) {
	return;
      }
      running = true;

      // initialize thread attributes
      pthread_attr_init(& thread_attributes);

      // start thread
      if (pthread_create( &thread_id,
			  &thread_attributes,
			  &pthread_create_start<thread>,
			  &pthread_args ) < 0) {
        perror(NULL);
        exit(1);
      }
      // destroy attribute struct so we can use it again
      pthread_attr_destroy(& thread_attributes);
    }
    // -------------------------------------------------
    /// waits for thread to terminate
    void join() {
      pthread_join(thread_id,NULL);
    }
  };
}
#endif // FS_THREAD_H
