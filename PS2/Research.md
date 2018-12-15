# Sony PlayStation 2™
# Tech Specs
Two CPUs:
* Custom MIPS R5900-based "Emotion Engine", running at ~300MHz (294.912 MHz?), the main processor running the whole system
* MIPS R3000A "IOP" I/O Processor that provides services and backwards compatibility for PS1 titles¹

¹ Replaced with a "Deckard" PowerPC 405 chip in later models, varying compatibility

# Boot Process
### **Incomplete**

Power is switched on, EE/IOP have their own on-dye bootroms (which I need to obtain....somehow), which initializes each CPU, which load the BIOS to 0xBFC00000²

² figure out if it's ever unloaded
