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


void setup_scr_scrOverview(lv_ui *ui)
{
	//Write codes scrOverview
	ui->scrOverview = lv_obj_create(NULL);
	lv_obj_set_size(ui->scrOverview, 480, 320);
	lv_obj_set_scrollbar_mode(ui->scrOverview, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->scrOverview, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrOverview, lv_color_hex(0x161d27), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_img_Header
	ui->scrOverview_img_Header = lv_img_create(ui->scrOverview);
	lv_obj_add_flag(ui->scrOverview_img_Header, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrOverview_img_Header, &_ebike_header_bg_alpha_480x51);
	lv_img_set_pivot(ui->scrOverview_img_Header, 50,50);
	lv_img_set_angle(ui->scrOverview_img_Header, 0);
	lv_obj_set_pos(ui->scrOverview_img_Header, 0, 0);
	lv_obj_set_size(ui->scrOverview_img_Header, 480, 51);
	lv_obj_set_scrollbar_mode(ui->scrOverview_img_Header, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_img_Header, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrOverview_img_Header, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Date
	ui->scrOverview_label_Date = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Date, "Jan 30,2024");
	lv_label_set_long_mode(ui->scrOverview_label_Date, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Date, 20, 2);
	lv_obj_set_size(ui->scrOverview_label_Date, 133, 18);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Date, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Date, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Title
	ui->scrOverview_label_Title = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Title, "OVERVIEW");
	lv_label_set_long_mode(ui->scrOverview_label_Title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Title, 155, 3);
	lv_obj_set_size(ui->scrOverview_label_Title, 143, 24);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Title, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Title, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Time
	ui->scrOverview_label_Time = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Time, "10:28 AM");
	lv_label_set_long_mode(ui->scrOverview_label_Time, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Time, 370, 3);
	lv_obj_set_size(ui->scrOverview_label_Time, 102, 18);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Time, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Time, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_img_GPS_Icon
	ui->scrOverview_img_GPS_Icon = lv_img_create(ui->scrOverview);
	lv_obj_add_flag(ui->scrOverview_img_GPS_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrOverview_img_GPS_Icon, &_ebike_gps_arrow_alpha_28x48);
	lv_img_set_pivot(ui->scrOverview_img_GPS_Icon, 50,50);
	lv_img_set_angle(ui->scrOverview_img_GPS_Icon, 0);
	lv_obj_set_pos(ui->scrOverview_img_GPS_Icon, 274, 60);
	lv_obj_set_size(ui->scrOverview_img_GPS_Icon, 28, 48);
	lv_obj_set_scrollbar_mode(ui->scrOverview_img_GPS_Icon, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_img_GPS_Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrOverview_img_GPS_Icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Distance
	ui->scrOverview_label_Distance = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Distance, "3.1");
	lv_label_set_long_mode(ui->scrOverview_label_Distance, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Distance, 329, 49);
	lv_obj_set_size(ui->scrOverview_label_Distance, 36, 19);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Distance, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Distance, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Distance, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Distance, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Distance, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Distance, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Direction
	ui->scrOverview_label_Direction = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Direction, "Turn right to");
	lv_label_set_long_mode(ui->scrOverview_label_Direction, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Direction, 320, 74);
	lv_obj_set_size(ui->scrOverview_label_Direction, 147, 18);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Direction, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Direction, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Direction, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Direction, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Direction, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Direction, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Direction, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Street
	ui->scrOverview_label_Street = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Street, "Ed Bluestein Blvd");
	lv_label_set_long_mode(ui->scrOverview_label_Street, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Street, 288, 97);
	lv_obj_set_size(ui->scrOverview_label_Street, 184, 17);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Street, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Street, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Street, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Street, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Street, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Street, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Street, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_ima_Travell_Icon
	ui->scrOverview_ima_Travell_Icon = lv_img_create(ui->scrOverview);
	lv_obj_add_flag(ui->scrOverview_ima_Travell_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrOverview_ima_Travell_Icon, &_ebike_icn_distance_travelled_alpha_21x14);
	lv_img_set_pivot(ui->scrOverview_ima_Travell_Icon, 50,50);
	lv_img_set_angle(ui->scrOverview_ima_Travell_Icon, 0);
	lv_obj_set_pos(ui->scrOverview_ima_Travell_Icon, 220, 130);
	lv_obj_set_size(ui->scrOverview_ima_Travell_Icon, 21, 14);
	lv_obj_set_scrollbar_mode(ui->scrOverview_ima_Travell_Icon, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_ima_Travell_Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrOverview_ima_Travell_Icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Travelled_1
	ui->scrOverview_label_Travelled_1 = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Travelled_1, "Distance \nTravelled");
	lv_label_set_long_mode(ui->scrOverview_label_Travelled_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Travelled_1, 250, 118);
	lv_obj_set_size(ui->scrOverview_label_Travelled_1, 94, 38);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Travelled_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Travelled_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Travelled_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Travelled_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Travelled_1, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Travelled_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Travelled_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Travelled_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Travelled_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Travelled_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Travelled_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Travelled_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Travelled_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Travelled_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Travelled_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Travelled_2
	ui->scrOverview_label_Travelled_2 = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Travelled_2, "12.7");
	lv_label_set_long_mode(ui->scrOverview_label_Travelled_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Travelled_2, 220, 157);
	lv_obj_set_size(ui->scrOverview_label_Travelled_2, 70, 25);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Travelled_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Travelled_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Travelled_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Travelled_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Travelled_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Travelled_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Travelled_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Travelled_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Travelled_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Travelled_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Travelled_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Travelled_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Travelled_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Travelled_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Travelled_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Travelled_3
	ui->scrOverview_label_Travelled_3 = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Travelled_3, "km");
	lv_label_set_long_mode(ui->scrOverview_label_Travelled_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Travelled_3, 300, 157);
	lv_obj_set_size(ui->scrOverview_label_Travelled_3, 40, 20);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Travelled_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Travelled_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Travelled_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Travelled_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Travelled_3, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Travelled_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Travelled_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Travelled_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Travelled_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Travelled_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Travelled_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Travelled_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Travelled_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Travelled_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Travelled_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Speed_3
	ui->scrOverview_label_Speed_3 = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Speed_3, "km/h");
	lv_label_set_long_mode(ui->scrOverview_label_Speed_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Speed_3, 410, 157);
	lv_obj_set_size(ui->scrOverview_label_Speed_3, 60, 17);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Speed_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Speed_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Speed_3, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Speed_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Speed_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Speed_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Speed_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Speed_2
	ui->scrOverview_label_Speed_2 = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Speed_2, "16.1");
	lv_label_set_long_mode(ui->scrOverview_label_Speed_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Speed_2, 357, 157);
	lv_obj_set_size(ui->scrOverview_label_Speed_2, 70, 25);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Speed_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Speed_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Speed_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Speed_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Speed_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Speed_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Speed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Speed_1
	ui->scrOverview_label_Speed_1 = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Speed_1, "Average \nSpeed");
	lv_label_set_long_mode(ui->scrOverview_label_Speed_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Speed_1, 387, 118);
	lv_obj_set_size(ui->scrOverview_label_Speed_1, 87, 41);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Speed_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Speed_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Speed_1, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Speed_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Speed_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Speed_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Speed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_img_Speed_Icon
	ui->scrOverview_img_Speed_Icon = lv_img_create(ui->scrOverview);
	lv_obj_add_flag(ui->scrOverview_img_Speed_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrOverview_img_Speed_Icon, &_ebike_icn_average_speed_alpha_21x14);
	lv_img_set_pivot(ui->scrOverview_img_Speed_Icon, 50,50);
	lv_img_set_angle(ui->scrOverview_img_Speed_Icon, 0);
	lv_obj_set_pos(ui->scrOverview_img_Speed_Icon, 357, 130);
	lv_obj_set_size(ui->scrOverview_img_Speed_Icon, 21, 14);
	lv_obj_set_scrollbar_mode(ui->scrOverview_img_Speed_Icon, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_img_Speed_Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrOverview_img_Speed_Icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_img_Remain_Icon
	ui->scrOverview_img_Remain_Icon = lv_img_create(ui->scrOverview);
	lv_obj_add_flag(ui->scrOverview_img_Remain_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrOverview_img_Remain_Icon, &_ebike_icn_remaining_distance_alpha_21x20);
	lv_img_set_pivot(ui->scrOverview_img_Remain_Icon, 50,50);
	lv_img_set_angle(ui->scrOverview_img_Remain_Icon, 0);
	lv_obj_set_pos(ui->scrOverview_img_Remain_Icon, 220, 193);
	lv_obj_set_size(ui->scrOverview_img_Remain_Icon, 21, 20);
	lv_obj_set_scrollbar_mode(ui->scrOverview_img_Remain_Icon, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_img_Remain_Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrOverview_img_Remain_Icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Remain_1
	ui->scrOverview_label_Remain_1 = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Remain_1, "Remain \nDistance");
	lv_label_set_long_mode(ui->scrOverview_label_Remain_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Remain_1, 250, 190);
	lv_obj_set_size(ui->scrOverview_label_Remain_1, 94, 38);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Remain_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Remain_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Remain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Remain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Remain_1, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Remain_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Remain_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Remain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Remain_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Remain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Remain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Remain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Remain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Remain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Remain_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Remain_3
	ui->scrOverview_label_Remain_3 = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Remain_3, "km");
	lv_label_set_long_mode(ui->scrOverview_label_Remain_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Remain_3, 300, 229);
	lv_obj_set_size(ui->scrOverview_label_Remain_3, 40, 20);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Remain_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Remain_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Remain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Remain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Remain_3, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Remain_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Remain_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Remain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Remain_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Remain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Remain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Remain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Remain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Remain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Remain_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Remain_2
	ui->scrOverview_label_Remain_2 = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Remain_2, "18.3");
	lv_label_set_long_mode(ui->scrOverview_label_Remain_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Remain_2, 220, 229);
	lv_obj_set_size(ui->scrOverview_label_Remain_2, 70, 25);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Remain_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Remain_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Remain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Remain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Remain_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Remain_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Remain_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Remain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Remain_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Remain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Remain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Remain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Remain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Remain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Remain_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_img_Elapsed_Icon
	ui->scrOverview_img_Elapsed_Icon = lv_img_create(ui->scrOverview);
	lv_obj_add_flag(ui->scrOverview_img_Elapsed_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrOverview_img_Elapsed_Icon, &_ebike_icn_elapsed_time_alpha_20x25);
	lv_img_set_pivot(ui->scrOverview_img_Elapsed_Icon, 50,50);
	lv_img_set_angle(ui->scrOverview_img_Elapsed_Icon, 0);
	lv_obj_set_pos(ui->scrOverview_img_Elapsed_Icon, 357, 193);
	lv_obj_set_size(ui->scrOverview_img_Elapsed_Icon, 20, 25);
	lv_obj_set_scrollbar_mode(ui->scrOverview_img_Elapsed_Icon, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_img_Elapsed_Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrOverview_img_Elapsed_Icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Elapsed_1
	ui->scrOverview_label_Elapsed_1 = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Elapsed_1, "Elapsed \nTime");
	lv_label_set_long_mode(ui->scrOverview_label_Elapsed_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Elapsed_1, 387, 190);
	lv_obj_set_size(ui->scrOverview_label_Elapsed_1, 85, 35);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Elapsed_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Elapsed_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Elapsed_1, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Elapsed_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Elapsed_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Elapsed_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Elapsed_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Elapsed_2
	ui->scrOverview_label_Elapsed_2 = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Elapsed_2, "46:28");
	lv_label_set_long_mode(ui->scrOverview_label_Elapsed_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Elapsed_2, 357, 229);
	lv_obj_set_size(ui->scrOverview_label_Elapsed_2, 70, 25);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Elapsed_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Elapsed_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Elapsed_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Elapsed_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Elapsed_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Elapsed_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Elapsed_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_line_V_Seperator
	ui->scrOverview_line_V_Seperator = lv_line_create(ui->scrOverview);
	static lv_point_t scrOverview_line_V_Seperator[] ={{0, 0},{0, 240},};
	lv_line_set_points(ui->scrOverview_line_V_Seperator, scrOverview_line_V_Seperator, 2);
	lv_obj_set_pos(ui->scrOverview_line_V_Seperator, 345, 119);
	lv_obj_set_size(ui->scrOverview_line_V_Seperator, 5, 138);
	lv_obj_set_scrollbar_mode(ui->scrOverview_line_V_Seperator, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_line_V_Seperator, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_line_width(ui->scrOverview_line_V_Seperator, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->scrOverview_line_V_Seperator, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->scrOverview_line_V_Seperator, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_rounded(ui->scrOverview_line_V_Seperator, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_img_Footer
	ui->scrOverview_img_Footer = lv_img_create(ui->scrOverview);
	lv_obj_add_flag(ui->scrOverview_img_Footer, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrOverview_img_Footer, &_ebike_footer_bg_alpha_480x35);
	lv_img_set_pivot(ui->scrOverview_img_Footer, 50,50);
	lv_img_set_angle(ui->scrOverview_img_Footer, 0);
	lv_obj_set_pos(ui->scrOverview_img_Footer, 0, 279);
	lv_obj_set_size(ui->scrOverview_img_Footer, 480, 35);
	lv_obj_set_scrollbar_mode(ui->scrOverview_img_Footer, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_img_Footer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrOverview_img_Footer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_line_H_Seperator
	ui->scrOverview_line_H_Seperator = lv_line_create(ui->scrOverview);
	static lv_point_t scrOverview_line_H_Seperator[] ={{0, 0},{240, 0},};
	lv_line_set_points(ui->scrOverview_line_H_Seperator, scrOverview_line_H_Seperator, 2);
	lv_obj_set_pos(ui->scrOverview_line_H_Seperator, 225, 180);
	lv_obj_set_size(ui->scrOverview_line_H_Seperator, 240, 1);
	lv_obj_set_scrollbar_mode(ui->scrOverview_line_H_Seperator, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_line_H_Seperator, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_line_width(ui->scrOverview_line_H_Seperator, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->scrOverview_line_H_Seperator, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->scrOverview_line_H_Seperator, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_rounded(ui->scrOverview_line_H_Seperator, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Indicator_L
	ui->scrOverview_label_Indicator_L = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Indicator_L, "");
	lv_label_set_long_mode(ui->scrOverview_label_Indicator_L, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Indicator_L, 181, 301);
	lv_obj_set_size(ui->scrOverview_label_Indicator_L, 28, 8);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Indicator_L, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Indicator_L, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Indicator_L, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Indicator_L, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Indicator_L, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Indicator_L, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Indicator_L, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Indicator_L, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrOverview_label_Indicator_L, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Indicator_L, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Indicator_M
	ui->scrOverview_label_Indicator_M = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Indicator_M, "");
	lv_label_set_long_mode(ui->scrOverview_label_Indicator_M, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Indicator_M, 229, 301);
	lv_obj_set_size(ui->scrOverview_label_Indicator_M, 28, 8);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Indicator_M, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Indicator_M, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Indicator_M, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Indicator_M, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Indicator_M, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Indicator_M, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Indicator_M, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Indicator_M, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrOverview_label_Indicator_M, lv_color_hex(0xa8a6ad), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Indicator_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Indicator_R
	ui->scrOverview_label_Indicator_R = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Indicator_R, "");
	lv_label_set_long_mode(ui->scrOverview_label_Indicator_R, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Indicator_R, 277, 301);
	lv_obj_set_size(ui->scrOverview_label_Indicator_R, 28, 8);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Indicator_R, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Indicator_R, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Indicator_R, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Indicator_R, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Indicator_R, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Indicator_R, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Indicator_R, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Indicator_R, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrOverview_label_Indicator_R, lv_color_hex(0xa8a6ad), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Indicator_R, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_Distance_Unit
	ui->scrOverview_label_Distance_Unit = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_Distance_Unit, "KM");
	lv_label_set_long_mode(ui->scrOverview_label_Distance_Unit, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_Distance_Unit, 368, 49);
	lv_obj_set_size(ui->scrOverview_label_Distance_Unit, 48, 19);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_Distance_Unit, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_Distance_Unit, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_Distance_Unit, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_Distance_Unit, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_Distance_Unit, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_Distance_Unit, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_Distance_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_meter_Speed
	ui->scrOverview_meter_Speed = lv_meter_create(ui->scrOverview);
	// add scale scrOverview_meter_Speed_scale_1
	lv_meter_scale_t *scrOverview_meter_Speed_scale_1 = lv_meter_add_scale(ui->scrOverview_meter_Speed);
	lv_meter_set_scale_ticks(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1, 51, 3, 10, lv_color_hex(0x4a69ff));
	lv_meter_set_scale_major_ticks(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1, 5, 3, 14, lv_color_hex(0xffffff), 15);
	lv_meter_set_scale_range(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1, 0, 50, 300, 120);

	// add arc for scrOverview_meter_Speed_scale_1
	lv_meter_indicator_t *scrOverview_meter_Speed_scale_1_arc_0;
	scrOverview_meter_Speed_scale_1_arc_0 = lv_meter_add_arc(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1, 10, lv_color_hex(0xb3dc00), 0);
	lv_meter_set_indicator_start_value(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1_arc_0, 0);
	lv_meter_set_indicator_end_value(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1_arc_0, 20);

	// add arc for scrOverview_meter_Speed_scale_1
	lv_meter_indicator_t *scrOverview_meter_Speed_scale_1_arc_1;
	scrOverview_meter_Speed_scale_1_arc_1 = lv_meter_add_arc(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1, 10, lv_color_hex(0x00d6c2), 0);
	lv_meter_set_indicator_start_value(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1_arc_1, 20);
	lv_meter_set_indicator_end_value(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1_arc_1, 35);

	// add arc for scrOverview_meter_Speed_scale_1
	lv_meter_indicator_t *scrOverview_meter_Speed_scale_1_arc_2;
	scrOverview_meter_Speed_scale_1_arc_2 = lv_meter_add_arc(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1, 10, lv_color_hex(0x950080), 0);
	lv_meter_set_indicator_start_value(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1_arc_2, 35);
	lv_meter_set_indicator_end_value(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1_arc_2, 50);

	// add needle line for scrOverview_meter_Speed_scale_1.
	ui->scrOverview_meter_Speed_scale_1_ndline_0 = lv_meter_add_needle_line(ui->scrOverview_meter_Speed, scrOverview_meter_Speed_scale_1, 4, lv_color_hex(0xff0000), 1);
	lv_meter_set_indicator_value(ui->scrOverview_meter_Speed, ui->scrOverview_meter_Speed_scale_1_ndline_0, 20);
	lv_obj_set_pos(ui->scrOverview_meter_Speed, 9, 60);
	lv_obj_set_size(ui->scrOverview_meter_Speed, 200, 200);
	lv_obj_set_scrollbar_mode(ui->scrOverview_meter_Speed, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_meter_Speed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->scrOverview_meter_Speed, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->scrOverview_meter_Speed, lv_color_hex(0x142c58), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_meter_Speed, 100, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->scrOverview_meter_Speed, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->scrOverview_meter_Speed, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->scrOverview_meter_Speed, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_meter_Speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for scrOverview_meter_Speed, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->scrOverview_meter_Speed, lv_color_hex(0xffffff), LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_meter_Speed, &lv_font_montserratMedium_12, LV_PART_TICKS|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_MeterSpeed
	ui->scrOverview_label_MeterSpeed = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_MeterSpeed, "20");
	lv_label_set_long_mode(ui->scrOverview_label_MeterSpeed, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_MeterSpeed, 90, 190);
	lv_obj_set_size(ui->scrOverview_label_MeterSpeed, 39, 25);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_MeterSpeed, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_MeterSpeed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_MeterSpeed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_MeterSpeed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_MeterSpeed, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_MeterSpeed, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_MeterSpeed, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_MeterSpeed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_MeterSpeed, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_MeterSpeed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_MeterSpeed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_MeterSpeed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_MeterSpeed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_MeterSpeed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_MeterSpeed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_label_MeterSpeed_Unit
	ui->scrOverview_label_MeterSpeed_Unit = lv_label_create(ui->scrOverview);
	lv_label_set_text(ui->scrOverview_label_MeterSpeed_Unit, "Km/h");
	lv_label_set_long_mode(ui->scrOverview_label_MeterSpeed_Unit, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->scrOverview_label_MeterSpeed_Unit, 82, 215);
	lv_obj_set_size(ui->scrOverview_label_MeterSpeed_Unit, 55, 24);
	lv_obj_set_scrollbar_mode(ui->scrOverview_label_MeterSpeed_Unit, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_label_MeterSpeed_Unit, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->scrOverview_label_MeterSpeed_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->scrOverview_label_MeterSpeed_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->scrOverview_label_MeterSpeed_Unit, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrOverview_label_MeterSpeed_Unit, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->scrOverview_label_MeterSpeed_Unit, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->scrOverview_label_MeterSpeed_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->scrOverview_label_MeterSpeed_Unit, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->scrOverview_label_MeterSpeed_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->scrOverview_label_MeterSpeed_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->scrOverview_label_MeterSpeed_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->scrOverview_label_MeterSpeed_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->scrOverview_label_MeterSpeed_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->scrOverview_label_MeterSpeed_Unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrOverview_img_Logo
	ui->scrOverview_img_Logo = lv_img_create(ui->scrOverview);
	lv_obj_add_flag(ui->scrOverview_img_Logo, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrOverview_img_Logo, &_logo_alpha_49x10);
	lv_img_set_pivot(ui->scrOverview_img_Logo, 50,50);
	lv_img_set_angle(ui->scrOverview_img_Logo, 0);
	lv_obj_set_pos(ui->scrOverview_img_Logo, 84, 239);
	lv_obj_set_size(ui->scrOverview_img_Logo, 49, 10);
	lv_obj_set_scrollbar_mode(ui->scrOverview_img_Logo, LV_SCROLLBAR_MODE_OFF);

	//Write style for scrOverview_img_Logo, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->scrOverview_img_Logo, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->scrOverview);

	
        ebike_timer_create();
	//Init events for screen.
	events_init_scrOverview(ui);
}
