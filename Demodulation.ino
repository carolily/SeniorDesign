bool state = false;
unsigned int newstate;
unsigned i = 0;
unsigned int t1 = 0;
unsigned int t2 = 0;
void setup()
{
 DDRB = 0x02;
  //TCCR1A = 0x40; // set to toggle mode 
  TIMSK1 = 0;                   // Disable all interrupts incase they were set
  TCCR1B = 0x01;                // Falling edge time and no prescaler
  TCNT1 = 0; 
}
 void loop()
  {   
    //------------------------------ Demodulation Begin ------------------------------
       //TCCR1B = 0x01;                                  /* No prescaler */
       TCNT1 = 0;
    
       while ( (TIFR1&(1<<ICF1)) == 0);
       t1 = ICR1;                                     /* Store time of first falling edge */
       TIFR1 = (1<<ICF1);
       while ( (TIFR1&(1<<ICF1)) == 0);
  
       t2 = ICR1;                                     /* Store time of first falling edge */
       TIFR1 = (1<<ICF1);                             /* Clear the IC flags */
                                        
      //newstate = (t2 - t1);                    
                                                      /* Period */
                                                      // 5k Hz   -> 3200 ticks
                                                      // 10k Hz  -> 1600 ticks
                                                      // 20k Hz  -> 800 ticks
                                                      // 40k Hz  -> 400 ticks 
                                                      // (High i = 20 -> 60.98 kHz / Low i = 42 -> 30.4 kHz)
                                                      // 80k Hz  -> 200 ticks
                                                      // (High 90 kHz / Low 70 kHz)
                                                      // 160k Hz -> 100 ticks
                                                      // (High 170 kHz / Low 150 kHz)
                                                      // 320k Hz -> 50 ticks
                                                      // 640k Hz -> 25 ticks
    if((newstate = t2 - t1) < 1000){
        if(newstate < 400)
        {
          TCCR1A = 0xC0;
          TCCR1C = 0X80;
        }
        else{
          TCCR1A = 0x80;
          TCCR1C = 0X80;
        }
    }
   
//       if(newstate != state)
//       {
//          TCCR1C = 0x80;                              /* Force output compare: Toggle */
//          state = !state;
//       }
       TCCR1B ^= 1<<6 ;                               /* Toggle. First will be rising then falling */
    //------------------------------ Demodulation End ------------------------------  
    
  } //void loop() end
