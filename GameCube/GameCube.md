# CodeWarrior / GameCube Runtime
GameCube games were developed/compiled with Metrowerks (later Freescale, now owned by NXP)'s IDE CodeWarrior. The boot process of games looks something like

- GameCube power on, IPL (Initial Program Loader) is executed which either displays the menu or launches a game
- game execution starts with "apploader.img" which sets up a bunch of metadata for the program (TODO: figure out what) such as BootInfo2/BI2
- DOL execution starts at the entrypoint, `__start`, which sets up the rest of the runtime environment, initializing registers, all the various pieces (VI, OSThread, etc), and calls InitMetroTRK for debugging.
- main() is eventually called, can pass arguments via BI2 information, `int main(int argc, char** argv)` like usual

Once main() is called, it's acting as a normal program. The apploader.img is provided and developers link to .a libraries and .h headers for all the necessary function calls (GX rendering, creating threads, etc), source code is never provided.

# C++ EABI
C++ is supported for development, `__start` calls `__init_cpp` which sets up all the needed info. CodeWarrior also adds a .ctors and .dtors section (tables of the constructors/destructors) after the .text section. Technical details about how functions are called will be covered in another file.

# Apploader
## Overview
*Note: this is mostly informed spitballing because the trailer isn't documented anywhere.*

apploader.img is stored at 0x2440 on the disc, and is read as 3 chunks:
- 0x20 byte header
- apploader payload
- apploader trailer

The header looks something like
```C
typedef struct {
    char build_date[16]; //2004/11/10, also has build time in strings
    void* entrypoint; //what's called after the apploader is loaded into memory
    uint32_t entry_size; //size of the initial payload
    uint32_t trailer_size; //size of the trailer payload
    uint8_t padding[4];
};
```
The IPL(?)
- reads the header
- copies `apploader + 0x20` (0x2460) to 0x81200000
- copies `apploader + 0x20 + entry_size` to 0x81300000
- calls entrypoint(r3** init, r4** main, r5** close);

The apploader stores the pointer to its init, main, and close functions so the IPL can call them as needed.

The rest of this is redundant so go look at [GC-Forever](https://www.gc-forever.com/wiki/index.php?title=Apploader#Overview)'s page for the full teardown.

## Apploader "trailer"
The apploader trailer is structured the same as a normal dolfile is, .init, extab, extabindex, .text, (.ctors .dtors?) .rodata, .data, .bss, with extab listing all the sections.
