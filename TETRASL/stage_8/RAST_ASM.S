
	
	xdef _get_video_base
	xdef _set_video_base



video_base_address	equ	$FFFF8201
GEMDOS				equ 1


;----- SUBROUTINE: UINT32 *get_video_base(); ------
; PURPOSE: Returns the address stored at the video base register
; AUTHOR: Depanshu Suyal
; REFERENCE: D. Suyal, "get_video_base function," [Online].
; Available: [https://github.com/Kevinmru737/COMP-2659-Project/blob/main/stage-8/RAST_ASM.S].
; [Accessed: Dec. 2024].

_get_video_base:
	link 	a6,#0
	movem.l d3/a0,-(sp)

	bsr 	_enter_super

	clr.l 	d3
	move.l	#video_base_address,a0
	movep.w	(a0),d3
	lsl.l	#8,d3

	bsr 	_exit_super

	movem.l	(sp)+,d3/d0
	unlk	a6
	rts
	


;----- SUBROUTINE: void set_video_base(UINT32 *); ------
; PURPOSE: Sets the address stored at the video base register to the input address
; AUTHOR: Depanshu Suyal
; REFERENCE: D. Suyal, "get_video_base function," [Online].
; Available: [https://github.com/Kevinmru737/COMP-2659-Project/blob/main/stage-8/RAST_ASM.S].
; [Accessed: Dec. 2024].

NEW_VIDEO_BASE_OFFSET 	equ     	8

_set_video_base:
		link	a6,#0
		movem.l	d0/a0,-(sp)

		bsr		_enter_super

		clr.l 	d0
		move.l	NEW_VIDEO_BASE_OFFSET(a6),d0
		lsr.l   #8,d0
		move.l 	#video_base_address,a0
		movep.w d0,(a0)
		
		bsr		_exit_super
		
		movem.l	(sp)+,d0/a0
		unlk	a6
		rts


;----- SUBROUTINE: void enter_super(); -----
; PURPOSE: Enter supervisor mode
; AUTHOR: Depanshu Suyal
; REFERENCE: D. Suyal, "enter_super function," [Online].
; Available: [https://github.com/Kevinmru737/COMP-2659-Project/blob/main/stage-8/RAST_ASM.S].
; [Accessed: Dec. 2024].

_enter_super:

	movem.l	d0,-(sp)

	clr.l	-(sp)
	move.w	#320,-(sp)
	trap	#GEMDOS
	addq.l	#6,sp
	movem.l	(sp)+,d0

	rts


;----- SUBROUTINE: void exit_super(); -----
; PURPOSE: Exit supervisor mode
; AUTHOR: Depanshu Suyal
; REFERENCE: D. Suyal, "exit_super function," [Online].
; Available: [https://github.com/Kevinmru737/COMP-2659-Project/blob/main/stage-8/RAST_ASM.S].
; [Accessed: Dec. 2024].


_exit_super:
	movem.l	d0,-(sp)

	move.l	old_ssp(pc),-(sp)
	move.w	#$20,-(sp)
	trap 	#GEMDOS
	addq.l	#6,sp

	movem.l	(sp)+,d0
	rts

old_ssp		ds.l	1
