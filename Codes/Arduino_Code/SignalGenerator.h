#ifndef SIGNALGENERATOR_h
#define SIGNALGENERATOR_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define RESOLUTION 65536    // Timer1 is 16 bit
#define TOTAL_SAMPLES 160


const uint16_t sinewave[] PROGMEM =
{0, 0, 10, 15, 20, 24, 29, 34, 39, 44, 49, 53, 58, 63, 68, 72, 77, 82, 86, 91, 95, 100, 104, 109, 113, 117, 
122, 126, 130, 134, 138, 142, 146, 150, 154, 158, 162, 165, 169, 173, 176, 179, 183, 186, 189, 192, 196, 199,
201, 204, 207, 210, 212, 215, 217, 220, 222, 224, 226, 228, 230, 232, 234, 235, 237, 238, 240, 241, 242, 243,
244, 245, 246, 247, 247, 248, 248, 249, 249, 249, 249, 249, 249, 249, 248, 248, 247, 247, 246, 245, 244, 243,
242, 241, 240, 238, 237, 235, 234, 232, 230, 228, 226, 224, 222, 220, 217, 215, 212, 210, 207, 204, 201, 199, 
196, 192, 189, 186, 183, 179, 176, 173, 169, 165, 162, 158, 154, 150, 146, 142, 138, 134, 130, 126, 122, 117, 
113, 109, 104, 100, 95, 91, 86, 82, 77, 72, 68, 63, 58, 53, 49, 44, 39, 34, 29, 24, 20, 15, 0, 0};


class Timerone
{
  public:
  // properties
  unsigned int pwmPeriod;
  unsigned char clockSelectBits;
  char oldSREG;         // To hold Status Register while ints disabled
  
  

  void initialize(long microseconds=1000000);
  void setPeriod(long microseconds);
  void setPwmDuty(char pin, int duty);
  void resume();
  void pwm(char pin, int duty, long microseconds=-1);
  void attachInterrupt();
};

extern Timerone timer1;


#endif

