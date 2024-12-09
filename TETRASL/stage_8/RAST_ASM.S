
	
	xdef _get_video_base
	xdef _set_video_base



video_base_address	equ	$FFFF8201
GEMDOS				equ 1


;----- SUBROUTINE: UINT32 *get_video_base(); ------
; PURPOSE: Returns the address stored at the video base register
; DETAILS: 
;		- This function transitions the CPU into supervisor mode to safely access the hardware register.
;		- It reads the 24-bit video base address stored at $FFFF8201 into a 32-bit value,
;			performing a left shift to align the address properly.
;		- The function then exits supervisor mode and returns the address.
; RETURN:
;		- UINT32 (D0): The 24-bit base address of the video memory, zero-extended to 32 bits.

_get_video_base:
		link	a6,#0
		movem.l	d3/a0,-(sp)

		bsr _enter_super

		clr.l 	d3
		move.l  #video_base_address,a0
		movep.w (a0),d3
		lsl.l   #8,d3

		bsr _exit_super
		
		move.l d3,d0
		
		movem.l	(sp)+,d3/a0
		unlk	a6
		rts
	


;----- SUBROUTINE: void set_video_base(UINT32 *); ------
; PURPOSE: Sets the video base register to a new address provided as input.
; DETAILS: 
;		- The function takes a 32-bit address, converts it to a 24-bit format by shifting it 8 bits to the right, 
;			and stores it in the video base register at $FFFF8201.
;		- Supervisor mode is entered for safe register access and exited after the update.
; PARAMETERS:
;		- UINT32 * (D0): Pointer to the new 24-bit video base address (zero-extended to 32 bits)
;			that will replace the current address in the register.

NEW_VIDEO_BASE_OFFSET 	equ     	8

_set_video_base:
		link	a6,#0
		movem.l	d0/a0,-(sp)

		bsr		_enter_super

		clr.l 	d0
		move.l	NEW_VIDEO_BASE_OFFSET(a6),d0
		lsr.l   #8,d0
		move.l  #video_base_address,a0
		movep.w d0,(a0)
		
		bsr		_exit_super
		
		movem.l	(sp)+,d0/a0
		unlk	a6
		rts


;----- SUBROUTINE: void enter_super(); -----
; PURPOSE: Enter supervisor mode
; P. Pospisil, "enter_super function," lab material, COMP2659 Computing Machinery II , Mount Royal University, Nov. 2024.
; AUTHOR: Paul Pospisil

_enter_super:
		movem.l	d0,-(sp)

		clr.l	-(sp)		; enter supervisor mode with user stack
		move.w	#$20,-(sp)
		trap	#GEMDOS
		addq.l	#6,sp
		move.l	d0,old_ssp	; save old system stack pointer
		
		movem.l	(sp)+,d0
		rts


;----- SUBROUTINE: void exit_super(); -----
; PURPOSE: Exit supervisor mode
; P. Pospisil, "exit_super function," lab material, COMP2659 Computing Machinery II , Mount Royal University, Nov. 2024.
; AUTHOR: Paul Pospisil



_exit_super:
		movem.l	d0,-(sp)

		move.l	old_ssp(pc),-(sp)	; return to user mode, restoring
		move.w	#$20,-(sp)			; system stack pointer
		trap	#GEMDOS
		addq.l	#6,sp
		
		movem.l	(sp)+,d0
		rts

old_ssp		ds.l	1
