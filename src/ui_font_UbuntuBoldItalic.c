/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: --bpp 1 --size 18 --font Ubuntu-BoldItalic.ttf -o ui_font_UbuntuBoldItalic.c --format lvgl --symbols ABCDEFGHIBCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_*.%  --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_UBUNTUBOLDITALIC
#define UI_FONT_UBUNTUBOLDITALIC 1
#endif

#if UI_FONT_UBUNTUBOLDITALIC

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0025 "%" */
    0x3c, 0x39, 0xf0, 0xce, 0xe6, 0x33, 0x38, 0xcd,
    0xc3, 0xf6, 0x7, 0xb3, 0x81, 0xff, 0xe, 0xcc,
    0x73, 0x31, 0x8d, 0xce, 0x3e, 0x70, 0x70,

    /* U+002A "*" */
    0x18, 0x18, 0x7f, 0xff, 0x1c, 0x7e, 0x36,

    /* U+002E "." */
    0x7f, 0x80,

    /* U+0030 "0" */
    0xf, 0x1f, 0xcc, 0xee, 0x3e, 0x1f, 0xf, 0x8f,
    0x87, 0xc3, 0x63, 0xb1, 0x9f, 0xc7, 0x80,

    /* U+0031 "1" */
    0xc, 0xff, 0xfe, 0xb8, 0xe3, 0x8e, 0x31, 0xc7,
    0x1c, 0x60,

    /* U+0032 "2" */
    0xf, 0x8f, 0xf1, 0x9c, 0x7, 0x1, 0xc0, 0xf0,
    0x78, 0x3c, 0x3c, 0x1e, 0x7, 0x3, 0xfe, 0xff,
    0x80,

    /* U+0033 "3" */
    0x1f, 0x7, 0xe1, 0x1c, 0x7, 0x1, 0xc7, 0xe1,
    0xf0, 0xe, 0x3, 0x80, 0xe4, 0x3b, 0xfc, 0x7c,
    0x0,

    /* U+0034 "4" */
    0x1, 0xc0, 0xf0, 0x7c, 0x3f, 0x1d, 0x86, 0x63,
    0x39, 0xce, 0x7f, 0xff, 0xf0, 0x70, 0x1c, 0x7,
    0x0,

    /* U+0035 "5" */
    0xf, 0xe1, 0xf8, 0x70, 0xc, 0x1, 0x80, 0x7e,
    0xf, 0xe0, 0x1c, 0x3, 0x80, 0x71, 0xe, 0x7f,
    0x87, 0xe0,

    /* U+0036 "6" */
    0x3, 0xc7, 0xe3, 0xc1, 0xc0, 0x70, 0x3f, 0x8f,
    0xf3, 0x8e, 0xc3, 0xb8, 0xce, 0x71, 0xf8, 0x3c,
    0x0,

    /* U+0037 "7" */
    0x7f, 0xdf, 0xf0, 0x38, 0x1c, 0xf, 0x3, 0x81,
    0xc0, 0x70, 0x38, 0xc, 0x7, 0x1, 0xc0, 0x60,
    0x0,

    /* U+0038 "8" */
    0xf, 0x1f, 0xcc, 0x6e, 0x37, 0x39, 0xf8, 0xf8,
    0xfe, 0xe3, 0x61, 0xb9, 0xdf, 0xc7, 0xc0,

    /* U+0039 "9" */
    0xf, 0x7, 0xe3, 0x9c, 0xc3, 0x70, 0xcc, 0x73,
    0xfc, 0x7f, 0x3, 0x80, 0xe0, 0xf1, 0xf8, 0xf0,
    0x0,

    /* U+0041 "A" */
    0x0, 0xe0, 0x1e, 0x3, 0xe0, 0x36, 0x7, 0x60,
    0x67, 0xe, 0x71, 0xc7, 0x1f, 0xf3, 0xff, 0x30,
    0x77, 0x3, 0x60, 0x30,

    /* U+0042 "B" */
    0x1f, 0xc1, 0xfe, 0x18, 0xf3, 0x87, 0x38, 0xe3,
    0xfc, 0x3f, 0xc3, 0xe, 0x70, 0xe7, 0xe, 0x71,
    0xc7, 0xfc, 0xff, 0x0,

    /* U+0043 "C" */
    0x7, 0xe3, 0xfc, 0xf0, 0x38, 0x7, 0x0, 0xc0,
    0x38, 0x7, 0x0, 0xe0, 0x1c, 0x1, 0xc2, 0x1f,
    0xc1, 0xf8,

    /* U+0044 "D" */
    0x1f, 0xc0, 0xff, 0x6, 0x1c, 0x70, 0xe3, 0x83,
    0x9c, 0x1c, 0xe0, 0xc6, 0xe, 0x70, 0x73, 0x87,
    0x1c, 0x78, 0xff, 0xf, 0xe0, 0x0,

    /* U+0045 "E" */
    0x1f, 0xe3, 0xfc, 0x60, 0xc, 0x3, 0x80, 0x7f,
    0x8f, 0xe1, 0x80, 0x70, 0xe, 0x1, 0xc0, 0x3f,
    0xcf, 0xf8,

    /* U+0046 "F" */
    0x1f, 0xe3, 0xfc, 0x60, 0xc, 0x3, 0x80, 0x7f,
    0xf, 0xe1, 0x80, 0x70, 0xe, 0x1, 0xc0, 0x30,
    0xe, 0x0,

    /* U+0047 "G" */
    0x7, 0xe3, 0xfc, 0xf0, 0xb8, 0x7, 0x0, 0xc0,
    0x38, 0x3f, 0x6, 0xe1, 0xdc, 0x39, 0xc7, 0x3f,
    0xc1, 0xf8,

    /* U+0048 "H" */
    0x1c, 0x38, 0xe1, 0xc7, 0xe, 0x30, 0x73, 0x83,
    0x1f, 0xf8, 0xff, 0xc6, 0xe, 0x70, 0x63, 0x87,
    0x1c, 0x38, 0xc1, 0xce, 0xe, 0x0,

    /* U+0049 "I" */
    0x1c, 0x71, 0xc6, 0x38, 0xe3, 0x8c, 0x71, 0xc7,
    0x1c, 0xe0,

    /* U+004A "J" */
    0x0, 0xe0, 0x18, 0x7, 0x0, 0xe0, 0x1c, 0x3,
    0x80, 0x60, 0x1c, 0x3, 0x80, 0x71, 0x1c, 0x3f,
    0x87, 0xc0,

    /* U+004B "K" */
    0x1c, 0x38, 0xe3, 0x87, 0x78, 0x37, 0x83, 0xf8,
    0x1f, 0x80, 0xf8, 0x7, 0xe0, 0x77, 0x3, 0x9c,
    0x1c, 0xf0, 0xe3, 0x8e, 0x1e, 0x0,

    /* U+004C "L" */
    0x1c, 0xe, 0x7, 0x3, 0x3, 0x81, 0xc0, 0xe0,
    0x70, 0x70, 0x38, 0x1c, 0xf, 0xff, 0xf8,

    /* U+004D "M" */
    0xe, 0x6, 0x1e, 0xe, 0x1e, 0x1e, 0x1e, 0x1e,
    0x3e, 0x3e, 0x3f, 0x7e, 0x37, 0x6e, 0x33, 0xce,
    0x73, 0xcc, 0x73, 0x8c, 0x63, 0x9c, 0xe0, 0x1c,
    0xe0, 0x1c,

    /* U+004E "N" */
    0x1c, 0x1c, 0x70, 0x71, 0xe1, 0x87, 0x8e, 0x3f,
    0x38, 0xec, 0xe3, 0xbb, 0xc, 0x7c, 0x71, 0xf1,
    0xc7, 0xc7, 0xe, 0x18, 0x38, 0xe0, 0x60,

    /* U+004F "O" */
    0x7, 0xc1, 0xfe, 0x38, 0xf7, 0x7, 0x70, 0x76,
    0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0xe, 0x71,
    0xc3, 0xf8, 0x1f, 0x0,

    /* U+0050 "P" */
    0x1f, 0xc1, 0xfe, 0x1c, 0xf1, 0x87, 0x38, 0x73,
    0x8e, 0x3f, 0xc3, 0xf8, 0x70, 0x7, 0x0, 0x70,
    0x6, 0x0, 0xe0, 0x0,

    /* U+0051 "Q" */
    0x7, 0xc1, 0xfe, 0x38, 0x77, 0x7, 0x70, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xe0, 0xff, 0xe, 0x7f,
    0xc3, 0xf8, 0x1e, 0x0, 0xe0, 0xf, 0xc0, 0x38,

    /* U+0052 "R" */
    0x1f, 0xc1, 0xfe, 0x1c, 0xe1, 0x87, 0x38, 0x73,
    0x8e, 0x3f, 0xc3, 0xf8, 0x73, 0x87, 0x38, 0x71,
    0xc6, 0x1c, 0xe1, 0xc0,

    /* U+0053 "S" */
    0xf, 0x87, 0xf3, 0x80, 0xe0, 0x38, 0xf, 0x81,
    0xf0, 0x3e, 0x3, 0x80, 0xe4, 0x3b, 0xfc, 0x7e,
    0x0,

    /* U+0054 "T" */
    0xff, 0xff, 0xf1, 0xc0, 0x70, 0x1c, 0xe, 0x3,
    0x80, 0xe0, 0x38, 0xc, 0x7, 0x1, 0xc0, 0x70,
    0x0,

    /* U+0055 "U" */
    0x38, 0x73, 0x87, 0x30, 0x67, 0xe, 0x70, 0xe7,
    0xe, 0x60, 0xce, 0x1c, 0xe1, 0xce, 0x1c, 0xe3,
    0x87, 0xf0, 0x3e, 0x0,

    /* U+0056 "V" */
    0xe0, 0x7e, 0xe, 0xe0, 0xee, 0x1c, 0x61, 0x86,
    0x38, 0x73, 0x7, 0x70, 0x7e, 0x7, 0xe0, 0x7c,
    0x3, 0x80, 0x38, 0x0,

    /* U+0057 "W" */
    0xe0, 0x7, 0xe0, 0x7, 0xe3, 0x8e, 0xe3, 0x8e,
    0xe7, 0x8e, 0xe7, 0x9c, 0xef, 0x9c, 0xed, 0xb8,
    0xf9, 0xf8, 0xf9, 0xf0, 0xf1, 0xf0, 0xf0, 0xe0,
    0xe0, 0xe0,

    /* U+0058 "X" */
    0xe, 0x1c, 0x38, 0xe0, 0xe7, 0x1, 0xf8, 0x7,
    0xe0, 0xf, 0x0, 0x78, 0x1, 0xf0, 0xf, 0xc0,
    0x73, 0x83, 0x8e, 0x1e, 0x38, 0x70, 0x70,

    /* U+0059 "Y" */
    0xe0, 0xfc, 0x39, 0xcf, 0x39, 0xc7, 0x70, 0x7c,
    0xf, 0x1, 0xe0, 0x38, 0x7, 0x0, 0xe0, 0x1c,
    0x7, 0x0,

    /* U+005A "Z" */
    0x1f, 0xf1, 0xff, 0x0, 0xe0, 0x1c, 0x3, 0x80,
    0x70, 0xf, 0x1, 0xe0, 0x3c, 0x7, 0x80, 0x70,
    0xf, 0xfc, 0xff, 0xc0,

    /* U+005F "_" */
    0x7f, 0xdf, 0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 69, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 251, .box_w = 14, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 145, .box_w = 8, .box_h = 7, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 31, .adv_w = 73, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 164, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 164, .box_w = 6, .box_h = 13, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 164, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 164, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 164, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 164, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 164, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 164, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 164, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 164, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 206, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 190, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 184, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 207, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 171, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 166, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 198, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 206, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 90, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 149, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 191, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 162, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 253, .box_w = 16, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 214, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 218, .box_w = 12, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 184, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 218, .box_w = 12, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 527, .adv_w = 189, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 161, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 171, .box_w = 10, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 197, .box_w = 12, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 198, .box_w = 12, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 270, .box_w = 16, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 193, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 188, .box_w = 11, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 184, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 708, .adv_w = 145, .box_w = 10, .box_h = 2, .ofs_x = -1, .ofs_y = -3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x5, 0xa, 0xe
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 15, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 4, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 48, .range_length = 10, .glyph_id_start = 5,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65, .range_length = 26, .glyph_id_start = 15,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 95, .range_length = 1, .glyph_id_start = 41,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 1, 2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 3,
    4, 5, 6, 7, 8, 9, 0, 0,
    10, 11, 12, 13, 0, 6, 14, 6,
    15, 16, 17, 18, 19, 20, 21, 22,
    23, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 1, 2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 3,
    4, 5, 4, 4, 4, 5, 4, 4,
    6, 4, 4, 7, 4, 5, 4, 5,
    4, 8, 9, 10, 11, 12, 13, 14,
    15, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, -17, 0, -4, -30, -5, 0,
    -4, -2, -3, 0, -13, -9, -10, 0,
    0, 14, 0, -17, 13, 3, 12, -17,
    0, -17, -3, 12, -29, 12, -23, 3,
    0, -2, -13, 4, 0, 0, -20, -4,
    -20, -8, 0, -26, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, 0, -5,
    0, -3, -10, 0, 0, 0, 3, 0,
    -6, 3, 0, 6, 3, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 3, 0, -14, 0, -9, 0, -10,
    -19, -4, 0, 0, 4, 0, 0, 3,
    0, 0, 0, 0, 3, 1, 3, 0,
    0, 4, -17, -10, 0, -6, -35, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 3, 0, 0, 0, 0, 0, 0,
    -3, 0, -3, 0, 0, -4, 0, 0,
    0, -6, 0, 0, -5, 0, 0, 0,
    0, 0, 0, -2, 0, 0, -3, 6,
    6, 0, -17, 0, 0, 0, 3, 0,
    6, 3, 6, 6, 3, -35, 3, 6,
    -2, -17, 6, 0, 0, -35, -6, -35,
    -17, 3, -40, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, -6, 0,
    0, -6, 0, 0, -17, -20, 0, 0,
    -35, 0, 0, 0, 0, -3, 0, -14,
    -8, -17, 0, 0, 6, 0, -2, 3,
    0, 0, -4, 0, -6, 0, 7, -11,
    0, -3, 3, 0, 0, -3, 3, 0,
    0, 0, 0, -9, 0, 0, -9, 0,
    12, -17, -22, 0, -3, -29, -4, 12,
    9, 0, 10, 7, 5, 8, 0, 0,
    0, -3, 0, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 9, -20,
    -14, 0, -9, -35, -5, 0, 6, 0,
    0, 0, 0, 0, 0, 9, -12, -8,
    0, 29, -17, 0, 9, 6, 0, 0,
    0, 0, 0, 0, 0, 7, 0, 0,
    -10, 5, 0, 6, -3, -3, 0, 0,
    0, 0, 5, 0, -20, -20, 0, -7,
    -35, -6, 3, 6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -7, 5,
    0, 0, 0, 0, 5, 3, 5, 0,
    0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 23,
    .right_class_cnt     = 15,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 4,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t ui_font_UbuntuBoldItalic = {
#else
lv_font_t ui_font_UbuntuBoldItalic = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_UBUNTUBOLDITALIC*/

