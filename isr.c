#include <xc.h>
#include "helper.h"
#include "clcd.h"

unsigned int count = 0;
unsigned int count_blink = 0;

extern unsigned char blink;
extern unsigned char sec;
extern unsigned char min;
extern unsigned char status;
extern unsigned char mode;
extern unsigned char operation;

void __interrupt() isr(void)
{
    
    if (TMR2IF == 1)
    {
        TMR2IF = 0;
        
        if(++count_blink == 10000)
        {
            count_blink = 0;
            blink = !blink;
        }
        
        
        if(mode == RUN_MODE || operation == OP_PRETEMP)
        {
        if(++count == 20000)
        {
            count = 0;
            
            if(sec>0)
                sec--;
            
            if(sec == 0)
            {
                if(min == 0)
                {
                    if(mode == RUN_MODE)
                    {
                        clear_screen();
                        BUZZER = 1;
                        clcd_print("TIME UP!!!",LINE1(4));
                        clcd_print("ENJOY YOUR MEAL!",LINE2(0));
                        __delay_ms(2000);
                        BUZZER = 0;
                    }
                    status = OP_COMPLETED;
                }
                else
                {
                    if(min>0)
                        min--;
                    
                    sec = 59;
                }
            }
        }
        }
    }
}