/*
 * The common part of the default linker scripts for standalone executables
 * running on single core Blackfin processors.
 *
 * Copyright (C) 2008 Analog Devices, Inc.
 * Modified 2017 Dean Miller
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 */

MEMORY
{
  MEM_L1_CODE : ORIGIN = 0x11A00000, LENGTH = 0xC000
  MEM_L1_CODE_CACHE : ORIGIN = 0x11A0C000, LENGTH = 0x4000
  MEM_L1_SCRATCH : ORIGIN = 0x11B00000, LENGTH = 0x2000
  MEM_L1_DATA_A : ORIGIN = 0x11800000, LENGTH = 0x8000
  MEM_L1_DATA_B : ORIGIN = 0x11900000, LENGTH = 0x8000

  MEM_L2 : ORIGIN = 0x08002000, LENGTH = 0x0EE000 + 0x10000 /* cached + uncached, should we do? idk */
}

/* The default linker script, for single core blackfin standalone executables */
OUTPUT_FORMAT("elf32-bfin", "elf32-bfin",
	      "elf32-bfin")
OUTPUT_ARCH(bfin)
ENTRY(__start)

SECTIONS
{
  /* Read-only sections, merged into text segment: */
  PROVIDE (__executable_start = 0x0); . = 0x0;
  .l2             :
  {
    *(.l2 .l2.*)
  } >MEM_L2 =0

  .text           :
  {
    *(.text.prologue);
    KEEP(*(.isr_vector))
    *(.text .text.* .l1.text .l1.text.*)
    KEEP (*(.text.*personality*))
    /* .gnu.warning sections are handled specially by elf32.em.  */
    *(.gnu.warning)
  } >MEM_L1_CODE =0
 
  .init           :
  {
    KEEP (*(.init))
  } >MEM_L1_CODE =0
 
  .fini           :
  {
    KEEP (*(.fini))
  } >MEM_L1_CODE =0
 
  .rodata         : 
  { 
    *(.rodata .rodata.*) 
  } >MEM_L1_DATA_A

  .data2           :
  {
    *(.data2 .data2.* .l1.data2 .l1.data2.*)
    KEEP (*(.*personality*))
  } >MEM_L1_DATA_B

  .data           :
  {
    *(.data .data.* .l1.data .l1.data.*)
    KEEP (*(.*personality*))
  } >MEM_L1_DATA_A
 
  .bss            :
  {
   __bss_start = .;
    *(.bss .bss.*)
    *(COMMON)
    __bss_end = .;
  } >MEM_L1_DATA_A
 
  . = ALIGN(32 / 8);
  . = ALIGN(32 / 8);
 
  __end = .; PROVIDE (_end = .);
  __stack_start = ORIGIN(MEM_L1_SCRATCH);
  __stack_end   = ORIGIN(MEM_L1_SCRATCH) + 0x200;
 
  /DISCARD/ : { *(.note.GNU-stack) }
}