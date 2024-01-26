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


void setup_scr_scrRide2(lv_ui *ui)
{
	//Write codes scrRide2
	ui->scrRide2 = lv_obj_create(NULL);
	lv_obj_set_size(ui->scrRide2, 480, 320);
	lv_obj_set_scrollbar_mode(ui->scrRide2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->scrRide2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrRide2, lv_color_hex(0x161d27), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_img_Header
	ui->scrRide2_img_Header = lv_img_create(ui->scrRide2);
	lv_obj_add_flag(ui->scrRide2_img_Header, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide2_img_Header, &_ebike_header_bg_alpha_480x51);
	lv_img_set_pivot(ui->scrRide2_img_Header, 50,50);
	lv_img_set_angle(ui->scrRide2_img_Header, 0);
	lv_obj_set_pos(ui->scrRide2_img_Header, 0, 0);
	lv_obj_set_size(ui->scrRide2_img_Header, 480, 51);
	lv_obj_set_scrollbar_mode(ui->scrRide2_img_Header, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_img_Header, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide2_img_Header, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Date
	ui->scrRide2_label_Date = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Date, "Jan 30,2024");
	lv_label_set_long_mode(ui->scrRide2_label_Date, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Date, 20, 2);
	lv_obj_set_size(ui->scrRide2_label_Date, 133, 18);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Date, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Date, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Title
	ui->scrRide2_label_Title = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Title, "RIDE DETAILS");
	lv_label_set_long_mode(ui->scrRide2_label_Title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Title, 155, 3);
	lv_obj_set_size(ui->scrRide2_label_Title, 170, 24);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Title, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Title, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Time
	ui->scrRide2_label_Time = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Time, "10:28 AM");
	lv_label_set_long_mode(ui->scrRide2_label_Time, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Time, 370, 3);
	lv_obj_set_size(ui->scrRide2_label_Time, 102, 18);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Time, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Time, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_img_GPS_Icon
	ui->scrRide2_img_GPS_Icon = lv_img_create(ui->scrRide2);
	lv_obj_add_flag(ui->scrRide2_img_GPS_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide2_img_GPS_Icon, &_ebike_gps_arrow_alpha_28x48);
	lv_img_set_pivot(ui->scrRide2_img_GPS_Icon, 50,50);
	lv_img_set_angle(ui->scrRide2_img_GPS_Icon, 0);
	lv_obj_set_pos(ui->scrRide2_img_GPS_Icon, 274, 60);
	lv_obj_set_size(ui->scrRide2_img_GPS_Icon, 28, 48);
	lv_obj_set_scrollbar_mode(ui->scrRide2_img_GPS_Icon, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_img_GPS_Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide2_img_GPS_Icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Distance
	ui->scrRide2_label_Distance = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Distance, "3.1");
	lv_label_set_long_mode(ui->scrRide2_label_Distance, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Distance, 329, 49);
	lv_obj_set_size(ui->scrRide2_label_Distance, 36, 19);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Distance, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Distance, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Distance, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Distance, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Distance, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Distance, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Direction
	ui->scrRide2_label_Direction = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Direction, "Turn right to");
	lv_label_set_long_mode(ui->scrRide2_label_Direction, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Direction, 320, 74);
	lv_obj_set_size(ui->scrRide2_label_Direction, 147, 18);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Direction, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Direction, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Direction, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Direction, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Direction, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Direction, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Street
	ui->scrRide2_label_Street = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Street, "Ed Bluestein Blvd");
	lv_label_set_long_mode(ui->scrRide2_label_Street, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Street, 288, 97);
	lv_obj_set_size(ui->scrRide2_label_Street, 184, 17);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Street, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Street, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Street, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Street, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Street, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Street, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_ima_Calories_Icon
	ui->scrRide2_ima_Calories_Icon = lv_img_create(ui->scrRide2);
	lv_obj_add_flag(ui->scrRide2_ima_Calories_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide2_ima_Calories_Icon, &_ebike_icn_calories_burned_alpha_19x21);
	lv_img_set_pivot(ui->scrRide2_ima_Calories_Icon, 50,50);
	lv_img_set_angle(ui->scrRide2_ima_Calories_Icon, 0);
	lv_obj_set_pos(ui->scrRide2_ima_Calories_Icon, 220, 130);
	lv_obj_set_size(ui->scrRide2_ima_Calories_Icon, 19, 21);
	lv_obj_set_scrollbar_mode(ui->scrRide2_ima_Calories_Icon, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_ima_Calories_Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide2_ima_Calories_Icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Calories_1
	ui->scrRide2_label_Calories_1 = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Calories_1, "CaloriesBurned");
	lv_label_set_long_mode(ui->scrRide2_label_Calories_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Calories_1, 250, 118);
	lv_obj_set_size(ui->scrRide2_label_Calories_1, 94, 38);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Calories_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Calories_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Calories_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Calories_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Calories_1, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Calories_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Calories_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Calories_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Calories_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Calories_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Calories_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Calories_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Calories_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Calories_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Calories_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Calories_2
	ui->scrRide2_label_Calories_2 = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Calories_2, "12.7");
	lv_label_set_long_mode(ui->scrRide2_label_Calories_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Calories_2, 220, 157);
	lv_obj_set_size(ui->scrRide2_label_Calories_2, 70, 25);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Calories_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Calories_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Calories_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Calories_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Calories_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Calories_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Calories_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Calories_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Calories_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Calories_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Calories_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Calories_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Calories_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Calories_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Calories_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Calories_3
	ui->scrRide2_label_Calories_3 = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Calories_3, "Kcal");
	lv_label_set_long_mode(ui->scrRide2_label_Calories_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Calories_3, 293, 157);
	lv_obj_set_size(ui->scrRide2_label_Calories_3, 57, 20);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Calories_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Calories_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Calories_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Calories_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Calories_3, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Calories_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Calories_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Calories_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Calories_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Calories_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Calories_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Calories_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Calories_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Calories_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Calories_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Heart_3
	ui->scrRide2_label_Heart_3 = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Heart_3, "BPM");
	lv_label_set_long_mode(ui->scrRide2_label_Heart_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Heart_3, 410, 157);
	lv_obj_set_size(ui->scrRide2_label_Heart_3, 60, 17);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Heart_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Heart_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Heart_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Heart_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Heart_3, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Heart_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Heart_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Heart_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Heart_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Heart_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Heart_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Heart_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Heart_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Heart_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Heart_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Heart_2
	ui->scrRide2_label_Heart_2 = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Heart_2, "16.1");
	lv_label_set_long_mode(ui->scrRide2_label_Heart_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Heart_2, 357, 157);
	lv_obj_set_size(ui->scrRide2_label_Heart_2, 70, 25);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Heart_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Heart_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Heart_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Heart_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Heart_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Heart_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Heart_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Heart_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Heart_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Heart_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Heart_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Heart_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Heart_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Heart_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Heart_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Heart_1
	ui->scrRide2_label_Heart_1 = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Heart_1, "Heart\nRate");
	lv_label_set_long_mode(ui->scrRide2_label_Heart_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Heart_1, 387, 118);
	lv_obj_set_size(ui->scrRide2_label_Heart_1, 87, 41);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Heart_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Heart_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Heart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Heart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Heart_1, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Heart_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Heart_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Heart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Heart_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Heart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Heart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Heart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Heart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Heart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Heart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_img_Heart_Icon
	ui->scrRide2_img_Heart_Icon = lv_img_create(ui->scrRide2);
	lv_obj_add_flag(ui->scrRide2_img_Heart_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide2_img_Heart_Icon, &_ebike_icn_heart_rate_alpha_24x21);
	lv_img_set_pivot(ui->scrRide2_img_Heart_Icon, 50,50);
	lv_img_set_angle(ui->scrRide2_img_Heart_Icon, 0);
	lv_obj_set_pos(ui->scrRide2_img_Heart_Icon, 357, 130);
	lv_obj_set_size(ui->scrRide2_img_Heart_Icon, 24, 21);
	lv_obj_set_scrollbar_mode(ui->scrRide2_img_Heart_Icon, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_img_Heart_Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide2_img_Heart_Icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_img_Cadence_Icon
	ui->scrRide2_img_Cadence_Icon = lv_img_create(ui->scrRide2);
	lv_obj_add_flag(ui->scrRide2_img_Cadence_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide2_img_Cadence_Icon, &_ebike_icn_round_per_minute_alpha_20x20);
	lv_img_set_pivot(ui->scrRide2_img_Cadence_Icon, 50,50);
	lv_img_set_angle(ui->scrRide2_img_Cadence_Icon, 0);
	lv_obj_set_pos(ui->scrRide2_img_Cadence_Icon, 220, 193);
	lv_obj_set_size(ui->scrRide2_img_Cadence_Icon, 20, 20);
	lv_obj_set_scrollbar_mode(ui->scrRide2_img_Cadence_Icon, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_img_Cadence_Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide2_img_Cadence_Icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Cadence_1
	ui->scrRide2_label_Cadence_1 = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Cadence_1, "Cadence");
	lv_label_set_long_mode(ui->scrRide2_label_Cadence_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Cadence_1, 250, 190);
	lv_obj_set_size(ui->scrRide2_label_Cadence_1, 94, 38);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Cadence_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Cadence_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Cadence_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Cadence_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Cadence_1, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Cadence_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Cadence_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Cadence_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Cadence_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Cadence_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Cadence_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Cadence_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Cadence_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Cadence_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Cadence_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Cadence_3
	ui->scrRide2_label_Cadence_3 = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Cadence_3, "RPM");
	lv_label_set_long_mode(ui->scrRide2_label_Cadence_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Cadence_3, 293, 229);
	lv_obj_set_size(ui->scrRide2_label_Cadence_3, 57, 20);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Cadence_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Cadence_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Cadence_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Cadence_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Cadence_3, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Cadence_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Cadence_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Cadence_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Cadence_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Cadence_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Cadence_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Cadence_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Cadence_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Cadence_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Cadence_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Cadence_2
	ui->scrRide2_label_Cadence_2 = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Cadence_2, "86");
	lv_label_set_long_mode(ui->scrRide2_label_Cadence_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Cadence_2, 220, 229);
	lv_obj_set_size(ui->scrRide2_label_Cadence_2, 70, 25);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Cadence_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Cadence_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Cadence_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Cadence_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Cadence_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Cadence_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Cadence_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Cadence_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Cadence_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Cadence_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Cadence_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Cadence_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Cadence_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Cadence_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Cadence_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_img_Elapsed_Icon
	ui->scrRide2_img_Elapsed_Icon = lv_img_create(ui->scrRide2);
	lv_obj_add_flag(ui->scrRide2_img_Elapsed_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide2_img_Elapsed_Icon, &_ebike_icn_elapsed_time_alpha_20x25);
	lv_img_set_pivot(ui->scrRide2_img_Elapsed_Icon, 50,50);
	lv_img_set_angle(ui->scrRide2_img_Elapsed_Icon, 0);
	lv_obj_set_pos(ui->scrRide2_img_Elapsed_Icon, 357, 193);
	lv_obj_set_size(ui->scrRide2_img_Elapsed_Icon, 20, 25);
	lv_obj_set_scrollbar_mode(ui->scrRide2_img_Elapsed_Icon, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_img_Elapsed_Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide2_img_Elapsed_Icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Elapsed_1
	ui->scrRide2_label_Elapsed_1 = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Elapsed_1, "Elapsed \nTime");
	lv_label_set_long_mode(ui->scrRide2_label_Elapsed_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Elapsed_1, 387, 190);
	lv_obj_set_size(ui->scrRide2_label_Elapsed_1, 85, 35);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Elapsed_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Elapsed_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Elapsed_1, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Elapsed_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Elapsed_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Elapsed_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Elapsed_2
	ui->scrRide2_label_Elapsed_2 = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Elapsed_2, "46:28");
	lv_label_set_long_mode(ui->scrRide2_label_Elapsed_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Elapsed_2, 357, 229);
	lv_obj_set_size(ui->scrRide2_label_Elapsed_2, 70, 25);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Elapsed_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Elapsed_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Elapsed_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Elapsed_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Elapsed_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Elapsed_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_line_V_Seperator
	ui->scrRide2_line_V_Seperator = lv_line_create(ui->scrRide2);
	static lv_point_t scrRide2_line_V_Seperator[] ={{0, 0},{0, 240},};
	lv_line_set_points(ui->scrRide2_line_V_Seperator, scrRide2_line_V_Seperator, 2);
	lv_obj_set_pos(ui->scrRide2_line_V_Seperator, 345, 119);
	lv_obj_set_size(ui->scrRide2_line_V_Seperator, 5, 138);
	lv_obj_set_scrollbar_mode(ui->scrRide2_line_V_Seperator, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_line_V_Seperator, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_line_width(ui->scrRide2_line_V_Seperator, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->scrRide2_line_V_Seperator, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->scrRide2_line_V_Seperator, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_rounded(ui->scrRide2_line_V_Seperator, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_img_Footer
	ui->scrRide2_img_Footer = lv_img_create(ui->scrRide2);
	lv_obj_add_flag(ui->scrRide2_img_Footer, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrRide2_img_Footer, &_ebike_footer_bg_alpha_480x35);
	lv_img_set_pivot(ui->scrRide2_img_Footer, 50,50);
	lv_img_set_angle(ui->scrRide2_img_Footer, 0);
	lv_obj_set_pos(ui->scrRide2_img_Footer, 0, 279);
	lv_obj_set_size(ui->scrRide2_img_Footer, 480, 35);
	lv_obj_set_scrollbar_mode(ui->scrRide2_img_Footer, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_img_Footer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrRide2_img_Footer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_line_H_Seperator
	ui->scrRide2_line_H_Seperator = lv_line_create(ui->scrRide2);
	static lv_point_t scrRide2_line_H_Seperator[] ={{0, 0},{240, 0},};
	lv_line_set_points(ui->scrRide2_line_H_Seperator, scrRide2_line_H_Seperator, 2);
	lv_obj_set_pos(ui->scrRide2_line_H_Seperator, 225, 180);
	lv_obj_set_size(ui->scrRide2_line_H_Seperator, 240, 1);
	lv_obj_set_scrollbar_mode(ui->scrRide2_line_H_Seperator, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_line_H_Seperator, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_line_width(ui->scrRide2_line_H_Seperator, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->scrRide2_line_H_Seperator, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->scrRide2_line_H_Seperator, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_rounded(ui->scrRide2_line_H_Seperator, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Indicator_L
	ui->scrRide2_label_Indicator_L = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Indicator_L, "");
	lv_label_set_long_mode(ui->scrRide2_label_Indicator_L, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Indicator_L, 181, 301);
	lv_obj_set_size(ui->scrRide2_label_Indicator_L, 28, 8);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Indicator_L, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Indicator_L, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Indicator_L, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Indicator_L, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Indicator_L, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Indicator_L, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Indicator_L, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Indicator_L, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrRide2_label_Indicator_L, lv_color_hex(0xa8a6ad), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Indicator_M
	ui->scrRide2_label_Indicator_M = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Indicator_M, "");
	lv_label_set_long_mode(ui->scrRide2_label_Indicator_M, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Indicator_M, 229, 301);
	lv_obj_set_size(ui->scrRide2_label_Indicator_M, 28, 8);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Indicator_M, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Indicator_M, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Indicator_M, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Indicator_M, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Indicator_M, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Indicator_M, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Indicator_M, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Indicator_M, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrRide2_label_Indicator_M, lv_color_hex(0xa8a6ad), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Indicator_R
	ui->scrRide2_label_Indicator_R = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Indicator_R, "");
	lv_label_set_long_mode(ui->scrRide2_label_Indicator_R, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Indicator_R, 277, 301);
	lv_obj_set_size(ui->scrRide2_label_Indicator_R, 28, 8);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Indicator_R, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Indicator_R, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Indicator_R, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Indicator_R, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Indicator_R, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Indicator_R, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Indicator_R, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Indicator_R, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrRide2_label_Indicator_R, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Distance_Unit
	ui->scrRide2_label_Distance_Unit = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Distance_Unit, "KM");
	lv_label_set_long_mode(ui->scrRide2_label_Distance_Unit, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Distance_Unit, 368, 49);
	lv_obj_set_size(ui->scrRide2_label_Distance_Unit, 48, 19);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Distance_Unit, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Distance_Unit, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Distance_Unit, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Distance_Unit, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Distance_Unit, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Distance_Unit, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_arc_Watts
	ui->scrRide2_arc_Watts = lv_arc_create(ui->scrRide2);
	lv_arc_set_mode(ui->scrRide2_arc_Watts, LV_ARC_MODE_NORMAL);
	lv_arc_set_range(ui->scrRide2_arc_Watts, 0, 100);
	lv_arc_set_bg_angles(ui->scrRide2_arc_Watts, 0, 360);
	lv_arc_set_angles(ui->scrRide2_arc_Watts, 90, 180);
	lv_arc_set_rotation(ui->scrRide2_arc_Watts, 0);
	lv_obj_set_style_arc_rounded(ui->scrRide2_arc_Watts, 0,  LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_rounded(ui->scrRide2_arc_Watts, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->scrRide2_arc_Watts, 10, 49);
	lv_obj_set_size(ui->scrRide2_arc_Watts, 200, 200);
	lv_obj_set_scrollbar_mode(ui->scrRide2_arc_Watts, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_arc_Watts, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->scrRide2_arc_Watts, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->scrRide2_arc_Watts, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->scrRide2_arc_Watts, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->scrRide2_arc_Watts, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_arc_Watts, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_arc_Watts, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_arc_Watts, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_arc_Watts, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_arc_Watts, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_arc_Watts, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for scrRide2_arc_Watts, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->scrRide2_arc_Watts, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->scrRide2_arc_Watts, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for scrRide2_arc_Watts, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->scrRide2_arc_Watts, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->scrRide2_arc_Watts, 5, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Watts_Unit
	ui->scrRide2_label_Watts_Unit = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Watts_Unit, "Watts");
	lv_label_set_long_mode(ui->scrRide2_label_Watts_Unit, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Watts_Unit, 74, 147);
	lv_obj_set_size(ui->scrRide2_label_Watts_Unit, 72, 26);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Watts_Unit, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Watts_Unit, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Watts_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Watts_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Watts_Unit, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Watts_Unit, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Watts_Unit, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Watts_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Watts_Unit, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Watts_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Watts_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Watts_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Watts_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Watts_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Watts_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrRide2_label_Watts_Num
	ui->scrRide2_label_Watts_Num = lv_label_create(ui->scrRide2);
	lv_label_set_text(ui->scrRide2_label_Watts_Num, "15.7");
	lv_label_set_long_mode(ui->scrRide2_label_Watts_Num, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrRide2_label_Watts_Num, 90, 119);
	lv_obj_set_size(ui->scrRide2_label_Watts_Num, 53, 20);
	lv_obj_set_scrollbar_mode(ui->scrRide2_label_Watts_Num, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrRide2_label_Watts_Num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrRide2_label_Watts_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrRide2_label_Watts_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrRide2_label_Watts_Num, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrRide2_label_Watts_Num, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrRide2_label_Watts_Num, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrRide2_label_Watts_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrRide2_label_Watts_Num, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrRide2_label_Watts_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrRide2_label_Watts_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrRide2_label_Watts_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrRide2_label_Watts_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrRide2_label_Watts_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrRide2_label_Watts_Num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->scrRide2);

	
	//Init events for screen.
	events_init_scrRide2(ui);
}
