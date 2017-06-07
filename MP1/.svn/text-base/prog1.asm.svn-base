;									tab:8
;
; prog1.asm - starting code for ECE198KL Spring 2013 Program 1
;
; "Copyright (c) 2013 by Steven S. Lumetta.
;
; Permission to use, copy, modify, and distribute this software and its
; documentation for any purpose, without fee, and without written agreement is
; hereby granted, provided that the above copyright notice and the following
; two paragraphs appear in all copies of this software.
; 
; IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
; ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
; DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
; EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
; OF THE POSSIBILITY OF SUCH DAMAGE.
; 
; THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
; WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
; MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
; PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
; THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
; SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
;
; Author:	    Steve Lumetta
; Version:	    1.00
; Creation Date:    11 January 2013
; Filename:	    prog1.asm
; History:
;	SL	1.00	11 January 2013
;		Adapted from ECE190 example code.
;


;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming studio, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **
; you may want to try (in increasing order of difficulty)
;   - printing leading zeroes as spaces instead
;   - allowing the user to type the string to be processed using
;     the keyboard (either with GETC or directly using the KBSR
;     and the KBDR)
;   - wrapping the pieces up as subroutines (you may need to read
;     farther ahead to do this well)
;   - printing histogram results in decimal rather than in hexadecimal
;


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; I will go through each address of the histogram and print out the letter corresponding to the bin then 
; and turn each of the 4 sets of 4 bits at the address and convert its value to hex in ascii code and 
; print it in order to get a 4 digit hex code for each letter.

; R0: holds value of a set of 4 bits
; R1: keeps track
; R2: holds address of current bin
; R3: holds the character count of the current bin
; R4: counts the number of checked bits for each set of 4
; R5: counts the number of checked sets of 4 bits for current bin
; R6: temporary value holder
	
	LD R2,HIST_ADDR ; loads the start of histogram onto R2
	AND R1,R1,#0	; initialize the bin counter
Hist_Loop
	LD R0,Ascii_AT	; load @ onto R0
	ADD R0,R0,R1	; increment to correct bin letter
	out		; print bin letter
	LD R0,Ascii_spc ; load space onto R0
	out		; print space
	LDR R3,R2,#0	; load the bin value onto R3
	AND R5,R5,#0	; set R5 to 0
Digit_Loop
	AND R4,R4,#0	; set R4 to 0
	AND R0,R0,#0	; set R0 to 0
Bit_Loop
	ADD R0,R0,R0	; bit shift R0
	ADD R3,R3,#0	; set nzp
	BRzp MSB_CLEAR	; if the MSB of R3 is 0 then skip next step
	ADD R0,R0,#1	; put a 1 in R0's LSB
MSB_CLEAR
	ADD R3,R3,R3	; bit shift R3
	ADD R4,R4,#1	; increment bit counter
	ADD R6,R4,#-4	; check to see if 4 bits have been checked
	BRn Bit_Loop	; if 4 bits have not been checked than repeat bit checking
	ADD R6,R0,#-10	; check to see if the hex value of the set of 4 bits is a letter or number
	BRzp Letter	; if hex value is a letter than go to letter section
	LD R6,Ascii_0	; load ascii value for 0 onto R6
	BRnzp Print	; go to print section
Letter
	LD R6,Ascii_A	; load ascii value for A onto R6
Print
	ADD R0,R0,R6	; add R6 to R0
	OUT		; print the hex value of set of 4 bits
	ADD R5,R5,#1	; increment R5
	ADD R6,R5,#-4	; check to see if 4 sets of 4 bits have been printed
	BRn Digit_Loop	; if 4 sets have not been printed loop back to print more
	ADD R2,R2,#1	; increment histogram address
	ADD R1,R1,#1	; increment bin counter
	LD R0,Ascii_nl  ; load next line onto R0
	out		; print next line
	LD R6,NEG_27	; load R6 with -27
	ADD R6,R6,R1	; check the loop count
	BRn Hist_Loop	; loop back if the loop count is less than 27



DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_27		.FILL #-27	; -27
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
Ascii_0		.FILL x0030	; Ascii hex value for 0
Ascii_A		.FILL x0037	; Ascii hex value for A
Ascii_AT	.FILL x0040	; Ascii hex value for @
Ascii_spc	.FILL x0020	; Ascii hex value for space
Ascii_nl	.FILL x000A	; Ascii hex value for next line
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
