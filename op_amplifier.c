// To make this code work without going through ADC-DAC I had to do some external wiring and shorten some legs
// because the software doesn't allow to change the value. 
// I shorted leg H8.7 (P6.6)  and resistor R28. 

#include "msp430xG46x.h" 
 
 
P6SEL = 0xBF;                             // All but P6.6 analog funct. 
 
P2OUT |= 0x08;                            // Mic supply on 
 
 
 // Setup OA0 = Microphone pre-amplifier 
  // OA0+ = P6.2/OA0I1 
  // OA0- = P6.0/OA0I0 
  // OA0OUT = P6.1/OA0O, A1 (internal) 
  OA0CTL0 = OAP_1 + OAPM_3;                 // Select inputs, power mode 
  OA0CTL1 = OARRIP;                         // General purp., rail-to-rail inp. 
 
  OA0CTL0 = 0;                              // Disable OA0 
 
  P2OUT &= ~0x08;                           // Mic supply off 

 // Setup OA1 = S-K Output filter for DAC12_1 
  // OA1+ = P6.4/OA1I0 
  // OA1- = R_Bottom (internal) 
  // OA1OUT = P6.3/A3/OA1O, R_Bottom (internal) 
  OA1CTL0 = OAPM_3 + OAADC1;                // Select inputs, power mode 
  OA1CTL1 = OAFC_1 + OARRIP;                // Unity Gain, rail-to-rail inputs 
 
  // Setup OA2 = Gain stage 
  // OA2+ = DAC12_0OUT 
  // OA2- = OA1OUT 
  // OA2OUT = P6.5/OA2O 
  OA2CTL0 = OAN_2 + OAP_2 + OAPM_3 + OAADC1;// Select inputs, power mode 
  OA2CTL1 = OAFC_6 + OAFBR_2 + OARRIP;      // Invert. PGA, OAFBRx sets gain 
 
 
 OA1CTL0 = 0;                              // Disable OA1 
  OA2CTL0 = 0;                              // Disable OA2 
