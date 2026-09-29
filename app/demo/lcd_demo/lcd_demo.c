#include "mbtk_gpio.h"
#include "mbtk_api.h"
#include "mbtk_comm_api.h"

#define   BLACK     0x0000       //   oи▓иж?    
#define   NAVY      0x000F      //    иж?ид?иж?  
#define   DGREEN    0x03E0        //  иж??имиж?  
#define   DCYAN     0x03EF       //   иж??идиж?  
#define   MAROON    0x7800       //   иж?oимиж?      
#define   PURPLE    0x780F       //   б┴?иж?  
#define   OLIVE     0x7BE0       //   иж?иж-?им      
#define   LGRAY     0xC618        //  ?и░буб┴иж?
#define   DGRAY     0x7BEF        //  иж??и░иж?      
#define   BLUE      0x001F        //  ид?иж?    
#define   GREEN     0x07E0        //  ?имиж?          
#define   CYAN      0x07FF        //  ?идиж?  
#define   RED       0xF800        //  oимиж?       
#define   MAGENTA   0xF81F        //  ?бдoим    
#define   YELLOW    0xFFE0        //  ??иж?        
#define   WHITE     0xFFFF        //  буб┴иж?  

//static mbtk_lcd_color_struct test_color[240*240] = {};//[240*240];
#define MAX_WIDTH_HEIGHT 128
#define MAX_WIDTH_WIDTH 128

static  mbtk_lcd_color_struct *test_color = NULL;


void lcd_color_set(u16 color,u16 width, u16 height)
{
    int i = 0;
    int full_screen_pixels = width*height;
    
    if(test_color == NULL)
    {
        return;
    }
    
    for(i = 0; i < full_screen_pixels; i++)
    {
        test_color[i].full = color;
    }

}

static void ShowColorBarRGB565(UINT16* lcdbuffer, unsigned short width, unsigned short height)
{
	int i, j;

	UINT16 const red    = (0x1F << 11) | (0x00 << 5) | 0x00;
	UINT16 const green  = (0x00 << 11) | (0x3F << 5) | 0x00;
	UINT16 const blue   = (0x00 << 11) | (0x00 << 5) | 0x1F;
	UINT16 const black  = (0x00 << 11) | (0x00 << 5) | 0x00;
	UINT16 const white  = (0x1F << 11) | (0x3F << 5) | 0x1F;

	UINT16 color_bar[] = {
		red, green, blue, black, white,
	};

	UINT32 color_number = sizeof(color_bar) / sizeof(color_bar[0]);


	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			*(lcdbuffer + i + j * width) = color_bar[i * color_number / width];
		}
	}

	//mci_LcdBlockWrite_sync(
		//lcdbuffer, 0, 0, width - 1, height - 1);
	ol_lcd_clean_screen_ex(0, 0,width-1,height-1, lcdbuffer);

	ol_os_task_sleep(600);

	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			*(lcdbuffer + i + j * width) = color_bar[j * color_number / height];
		}
	}

	//mci_LcdBlockWrite_sync(
	//	lcdbuffer, 0, 0, width - 1, height - 1);	
	ol_lcd_clean_screen_ex(0, 0,width-1,height-1, lcdbuffer);
	
	ol_os_task_sleep(600);
}

int lcd_demo_2(void)
{
    u16 width, height;
    u16 pixel_color = 0;
    u8 i=0;
    u32 test_color_size = 0;
    op_uart_printf("ol_lcd_power_switch : %d \n", ol_lcd_power_switch(mbtk_lcd_pmic_power_on));
    ol_lcd_get_dimension(&width, &height);

    if(width >MAX_WIDTH_WIDTH || height > MAX_WIDTH_HEIGHT)
    {
        op_uart_printf("lcd_demo error: width OR height lcd[%d X %d] \n", width,height);
        return -1;       
    }
    test_color_size = sizeof(mbtk_lcd_color_struct)*width*height;
    test_color = malloc(test_color_size);
    
    if(test_color ==NULL)
    {
        op_uart_printf("lcd_demo error: not enough heap to malloc for testing lcd[%d X %d] \n", width,height);
        return -2;
    }

    op_uart_printf("ol_lcd_get_dimension : %d,%d \n", width, height);
    
    
    memset(test_color,0,test_color_size);
    
    ol_lcd_wakeup();
    
    lcd_color_set(BLACK,width, height);
    
    ol_lcd_flush(test_color);
    
    ol_lcd_set_backlight_level(5);
    
    for(i=0;i<3;i++)
    {
       switch(i)
        {
        case 0:
           pixel_color = RED;
           break;
        case 1:
           pixel_color = GREEN;
           break;
        
        case 2:
           pixel_color = BLUE;
           break;           
        }
       
       lcd_color_set(pixel_color,width, height);
       
       ol_lcd_flush(test_color);
       
       ol_os_task_sleep(200);
       
    }
	width=128;
	height=128;
	ShowColorBarRGB565((UINT16*)test_color, width, height);
	ol_os_task_sleep(600);
	ShowColorBarRGB565((UINT16*)test_color, width, height);
	ol_os_task_sleep(600);
    ol_lcd_set_backlight_level(0);
    ol_lcd_sleep();
    ol_lcd_power_switch(mbtk_lcd_pmic_power_off);
    
    free(test_color);
    test_color =NULL;

    return 0;
}

	void app2_open_task(void *argv)
	{lcd_demo_2();}
int lcd_demo(void)
{mbtk_taskref mbtk_test_task_ref;
	ol_os_task_creat(&mbtk_test_task_ref,NULL, 10*1024, 220, "app2_at_task", app2_open_task, NULL);
}