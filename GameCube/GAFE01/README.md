# Intro
This here is an attempt to translate Animal Crossing for GameCube back to source code, since it has full symbols.

# Bootloader
This is what loads the Nintendo logo (nintendo_376x104) and sound byte (nintendo_hi_0):
```
sound_initial();
initial_menu_init();
dvderr_init();
sound_initial2();
```
While those are playing, it'll load, decompress, and run _prolog for foresta.rel, which are all done in LoadLink (chainloads OSLink, the SDK function that loads the REL into memory).

After that, it'll call HotStartEntry(), which _prolog sets to foresta's entry(), which boots the actual title screen and game.

# Notes
File loading seems to happen in several ways, actual archive handling is done in main.dol/static.map, JKernel's ARAM (Archive RAM?), the foresta.rel just requests to load files and get data from them, which is all done in memory (hence ARAM).

_JW_GetResourceAram is a stub to call JKRAram::aramToMainRam() for when you need to get data from memory

Usually though, it looooks like foresta just does high level stuff, with some intermediary stuff when needed, e.g. loading strings from the table


# Research Dump
JW_GetAramAddress(archiveIndex) gets the A(rchive?) RAM address for the file you want in forest_1st/forest_2nd, looks like famicom.arc has its own system

```
.data:800B045C aram_resName:   .long str_800AFFC0                              # 0x00,  "fgdata.bin"
.data:800B0460                 .long str_800AFFCC                              # 0x01,  "mail_data.bin"
.data:800B0464                 .long str_800AFFDC                              # 0x02,  "mail_data_table.bin"
.data:800B0468                 .long str_800AFFF0                              # 0x03,  "maila_data.bin"
.data:800B046C                 .long str_800B0000                              # 0x04,  "maila_data_table.bin"
.data:800B0470                 .long str_800B0018                              # 0x05,  "mailb_data.bin"
.data:800B0474                 .long str_800B0028                              # 0x06,  "mailb_data_table.bin"
.data:800B0478                 .long str_800B0040                              # 0x07,  "mailc_data.bin"
.data:800B047C                 .long str_800B0050                              # 0x08,  "mailc_data_table.bin"
.data:800B0480                 .long str_800B0068                              # 0x09,  "pallet_boy.bin"
.data:800B0484                 .long str_800B0078                              # 0x0A,  "ps_data.bin"
.data:800B0488                 .long str_800B0084                              # 0x0B,  "ps_data_table.bin"
.data:800B048C                 .long str_800B0098                              # 0x0C,  "psz_data.bin"
.data:800B0490                 .long str_800B00A8                              # 0x0D,  "psz_data_table.bin"
.data:800B0494                 .long str_800B00BC                              # 0x0E,  "select_data.bin"
.data:800B0498                 .long str_800B00CC                              # 0x0F,  "select_data_table.bin"
.data:800B049C                 .long str_800B00E4                              # 0x10,  "string_data.bin"
.data:800B04A0                 .long str_800B00F4                              # 0x11,  "string_data_table.bin"
.data:800B04A4                 .long str_800B010C                              # 0x12,  "superz_data.bin"
.data:800B04A8                 .long str_800B011C                              # 0x13,  "superz_data_table.bin"
.data:800B04AC                 .long str_800B0134                              # 0x14,  "super_data.bin"
.data:800B04B0                 .long str_800B0144                              # 0x15,  "super_data_table.bin"
.data:800B04B4                 .long str_800B015C                              # 0x16,  "tex_boy.bin"
.data:800B04B8                 .long str_800B0168                              # 0x17,  "face_boy.bin"
.data:800B04BC                 .long str_800B0178                              # 0x18,  "fgnpcdata.bin"
.data:800B04C0                 .long str_800B0188                              # 0x19,  "message_data.bin"
.data:800B04C4                 .long str_800B019C                              # 0x1A,  "message_data_table.bin"
.data:800B04C8                 .long str_800B01B4                              # 0x1B,  "my_original.bin"
.data:800B04CC                 .long str_800B01C4                              # 0x1C,  "needlework.bin"
.data:800B04D0                 .long str_800B01D4                              # 0x1D,  "player_room_floor.bin"
.data:800B04D4                 .long str_800B01EC                              # 0x1E,  "player_room_wall.bin"
.data:800B04D8                 .long str_800B0204                              # 0x1F,  "npc_name_str_table.bin"
.data:800B04DC                 .long str_800B021C                              # 0x20,  "d_obj_npc_stock_sch.bin"
.data:800B04E0                 .long str_800B0234                              # 0x21,  "d_obj_npc_stock_scl.bin"
.data:800B04E4                 .long str_800B024C                              # 0x22,  "title.bti"
.data:800B04E8                 .long str_800B0258                              # 0x23,  "mura_spring.bti"
.data:800B04EC                 .long str_800B0268                              # 0x24,  "mura_summer.bti"
.data:800B04F0                 .long str_800B0278                              # 0x25,  "mura_fall.bti"
.data:800B04F4                 .long str_800B0288                              # 0x26,  "mura_winter.bti"
.data:800B04F8                 .long str_800B0298                              # 0x27,  "odekake.bti"
.data:800B04FC                 .long str_800B02A4                              # 0x28,  "omake.bti"
.data:800B0500                 .long str_800B02B0                              # 0x29,  "eki1.bti"
.data:800B0504                 .long str_800B02BC                              # 0x2A,  "eki1_2.bti"
.data:800B0508                 .long str_800B02C8                              # 0x2B,  "eki1_3.bti"
.data:800B050C                 .long str_800B02D4                              # 0x2C,  "eki1_4.bti"
.data:800B0510                 .long str_800B02E0                              # 0x2D,  "eki1_5.bti"
.data:800B0514                 .long str_800B02EC                              # 0x2E,  "eki2.bti"
.data:800B0518                 .long str_800B02F8                              # 0x2F,  "eki2_2.bti"
.data:800B051C                 .long str_800B0304                              # 0x30,  "eki2_3.bti"
.data:800B0520                 .long str_800B0310                              # 0x31,  "eki2_4.bti"
.data:800B0524                 .long str_800B031C                              # 0x32,  "eki2_5.bti"
.data:800B0528                 .long str_800B0328                              # 0x33,  "eki3.bti"
.data:800B052C                 .long str_800B0334                              # 0x34,  "eki3_2.bti"
.data:800B0530                 .long str_800B0340                              # 0x35,  "eki3_3.bti"
.data:800B0534                 .long str_800B034C                              # 0x36,  "eki3_4.bti"
.data:800B0538                 .long str_800B0358                              # 0x37,  "eki3_5.bti"
.data:800B053C                 .long str_800B0364                              # 0x38,  "tegami.bti"
.data:800B0540                 .long str_800B0370                              # 0x39,  "tegami2.bti"
.data:800B0544                 .long str_800B037C                              # 0x3A,  "famikon.bti"
.data:800B0548                 .long str_800B0388                              # 0x3B,  "boy1.bti"
.data:800B054C                 .long str_800B0394                              # 0x3C,  "boy2.bti"
.data:800B0550                 .long str_800B03A0                              # 0x3D,  "boy3.bti"
.data:800B0554                 .long str_800B03AC                              # 0x3E,  "boy4.bti"
.data:800B0558                 .long str_800B03B8                              # 0x3F,  "boy5.bti"
.data:800B055C                 .long str_800B03C4                              # 0x40,  "boy6.bti"
.data:800B0560                 .long str_800B03D0                              # 0x41,  "boy7.bti"
.data:800B0564                 .long str_800B03DC                              # 0x42,  "boy8.bti"
.data:800B0568                 .long str_800B03E8                              # 0x43,  "girl1.bti"
.data:800B056C                 .long str_800B03F4                              # 0x44,  "girl2.bti"
.data:800B0570                 .long str_800B0400                              # 0x45,  "girl3.bti"
.data:800B0574                 .long str_800B040C                              # 0x46,  "girl4.bti"
.data:800B0578                 .long str_800B0418                              # 0x47,  "girl5.bti"
.data:800B057C                 .long str_800B0424                              # 0x48,  "girl6.bti"
.data:800B0580                 .long str_800B0430                              # 0x49,  "girl7.bti"
.data:800B0584                 .long str_800B043C                              # 0x4A,  "girl8.bti"
.data:800B0588                 .long str_800B0448                              # 0x4B,  "d_bg_island_sch.bin"
```
