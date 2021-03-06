#include <platform.h>
#include <N6100LCD.h>

/* http://philrobotics.com/forum/index.php/topic,90.0.html */

// N6100LCD(DAT_PIN, CLK_PIN, CS_PIN, RST_PIN)
N6100LCD mylcd(PA0, PA2, PA3, PA1);

int main(void)
{
	Serial.begin(115200);
	
	mylcd.init();
	mylcd.setArea(0,131,0,131);
    
	while(true)
	{
		mylcd.send(1, Serial.getc() );
	}
}
