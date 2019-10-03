#include "SignalGenerator.h"

int analogPin0 = A1;
const int analogIn = A0;
int mVperAmp = 185;
int RawValue = 0;
double ACSoffest = 2500;
double Voltage = 0;
double Amps = 0;
//int ledPin = 13;
double duty_cycle1 = 70;
double vltg_i = 0;
double Amps_i = 0;
double pwr_i = 0;
int mltp = 5;

const int fanPin = 9;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  timer1.initialize(100);  // 100 us = 10 kHz
}

void loop() {
  Amps = 0;
  double vltg = 0;
  for (int count = 1; count<=100; count++)
  {
    int vlt_rl = analogRead(analogPin0);
    int rfrnc = 5;
    double vltg1 = mltp * (vlt_rl * rfrnc) / 1023;
    vltg = vltg + vltg1;
    RawValue = analogRead(analogIn);
    Voltage = (RawValue / 1023) * 5000;
    double Amps1 = ((Voltage-ACSoffest) / mVperAmp);
    Amps = Amps + Amps1;

  }
  vltg = vltg / 100;
  Serial.print("\t Voltage ==== ");
  Serial.println(vltg);
  
  double del_vltg = vltg - vltg_i;
  Amps = Amps / 100;
  double del_Amps = Amps - Amps_i;
  double pwr = vltg * Amps;

  Serial.print("\t Current ==== ");
  Serial.println(Amps);


  if(del_vltg== 0)
  {
    if(del_Amps == 0)
    {
      duty_cycle1 = duty_cycle1;
    }
    else
    {
      if(del_Amps > 0)
      {
        duty_cycle1 = duty_cycle1 + 0.01;
      }
      else
      {
        duty_cycle1 = duty_cycle1 - 0.01;
      }
    }
  }
  else
  {
    double inc_cond = del_Amps / del_vltg;
    double ins_cond = Amps / vltg;
    if(inc_cond + ins_cond == 0)
    {
      duty_cycle1 = duty_cycle1;
    }
    else
    {
      if(inc_cond + ins_cond > 0)
      {
        duty_cycle1 = duty_cycle1 + 0.1;
      }
      else
      {
        duty_cycle1 = duty_cycle1 - 0.1;
      }
    }
  }

  vltg_i = vltg;
  Amps_i = Amps;
  Serial.print("\tPower === ");
  Serial.println(pwr);
  Serial.print("\tduty_cycle === ");
  Serial.println(duty_cycle1);
  Serial.print("\n \n \n \n");
  //int duty_cycle = (duty_cycle1 / 100) * 255;
  //analogWrite(ledPin, duty_cycle);
  timer1.pwm(fanPin, (duty_cycle1 / 100) * 1023);
  delay(500);
}
