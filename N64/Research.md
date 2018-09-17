# IPL "Initial Program Loader" Research
N64 IPL has 3 stages, 1, 2, and 3. 1 and 2 are the Peripheral InterFace ROM (PIF ROM), which chainloads the cartridge boot code (todo: figure that out). As usual, console boot is pretty straightforward:
* Console power is turned on
* CPU starts execution, "entry point" is 0x1FC00000¹.
* That sets the hardware to a "known state" (sets all registers and memory so nothing funky happens).

## Links

1. http://www.emulation64.com/ultra64/bootn64.html

2. https://tomplaskon.wordpress.com/2014/06/30/anatomy-of-a-nintendo-64/
