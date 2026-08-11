/*
 * File:   main.c
 * Author: sharo
 *
 * Created on 9 July, 2026, 8:37 PM
 */


#include <xc.h>
#include "clcd.h"
#include "helper.h"
#include "matrix_keypad.h"
#include "timers.h"

#pragma config WDTE = OFF

unsigned char screen_flag = STARTUP_SCREEN;
unsigned char reset_flag;
unsigned char disp = 0;

void init_config() {
    //init clcd
    init_clcd();
    //init timer
    init_timer2();
    //init mkp
    init_matrix_keypad();
    
    //enable interrupt
    PEIE = 1;
    GIE = 1;
    
    //set TRISC1 and TRISC2 as output
    FAN_DDR = 0;
    BUZZER_DDR = 0;
    
}

void main(void) {

    init_config();
    
    //declare variables
    unsigned char key;
    unsigned char option;
    
    //initialize variable
    unsigned char prev_flag = STARTUP_SCREEN;

    while (1) 
    {
        //read input
        key = read_matrix_keypad(STATE);
        
        switch(screen_flag)
        {
            case STARTUP_SCREEN:
                        //display startup screen
                        startup_screen();
                        break;
            
            case MENU_SCREEN:
                        //display menu and read user's choice
                        option = menu_screen(key);
                        
                        //run mode based on user's choice
                        switch(option)
                        {
                            case MICRO_MODE:
                                        reset_flag = RESET_MICRO;
                                        screen_flag = MICRO_MODE;
                                        break;
                            case GRILL_MODE:
                                        reset_flag = RESET_GRILL;
                                        screen_flag = GRILL_MODE;
                                        break;
                            case CONVECTION_MODE:
                                        reset_flag = RESET_CONVECTION;
                                        screen_flag = CONVECTION_MODE;
                                        break;
                            case START:
                                        reset_flag = RESET_START;
                                        screen_flag = START;
                                        break;
                        }
                        break;
                        
            case MICRO_MODE:
                        //micro mode
                        micro_mode(key);
                        break;
                        
            case GRILL_MODE:
                        //grill mode
                        grill_mode(key);
                        break;
                        
            case CONVECTION_MODE:
                        //convection mode
                        convection_mode(key);
                        break;
                        
            case START:
                        //start
                        start(key);
                        break;
        }
        
        if(screen_flag != prev_flag)
        {
            disp = 0;
            prev_flag = screen_flag;
        }
        
    }

    return;
}
