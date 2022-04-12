#include <stdio.h>
#include <string.h>
#include "daisy_seed.h"
#include "dev/oled_ssd130x.h"

using namespace daisy;

/** Typedef the OledDisplay to make syntax cleaner below 
 *  This is a 4Wire SPI Transport controlling an 128x64 sized SSDD1306
 * 
 *  There are several other premade test 
*/
using Display1306 = OledDisplay<SSD130x4WireSpi128x64Driver>;

DaisySeed     hw;
Display1306 display;

int main(void)
{
    uint8_t message_idx;
    hw.Configure();
    hw.Init();

    /** Configure the Display */
    //dp 9 d0
    //dp 10 cs
    //dp 11 d1
    Display1306::Config disp_cfg;
    disp_cfg.driver_config.transport_config.pin_config.dc    = hw.GetPin(9); //daisy pin 8
    disp_cfg.driver_config.transport_config.pin_config.reset = hw.GetPin(30); //daisy pin 37
    /** And Initialize */
    display.Init(disp_cfg);

    message_idx = 0;
    char strbuff[128];
    while(1)
    {
        System::Delay(500);
        switch(message_idx)
        {
            case 0: sprintf(strbuff, "Testing. . ."); break;
            case 1: sprintf(strbuff, "Daisy. . ."); break;
            case 2: sprintf(strbuff, "1. . ."); break;
            case 3: sprintf(strbuff, "2. . ."); break;
            case 4: sprintf(strbuff, "3. . ."); break;
            default: break;
        }
        message_idx = (message_idx + 1) % 5;                                // repeat modulo 5
        display.Fill(true);                                                 // white bg
        display.SetCursor(0, 0);                                            // upper left
        display.WriteString(strbuff, Font_11x18, false);                    // Font_6x8, black (inverted)
        display.Update();
    }
}
