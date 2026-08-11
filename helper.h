#ifndef HELPER_C
#define HELPER_C

#define STARTUP_SCREEN      0x50
#define MENU_SCREEN         0x51

#define NO_INPUT            0x90

#define OP_COMPLETED        0x91
#define OP_IN_PROGRESS      0x92
#define OP_SET_PRETEMP      0x93
#define OP_PRETEMP          0x94

#define RETURN_SUCCESS      0x00
#define RETURN_FAILURE      0x01
#define RETURN_IN_PROGRESS  0x02

#define RESET_MICRO         0x80
#define RESET_NOTHING       0x81
#define RESET_SET_TIME      0x82
#define RESET_RUN_MODE      0x83
#define RESET_GRILL         0x84
#define RESET_CONVECTION    0x85
#define RESET_PRETEMP       0x86
#define RESET_START         0x87

#define SW1                 0x10
#define SW2                 0x11
#define SW3                 0x12

#define SW4                 0x13
#define SW5                 0x14
#define SW6                 0x17

#define SW7                 0x18
#define SW8                 0x19
#define SW9                 0xA0

#define SW_STAR             0xA3
#define SW0                 0xA2
#define SW_HASH             0xA1


#define MICRO_MODE          0x30
#define GRILL_MODE          0x31
#define CONVECTION_MODE     0x32
#define START               0x33
#define RUN_MODE            0x34

#define FAN_DDR             TRISC2
#define FAN                 RC2

#define BUZZER_DDR          TRISC1
#define BUZZER              RC1


void startup_screen();
void run_mode(unsigned char key);
unsigned char set_time(unsigned char key);
unsigned char menu_screen(unsigned char key);
void micro_mode(unsigned char key);
void grill_mode(unsigned char key);
void convection_mode(unsigned char key);
void start(unsigned char key);


#endif