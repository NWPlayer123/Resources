# Introduction

[Ghidra](https://github.com/NationalSecurityAgency/ghidra) is a reverse engineering tool released/developed by the NSA in March 2019. 

Note that this document will focus mostly on Nintendo reverse engineering with Ghidra.

# Getting Started
* Download the latest release of Ghidra [here](https://ghidra-sre.org), and put it somewhere safe (I have it in C:\Hacks\Ghidra\ghidra_9.x)
* Download the [Gecko extension](https://github.com/aldelaro5/ghidra-gekko-broadway-lang), and follow instructions to install it.
* Download the [DOL/REL loaders](https://github.com/Cuyler36/Ghidra-GameCube-Loader), and follow instructions to install it.

# How to use Ghidra
On first boot, you'll be greeted with this screen.

<img src="https://github.com/NWPlayer123/Resources/blob/master/Ghidra/pictures/Screenshot_506.png" width="400">

Ghidra is a project-based system. I don't bother and just have a singular "Ghidra" project. To create one, is just `File->New Project`. There are two options:
* Non-Shared Project - local project that you can work on. (Note: you can export programs and send them to others as a gzf file).
* Shared Project - requires a server running the Ghidra server code to relay changes between multiple people on the same project.

Once you create a project, you can start importing files. You can either do it with `File->Import File`, or do a Batch Import. The default options are usually fine.
Ghidra has a [number of supported formats](https://github.com/NationalSecurityAgency/ghidra/blob/master/Ghidra/Features/Base/src/main/help/help/topics/ImporterPlugin/importer.htm#L28), and you can expand that with extensions as above.

Once it's imported in the list, you can double click it to open up the CodeBrowser window. You may have to enable certain things with `File->Configure...`

# Useful windows
Currently, I have
* Data Type Manager, for creating structs, enums, and typedefs, and Symbol Tree, for hunting down specific functions, on the left side.
* Disassembly view in the middle
* Decompiler and Bytes View on the left.

<img src="https://github.com/NWPlayer123/Resources/blob/master/Ghidra/pictures/Screenshot_510.png" width="800">

Other useful things:
* `Window->Defined Strings`, `Right Click->Default Settings...` and changing charset to Shift-JIS or UTF-8/16 so it reads strings correctly.
* `Window->Memory Map`, for all the code/data segments. Note that Ghidra is a lot more picky than IDA, IDA lets sections overlap while Ghidra will complain if you try to define over a section that already exists (as noticed when creating BSS sections for DOL ^)

# GameCube specific notes
### r2 and r13
GameCube uses two reference registers, r2 and r13, which are set to SDA2 and SDA (Small Data Area), respectively. The Gecko extension above allows Ghidra to recognize them as static registers, but you need to supply the actual values it sets them to. This is easy enough. You'll need to find the entrypoint, which for the CodeWarrior EABI is `__start`, somewhere near 0x80003100. It has two function calls, a stack frame, and then another call. Those functions are `__init_registers`, `__init_hardware`, and `__init_data`, respectively. If you go to `__init_registers`, depending on the SDK version, will set r1, r2, and r13, or all 32 registers, to their default values.

<img src="https://github.com/NWPlayer123/Resources/blob/master/Ghidra/pictures/Screenshot_511.png" width="400">

<img src="https://github.com/NWPlayer123/Resources/blob/master/Ghidra/pictures/Screenshot_512.png" width="400">

What you want to do is `Right Click->Set Register Values....`, register r2, set to the value `__init_registers` uses, e.g. 0x8041DD00, and then hit okay. Repeat for r13. I'd recommend also setting GQR0 to 0 (very few games actually modify the value), so the decompiler will understand Paired Singles instructions.

<img src="https://github.com/NWPlayer123/Resources/blob/master/Ghidra/pictures/Screenshot_507.png" width="400">

Then, go to `Window->Register Manager`, find r2, r13, and GQR0, and then double click to edit, and change the address range to 80000000-81800000 (the full GameCube memory range).

<img src="https://github.com/NWPlayer123/Resources/blob/master/Ghidra/pictures/Screenshot_508.png" width="400">

<img src="https://github.com/NWPlayer123/Resources/blob/master/Ghidra/pictures/Screenshot_509.png" width="400">

Then your decompilation will clean up to usable and in some cases, entirely valid C(++)

<img src="https://github.com/NWPlayer123/Resources/blob/master/Ghidra/pictures/Screenshot_513.png" width="400">

# Tips and Tricks
If you're trying to define a 64-bit variable, it can't fit inside a 32-bit register, obviously. Ghidra will try to define it on the stack, so you'll have to turn on "Use Custom Storage", and manually define the two registers it's using. This comes up with e.g. OSTime is an int64_t.

<img src="https://github.com/NWPlayer123/Resources/blob/master/Ghidra/pictures/Screenshot_514.png" width="400">

<img src="https://github.com/NWPlayer123/Resources/blob/master/Ghidra/pictures/Screenshot_515.png" width="400">

<img src="https://github.com/NWPlayer123/Resources/blob/master/Ghidra/pictures/Screenshot_516.png" width="400">

# TODO
* Add more tricks that people ask about
