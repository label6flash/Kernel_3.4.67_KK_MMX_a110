#include <linux/string.h>

#include "lcm_drv.h"

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  										(720)
#define FRAME_HEIGHT 										(1280)

#define REGFLAG_DELAY             							0xFE
#define REGFLAG_END_OF_TABLE      							0xFF   // END OF REGISTERS MARKER

#define LCM_DSI_CMD_MODE									1

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)									lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)				lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg											lcm_util.dsi_read_reg()
       

static struct LCM_setting_table {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};


static struct LCM_setting_table lcm_initialization_setting[] = {
	
	/*
	Note :

	Data ID will depends on the following rule.
	
		count of parameters > 1	=> Data ID = 0x39
		count of parameters = 1	=> Data ID = 0x15
		count of parameters = 0	=> Data ID = 0x05

	Structure Format :

	{DCS command, count of parameters, {parameter list}}
	{REGFLAG_DELAY, milliseconds of time, {}},

	...

	Setting ending by predefined flag
	
	{REGFLAG_END_OF_TABLE, 0x00, {}}
	*/

	
	{0x11,	0,	{}},     //sleep out
	{REGFLAG_DELAY, 150, {}},

	{0xB9,	3,	{0xFF,0x83,0x92}},
	{REGFLAG_DELAY, 10, {}},

  {0x35,	1,	{0x00}},    // set TE on
  {REGFLAG_DELAY, 10, {}},
  
  {0x51,	1,	{0xF0}},    // set CABC bl
  {REGFLAG_DELAY, 10, {}},
    
  {0x53,	1,	{0x24}},    // set cabc on
  {REGFLAG_DELAY, 10, {}},
  
  {0x55,	1,	{0x02}},    // set cabc on
  {REGFLAG_DELAY, 10, {}},
  
  {0xBF,	4,	{0x05,0x60,0x82,0x00}},    //
  {REGFLAG_DELAY, 10, {}},
    
        
	{0xB1,	13,	{0x7C, 0x00, 0x44, 0x94,
				 0x00, 0x0E, 0x0E, 0x20,
				 0x28, 0x3F, 0x3F, 0x42,
				 0x72}},
	{REGFLAG_DELAY, 10, {}},

	{0xB2, 	12,	{0x0F,0xC8,0x05,0x0F,
		           0x08,0x84,0x00,0xFF,
		           0x05,0x0F,0x04,0x20}},
	{REGFLAG_DELAY, 10, {}},
	

	{0xB4,	23, {0x00, 0x00, 0x05, 0x00,
				 0xA0, 0x05, 0x16, 0x9D,
				 0x30, 0x03, 0x16, 0x00,
				 0x03, 0x03, 0x00, 0x1B,
				 0x06, 0x07, 0x07, 0x00,
				 0x00, 0x1A, 0x84}},
	{REGFLAG_DELAY, 10, {}},

	{0xBA,	2,	{0x10, 0x83}},   //set mipi 2 lane
	{REGFLAG_DELAY, 10, {}},

	{0xC2, 	1,	{0x08}},
	{REGFLAG_DELAY, 10, {}},

	{0xC7, 	2,	{0x00,0x40}},
	{REGFLAG_DELAY, 10, {}},
	
	{0xCC, 	1,	{0x08}},
	{REGFLAG_DELAY, 10, {}},	
		
	{0xD4, 	1,	{0x0C}},
	{REGFLAG_DELAY, 10, {}},
			
	{0xD5, 	21,	{0x00,0x08,0x08,0x00,
		           0x44,0x55,0x66,0x77,
		           0xCC,0xCC,0xCC,0xCC,
		           0x00,0x77,0x66,0x55,
		           0x44,0xCC,0xCC,0xCC,
		           0xCC}},
	{REGFLAG_DELAY, 10, {}},
	
	{0xD8, 	23,	{0x00,0x00,0x04,0x00,
		           0xA0,0x04,0x16,0x9D,
		           0x30,0x03,0x16,0x00,
		           0x03,0x03,0x00,0x1B,
		           0x06,0x07,0x07,0x00,
		           0x00,0x1A,0x84}},
	{REGFLAG_DELAY, 10, {}},	
				
	{0xE0, 	34,	{0x33,0x32,0x34,0x38,
		           0x3C,0x3C,0x30,0x47,
		           0x06,0x0B,0x0D,0x10,
		           0x12,0x10,0x10,0x13,
		           0x1B,0x33,0x32,0x34,
		           0x38,0x3C,0x3C,0x30,
		           0x47,0x06,0x0B,0x0D,
		           0x10,0x12,0x10,0x10,
		           0x13,0x1B}},
	{REGFLAG_DELAY, 10, {}},
	
	{0xE1, 	34,	{0x33,0x36,0x35,0x39,
		           0x3C,0x3C,0x32,0x48,
		           0x07,0x0B,0x0C,0x0E,
		           0x10,0x0E,0x0F,0x13,
		           0x1B,0x33,0x36,0x35,
		           0x39,0x3C,0x3C,0x32,
		           0x48,0x07,0x0B,0x0C,
		           0x0E,0x10,0x0E,0x0F,
		           0x13,0x1B}},
	{REGFLAG_DELAY, 10, {}},	
					
	{0xE2, 	34,	{0x01,0x14,0x18,0x3B,
		           0x3B,0x3C,0x28,0x46,
		           0x05,0x0D,0x0E,0x10,
		           0x13,0x11,0x10,0x11,
		           0x1A,0x01,0x14,0x18,
		           0x3B,0x3B,0x3C,0x28,
		           0x46,0x05,0x0D,0x0E,
		           0x10,0x13,0x11,0x10,
		           0x11,0x1A}},
	{REGFLAG_DELAY, 10, {}},	
	
	{0x29,	0,	{}},
	{REGFLAG_DELAY, 150, {}},
	// Note
	// Strongly recommend not to set Sleep out / Display On here. That will cause messed frame to be shown as later the backlight is on.


	// Setting ending by predefined flag
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static struct LCM_setting_table lcm_set_window[] = {
	{0x2A,	4,	{0x00, 0x00, (FRAME_WIDTH>>8), (FRAME_WIDTH&0xFF)}},
	{0x2B,	4,	{0x00, 0x00, (FRAME_HEIGHT>>8), (FRAME_HEIGHT&0xFF)}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static struct LCM_setting_table lcm_sleep_out_setting[] = {
    // Sleep Out
	{0x11, 1, {0x00}},
    {REGFLAG_DELAY, 120, {}},

    // Display ON
	{0x29, 1, {0x00}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static struct LCM_setting_table lcm_deep_sleep_mode_in_setting[] = {
	// Display off sequence
	{0x28, 1, {0x00}},

    // Sleep Mode On
	{0x10, 1, {0x00}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static struct LCM_setting_table lcm_backlight_level_setting[] = {
	{0x51, 1, {0xFF}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

    for(i = 0; i < count; i++) {
		
        unsigned cmd;
        cmd = table[i].cmd;
		
        switch (cmd) {
			
            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;
				
            case REGFLAG_END_OF_TABLE :
                break;
				
            default:
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
       	}
    }
	
}


// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{
		memset(params, 0, sizeof(LCM_PARAMS));
	
		params->type   = LCM_TYPE_DSI;

		params->width  = FRAME_WIDTH;
		params->height = FRAME_HEIGHT;

		// enable tearing-free
		params->dbi.te_mode 				= LCM_DBI_TE_MODE_VSYNC_ONLY;
	  //params->dbi.te_mode 				= LCM_DBI_TE_MODE_DISABLED;
		params->dbi.te_edge_polarity		= LCM_POLARITY_RISING;

#if (LCM_DSI_CMD_MODE)
		params->dsi.mode   = CMD_MODE;
#else
		params->dsi.mode   = SYNC_PULSE_VDO_MODE;
#endif
	
		// DSI
		/* Command mode setting */
		params->dsi.LANE_NUM				= LCM_ONE_LANE;
		//The following defined the fomat for data coming from LCD engine.
		params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
		params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST;
		params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
		params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;




		// Highly depends on LCD driver capability.
		// Not support in MT6573
		params->dsi.packet_size=254;

		// Video mode setting		
		params->dsi.intermediat_buffer_num = 2;

		params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
		
		/*
		params->dsi.word_count=480*3;	

		params->dsi.vertical_sync_active=3;
		params->dsi.vertical_backporch=12;
		params->dsi.vertical_frontporch=2;
		params->dsi.vertical_active_line=800;
	
		params->dsi.line_byte=2048;		// 2256 = 752*3
		params->dsi.horizontal_sync_active_byte=26;
		params->dsi.horizontal_backporch_byte=146;
		params->dsi.horizontal_frontporch_byte=146;	
		params->dsi.rgb_byte=(480*3+6);	
	
		params->dsi.horizontal_sync_active_word_count=20;	
		params->dsi.horizontal_backporch_word_count=140;
		params->dsi.horizontal_frontporch_word_count=140;
    */
    
		// Bit rate calculation
		params->dsi.pll_div1=32;		// fref=26MHz, fvco=fref*(div1+1)	(div1=0~63, fvco=500MHZ~1GHz)
		params->dsi.pll_div2=0;			// div2=0~15: fout=fvo/(2*div2)
  //  params->dsi.HS_ZERO = 1;
  //  params->dsi.HS_PRPR = 6;
}


static void lcm_init(void)
{
    SET_RESET_PIN(1);
    SET_RESET_PIN(0);
    MDELAY(10);
    SET_RESET_PIN(1);
    MDELAY(20);

	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}


static void lcm_suspend(void)
{
	push_table(lcm_deep_sleep_mode_in_setting, sizeof(lcm_deep_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);

}


static void lcm_resume(void)
{

	
	push_table(lcm_sleep_out_setting, sizeof(lcm_sleep_out_setting) / sizeof(struct LCM_setting_table), 1);
}


static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
	unsigned int x0 = x;
	unsigned int y0 = y;
	unsigned int x1 = x0 + width - 1;
	unsigned int y1 = y0 + height - 1;

	unsigned char x0_MSB = ((x0>>8)&0xFF);
	unsigned char x0_LSB = (x0&0xFF);
	unsigned char x1_MSB = ((x1>>8)&0xFF);
	unsigned char x1_LSB = (x1&0xFF);
	unsigned char y0_MSB = ((y0>>8)&0xFF);
	unsigned char y0_LSB = (y0&0xFF);
	unsigned char y1_MSB = ((y1>>8)&0xFF);
	unsigned char y1_LSB = (y1&0xFF);

	unsigned int data_array[16];

	data_array[0]= 0x00053902;
	data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x2a;
	data_array[2]= (x1_LSB);
	data_array[3]= 0x00053902;
	data_array[4]= (y1_MSB<<24)|(y0_LSB<<16)|(y0_MSB<<8)|0x2b;
	data_array[5]= (y1_LSB);
	data_array[6]= 0x002c3909;

	dsi_set_cmdq(&data_array, 7, 0);

}


static void lcm_setbacklight(unsigned int level)
{
	unsigned int default_level = 145;
	unsigned int mapped_level = 0;

	//                                  
	if(level > 255) 
			level = 255;
 
	if(level >0) 
			mapped_level = default_level+(level)*(255-default_level)/(255);
	else
			mapped_level=0;

	// Refresh value of backlight level.
	lcm_backlight_level_setting[0].para_list[0] = mapped_level;

	push_table(lcm_backlight_level_setting, sizeof(lcm_backlight_level_setting) / sizeof(struct LCM_setting_table), 1);
}


static void lcm_setpwm(unsigned int divider)
{
	// TBD
}


static unsigned int lcm_getpwm(unsigned int divider)
{
	// ref freq = 15MHz, B0h setting 0x80, so 80.6% * freq is pwm_clk;
	// pwm_clk / 255 / 2(lcm_setpwm() 6th params) = pwm_duration = 23706
	unsigned int pwm_clk = 23706 / (1<<divider);	
	return pwm_clk;
}
LCM_DRIVER hx8392a_dsi_cmd_lcm_drv = 
{
    .name			= "hx8392a_dsi_cmd",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
#if (LCM_DSI_CMD_MODE)
        .set_backlight	= lcm_setbacklight,
		//.set_pwm        = lcm_setpwm,
		//.get_pwm        = lcm_getpwm,
        .update         = lcm_update
#endif
    };
