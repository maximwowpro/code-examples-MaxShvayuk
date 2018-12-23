# ATMega2560 combination door lock
This is **BARE-METAL-AVR** project, **without** using any Arduino functions or libraries.

#### Avaiable features:
* UART communication (for example with PC);
* Resistic keyboard which occupies just 1 ADC pin;
* alarm with reed switch and zummer;
* all passwords store at EEPROM;
* OLED display **ssd1306** library;
* stepper motor **28BYJ-48** library;
* RGB LED library.

To flash this project to your ATMega2560 MCU, just run `make all` from _src_ folder.

#### This is how lock looks like at breaddoard:
![This is how lock looks like at breaddoard](https://picua.org/images/2018/08/29/fdb3c1003496bf6d074d16317bc1e77a.jpg "")

### Also you can see demonstration of work at YouTube:
[Video](https://www.youtube.com/watch?v=Rg2NvHXRdqM)
 
