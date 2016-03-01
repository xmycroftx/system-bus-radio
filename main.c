// SYSTEM BUS RADIO
// https://github.com/fulldecent/system-bus-radio
// Copyright 2016 William Entriken

#include <stdio.h>
#include <emmintrin.h>
#include <mach/mach_traps.h>
#include <mach/mach_time.h>
#include <math.h>
#include <string.h>


#define am_delay(x) (square_am_signal(x, 0))
__m128i reg;
__m128i reg_zero;
__m128i reg_one;
mach_port_t clock_port;
mach_timespec_t remain;

static inline void square_am_signal(float time, float frequency) {
  printf("Playing / %0.3f seconds / %4.0f Hz\n", time, frequency);
	uint64_t period = NSEC_PER_SEC / frequency;

	uint64_t start = mach_absolute_time();
	uint64_t end = start + time * NSEC_PER_SEC;

	while (mach_absolute_time() < end) {
    uint64_t mid = start + period / 2;
		uint64_t reset = start + period;
    while (mach_absolute_time() < mid) {
      _mm_stream_si128(&reg, reg_one);
      _mm_stream_si128(&reg, reg_zero);
    }
    clock_sleep_trap(clock_port, TIME_ABSOLUTE, reset / NSEC_PER_SEC, reset % NSEC_PER_SEC, &remain);
		start = reset;
	}
}

int prefix(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

int main(int argc, char* argv[])
{
	mach_timebase_info_data_t theTimeBaseInfo;
  mach_timebase_info(&theTimeBaseInfo);
  puts("TESTING TIME BASE: the following should be 1 / 1");
	printf("  Mach base: %u / %u nanoseconds\n\n", theTimeBaseInfo.numer, theTimeBaseInfo.denom);

	uint64_t start = mach_absolute_time();
	uint64_t end = mach_absolute_time();
	printf("TESTING TIME TO EXECUTE mach_absolute_time()\n  Result: %lld nanoseconds\n\n", end - start);

	reg_zero = _mm_set_epi32(0, 0, 0, 0);
	reg_one = _mm_set_epi32(-1, -1, -1, -1);
  FILE* fp;
  if (argc == 2) {
    fp = fopen(argv[1], "r");
  } else {
    puts("Supply file to read song from.");
    exit(1);
  }
  char buffer[256];
	while (1) {
    fgets(buffer, 256 - 1, fp);
    if (strlen(buffer) == 0) {
      /* skip blank lines */
      continue;
    }

    if (prefix(":beep", buffer)) {
      int t;
      int f;
      if(sscanf(buffer, ":beep frequency=%d length=%dms",  &f, &t) == 0) {
        continue;
      }
      printf("F: %d, T: %d\n", f, t);
      square_am_signal(t / 1000.0, f);
    } else if (prefix(":delay", buffer)) {
      int d;
      if (sscanf(buffer, ":delay %dms", &d) == 0) {
        continue;
      }
      printf("D: %d\n", d);
      square_am_signal(d / 1000.0, 0);
    }
    /* Super Mario Bros. Theme
    square_am_signal(0.100, 660);
    am_delay(0.150);
    square_am_signal(0.100, 660);
    am_delay(0.300);
    square_am_signal(0.100, 660);
    am_delay(0.300);
    square_am_signal(0.100, 510);
    am_delay(0.100);
    square_am_signal(0.100, 660);
    am_delay(0.300);
    square_am_signal(0.100, 770);
    am_delay(0.550);
    square_am_signal(0.100, 380);
    am_delay(0.575);*/



	}
}
