/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: NXP EULA
 
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

extern lv_chart_series_t *pchart_ser;

void setup_scr_scrRide1(lv_ui *ui)
{
	//Write codes scrRide1
	ui->scrRide1 = lv_obj_create(NULL);
	lv_obj_set_size(ui->scrRide1, 480, 320);
	lv_obj_set_scrollbar_mode(ui->scrRide1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->scrRide1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrRide1, lv_color_hex(0x161d27), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_img_Header
	ui->scrRide1_img_Header = lv_img_create(ui->scrRide1);
	lv_obj_add_flag(ui->scrRide1_img_Header, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide1_img_Header, &_ebike_header_bg_alpha_480x51);
	lv_img_set_pivot(ui->scrRide1_img_Header, 50,50);
	lv_img_set_angle(ui->scrRide1_img_Header, 0);
	lv_obj_set_pos(ui->scrRide1_img_Header, 0, 0);
	lv_obj_set_size(ui->scrRide1_img_Header, 480, 51);
	lv_obj_set_scrollbar_mode(ui->scrRide1_img_Header, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_img_Header, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide1_img_Header, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Time
	ui->scrRide1_label_Time = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Time, "10:28 AM");
	lv_label_set_long_mode(ui->scrRide1_label_Time, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Time, 370, 3);
	lv_obj_set_size(ui->scrRide1_label_Time, 102, 18);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Time, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Time, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Title
	ui->scrRide1_label_Title = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Title, "RIDE DETAILS");
	lv_label_set_long_mode(ui->scrRide1_label_Title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Title, 155, 3);
	lv_obj_set_size(ui->scrRide1_label_Title, 170, 24);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Title, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Title, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Date
	ui->scrRide1_label_Date = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Date, "Jan 30,2024");
	lv_label_set_long_mode(ui->scrRide1_label_Date, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Date, 20, 3);
	lv_obj_set_size(ui->scrRide1_label_Date, 133, 18);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Date, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Date, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_img_Footer
	ui->scrRide1_img_Footer = lv_img_create(ui->scrRide1);
	lv_obj_add_flag(ui->scrRide1_img_Footer, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide1_img_Footer, &_ebike_footer_bg_alpha_480x35);
	lv_img_set_pivot(ui->scrRide1_img_Footer, 50,50);
	lv_img_set_angle(ui->scrRide1_img_Footer, 0);
	lv_obj_set_pos(ui->scrRide1_img_Footer, 0, 279);
	lv_obj_set_size(ui->scrRide1_img_Footer, 480, 35);
	lv_obj_set_scrollbar_mode(ui->scrRide1_img_Footer, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_img_Footer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide1_img_Footer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Indicator_R
	ui->scrRide1_label_Indicator_R = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Indicator_R, "");
	lv_label_set_long_mode(ui->scrRide1_label_Indicator_R, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Indicator_R, 277, 301);
	lv_obj_set_size(ui->scrRide1_label_Indicator_R, 28, 8);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Indicator_R, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Indicator_R, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Indicator_R, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Indicator_R, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Indicator_R, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Indicator_R, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Indicator_R, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Indicator_R, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrRide1_label_Indicator_R, lv_color_hex(0xa8a6ad), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Indicator_M
	ui->scrRide1_label_Indicator_M = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Indicator_M, "");
	lv_label_set_long_mode(ui->scrRide1_label_Indicator_M, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Indicator_M, 229, 301);
	lv_obj_set_size(ui->scrRide1_label_Indicator_M, 28, 8);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Indicator_M, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Indicator_M, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Indicator_M, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Indicator_M, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Indicator_M, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Indicator_M, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Indicator_M, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Indicator_M, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrRide1_label_Indicator_M, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Indicator_L
	ui->scrRide1_label_Indicator_L = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Indicator_L, "");
	lv_label_set_long_mode(ui->scrRide1_label_Indicator_L, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Indicator_L, 181, 301);
	lv_obj_set_size(ui->scrRide1_label_Indicator_L, 28, 8);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Indicator_L, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Indicator_L, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Indicator_L, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Indicator_L, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Indicator_L, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Indicator_L, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Indicator_L, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Indicator_L, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrRide1_label_Indicator_L, lv_color_hex(0xa8a6ad), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Distance_1
	ui->scrRide1_label_Distance_1 = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Distance_1, "Distance Travelled");
	lv_label_set_long_mode(ui->scrRide1_label_Distance_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Distance_1, 280, 55);
	lv_obj_set_size(ui->scrRide1_label_Distance_1, 189, 16);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Distance_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Distance_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Distance_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Distance_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Distance_1, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Distance_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Distance_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Distance_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Distance_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Distance_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Distance_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Distance_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Distance_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Distance_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Distance_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_img_Distance
	ui->scrRide1_img_Distance = lv_img_create(ui->scrRide1);
	lv_obj_add_flag(ui->scrRide1_img_Distance, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide1_img_Distance, &_ebike_icn_distance_travelled_big_alpha_42x28);
	lv_img_set_pivot(ui->scrRide1_img_Distance, 50,50);
	lv_img_set_angle(ui->scrRide1_img_Distance, 0);
	lv_obj_set_pos(ui->scrRide1_img_Distance, 230, 80);
	lv_obj_set_size(ui->scrRide1_img_Distance, 42, 28);
	lv_obj_set_scrollbar_mode(ui->scrRide1_img_Distance, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_img_Distance, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide1_img_Distance, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Distance_3
	ui->scrRide1_label_Distance_3 = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Distance_3, "km");
	lv_label_set_long_mode(ui->scrRide1_label_Distance_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Distance_3, 410, 90);
	lv_obj_set_size(ui->scrRide1_label_Distance_3, 40, 20);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Distance_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Distance_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Distance_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Distance_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Distance_3, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Distance_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Distance_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Distance_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Distance_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Distance_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Distance_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Distance_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Distance_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Distance_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Distance_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Distance_2
	ui->scrRide1_label_Distance_2 = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Distance_2, "12.7");
	lv_label_set_long_mode(ui->scrRide1_label_Distance_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Distance_2, 290, 90);
	lv_obj_set_size(ui->scrRide1_label_Distance_2, 70, 25);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Distance_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Distance_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Distance_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Distance_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Distance_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Distance_2, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Distance_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Distance_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Distance_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Distance_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Distance_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Distance_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Distance_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Distance_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Distance_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_line_H_Seperator_1
	ui->scrRide1_line_H_Seperator_1 = lv_line_create(ui->scrRide1);
	static lv_point_t scrRide1_line_H_Seperator_1[] ={{0, 0},{240, 0},};
	lv_line_set_points(ui->scrRide1_line_H_Seperator_1, scrRide1_line_H_Seperator_1, 2);
	lv_obj_set_pos(ui->scrRide1_line_H_Seperator_1, 230, 120);
	lv_obj_set_size(ui->scrRide1_line_H_Seperator_1, 240, 1);
	lv_obj_set_scrollbar_mode(ui->scrRide1_line_H_Seperator_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_line_H_Seperator_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_line_width(ui->scrRide1_line_H_Seperator_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->scrRide1_line_H_Seperator_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->scrRide1_line_H_Seperator_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_rounded(ui->scrRide1_line_H_Seperator_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Speed_3
	ui->scrRide1_label_Speed_3 = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Speed_3, "km/h");
	lv_label_set_long_mode(ui->scrRide1_label_Speed_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Speed_3, 410, 170);
	lv_obj_set_size(ui->scrRide1_label_Speed_3, 60, 20);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Speed_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Speed_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Speed_3, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Speed_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Speed_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Speed_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Speed_2
	ui->scrRide1_label_Speed_2 = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Speed_2, "16.1");
	lv_label_set_long_mode(ui->scrRide1_label_Speed_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Speed_2, 290, 170);
	lv_obj_set_size(ui->scrRide1_label_Speed_2, 70, 25);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Speed_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Speed_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Speed_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Speed_2, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Speed_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Speed_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Speed_1
	ui->scrRide1_label_Speed_1 = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Speed_1, "Average Speed");
	lv_label_set_long_mode(ui->scrRide1_label_Speed_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Speed_1, 280, 132);
	lv_obj_set_size(ui->scrRide1_label_Speed_1, 189, 16);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Speed_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Speed_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Speed_1, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Speed_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Speed_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Speed_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_img_Speed
	ui->scrRide1_img_Speed = lv_img_create(ui->scrRide1);
	lv_obj_add_flag(ui->scrRide1_img_Speed, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide1_img_Speed, &_ebike_icn_average_speed_big_alpha_40x31);
	lv_img_set_pivot(ui->scrRide1_img_Speed, 50,50);
	lv_img_set_angle(ui->scrRide1_img_Speed, 0);
	lv_obj_set_pos(ui->scrRide1_img_Speed, 230, 160);
	lv_obj_set_size(ui->scrRide1_img_Speed, 40, 31);
	lv_obj_set_scrollbar_mode(ui->scrRide1_img_Speed, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_img_Speed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide1_img_Speed, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_line_H_Seperator_2
	ui->scrRide1_line_H_Seperator_2 = lv_line_create(ui->scrRide1);
	static lv_point_t scrRide1_line_H_Seperator_2[] ={{0, 0},{240, 0},};
	lv_line_set_points(ui->scrRide1_line_H_Seperator_2, scrRide1_line_H_Seperator_2, 2);
	lv_obj_set_pos(ui->scrRide1_line_H_Seperator_2, 230, 200);
	lv_obj_set_size(ui->scrRide1_line_H_Seperator_2, 240, 1);
	lv_obj_set_scrollbar_mode(ui->scrRide1_line_H_Seperator_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_line_H_Seperator_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_line_width(ui->scrRide1_line_H_Seperator_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->scrRide1_line_H_Seperator_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->scrRide1_line_H_Seperator_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_rounded(ui->scrRide1_line_H_Seperator_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_img_Eleva_Gain
	ui->scrRide1_img_Eleva_Gain = lv_img_create(ui->scrRide1);
	lv_obj_add_flag(ui->scrRide1_img_Eleva_Gain, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide1_img_Eleva_Gain, &_ebike_icn_elevation_gained_alpha_22x18);
	lv_img_set_pivot(ui->scrRide1_img_Eleva_Gain, 50,50);
	lv_img_set_angle(ui->scrRide1_img_Eleva_Gain, 0);
	lv_obj_set_pos(ui->scrRide1_img_Eleva_Gain, 210, 215);
	lv_obj_set_size(ui->scrRide1_img_Eleva_Gain, 22, 18);
	lv_obj_set_scrollbar_mode(ui->scrRide1_img_Eleva_Gain, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_img_Eleva_Gain, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide1_img_Eleva_Gain, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Gain_1
	ui->scrRide1_label_Gain_1 = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Gain_1, "ElevationGained");
	lv_label_set_long_mode(ui->scrRide1_label_Gain_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Gain_1, 240, 210);
	lv_obj_set_size(ui->scrRide1_label_Gain_1, 95, 33);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Gain_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Gain_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Gain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Gain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Gain_1, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Gain_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Gain_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Gain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Gain_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Gain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Gain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Gain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Gain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Gain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Gain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_line_V_Seperator
	ui->scrRide1_line_V_Seperator = lv_line_create(ui->scrRide1);
	static lv_point_t scrRide1_line_V_Seperator[] ={{0, 0},{0, 80},};
	lv_line_set_points(ui->scrRide1_line_V_Seperator, scrRide1_line_V_Seperator, 2);
	lv_obj_set_pos(ui->scrRide1_line_V_Seperator, 340, 200);
	lv_obj_set_size(ui->scrRide1_line_V_Seperator, 3, 80);
	lv_obj_set_scrollbar_mode(ui->scrRide1_line_V_Seperator, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_line_V_Seperator, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_line_width(ui->scrRide1_line_V_Seperator, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->scrRide1_line_V_Seperator, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->scrRide1_line_V_Seperator, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_rounded(ui->scrRide1_line_V_Seperator, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Gain_2
	ui->scrRide1_label_Gain_2 = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Gain_2, "25.1");
	lv_label_set_long_mode(ui->scrRide1_label_Gain_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Gain_2, 210, 255);
	lv_obj_set_size(ui->scrRide1_label_Gain_2, 70, 25);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Gain_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Gain_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Gain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Gain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Gain_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Gain_2, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Gain_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Gain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Gain_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Gain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Gain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Gain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Gain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Gain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Gain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Gain_3
	ui->scrRide1_label_Gain_3 = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Gain_3, "m");
	lv_label_set_long_mode(ui->scrRide1_label_Gain_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Gain_3, 310, 259);
	lv_obj_set_size(ui->scrRide1_label_Gain_3, 23, 21);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Gain_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Gain_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Gain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Gain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Gain_3, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Gain_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Gain_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Gain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Gain_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Gain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Gain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Gain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Gain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Gain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Gain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Lost_3
	ui->scrRide1_label_Lost_3 = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Lost_3, "m");
	lv_label_set_long_mode(ui->scrRide1_label_Lost_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Lost_3, 450, 259);
	lv_obj_set_size(ui->scrRide1_label_Lost_3, 23, 21);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Lost_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Lost_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Lost_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Lost_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Lost_3, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Lost_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Lost_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Lost_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Lost_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Lost_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Lost_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Lost_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Lost_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Lost_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Lost_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Lost_2
	ui->scrRide1_label_Lost_2 = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Lost_2, "10.2");
	lv_label_set_long_mode(ui->scrRide1_label_Lost_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Lost_2, 350, 255);
	lv_obj_set_size(ui->scrRide1_label_Lost_2, 70, 25);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Lost_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Lost_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Lost_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Lost_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Lost_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Lost_2, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Lost_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Lost_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Lost_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Lost_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Lost_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Lost_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Lost_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Lost_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Lost_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Lost_1
	ui->scrRide1_label_Lost_1 = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Lost_1, "ElevationLost");
	lv_label_set_long_mode(ui->scrRide1_label_Lost_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Lost_1, 380, 210);
	lv_obj_set_size(ui->scrRide1_label_Lost_1, 95, 33);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Lost_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Lost_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Lost_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Lost_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Lost_1, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Lost_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Lost_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Lost_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Lost_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Lost_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Lost_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Lost_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Lost_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Lost_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Lost_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_img_Eleva_Lost
	ui->scrRide1_img_Eleva_Lost = lv_img_create(ui->scrRide1);
	lv_obj_add_flag(ui->scrRide1_img_Eleva_Lost, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide1_img_Eleva_Lost, &_ebike_icn_elevation_lost_alpha_22x18);
	lv_img_set_pivot(ui->scrRide1_img_Eleva_Lost, 50,50);
	lv_img_set_angle(ui->scrRide1_img_Eleva_Lost, 0);
	lv_obj_set_pos(ui->scrRide1_img_Eleva_Lost, 350, 215);
	lv_obj_set_size(ui->scrRide1_img_Eleva_Lost, 22, 18);
	lv_obj_set_scrollbar_mode(ui->scrRide1_img_Eleva_Lost, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_img_Eleva_Lost, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide1_img_Eleva_Lost, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_chart_Elevation
	ui->scrRide1_chart_Elevation = lv_chart_create(ui->scrRide1);
	lv_chart_set_type(ui->scrRide1_chart_Elevation, LV_CHART_TYPE_LINE);
	lv_chart_set_range(ui->scrRide1_chart_Elevation,LV_CHART_AXIS_PRIMARY_Y, 0, 100);
	lv_chart_set_div_line_count(ui->scrRide1_chart_Elevation, 4, 5);
	lv_chart_set_point_count(ui->scrRide1_chart_Elevation, 100);
	lv_chart_series_t * scrRide1_chart_Elevation_0 = lv_chart_add_series(ui->scrRide1_chart_Elevation, lv_color_hex(0xff007a), LV_CHART_AXIS_PRIMARY_Y);
	lv_obj_set_pos(ui->scrRide1_chart_Elevation, 35, 75);
	lv_obj_set_size(ui->scrRide1_chart_Elevation, 161, 144);
	lv_obj_set_scrollbar_mode(ui->scrRide1_chart_Elevation, LV_SCROLLBAR_MODE_OFF);
        
        int cnt = 0;
	for(cnt = 0 ; cnt < 20 ; cnt++)
	{
          lv_chart_set_next_value(ui->scrRide1_chart_Elevation, scrRide1_chart_Elevation_0, 10 + cnt);
	}
	for(cnt = 0 ; cnt < 10 ; cnt++)
	{
          lv_chart_set_next_value(ui->scrRide1_chart_Elevation, scrRide1_chart_Elevation_0, 29 - cnt);
	}
	for(cnt = 0 ; cnt < 10 ; cnt++)
	{
          lv_chart_set_next_value(ui->scrRide1_chart_Elevation, scrRide1_chart_Elevation_0, 19 + cnt);
	}
	for(cnt = 0 ; cnt < 20 ; cnt++)
	{
          lv_chart_set_next_value(ui->scrRide1_chart_Elevation, scrRide1_chart_Elevation_0, 29 - cnt);
	}
	for(cnt = 0 ; cnt < 10 ; cnt++)
	{
          lv_chart_set_next_value(ui->scrRide1_chart_Elevation, scrRide1_chart_Elevation_0, 9 + cnt);
	}
	for(cnt = 0 ; cnt < 10 ; cnt++)
	{
          lv_chart_set_next_value(ui->scrRide1_chart_Elevation, scrRide1_chart_Elevation_0, 19 - cnt);
	}
	for(cnt = 0 ; cnt < 10 ; cnt++)
	{
          lv_chart_set_next_value(ui->scrRide1_chart_Elevation, scrRide1_chart_Elevation_0, 9 + cnt);
	}
	for(cnt = 0 ; cnt < 10 ; cnt++)
	{
          lv_chart_set_next_value(ui->scrRide1_chart_Elevation, scrRide1_chart_Elevation_0, 19 - cnt);
	}
	pchart_ser = scrRide1_chart_Elevation_0;
        lv_chart_set_update_mode(ui->scrRide1_chart_Elevation, LV_CHART_UPDATE_MODE_SHIFT);
        
	//Write style for scrRide1_chart_Elevation, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->scrRide1_chart_Elevation, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrRide1_chart_Elevation, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->scrRide1_chart_Elevation, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->scrRide1_chart_Elevation, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->scrRide1_chart_Elevation, lv_color_hex(0xe8e8e8), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_chart_Elevation, 11, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_width(ui->scrRide1_chart_Elevation, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->scrRide1_chart_Elevation, lv_color_hex(0x161d27), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->scrRide1_chart_Elevation, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_chart_Elevation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
        
	//Write codes scrRide1_label_Elev_H
	ui->scrRide1_label_Elev_H = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Elev_H, "5 10 15 20 25 30\n          Km");
	lv_label_set_long_mode(ui->scrRide1_label_Elev_H, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Elev_H, 40, 230);
	lv_obj_set_size(ui->scrRide1_label_Elev_H, 154, 32);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Elev_H, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Elev_H, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Elev_H, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Elev_H, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Elev_H, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Elev_H, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Elev_H, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Elev_H, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Elev_H, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Elev_H, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Elev_H, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Elev_H, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Elev_H, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Elev_H, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Elev_H, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Elev_V
	ui->scrRide1_label_Elev_V = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Elev_V, "\n50\n\n40\n\n30\n\n20\n\n10");
	lv_label_set_long_mode(ui->scrRide1_label_Elev_V, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Elev_V, 6, 65);
	lv_obj_set_size(ui->scrRide1_label_Elev_V, 26, 165);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Elev_V, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Elev_V, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Elev_V, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Elev_V, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Elev_V, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Elev_V, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Elev_V, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Elev_V, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Elev_V, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Elev_V, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Elev_V, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Elev_V, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Elev_V, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Elev_V, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Elev_V, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Elev_Title
	ui->scrRide1_label_Elev_Title = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Elev_Title, "Meter");
	lv_label_set_long_mode(ui->scrRide1_label_Elev_Title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Elev_Title, 6, 45);
	lv_obj_set_size(ui->scrRide1_label_Elev_Title, 61, 20);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Elev_Title, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Elev_Title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Elev_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Elev_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Elev_Title, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Elev_Title, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Elev_Title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Elev_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Elev_Title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Elev_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Elev_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Elev_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Elev_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Elev_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Elev_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Eleva_Content
	ui->scrRide1_label_Eleva_Content = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Eleva_Content, "Eleva Graph");
	lv_label_set_long_mode(ui->scrRide1_label_Eleva_Content, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Eleva_Content, 57, 90);
	lv_obj_set_size(ui->scrRide1_label_Eleva_Content, 120, 17);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Eleva_Content, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Eleva_Content, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Eleva_Content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Eleva_Content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Eleva_Content, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Eleva_Content, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Eleva_Content, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Eleva_Content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Eleva_Content, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Eleva_Content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Eleva_Content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Eleva_Content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Eleva_Content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Eleva_Content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Eleva_Content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Eleva_Num
	ui->scrRide1_label_Eleva_Num = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Eleva_Num, "15.3");
	lv_label_set_long_mode(ui->scrRide1_label_Eleva_Num, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Eleva_Num, 58, 122);
	lv_obj_set_size(ui->scrRide1_label_Eleva_Num, 60, 16);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Eleva_Num, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Eleva_Num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Eleva_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Eleva_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Eleva_Num, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Eleva_Num, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Eleva_Num, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Eleva_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Eleva_Num, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Eleva_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Eleva_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Eleva_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Eleva_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Eleva_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Eleva_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide1_label_Eleva_Unit
	ui->scrRide1_label_Eleva_Unit = lv_label_create(ui->scrRide1);
	lv_label_set_text(ui->scrRide1_label_Eleva_Unit, "m");
	lv_label_set_long_mode(ui->scrRide1_label_Eleva_Unit, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide1_label_Eleva_Unit, 149, 122);
	lv_obj_set_size(ui->scrRide1_label_Eleva_Unit, 22, 16);
	lv_obj_set_scrollbar_mode(ui->scrRide1_label_Eleva_Unit, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide1_label_Eleva_Unit, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide1_label_Eleva_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide1_label_Eleva_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide1_label_Eleva_Unit, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide1_label_Eleva_Unit, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide1_label_Eleva_Unit, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide1_label_Eleva_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide1_label_Eleva_Unit, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide1_label_Eleva_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide1_label_Eleva_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide1_label_Eleva_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide1_label_Eleva_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide1_label_Eleva_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide1_label_Eleva_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->scrRide1);

	
	//Init events for screen.
	events_init_scrRide1(ui);
}
