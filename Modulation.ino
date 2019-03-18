unsigned int i = 0;
void setup()
{
 DDRB = 0x02;
 Serial.begin(9600);
 TCCR1A = 0x40; // set to toggle mode 
}
  
 void loop()
  {   
    //------------------------------ Modulation Begin ------------------------------
    while(1)
    {
       TCNT1 = 0;
       TIFR1 = (1<<ICF1);                             /* Clear ICF (Input Capture flag) flag */
       //AT HIGH, WAITING FOR FIRST FALLING EDGE (1)
       TCCR1B = 0x05;                                 /* Falling edge, no prescaler */
       while ((TIFR1&(1<<ICF1)) == 0)                 /* Wait for timer to detect Falling Edge */
       {
         TCCR1C = 0x80;
         // Higher Frequency, Lower 'i'
         for (i = 0; i < 20; i++);                    /* i = 20 -> 60.98 kHz */
       }
       TIFR1 = (1<<ICF1);                             /* Clear ICF flag */
 
       //AT LOW, WAITING FIRST RISING EDGE (0)
       TCCR1B = 0x45;                                 /* Rising edge, no prescaler */
       while ((TIFR1&(1<<ICF1)) == 0)                 /* Wait for timer to detect Rising Edge */
       {
          TCCR1C = 0x80;
          // Lower Frequency, Higher 'i'
          for (i = 0; i < 44; i++);                   /* i = 42 -> 30.4 kHz */
       }
       // Switch toggle to down 
    
       TIFR1 = (1<<ICF1);                             /* Clear ICF flag */
    } // Modulation end
    //------------------------------ Modulation End ------------------------------  
      
  } //void loop() end
