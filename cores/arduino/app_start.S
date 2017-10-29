/*
 * Basic startup code for Blackfin processor
 *
 * Copyright (C) 2008 Analog Devices, Inc.
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

// basic startup code which
// - turns the cycle counter on
// - loads up FP & SP (both supervisor and user)
// - initialises the device drivers (FIOCRT)
// - calls monstartup to set up the profiling routines (PROFCRT)
// - calls the C++ startup (CPLUSCRT)
// - initialises argc/argv (FIOCRT/normal)
// - calls _main
// - calls _exit (which calls monexit to dump accumulated prof data (PROFCRT))
// - defines dummy IO routines (!FIOCRT)

//#include <bf706_device.h>
#include <sys/anomaly_macros_rtl.h>

#define EVT2h (0x1FC02008 >> 16)
#define EVT2l (0x1FC02008 & 0xFFFF)
#define UNASSIGNED_VAL 0
#define UNASSIGNED_FILL 0
// just IVG15
#define INTERRUPT_BITS 0x8800

	.text;
	.align 2;
	.global __start;
	.type __start, STT_FUNC;
	.section .text.prologue, "ax"
__start:

	CSYNC;

	// Zap loop counters to zero, to make sure that
	// hw loops are disabled - it could be really baffling
	// if the counters and bottom regs are set, and we happen
	// to run into them.
	R7 = 0;
	LC0 = R7;
	LC1 = R7;

	// Clear the DAG Length regs too, so that its safe to
	// use I-regs without them wrapping around.
	L0 = R7;
	L1 = R7;
	L2 = R7;
	L3 = R7;

	// Initialise the Event Vector table.
	P0.H = EVT2h;
	P0.L = EVT2l;

	// Install __unknown_exception_occurred in EVT so that
	// there is defined behaviour.
	P1 = 13;
	R1.L = __unknown_exception_occurred;
	R1.H = __unknown_exception_occurred;
	LSETUP (L$ivt,L$ivt) LC0 = P1;
L$ivt:	[P0++] = R1;
	// Set IVG15s handler to be the start of the mode-change
	// code. Then, before we return from the Reset back to user
	// mode, well raise IVG15. This will mean we stay in supervisor
	// mode, and continue from the mode-change point., but at a
	// much lower priority.
	P1.H = L$supervisor_mode;
	P1.L = L$supervisor_mode;
	[P0] = P1;

	// Initialise the stack.
	// Note: this points just past the end of the section.
	// First write should be with [--SP].

	SP.L=__stack_end - 12;
	SP.H=__stack_end - 12;
	usp = sp;

	// Were still in supervisor mode at the moment, so the FP
	// needs to point to the supervisor stack.
	FP = SP;

	// And make space for incoming "parameters" for functions
	// we call from here:
	SP += -12;

	// Zero out bss section

	R0.L = __bss_start;
	R0.H = __bss_start;
	R1.L = __bss_end;
	R1.H = __bss_end;
	R2 = R1 - R0;
	R1 = 0;
	CALL.X _memset;

	R0 = INTERRUPT_BITS (Z);
	// CALL.X __install_default_handlers;
	R4 = R0;		// Save modified list

	R0 = SYSCFG;		// Enable the Cycle counter
	BITSET(R0,1);
	SYSCFG = R0;

	// Reinitialise data areas in RAM from ROM, if MemInits
	// been used.
	// CALL.X _mi_initialize;

L$no_cplbs:
	//  Enable interrupts
	STI R4;		// Using the mask from default handlers
	RAISE 15;

	// Move the processor into user mode.
	P0.L=L$still_interrupt_in_ipend;
	P0.H=L$still_interrupt_in_ipend;
	RETI=P0;

L$still_interrupt_in_ipend:
	rti;	// keep doing rti until weve finished servicing all
		// interrupts of priority higher than IVG15. Normally one
		// would expect to only have the reset interrupt in IPEND
		// being serviced, but occasionally when debugging this may
		// not be the case - if restart is hit when servicing an
		// interrupt.
		//
		// When we clear all bits from IPEND, well enter user mode,
		// then well automatically jump to supervisor_mode to start
		// servicing IVG15 (which we will service for the whole
		// program, so that the program is in supervisor mode.
		//
		// Need to do this to finish servicing the reset interupt.

L$supervisor_mode:
	[--SP] = RETI;	// re-enables the interrupt system

	R0.L = UNASSIGNED_VAL;
	R0.H = UNASSIGNED_VAL;
#if UNASSIGNED_FILL
	R2=R0;
	R3=R0;
	R4=R0;
	R5=R0;
	R6=R0;
	R7=R0;
	P0=R0;
	P1=R0;
	P2=R0;
	P3=R0;
	P4=R0;
	P5=R0;
#endif
	// Push a RETS and Old FP onto the stack, for sanity.
	[--SP]=R0;
	[--SP]=R0;
	// Make sure the FP is sensible.
	FP = SP;

	// And leave space for incoming "parameters"
	SP += -12;

#ifdef PROFCRT
	CALL.X monstartup; // initialise profiling routines
#endif  /* PROFCRT */

	CALL.X __init;

	R0.L = __fini;
	R0.H = __fini;
	CALL.X _atexit;

#if !defined(_ADI_THREADS)
#ifdef FIOCRT
	// FILE IO provides access to real command-line arguments.
	CALL.X __getargv;
	r1.l=__Argv;
	r1.h=__Argv;
#else
	// Default to having no arguments and a null list.
	R0=0;
	R1.L=L$argv;
	R1.H=L$argv;
#endif /* FIOCRT */
#endif /* _ADI_THREADS */
	CALL.X _main;

#if !defined(_ADI_THREADS)
	CALL.X _exit;	// passing in mains return value
#endif

	.size	__start, .-__start

	.align 2
	.type __unknown_exception_occurred, STT_FUNC;
__unknown_exception_occurred:
	// This function is invoked by the default exception
	// handler, if it does not recognise the kind of
	// exception that has occurred. In other words, the
	// default handler only handles some of the systems
	// exception types, and it does not expect any others
	// to occur. If your application is going to be using
	// other kinds of exceptions, you must replace the
	// default handler with your own, that handles all the
	// exceptions you will use.
	//
	// Since theres nothing we can do, we just loop here
	// at what we hope is a suitably informative label.
	IDLE;
	CSYNC;
	JUMP __unknown_exception_occurred;
	RTS;
	.size __unknown_exception_occurred, .-__unknown_exception_occurred

	.local	L$argv
	.comm	L$argv,4,4
