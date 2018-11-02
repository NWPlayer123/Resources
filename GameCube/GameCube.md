# CodeWarrior / GameCube Runtime
GameCube games were developed/compiled with Metrowerks (later Freescale, now owned by NXP)'s IDE CodeWarrior. The boot process of games looks something like

- GameCube power on, IPL (Initial Program Loader) is executed which either displays the menu or launches a game
- game execution starts with "apploader.img" which sets up a bunch of metadata for the program (TODO: figure out what) such as BootInfo2/BI2
- DOL execution starts at the entrypoint, `__start`, which sets up the rest of the runtime environment, initializing registers, all the various pieces (VI, OSThread, etc), and calls InitMetroTRK for debugging.
- main() is eventually called, can pass arguments via BI2 information, `int main(int argc, char** argv)` like usual

Once main() is called, it's acting as a normal program. The apploader.img is provided and developers link to .a libraries and .h headers for all the necessary function calls (GX rendering, creating threads, etc), source code is never provided.

# C++ EABI
C++ is supported for development, `__start` calls `__init_cpp` which sets up all the needed info. CodeWarrior also adds a .ctors and .dtors section (tables of the constructors/destructors) after the .text section. Technical details about how functions are called will be covered in another file.

