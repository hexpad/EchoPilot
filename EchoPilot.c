/*

The program that takes the servo motor to 180 degrees if the distance value is between 2cm and 10 cm, or 0 degrees if not.

*/


void main()
{
  int a;
  int counter;
  TRISB = 0b00000100;           //RB2 as Input PIN (ECHO)
  T1CON = 0x00;                 //Prescaler value set as 1:1

  while(1)
  {
    TMR1H = 0;                  //Sets the Initial Value of Timer
    TMR1L = 0;                  //Sets the Initial Value of Timer

    PORTB.F0 = 1;               //TRIGGER HIGH
    Delay_us(10);               //10uS Delay
    PORTB.F0 = 0;               //TRIGGER LOW

    while(!PORTB.F2);           //Wait for Echo

    T1CON.F0 = 1;               //Timer Starts
    while(PORTB.F2);            //Waiting for Echo goes LOW
    T1CON.F0 = 0;               //Timer Stops

    a = (TMR1L | (TMR1H<<8));   // Read Timer Value.                              

/*
    fosc = 20 MHz
    Internal Clock = fosc/4 = 5 MHz
    Time = (TMR1H:TMR1L)*(1/Internal Clock)*Prescaler
    Time = (TMR1H:TMR1L) * (1/5000000) * 1
    Time_us = Time/5
*/


    a = (a/58.82)/5;            //  Since the meter step interval is 0.2
                                //  microsecond, the counter value was converted to
                                //  microseconds by dividing it into 5.

    a = a + 1;                  //  Distance Calibration (Rounded up because
                                //  a is defined as an integer.)

    if(a>=2 && a<=50)           //  Check if the result is between 2cm and
                                //  10cm.
    {
       PORTB.F3=1;              // LED Turns On
       for(counter=0;counter<50;counter++)  //180 Degree
       {
           PORTB.F4 = 1;
           Delay_us(2200);
           PORTB.F4 = 0;
           Delay_us(17800);
       }

    }else{
        PORTB.F3=0;          //LED Turns Off

        for(counter=0;counter<50;counter++)    //0 Degree
        {
           PORTB.F4 = 1;
           Delay_us(800);
           PORTB.F4 = 0;
           Delay_us(19200);
        }
      }
    }
  }
