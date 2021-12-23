#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

#define BOOL int

#define THREADS 2
#define LDR_THR 0
#define CNY_THR 1

#define LDR_PIN 1 //GPIO 18
#define CNY_PIN 4 //GPIO 23

#define HIGH 1
#define LOW 0

// global variables
const int Tldr = 100;
BOOL Vldr = FALSE;
int ldr;

const int Tcny = 100;
BOOL Vcny = FALSE;
int cny;


// thread for LDR
PI_THREAD (ldr_loop)
{
 printf("Initiated ldr loop\n");
 pinMode(LDR_PIN, INPUT);
 ldr = digitalRead(LDR_PIN);

 for(;;)
 {
    int new_ldr = digitalRead(LDR_PIN);

    if(ldr != new_ldr)
    {
       ldr = new_ldr;

       piLock(LDR_THR);
       Vldr = TRUE;
       piUnlock(LDR_THR);
    }
    delay(Tldr);
  }
}


// thread for CNY
PI_THREAD (cny_loop)
{
  printf("Initiated cny loop\n");
  pinMode(CNY_PIN, INPUT);
  cny = digitalRead(CNY_PIN);

  for(;;)
  {
     int new_cny = digitalRead(CNY_PIN);

     if(cny != new_cny)
     {
       cny = new_cny;

       piLock(CNY_THR);
       Vcny = TRUE;
       piUnlock(CNY_THR);
     }
     delay(Tcny);
   }
}


// main thread
int main (int argc, char** argv)
{
  int threads[THREADS]; // no se usa
  int counter = 10000;
  int i;

  if(argc > 2) {
     printf("Usage: %s [milliseconds]\n", argv[0]);
     exit(0);
  }
  else if(argc == 2) {
    counter = atoi(argv[1]);
  }

  printf ("Robot: run for %d milliseconds\n", counter);

  wiringPiSetup();
  threads[LDR_THR] = piThreadCreate(ldr_loop);
  threads[CNY_THR] = piThreadCreate(cny_loop);

  for (i=0; i<counter; i++)
  {
    piLock(LDR_THR);
    if(Vldr)
    {
      printf("LDR value: %s\n", ldr == HIGH ? "high" : "low");
      Vldr = FALSE;
    }
    piUnlock(LDR_THR);

    piLock(CNY_THR);
    if(Vcny)
    {
      printf("CNY value: %s\n", cny == HIGH ? "high" : "low");
      Vcny = FALSE;
    }
    piUnlock(CNY_THR);

    delay(1);
  }
  printf("Finished\n");
  return 0 ;
}
