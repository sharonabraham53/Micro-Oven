/* 
 * File:   matrix_keypad.h
 */

#ifndef MATRIX_KEYPAD_H
#define	MATRIX_KEYPAD_H

#define MATRIX_KEYPAD_COLUMN_PORT_DDR           TRISB
#define MATRIX_KEYPAD_ROW_PORT_DDR              TRISD

#define ROW1                                    RD3
#define ROW2                                    RD2
#define ROW3                                    RD1
#define ROW4                                    RD0

#define COL1                                    RB0
#define COL2                                    RB1
#define COL3                                    RB2

#define SW1         0x10
#define SW2         0x11
#define SW3         0x12

#define SW4         0x13
#define SW5         0x14
#define SW6         0x17

#define SW7         0x18
#define SW8         0x19
#define SW9         0xA0

#define SW_STAR      0xA3
#define SW0          0xA2
#define SW_HASH      0xA1

#define HI                                      1
#define LOW                                     0

#define STATE                                   1
#define LEVEL                                   0

#define ALL_RELEASED                            0xFF

unsigned char read_matrix_keypad(unsigned char mode);
void init_matrix_keypad(void);

#endif	/* MATRIX_KEYPAD_H */

