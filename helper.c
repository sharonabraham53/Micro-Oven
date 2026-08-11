#include <xc.h>
#include "clcd.h"
#include "helper.h"
#include "timers.h"
#include "matrix_keypad.h"

unsigned char sec;
unsigned char min;
unsigned char status = OP_IN_PROGRESS;
unsigned char mode = MENU_SCREEN;
unsigned char blink = 0;
unsigned char operation;

extern unsigned char screen_flag;
extern unsigned char disp;
extern unsigned char reset_flag;
extern unsigned int count;
extern unsigned int count_blink;


void startup_screen()
{
    //initialize variable
    static unsigned char i = 0;
    
    //logic to display startup message and pattern
    if(i < 16)
    {
        clcd_putch(0xff,LINE1(i));
        __delay_ms(150);
        i++;
    }
    else if(i == 16)
    {
        clcd_print("Powering on",LINE2(3));
        clcd_print("Microwave oven",LINE3(1));
        i++;
    }
    else if(i<=32)
    {
        clcd_putch(0xff,LINE4(i-17));
        __delay_ms(150);
        i++;
    }else
    {
        __delay_ms(500);
        screen_flag = MENU_SCREEN;
        i = 0;
    }
    
}

unsigned char menu_screen(unsigned char key)
{
    //display available menu options
    if(disp == 0)
    {
        clear_screen();

        clcd_print("1.Micro",LINE1(0));
        clcd_print("2.Grill",LINE2(0));
        clcd_print("3.Convection",LINE3(0));
        clcd_print("4.Start",LINE4(0));
        
        disp++;
    }
        
    //return user choice
    if(key == SW1)
    {
        return MICRO_MODE;
    }
    else if(key == SW2)
    {
        return GRILL_MODE;
    }
    else if(key == SW3)
    {
        return CONVECTION_MODE;
    }
    else if(key == SW4)
    {
        return START;
    }
    
}

unsigned char set_time(unsigned char key)
{
    //initialize variables
    unsigned char value = NO_INPUT;
    static unsigned char key_press = 0;
    
    if(reset_flag == RESET_SET_TIME)
    {
        //clear screen
        clear_screen();
        
        //display string
        clcd_print("SET TIME <MM:SS>",LINE1(0));
        clcd_print("TIME:",LINE2(0));
        clcd_print("*:CLEAR  #:ENTER",LINE4(0));
        
        //clear min and sec
        min = 0;
        sec = 0;
        
        //clear reset flag
        reset_flag = RESET_NOTHING;
        
        //turn on timer
        TMR2ON = 1;
    }
    
    
    //read user input
    if(key == SW1)
    {
        key_press++;
        value = 1;
    }
    else if(key == SW2)
    {
        key_press++;
        value = 2;
    }
    else if(key == SW3)
    {
        key_press++;
        value = 3;
    }
    else if(key == SW4)
    {
        key_press++;
        value = 4;
    }
    else if(key == SW5)
    {
        key_press++;
        value = 5;
    }
    else if(key == SW6)
    {
        key_press++;
        value = 6;
    }
    else if(key == SW7)
    {
        key_press++;
        value = 7;
    }
    else if(key == SW8)
    {
        key_press++;
        value = 8;
    }
    else if(key == SW9)
    {
        key_press++;
        value = 9;
    }
    else if(key == SW_STAR)
    {
        value = NO_INPUT;
        
        if(key_press <= 2)
        {
            //clear sec
            sec = 0;
            key_press = 0;
        }
        else if(key_press <= 4)
        {
            //clear min
            min = 0;
            key_press = 2;
        }
//        else 
//        {
//            TMR2ON = 0;
//        }
        
    }
    else if(key == SW0)
    {
        key_press++;
        value = 0;
    }
    //stop reading time from user and return
    else if(key == SW_HASH)
    {
        //reset key_press
        key_press = 0;
        //reset count blink
        count_blink = 0;
        //turn off timer
        TMR2ON = 0;
        //return successs
        return RETURN_SUCCESS;
    }
    
    if(value != NO_INPUT)
    {
    if(key_press <= 2)
    {
        //set sec based on user input
        sec = (sec * 10) + value; 
        if(sec>59)
            sec = 59;
    }
    else if(key_press <= 4)
    {
        //set min based on user input
        min = (min * 10) + value;
        if(min>59)
            min = 59;
    }
    
    //reset value
    value = NO_INPUT;
    }
    
    //display min and sec along with blink
    if(key_press<2)
    {
    
        clcd_putch((min/10)+'0',LINE2(5));
        clcd_putch((min%10)+'0',LINE2(6));
        clcd_putch(':',LINE2(7));
        if(blink == 0)
        {
            clcd_putch(((sec/10)+'0'),LINE2(8));
            clcd_putch((sec%10)+'0',LINE2(9));
        }else
        {
            clcd_print("  ",LINE2(8));
        }
    }
    else if(key_press < 4)
    {
        clcd_putch(':',LINE2(7));
        clcd_putch(((sec/10)+'0'),LINE2(8));
        clcd_putch((sec%10)+'0',LINE2(9));
        
        if(blink == 0)
        {
           clcd_putch((min/10)+'0',LINE2(5));
           clcd_putch((min%10)+'0',LINE2(6)); 
        }else
        {
           clcd_print("  ",LINE2(5));
        }
    }
    else
    {
        clcd_putch((min/10)+'0',LINE2(5));
        clcd_putch((min%10)+'0',LINE2(6));
        clcd_putch(':',LINE2(7));
        clcd_putch(((sec/10)+'0'),LINE2(8));
        clcd_putch((sec%10)+'0',LINE2(9));
        
        
    }
    
    //return inprogress
    return RETURN_IN_PROGRESS;
}


void micro_mode(unsigned char key)
{
    //reset
    if(reset_flag == RESET_MICRO)
    {
        reset_flag = RESET_SET_TIME;
        //display power
        clear_screen();
        clcd_print("Power = 900W",LINE2(2));
        __delay_ms(800);
    }
    
    
    if(mode == RUN_MODE)
    {
        //run operation
        run_mode(key);
    }
    //set time
    else if(set_time(key) == RETURN_SUCCESS)
    {
        //after setting time set reset flag as reset run mode and mode as run
        mode = RUN_MODE;
        reset_flag = RESET_RUN_MODE;
        
    }
}
void grill_mode(unsigned char key)
{
    //reset
    if(reset_flag == RESET_GRILL)
    {
        reset_flag = RESET_SET_TIME;
    }
    
    
    //set time
    if(mode == RUN_MODE)
    {
        //run operation
        run_mode(key);
    }
    //set time
    else if(set_time(key) == RETURN_SUCCESS)
    {
        //after setting time set reset flag as reset run mode and mode as run
        mode = RUN_MODE;
        reset_flag = RESET_RUN_MODE;
        
    }
}


void convection_mode(unsigned char key)
{
    //declare variables
    static unsigned char key_press,value;
    static unsigned int temp;
    
    if(reset_flag == RESET_CONVECTION)
    {
        //reset value
        value = NO_INPUT;
        
        //reset temperature
        temp = 0;
        //reset key press
        key_press = 0;
        //set operation as set pre temp
        operation = OP_SET_PRETEMP;
        
        //change reset flag as reset pretemp
        reset_flag = RESET_PRETEMP;

        //turn on timer
        TMR2ON = 1;
        
        //clear screen
        clear_screen();
        //display output string
        clcd_print("SET Temp <*C>",LINE1(0));
        clcd_print("TEMP = ",LINE2(0));
        clcd_print("*:CLEAR  #:ENTER",LINE4(0));
    }
    
    
    if(operation == OP_SET_PRETEMP)
    {
        
        //read user input
        if(key == SW1)
        {
            key_press++;
            value = 1;
        }
        else if(key == SW2)
        {
            key_press++;
            value = 2;
        }
        else if(key == SW3)
        {
            key_press++;
            value = 3;
        }
        else if(key == SW4)
        {
            key_press++;
            value = 4;
        }
        else if(key == SW5)
        {
            key_press++;
            value = 5;
        }
        else if(key == SW6)
        {
            key_press++;
            value = 6;
        }
        else if(key == SW7)
        {
            key_press++;
            value = 7;
        }
        else if(key == SW8)
        {
            key_press++;
            value = 8;
        }
        else if(key == SW9)
        {
            key_press++;
            value = 9;
        }
        else if(key == SW_STAR)
        {
            //clear value
            value = NO_INPUT;
            //clear temperature
            temp = 0;
            //clear key press
            key_press = 0;
        }
        else if(key == SW0)
        {
            key_press++;
            value = 0;
        }
        else if(key == SW_HASH)
        {
            //clear key press
            key_press = 0;
            //turn timer off
            TMR2ON = 0;
            //clear count
            count_blink = 0;
            //clear blink
            blink = 0;
            //change operation to pretemp
            operation = OP_PRETEMP;
        }
        
        if(value != NO_INPUT)
        {
            //set temperature based on user input
            if(key_press < 4)
            {
                temp = (temp*10) + value;
                if(temp>180)
                    temp = 180;
                value = NO_INPUT;
            }
        }
        
        
        //display temp with blink
        if(blink == 0)
        {
            clcd_putch((temp/100)+'0',LINE2(7));
            clcd_putch(((temp/10)%10)+'0',LINE2(8));
            clcd_putch((temp%10)+'0',LINE2(9));
        }
        else
        {
            clcd_print("   ",LINE2(7));
        }
    }
    else if(operation == OP_PRETEMP)
    {
        if(reset_flag == RESET_PRETEMP)
        {
            //change reset flag
            reset_flag = RESET_NOTHING;
            //clear screen
            clear_screen();
            //clear count
            count = 0;
            //turn timer on
            TMR2ON = 1;
            //set sec as 60
            sec = 60;
            
            //clear screen
            clear_screen();
            //display output screen
            clcd_print("Pre_heating",LINE1(3));
            clcd_print("Time left:    s",LINE2(0));
        }
        
        clcd_putch((sec/10)+'0',LINE2(11));
        clcd_putch((sec%10)+'0',LINE2(12));
        
        
    if(status == OP_COMPLETED)
    {
        //tunr timer off
        TMR2ON = 0;
        //clear count
        count = 0;
        //set status as operation in progress
        status = OP_IN_PROGRESS;
        //set operation as convection mode
        operation = CONVECTION_MODE;
        //change reset flag as reset set time
        reset_flag = RESET_SET_TIME;
    }
        
        
    }
    else if(operation == CONVECTION_MODE)
    {
        //set time
        if(mode == RUN_MODE)
        {
            //run operation
            run_mode(key);
        }
        //set time
        else if(set_time(key) == RETURN_SUCCESS)
        {
            //after setting time set reset flag as reset run mode and mode as run
            mode = RUN_MODE;
            reset_flag = RESET_RUN_MODE;

        }
    }
    
    
}


void start(unsigned char key)
{
    if(reset_flag == RESET_START)
    {
        //set sec as 30 
        sec = 30;
        //change reset flag
        reset_flag = RESET_RUN_MODE;
        //change mode
        mode = RUN_MODE;
    }
    
    //run operation
    run_mode(key);
}

void run_mode(unsigned char key)
{
    if(reset_flag == RESET_RUN_MODE)
    {
        //clear screen
        clear_screen();
        
        //display output string
        clcd_print("TIME =  ",LINE1(1));
        clcd_print("4.START/RESUME",LINE2(2));
        clcd_print("5.PAUSE",LINE3(2));
        clcd_print("6.STOP",LINE4(2));

        //set mode as run mode
        mode = RUN_MODE;
        //clear count
        count = 0;
        
        //turn timer on
        TMR2ON = 1;
        
        //turn fan on
        FAN = 1;
        
        //change reset flag as reset nothing
        reset_flag = RESET_NOTHING;
        
    }

    //add 30 sec 
    if(key == SW4)
    {
        if(TMR2ON == 1)
        {
        if(sec < 30)
        {
            sec = sec + 30;
        }else 
        {
            min++;
            sec = sec - 30;
        }
        }else
        {
            FAN = 1;
            TMR2ON = 1;
        }
    }
    
    //pause
    else if(key == SW5)
    {
        TMR2ON = 0;
        FAN = 0;
    }
    
    //stop
    else if(key == SW6)
    {
        status = OP_COMPLETED;
    }

    
    //display min(s) and sec(s)
    clcd_putch((min/10)+'0',LINE1(9));
    clcd_putch((min%10)+'0',LINE1(10));
    clcd_putch(':',LINE1(11));
    clcd_putch(((sec/10)+'0'),LINE1(12));
    clcd_putch((sec%10)+'0',LINE1(13));
    
    if(status == OP_COMPLETED)
    {
        //turn timer off
        TMR2ON = 0;
        //turn fan off
        FAN = 0;
        //clear count
        count = 0;
        //change status
        status = OP_IN_PROGRESS;
        //change screen flag as menu screen
        screen_flag = MENU_SCREEN;
        //change mode
        mode = screen_flag;
    }
}