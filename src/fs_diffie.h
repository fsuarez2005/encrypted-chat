/** \file fs_diffie.h
 ** \brief Diffie-Hellman Key Exchange
 **/

#ifndef FS_DIFFIE_H
#define FS_DIFFIE_H

using namespace std;

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <stdint.h>

#include <string>
#include <iostream>

// number of state buffers for random number generator
// 8 <= PRNG_BUFSZ <= 256
#define PRNG_BUFSZ 256

namespace fs {
  /// Diffie-Hellman Key Exchange
  class diffie_hellman {
  private:
    int64_t g;
    int64_t n;
    int64_t gxn; // server's g^x % n
    int64_t gbn; // g^x % n from client
    int32_t x; // private number

    struct random_data * random_data_buf;
    char * random_state_buf;

    unsigned int seed;

    void setup_random_generator() {
      seed = random();

      // buffers needs to be zero'd
      random_data_buf = new struct random_data;
      memset(random_data_buf,0,sizeof(struct random_data));
      random_state_buf = new char[PRNG_BUFSZ];
      memset(random_state_buf,0,PRNG_BUFSZ * sizeof(char));

      // initialize random number generator
      initstate_r(seed,random_state_buf,PRNG_BUFSZ,random_data_buf);
    }

  public:
    /// calculates g^x mod n for large numbers
    // http://en.wikipedia.org/wiki/Modular_exponentiation
    static int64_t modular_pow(int64_t base,
			       int64_t exponent,
			       int64_t modulus) {
      int64_t result = 1;
      while (exponent > 0) {
	if ((exponent & 1) == 1) {
	  result = (result * base) % modulus;
	}
	exponent >>= 1;
	base = (base * base) % modulus;
      }
      return result;
    }
    // -------------------------------------------------
    diffie_hellman() {
      setup_random_generator();
      generate_random_private();
    }

    diffie_hellman(int64_t g, int64_t n) :
      g(g),
      n(n)
    {
      setup_random_generator();
      generate_random_private();
    }
    // -------------------------------------------------
    void set_g(int64_t g) {
      this->g = g;
    }
    int64_t get_g() {
      return g;
    }
    // -------------------------------------------------
    void set_n(int64_t n) {
      this->n = n;
    }
    int64_t get_n() {
      return n;
    }
    // -------------------------------------------------
    int32_t get_private() {
      return x;
    }
    void set_private(int32_t x) {
      this->x = x;
    }
    // -------------------------------------------------
    int64_t get_gxn() {
      return gxn;
    }
    // -------------------------------------------------
    void set_other_gxn(int64_t gbn) {
      this->gbn = gbn;
    }
    // -------------------------------------------------
    int64_t get_full_key() {
      return (gxn * gbn);
    }
    char get_key() {
      return (get_full_key() & 0xFF);
    }
    // -------------------------------------------------
    void generate_random_private() {
      random_r(random_data_buf,&x);
    }
    // -------------------------------------------------
    void calculate_gxn() {
      gxn = modular_pow(g,x,n);
    }
  };
} // namespace fs
#endif // FS_DIFFIE_H
