/*
******************************************************************************
**
**  File        : LinkerScript.ld
**
**  Author      : STM32CubeIDE
**
**  Abstract    : Linker script for STM32H7 series
**                      1024Kbytes FLASH
**                       800Kbytes RAM
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : STMicroelectronics STM32
**
**  Distribution: The file is distributed as is without any warranty
**                of any kind.
**
*****************************************************************************
** @attention
**
** Copyright (c) 2023 STMicroelectronics.
** All rights reserved.
**
** This software is licensed under terms that can be found in the LICENSE file
** in the root directory of this software component.
** If no LICENSE file comes with this software, it is provided AS-IS.
**
*****************************************************************************
*/

/* Entry Point */
ENTRY(Reset_Handler)

_Min_Heap_Size = 0; /* required amount of heap, null bcz we use external ram for this purpose  */
_Min_Stack_Size = 64K; /* required amount of stack */

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM_D3) + _Min_Stack_Size;

/* Memories definition */
MEMORY
{
  RAM_D1 (xrw)   : ORIGIN = 0x24000000, LENGTH =  512K
  DTCMRAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 128K
  RAM_D2 (xrw)   : ORIGIN = 0x30000000, LENGTH = 288K
  RAM_D3 (xrw)   : ORIGIN = 0x38000000, LENGTH = 64K
  ITCMRAM (xrw)  : ORIGIN = 0x00000000, LENGTH = 64K
  EXTRAM  (rw)   : ORIGIN = 0xD0000000, LENGTH = 32M
  FLASH   (rx)   : ORIGIN = 0x08000000, LENGTH = 2M    /* Memory is divided. Actual start is 0x08000000 and actual length is 2048K */
  DUMMY  (rw)   : ORIGIN = 0xE0000000, LENGTH = 32M
  DUMMY_2  (rw)   : ORIGIN = 0xF0000000, LENGTH = 32M
}

/* Sections */
SECTIONS
{
  /* The startup code into "FLASH" Rom type memory */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  _sihotfunc = LOADADDR(.hotfunc);
  .hotfunc :
  {
  _shotfunc = .;
  . = ALIGN(4);
  *(.hotfunc)
  *(.hotfunc*)
    /* renderer code is hot, put it in ITCM */
  *r_edge*(.text)
  *r_edge*(.text*)
  *r_scan*(.text)
  *r_scan*(.text*)
  *r_draw*(.text)
  *r_draw*(.text*)
  *r_rast*(.text)
  *r_rast*(.text*)
  *r_surf*(.text)
  *r_surf*(.text*)
  *r_triapi*(.text)
  *r_triapi*(.text*)
  *r_polyse*(.text)
  *r_polyse*(.text*)
  *r_trialias*(.text)
  *r_trialias*(.text*)
  *r_aclip*(.text)
  *r_aclip*(.text*)
  *r_light*(.text)
  *r_light*(.text*)
  *matrixlib*(.text)
  *matrixlib*(.text*)
  /* 
	  *StudioModelRenderer*(.text)
	  *StudioModelRenderer*(.text*)
  */
  /*
	  *r_studio*(.text)
	  *r_studio*(.text*)
  */
  . = ALIGN(4);
  _ehotfunc = .;
  } >ITCMRAM AT> FLASH

  /* The program code and other data into "FLASH" Rom type memory */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data into "FLASH" Rom type memory */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  .ARM.extab   : {
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } >FLASH

  .ARM : {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >FLASH

  .preinit_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .fini_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >FLASH

  . = ALIGN(4);
  .ramd2 :
  {
   PROVIDE(_ramd2_bss_start = .);
   *stm32h7*(.bss) /* HAL initialization code shouldnt be in SDRAM */
   *stm32h7*(.bss*)
   *is42s32800j*(.bss) /* HAL initialization code shouldnt be in SDRAM */
   *is42s32800j*(.bss*)
   *(.ramd2)
   *(.ramd2*)
   . = ALIGN(4);
   PROVIDE(_ramd2_bss_end = .);
  } > RAM_D2

  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections into "RAM" Ram type memory */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM_D2 AT> FLASH

  
  . = ALIGN(4);
  .ramd3 :
  {
   *(.ramd3)
   *(.ramd3*)
   . = ALIGN(4);
  } > RAM_D3

  . = ALIGN(4);
  
  .axiram (NOLOAD) :
  {
    *(.axiram)
    *(.axiram*)
   . = ALIGN(4);
  } > RAM_D1
  

  /* Uninitialized data section into "RAM" Ram type memory */
  /*
  . = ALIGN(4);
  .bss :
  {
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .; 
    __bss_end__ = _ebss;
  } >RAM_D1
  */
  
  . = ALIGN(4);
  .fastram :
  {  
   *(.fastram)
   *(.fastram*)
   . = ALIGN(4);
  } > DTCMRAM
  
  . = ALIGN(8);
  .extram (NOLOAD) : 
  {
   /* reserve space for the framebuffer */
  	/*. = . + (800*480*2);*/
  	. = ALIGN(8);
    _sextram = .;         /* define a global symbol at bss start */
    __extrambss_start__ = _sextram;
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
  	*(.extram)
  	*(.extram*)
    *(.ramd1)
    *(.ramd1*)
    _eextram = .;         /* define a global symbol at bss end */
    __extrambss_end__ = _eextram;
  	PROVIDE(_heap_start = .);
  	PROVIDE(_heap_limit = ORIGIN(EXTRAM) + LENGTH(EXTRAM));
  	. = ALIGN(8);
  } > EXTRAM

  /* User_heap_stack section, used to check that there is enough "RAM" Ram  type memory left */

  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM_D3

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
