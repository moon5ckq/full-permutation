/*
 *  * Author:  David Robert Nadeau
 *   * Site:    http://NadeauSoftware.com/
 *    * License: Creative Commons Attribution 3.0 Unported License
 *     *          http://creativecommons.org/licenses/by/3.0/deed.en_US
 *      */
#if defined(_WIN32)
#include <Windows.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h> /* POSIX flags */
#include <time.h> /* clock_gettime(), time() */
#include <sys/time.h> /* gethrtime(), gettimeofday() */

#if defined(__MACH__) && defined(__APPLE__)
#include <mach/mach.h>
#include <mach/mach_time.h>
#endif

#else
#error "Unable to define getRealTime( ) for an unknown OS."
#endif

/**
 *  * Returns the real time, in seconds, or -1.0 if an error occurred.
 *   *
 *    * Time is measured since an arbitrary and OS-dependent start time.
 *     * The returned real time is only useful for computing an elapsed time
 *      * between two calls to this function.
 *       */
double getRealTime( )
{
#if defined(_WIN32)
  FILETIME tm;
  ULONGLONG t;
#if defined(NTDDI_WIN8) && NTDDI_VERSION >= NTDDI_WIN8
  /* Windows 8, Windows Server 2012 and later. ---------------- */
  GetSystemTimePreciseAsFileTime( &tm );
#else
  /* Windows 2000 and later. ---------------------------------- */
  GetSystemTimeAsFileTime( &tm );
#endif
  t = ((ULONGLONG)tm.dwHighDateTime << 32) | (ULONGLONG)tm.dwLowDateTime;
  return (double)t / 10000000.0;

#elif (defined(__hpux) || defined(hpux)) || ((defined(__sun__) || defined(__sun) || defined(sun)) && (defined(__SVR4) || defined(__svr4__)))
  /* HP-UX, Solaris. ------------------------------------------ */
  return (double)gethrtime( ) / 1000000000.0;

#elif defined(__MACH__) && defined(__APPLE__)
  /* OSX. ----------------------------------------------------- */
  static double timeConvert = 0.0;
  if ( timeConvert == 0.0 )
  {
    mach_timebase_info_data_t timeBase;
    (void)mach_timebase_info( &timeBase );
    timeConvert = (double)timeBase.numer /
      (double)timeBase.denom /
      1000000000.0;
  }
  return (double)mach_absolute_time( ) * timeConvert;

#elif defined(_POSIX_VERSION)
  /* POSIX. --------------------------------------------------- */
#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
  {
    struct timespec ts;
#if defined(CLOCK_MONOTONIC_PRECISE)
    /* BSD. --------------------------------------------- */
    const clockid_t id = CLOCK_MONOTONIC_PRECISE;
#elif defined(CLOCK_MONOTONIC_RAW)
    /* Linux. ------------------------------------------- */
    const clockid_t id = CLOCK_MONOTONIC_RAW;
#elif defined(CLOCK_HIGHRES)
    /* Solaris. ----------------------------------------- */
    const clockid_t id = CLOCK_HIGHRES;
#elif defined(CLOCK_MONOTONIC)
    /* AIX, BSD, Linux, POSIX, Solaris. ----------------- */
    const clockid_t id = CLOCK_MONOTONIC;
#elif defined(CLOCK_REALTIME)
    /* AIX, BSD, HP-UX, Linux, POSIX. ------------------- */
    const clockid_t id = CLOCK_REALTIME;
#else
    const clockid_t id = (clockid_t)-1; /* Unknown. */
#endif /* CLOCK_* */
    if ( id != (clockid_t)-1 && clock_gettime( id, &ts ) != -1 )
      return (double)ts.tv_sec +
        (double)ts.tv_nsec / 1000000000.0;
    /* Fall thru. */
  }
#endif /* _POSIX_TIMERS */

  /* AIX, BSD, Cygwin, HP-UX, Linux, OSX, POSIX, Solaris. ----- */
  struct timeval tm;
  gettimeofday( &tm, NULL );
  return (double)tm.tv_sec + (double)tm.tv_usec / 1000000.0;
#else
  return -1.0;    /* Failed. */
#endif
}


/*
 * m.cpp
 * Copyright (C) 2014 mlckq <moon5ckq@gmail.com>, xxr <xxr3376@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include "HighAccuracy.h"
#include "BITree.h"
using std::string;
using std::vector;

vector<int> read(const char* path) {
    vector<int> ret;
    FILE* fin = fopen(path, "r");
    for (int x; fscanf(fin, "%d", &x) != EOF;)
        ret.push_back(x);
    std::reverse(ret.begin(), ret.end());
    fclose(fin);
    return ret;
}
vector<int> g;

void m1(int argc, char **argv) {
    vector<int> p(g), p_, q;
    int n = static_cast<int>(p.size());
    p_.resize(n);
    q.resize(n);
    HighAccuracy k;
    if (argc > 3)
        k.load(argv[3]);
    else
        k = 1;

    //step1
    HighAccuracy fact(1), m(0);
    BITree t(n, 0);
    for (int i = 0; i < n; ++i) {
        if (i) fact *= i;
        m += fact * t.sum(1, p[i]);
        t.set(p[i], 1);
    }
    //step 2
    HighAccuracy x = m + k;
    //step 3
    t.reset(n, 1);
    for (int i = 0; i < n; ++i)
        q[i] = x.div(i+1);
    for (int i = n - 1; i >= 0; --i) {
        p_[i] = t.getKth(q[i] + 1);
        t.set(p_[i], 0);
    }

}

void m2(int argc, char **argv) {
    vector<int> p(g), p_, q;
    int n = static_cast<int>(p.size());
    p_.resize(n);
    q.resize(n);
    HighAccuracy k;
    if (argc > 3)
        k.load(argv[3]);
    else
        k = 1;
    
    //step 1
    for (int i = 0; i < n; ++i)
        q[p[i] - 1] = i + 1;
    HighAccuracy m(0), fact(1);
    BITree t(n, 0);
    for (int i = n - 1; i >0; --i) {
        fact *= i;
        m = m * (i + 1) + (q[i] - t.sum(1, q[i]) - 1);
        t.set(q[i], 1);
    }
    //step 2
    HighAccuracy x = m + k;
    //step 3
    t.reset(n, 1);
    for (int i = 0; i < n; ++i)
        q[i] = x.div(i+1);
    for (int i = n - 1; i >= 0; --i) {
        int y = t.getKth(q[i] + 1);
        p_[y - 1] = i + 1;
        t.set(y, 0);
    }

}

void m3(int argc, char **argv) {
    vector<int> p(g), p_, q;
    int n = static_cast<int>(p.size());
    p_.resize(n);
    q.resize(n);
    HighAccuracy k;
    if (argc > 3)
        k.load(argv[3]);
    else
        k = 1;
    
    //step 1
    for (int i = 0; i < n; ++i)
        q[p[i] - 1] = i + 1;
    HighAccuracy m(0), fact(1);
    BITree t(n, 0);
    for (int i = n - 1; i >0; --i) {
        fact *= i;
        p[i] = q[i] - t.sum(1, q[i]) - 1;
        t.set(q[i], 1);
    }
    for (int i = 1; i < n; ++i)
        m = m * (i + 1) + p[i];
    //step 2
    HighAccuracy x = m + k;
    //step 3
    t.reset(n, 1);
    for (int i = n; i > 0; --i) {
        int c = x.div(i);
        int y = t.getKth(c + 1);
        p_[y - 1] = i;
        t.set(y, 0);
    }
    
}

void m4(int argc, char **argv) {
    vector<int> p(g), p_, q;
    int n = static_cast<int>(p.size());
    p_.resize(n);
    q.resize(n);
    HighAccuracy k;
    if (argc > 3)
        k.load(argv[3]);
    else
        k = 1;

    //step 1
    for (int i = 0; i < n; ++i)
        q[p[i] - 1] = i + 1;
    BITree t(n, 0);
    HighAccuracy m(0);
    t.set(q[0], 1);
    for (int i = 1, tmp = 0; i < n; ++i) {
      int cur = (tmp&1) ?
          t.sum(q[i] + 1, n) :
          t.sum(1, q[i] - 1);

      if (i&1) tmp = cur;
      else tmp += cur;

      m = m * (i + 1) + cur;
      t.set(q[i], 1);
    }
    //step 2
    HighAccuracy x = m + k;
    //step 3
    for (int i = n; i > 1; --i) {
        q[i - 1] = x.div(i);
    }
    //step 4
    t.reset(n, 1); //right
    BITree t_reverse(n, 1); //left

    for (int i = n - 1; i > 0; --i) {
      int cur = 0;
      if (i == 1)
          cur = 0;
      else if (i & 1)
          cur = q[i-1] + q[i - 2];
      else
          cur = q[i-1];

      int r;
      if (cur & 1)
          r = n - t_reverse.getKth(q[i] + 1);
      else
          r = t.getKth(q[i] + 1) - 1;

      t.set(r+1, 0);
      t_reverse.set(n - r, 0);

      p_[r] = i + 1;
    }

    // put 1 back
    p_[t.getKth(1) - 1] = 1;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("usage: %s <type> <input permutation> [next]\n", argv[0]);
        return 0;
    }
    double startTime, endTime;

    g = read(argv[2]);
    startTime = getRealTime( );

    for (int i = 0; i < 10; i++) {
      if (string(argv[1]) == "1") {
          m1(argc, argv);
      } else if (string(argv[1]) == "2") {
          m2(argc, argv);
      } else if (string(argv[1]) == "3") {
          m3(argc, argv);
      } else if (string(argv[1]) == "4") {
          m4(argc, argv);
      } else {
          printf("type: 1,2,3,4\n");
          return 0;
      }
    }
    endTime = getRealTime( );
    printf("%lf\n", (endTime - startTime));

    return 0;
}
