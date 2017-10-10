/*
  Tell DCS-BIOS to use a serial connection and use the default Arduino Serial
  library. This will work on the vast majority of Arduino-compatible boards,
  but you can get corrupted data if you have too many or too slow outputs
  (e.g. when you have multiple character displays), because the receive
  buffer can fill up if the sketch spends too much time updating them.
  
  If you can, use the IRQ Serial connection instead.
*/
#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"
#include <LedControl.h> //on inclus la librairie pour commander le MAX7219


/*display declaration 
 pin 10 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 12 is connected to LOAD 
 to one MAX7219
*/
LedControl lc=LedControl(10,11,12,1);



/* Fonction permettant la récupération et l'affichage du preset selectionné sur la radio UHF */
void onUhfPresetChange(unsigned int uhfPresetValue) {
unsigned int firstDigit;
unsigned int secondDigit;
   if (uhfPresetValue>2000 && uhfPresetValue<5000){firstDigit=0;secondDigit=1;}
   else if (uhfPresetValue>5000 && uhfPresetValue<7000){firstDigit=0;secondDigit=2;}
   else if (uhfPresetValue>7000 && uhfPresetValue<11000){firstDigit=0;secondDigit=3;}
   else if (uhfPresetValue>11000 && uhfPresetValue<14500){firstDigit=(0);secondDigit=(4);}
   else if (uhfPresetValue>14500 && uhfPresetValue<17500){firstDigit=0;secondDigit=5;}
   else if (uhfPresetValue>17500 && uhfPresetValue<21500){firstDigit=0;secondDigit=6;}
   else if (uhfPresetValue>21500 && uhfPresetValue<24000){firstDigit=0;secondDigit=7;}
   else if (uhfPresetValue>24000 && uhfPresetValue<27500){firstDigit=0;secondDigit=8;}
   else if (uhfPresetValue>27500 && uhfPresetValue<30500){firstDigit=0;secondDigit=9;}
   else if (uhfPresetValue>30500 && uhfPresetValue<34000){firstDigit=1;secondDigit=0;}
   else if (uhfPresetValue>34000 && uhfPresetValue<37500){firstDigit=1;secondDigit=1;}
   else if (uhfPresetValue>37500 && uhfPresetValue<41000){firstDigit=1;secondDigit=2;}
   else if (uhfPresetValue>41000 && uhfPresetValue<44000){firstDigit=1;secondDigit=3;}
   else if (uhfPresetValue>44000 && uhfPresetValue<47000){firstDigit=1;secondDigit=4;}
   else if (uhfPresetValue>47000 && uhfPresetValue<51000){firstDigit=1;secondDigit=5;}
   else if (uhfPresetValue>51000 && uhfPresetValue<54000){firstDigit=1;secondDigit=6;}
   else if (uhfPresetValue>54000 && uhfPresetValue<56500){firstDigit=1;secondDigit=7;}
   else if (uhfPresetValue>56500 && uhfPresetValue<60000){firstDigit=1;secondDigit=8;}
   else if (uhfPresetValue>60000 && uhfPresetValue<63000){firstDigit=1;secondDigit=9;}
   else if (uhfPresetValue>63000&& uhfPresetValue<=65535){firstDigit=2;secondDigit=0;}
lc.setDigit(0,0,firstDigit,false);
lc.setDigit(0,1,secondDigit,false);
}
DcsBios::IntegerBuffer uhfPresetBuffer(0x309c, 0xffff, 0, onUhfPresetChange);


/* Fonction permettant la récupération et l'affichage du preset selectionné sur la radio UHF */
void onUvhfPresetChange(unsigned int uvhfPresetValue) {
unsigned int firstDigit;
unsigned int secondDigit;
   if (uvhfPresetValue>2000 && uvhfPresetValue<5000){firstDigit=0;secondDigit=1;}
    else if (uvhfPresetValue>5000 && uvhfPresetValue<7000){firstDigit=0;secondDigit=2;}
    else if (uvhfPresetValue>7000 && uvhfPresetValue<11000){firstDigit=0;secondDigit=3;}
    else if (uvhfPresetValue>11000 && uvhfPresetValue<14500){firstDigit=0;secondDigit=4;}
    else if (uvhfPresetValue>14500 && uvhfPresetValue<17500){firstDigit=0;secondDigit=5;}
    else if (uvhfPresetValue>17500 && uvhfPresetValue<21500){firstDigit=0;secondDigit=6;}
    else if (uvhfPresetValue>21500 && uvhfPresetValue<24000){firstDigit=0;secondDigit=7;}
    else if (uvhfPresetValue>24000 && uvhfPresetValue<27500){firstDigit=0;secondDigit=8;}
    else if (uvhfPresetValue>27500 && uvhfPresetValue<30500){firstDigit=0;secondDigit=9;}
    else if (uvhfPresetValue>30500 && uvhfPresetValue<34000){firstDigit=1;secondDigit=0;}
    else if (uvhfPresetValue>34000 && uvhfPresetValue<37500){firstDigit=1;secondDigit=1;}
    else if (uvhfPresetValue>37500 && uvhfPresetValue<41000){firstDigit=1;secondDigit=2;}
    else if (uvhfPresetValue>41000 && uvhfPresetValue<44000){firstDigit=1;secondDigit=3;}
    else if (uvhfPresetValue>44000 && uvhfPresetValue<47000){firstDigit=1;secondDigit=4;}
    else if (uvhfPresetValue>47000 && uvhfPresetValue<51000){firstDigit=1;secondDigit=5;}
    else if (uvhfPresetValue>51000 && uvhfPresetValue<54000){firstDigit=1;secondDigit=6;}
    else if (uvhfPresetValue>54000 && uvhfPresetValue<56500){firstDigit=1;secondDigit=7;}
    else if (uvhfPresetValue>56500 && uvhfPresetValue<60000){firstDigit=1;secondDigit=8;}
    else if (uvhfPresetValue>60000 && uvhfPresetValue<63000){firstDigit=1;secondDigit=9;}
    else if (uvhfPresetValue>63000 && uvhfPresetValue<=65535){firstDigit=2;secondDigit=0;}
lc.setDigit(0,3,firstDigit,false);
lc.setDigit(0,4,secondDigit,false); 
}
DcsBios::IntegerBuffer uvhfPresetBuffer(0x30a6, 0xffff, 0, onUvhfPresetChange);




/* Fonctions pour les encodeurs */
DcsBios::RotaryEncoder uhfPresetKnob("UHF_PRESET_KNOB", "DEC", "INC", 6, 7);
DcsBios::RotaryEncoder uvhfPresetKnob("UVHF_PRESET_KNOB", "DEC", "INC", 4, 5);


void setup() {
  DcsBios::setup();
  lc.shutdown(0, false);
  lc.setIntensity(0,9);
}

void loop() {
  DcsBios::loop();
}

