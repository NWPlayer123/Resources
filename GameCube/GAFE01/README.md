# Intro
This here is an attempt to translate Animal Crossing for GameCube back to source code, since it has full symbols.

# Notes
File loading seems to happen in several ways, actual archive handling is done in main.dol/static.map, JKernel's ARAM (Archive RAM?), the foresta.rel just requests to load files and get data from them, which is all done in memory (hence ARAM).

_JW_GetResourceAram is a stub to call JKRAram::aramToMainRam() for when you need to get data from memory

Usually though, it looooks like foresta just does high level stuff, with some intermediary stuff when needed, e.g. loading strings from the table
