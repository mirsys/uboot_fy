/*
 * arch/arm/plat-s5p4418/nanopi2/lcds.c
 *
 * Copyright (c) 2015 FriendlyARM (www.arm9.net)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <config.h>
#include <common.h>
#include <asm/arch/mach-api.h>
#include <asm/arch/display.h>
#include <nxp-fb.h>

static void s70_gpio_init(void)
{
	int i;

	/* PVCLK */
	NX_GPIO_SetDriveStrength(PAD_GPIO_A, 0, 1);

	/* RGB24 */
	for (i = 1; i < 25; i++)
		NX_GPIO_SetDriveStrength(PAD_GPIO_A, i, 2);

	/* HS/VS/DE */
	for (; i < 28; i++)
		NX_GPIO_SetDriveStrength(PAD_GPIO_A, i, 1);
}

static void hd101_gpio_init(void)
{
	NX_GPIO_SetDriveStrength(PAD_GPIO_A,  0, 2);
	NX_GPIO_SetDriveStrength(PAD_GPIO_A, 27, 2);
}


/* NXP display configs for supported LCD */

static struct nxp_lcd wxga_hd700 = {
	.width = 800,
	.height = 1280,
	.p_width = 94,
	.p_height = 151,
	.bpp = 24,
	.freq = 60,

	.timing = {
		.h_fp = 20,
		.h_bp = 20,
		.h_sw = 24,
		.v_fp =  4,
		.v_fpe = 1,
		.v_bp =  4,
		.v_bpe = 1,
		.v_sw =  8,
	},
	.polarity = {
		.rise_vclk = 1,
		.inv_hsync = 0,
		.inv_vsync = 0,
		.inv_vden = 0,
	},
};

static struct nxp_lcd wvga_s70 = {
	.width = 800,
	.height = 480,
	.p_width = 155,
	.p_height = 93,
	.bpp = 24,
	.freq = 63,

	.timing = {
		.h_fp = 80,
		.h_bp = 36,
		.h_sw = 10,
		.v_fp = 22,
		.v_fpe = 1,
		.v_bp = 15,
		.v_bpe = 1,
		.v_sw = 8,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
	.gpio_init = s70_gpio_init,
};

static struct nxp_lcd wvga_s70d = {
	.width = 800,
	.height = 480,
	.p_width = 155,
	.p_height = 93,
	.bpp = 24,
	.freq = 63,

	.timing = {
		.h_fp = 80,
		.h_bp = 78,
		.h_sw = 10,
		.v_fp = 22,
		.v_fpe = 1,
		.v_bp = 24,
		.v_bpe = 1,
		.v_sw = 8,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct nxp_lcd wvga_w50 = {
	.width= 800,
	.height = 480,
	.p_width = 108,
	.p_height = 64,
	.bpp = 24,
	.freq = 70,

	.timing = {
		.h_fp = 40,
		.h_bp = 40,
		.h_sw = 48,
		.v_fp = 20,
		.v_fpe = 1,
		.v_bp = 20,
		.v_bpe = 1,
		.v_sw = 12,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct nxp_lcd wsvga_w101 = {
	.width= 1024,
	.height = 600,
	.p_width = 204,
	.p_height = 120,
	.bpp = 24,
	.freq = 60,

	.timing = {
		.h_fp = 40,
		.h_bp = 40,
		.h_sw = 200,
		.v_fp =  8,
		.v_fpe = 1,
		.v_bp =  8,
		.v_bpe = 1,
		.v_sw = 16,
	},
	.polarity = {
		.rise_vclk = 1,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct nxp_lcd xga_a97 = {
	.width = 1024,
	.height = 768,
	.p_width = 200,
	.p_height = 150,
	.bpp = 24,
	.freq = 61,

	.timing = {
		.h_fp = 12,
		.h_bp = 12,
		.h_sw = 4,
		.v_fp = 8,
		.v_fpe = 1,
		.v_bp = 8,
		.v_bpe = 1,
		.v_sw =  4,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct nxp_lcd xga_lq150 = {
	.width = 1024,
	.height = 768,
	.p_width = 304,
	.p_height = 228,
	.bpp = 24,
	.freq = 60,

	.timing = {
		.h_fp = 12,
		.h_bp = 12,
		.h_sw = 40,
		.v_fp = 8,
		.v_fpe = 1,
		.v_bp = 8,
		.v_bpe = 1,
		.v_sw = 40,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct nxp_lcd vga_l80 = {
	.width= 640,
	.height = 480,
	.p_width = 160,
	.p_height = 120,
	.bpp = 32,
	.freq = 60,

	.timing = {
		.h_fp = 35,
		.h_bp = 53,
		.h_sw = 73,
		.v_fp = 3,
		.v_fpe = 1,
		.v_bp = 29,
		.v_bpe = 1,
		.v_sw = 6,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct nxp_lcd wxga_bp101 = {
	.width = 1280,
	.height = 800,
	.p_width = 218,
	.p_height = 136,
	.bpp = 24,
	.freq = 60,

	.timing = {
		.h_fp = 20,
		.h_bp = 20,
		.h_sw = 24,
		.v_fp =  4,
		.v_fpe = 1,
		.v_bp =  4,
		.v_bpe = 1,
		.v_sw =  8,
	},
	.polarity = {
		.rise_vclk = 1,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct nxp_lcd wxga_hd101 = {
	.width = 1280,
	.height = 800,
	.p_width = 218,
	.p_height = 136,
	.bpp = 24,
	.freq = 60,

	.timing = {
		.h_fp = 16,
		.h_bp = 16,
		.h_sw = 30,
		.v_fp =  8,
		.v_fpe = 1,
		.v_bp =  8,
		.v_bpe = 1,
		.v_sw = 12,
	},
	.polarity = {
		.rise_vclk = 1,
		.inv_hsync = 0,
		.inv_vsync = 0,
		.inv_vden = 0,
	},
	.gpio_init = hd101_gpio_init,
};

/* HDMI */
static struct nxp_lcd hdmi_def = {
	.width = 1920,
	.height = 1080,
	.p_width = 480,
	.p_height = 320,
	.bpp = 24,
	.freq = 60,

	.timing = {
		.h_fp = 12,
		.h_bp = 12,
		.h_sw = 4,
		.v_fp = 8,
		.v_fpe = 1,
		.v_bp = 8,
		.v_bpe = 1,
		.v_sw =  4,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct hdmi_config {
	char *name;
	int width;
	int height;
} nanopi2_hdmi_config[] = {
	{ "HDMI1080P60",	1920, 1080 },
	{ "HDMI1080I60",	1920, 1080 },
	{ "HDMI1080P30",	1920, 1080 },
	{ "HDMI1080P50",	1920, 1080 },
	{ "HDMI1080I50",	1920, 1080 },

	{ "HDMI1080P60D",	 960,  536 },
	{ "HDMI1080I60D",	 960,  536 },
	{ "HDMI1080P30D",	 960,  536 },
	{ "HDMI1080P50D",	 960,  536 },
	{ "HDMI1080I50D",	 960,  536 },

	{ "HDMI720P60",		1280,  720 },
	{ "HDMI720P60D",	 640,  360 },
	{ "HDMI720P50",		1280,  720 },
	{ "HDMI720P50D",	 640,  360 },

	{ "HDMI576P16X9",	 720,  576 },
	{ "HDMI576P16X9D",	 720,  576 },
	{ "HDMI576P4X3",	 720,  576 },
	{ "HDMI576P4X3D",	 720,  576 },

	{ "HDMI480P16X9",	 720,  480 },
	{ "HDMI480P16X9D",	 720,  480 },
	{ "HDMI480P4X3",	 720,  480 },
	{ "HDMI480P4X3D",	 720,  480 },
};


/* Try to guess LCD panel by kernel command line, or
 * using *HD101* as default */

static struct {
	int id;
	char *name;
	struct nxp_lcd *lcd;
	int dpi;
	int ctp;
} nanopi2_lcd_config[] = {
	{  25, "HD101",	&wxga_hd101,   0, 1 },
	{  18, "HD700",	&wxga_hd700, 213, 1 },
	{   3, "S70",	&wvga_s70,   128, 1 },
	{  24, "S702",	&wvga_s70,   128, 3 },

	/* TODO: Testing */
	{  26, "S70D",	&wvga_s70d,  128, 0 },
	{   4, "W50",	&wvga_w50,     0, 0 },
	{  15, "W101",	&wsvga_w101,   0, 1 },
	{   5, "L80",	&vga_l80,      0, 1 },
	{  -1, "A97",	&xga_a97,      0, 0 },
	{  -1, "LQ150",	&xga_lq150,    0, 1 },
	{  -1, "BP101",	&wxga_bp101,   0, 1 },
	{ 128, "HDMI",	&hdmi_def,     0, 0 },	/* Pls keep it at last */
};

static int lcd_idx = 0;

int nanopi2_setup_lcd_by_id(int id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(nanopi2_lcd_config); i++) {
		if (nanopi2_lcd_config[i].id == id) {
			lcd_idx = i;
			break;
		}
	}

	if (i >= ARRAY_SIZE(nanopi2_lcd_config)) {
		/* NOT found */
		return -19;
	}

	return nanopi2_lcd_config[i].id;
}

int nanopi2_setup_lcd_by_name(char *str)
{
	char *delim;
	int i;

	delim = strchr(str, ',');
	if (delim)
		*delim++ = '\0';

	if (!strncasecmp("HDMI", str, 4)) {
		struct hdmi_config *cfg = &nanopi2_hdmi_config[0];
		struct nxp_lcd *lcd;

		lcd_idx = ARRAY_SIZE(nanopi2_lcd_config) - 1;
		lcd = nanopi2_lcd_config[lcd_idx].lcd;

		for (i = 0; i < ARRAY_SIZE(nanopi2_hdmi_config); i++, cfg++) {
			if (!strcasecmp(cfg->name, str)) {
				lcd->width = cfg->width;
				lcd->height = cfg->height;
				nanopi2_lcd_config[lcd_idx].name = cfg->name;
				goto __ret;
			}
		}
	}

	for (i = 0; i < ARRAY_SIZE(nanopi2_lcd_config); i++) {
		if (!strcasecmp(nanopi2_lcd_config[i].name, str)) {
			lcd_idx = i;
			break;
		}
	}

__ret:
	return 0;
}

struct nxp_lcd *nanopi2_get_lcd(void)
{
	return nanopi2_lcd_config[lcd_idx].lcd;
}

const char *nanopi2_get_lcd_name(void)
{
	return nanopi2_lcd_config[lcd_idx].name;
}

int nanopi2_get_lcd_density(void)
{
	return nanopi2_lcd_config[lcd_idx].dpi;
}
