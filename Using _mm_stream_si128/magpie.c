#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <emmintrin.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#ifdef __MACH__
#include <mach/mach_traps.h>
#include <mach/mach_time.h>
#endif

#ifndef NSEC_PER_SEC
#define NSEC_PER_SEC 1000000000ull
#endif

#ifndef __MACH__
#define TIME_ABSOLUTE CLOCK_REALTIME
typedef struct timespec mach_timespec_t;
typedef unsigned int mach_port_t;

static inline uint64_t mach_absolute_time(void) {
    mach_timespec_t tp;
    int res = clock_gettime(CLOCK_REALTIME, &tp);
    if (res < 0) {
        perror("clock_gettime");
        exit(1);
    }
    uint64_t result = tp.tv_sec * NSEC_PER_SEC;
    result += tp.tv_nsec;
    return result;
}

// non-conformant wrapper just for the purposes of this application
static inline void clock_sleep_trap(mach_port_t clock_port, int sleep_type, time_t sec, long nsec, mach_timespec_t *remain) {
    mach_timespec_t req = { sec, nsec };
    int res = clock_nanosleep(sleep_type, TIMER_ABSTIME, &req, remain);
    if (res < 0) {
        perror("clock_nanosleep");
        exit(1);
    }
}
#endif // __MACH__

__m128i reg;
__m128i reg_zero;
__m128i reg_one;
mach_port_t clock_port;
mach_timespec_t remain;

static inline void square_am_signal(float time, float frequency) {
    printf("Playing / %0.3f seconds / %4.0f Hz\n", time, frequency);
    uint64_t period = NSEC_PER_SEC / frequency;

    uint64_t start = mach_absolute_time();
    uint64_t end = start + (uint64_t)(time * NSEC_PER_SEC);

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
static inline void showhelp(char *argv[]){
            fprintf(stderr, "usage: %s [-m|a] [-l loops] -f fname\n",argv[0]);
            fprintf(stderr, "magpie - an AM-FSK file transmitter in the 1500khzrange\n\n Uses PWM of square waves to generate AM-AFSK transmission of a file \n\nbased on SBR by William Entriken:https://github.com/fulldecent\n\n");
            char uc[] = "  -l|loops [int] \t loops sets the number of times the data is transmitted. \n  -f [filename] \t the file specified in filename is read and transmitted\n";
            fprintf(stderr,uc);
            char uc2[] = "  -m\t\t\t uses (3)FSK repeat per bit with a FC/FC+300hz/FC+450hz encoding\n  -a\t\t\t uses AFSK encoding (0=1200hz, 1=2200hz)\n\n";
            fprintf(stderr,uc2);
}
static inline void fileplayer(char *file, int loops, int enc){
FILE *fileptr;
char *buffer;
long filelen;

fileptr = fopen(file, "rb");  // Open the file in binary mode
fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
filelen = ftell(fileptr);             // Get the current byte offset in the file
printf("filelen:%ld\n",filelen);
rewind(fileptr);                      // Jump back to the beginning of the file

buffer = (char *)malloc((filelen+1)*sizeof(char)); // Enough memory for file + \0
fread(buffer, filelen, 1, fileptr); // Read in the entire file
fclose(fileptr); // Close the file
char bitnow=0;

int time_ms=200;
int freq_hz;

int i,b;
for ( int j = 0; j < loops; j ++){

for ( int i = 0; i < filelen + 1; i++) {
    printf("byte #%d\n",i);
    for ( int b =0; b < 7; b++) {
    bitnow = (buffer[i] & ( 1 << b )) >> b ;
    if(bitnow == 1) 
        freq_hz = 1200;
    else
        freq_hz = 2200;
    if(enc == 1) {
        square_am_signal(1.0 * time_ms / 1000, freq_hz);
        }
    else {
        square_am_signal(1.0 * time_ms /2 / 1000, freq_hz);
        square_am_signal(1.0 * time_ms /2 / 1000, freq_hz+(2*150));
        square_am_signal(1.0 * time_ms /2 / 1000, freq_hz+(3*150));
        }
    }
}
}
}

int
main(int argc, char *argv[ ])
{
    int c;
    int tflg=-1, eflg=-1, errflg = 0;
    char *file = NULL;
    int loops=1;
    //char *loops;
    extern char *optarg;
    extern int optind, optopt;
    while ((c = getopt(argc, argv, ":hmaf:l:")) != -1) {
        switch(c) {
        case 'h':
            showhelp(argv);
            exit(0);
        case 'm':
            if (eflg){
                errflg++;
                }
            else{
                tflg=1;
                }
            break;
        case 'a':
            if (tflg){
                errflg++;
                }
            else {
                eflg=1;
            }
            break;
        case 'f':
            file = optarg;
            break;
        case 'l':
            loops = atoi(optarg);
            break;
            case ':':       /* -f or -o without operand */
                    fprintf(stderr,
                            "Option -%c requires an operand\n", optopt);
                    errflg++;
                    break;
        case '?':
            showhelp(argv);
            exit(0);
        }
    }
    if (file == NULL)
        fprintf(stderr, "missing -f filename\n");
        errflg++;
    if (errflg) {
        fprintf(stderr, "usage: %s [-t|e] [-c loops] -f fname\n",argv[0]);
        exit(2);
    }
//printf("infile: %s loops:%i tflag:%i eflag:%i\n" ,file, loops,tflg,eflg);
//Setup below

#ifdef __MACH__
    mach_timebase_info_data_t theTimeBaseInfo;
    mach_timebase_info(&theTimeBaseInfo);
    puts("TESTING TIME BASE: the following should be 1 / 1");
    printf("  Mach base: %u / %u nanoseconds\n\n", theTimeBaseInfo.numer, theTimeBaseInfo.denom);
#endif
    uint64_t start = mach_absolute_time();
    uint64_t end = mach_absolute_time();
    printf("TESTING TIME TO EXECUTE mach_absolute_time()\n  Result: %"PRIu64" nanoseconds\n\n", end - start);

    reg_zero = _mm_set_epi32(0, 0, 0, 0);
    reg_one = _mm_set_epi32(-1, -1, -1, -1);

int enc=1;
if(tflg==1)
    enc=2;

// Setup Code goes ^^^

fileplayer(file,loops,enc);
}
