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

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *scrOverview;
	bool scrOverview_del;
	lv_obj_t *scrOverview_img_Header;
	lv_obj_t *scrOverview_label_Date;
	lv_obj_t *scrOverview_label_Title;
	lv_obj_t *scrOverview_label_Time;
	lv_obj_t *scrOverview_img_GPS_Icon;
	lv_obj_t *scrOverview_label_Distance;
	lv_obj_t *scrOverview_label_Direction;
	lv_obj_t *scrOverview_label_Street;
	lv_obj_t *scrOverview_ima_Travell_Icon;
	lv_obj_t *scrOverview_label_Travelled_1;
	lv_obj_t *scrOverview_label_Travelled_2;
	lv_obj_t *scrOverview_label_Travelled_3;
	lv_obj_t *scrOverview_label_Speed_3;
	lv_obj_t *scrOverview_label_Speed_2;
	lv_obj_t *scrOverview_label_Speed_1;
	lv_obj_t *scrOverview_img_Speed_Icon;
	lv_obj_t *scrOverview_img_Remain_Icon;
	lv_obj_t *scrOverview_label_Remain_1;
	lv_obj_t *scrOverview_label_Remain_3;
	lv_obj_t *scrOverview_label_Remain_2;
	lv_obj_t *scrOverview_img_Elapsed_Icon;
	lv_obj_t *scrOverview_label_Elapsed_1;
	lv_obj_t *scrOverview_label_Elapsed_2;
	lv_obj_t *scrOverview_line_V_Seperator;
	lv_obj_t *scrOverview_img_Footer;
	lv_obj_t *scrOverview_line_H_Seperator;
	lv_obj_t *scrOverview_label_Indicator_L;
	lv_obj_t *scrOverview_label_Indicator_M;
	lv_obj_t *scrOverview_label_Indicator_R;
	lv_obj_t *scrOverview_label_Distance_Unit;
	lv_obj_t *scrOverview_meter_Speed;
	lv_meter_indicator_t *scrOverview_meter_Speed_scale_1_ndline_0;
	lv_obj_t *scrOverview_label_MeterSpeed;
	lv_obj_t *scrOverview_label_MeterSpeed_Unit;
	lv_obj_t *scrOverview_img_Logo;
	lv_obj_t *scrRide1;
	bool scrRide1_del;
	lv_obj_t *scrRide1_img_Header;
	lv_obj_t *scrRide1_label_Time;
	lv_obj_t *scrRide1_label_Title;
	lv_obj_t *scrRide1_label_Date;
	lv_obj_t *scrRide1_img_Footer;
	lv_obj_t *scrRide1_label_Indicator_R;
	lv_obj_t *scrRide1_label_Indicator_M;
	lv_obj_t *scrRide1_label_Indicator_L;
	lv_obj_t *scrRide1_label_Distance_1;
	lv_obj_t *scrRide1_img_Distance;
	lv_obj_t *scrRide1_label_Distance_3;
	lv_obj_t *scrRide1_label_Distance_2;
	lv_obj_t *scrRide1_line_H_Seperator_1;
	lv_obj_t *scrRide1_label_Speed_3;
	lv_obj_t *scrRide1_label_Speed_2;
	lv_obj_t *scrRide1_label_Speed_1;
	lv_obj_t *scrRide1_img_Speed;
	lv_obj_t *scrRide1_line_H_Seperator_2;
	lv_obj_t *scrRide1_img_Eleva_Gain;
	lv_obj_t *scrRide1_label_Gain_1;
	lv_obj_t *scrRide1_line_V_Seperator;
	lv_obj_t *scrRide1_label_Gain_2;
	lv_obj_t *scrRide1_label_Gain_3;
	lv_obj_t *scrRide1_label_Lost_3;
	lv_obj_t *scrRide1_label_Lost_2;
	lv_obj_t *scrRide1_label_Lost_1;
	lv_obj_t *scrRide1_img_Eleva_Lost;
	lv_obj_t *scrRide1_chart_Elevation;
	lv_obj_t *scrRide1_label_Elev_H;
	lv_obj_t *scrRide1_label_Elev_V;
	lv_obj_t *scrRide1_label_Elev_Title;
	lv_obj_t *scrRide1_label_Eleva_Content;
	lv_obj_t *scrRide1_label_Eleva_Num;
	lv_obj_t *scrRide1_label_Eleva_Unit;
	lv_obj_t *scrRide2;
	bool scrRide2_del;
	lv_obj_t *scrRide2_img_Header;
	lv_obj_t *scrRide2_label_Date;
	lv_obj_t *scrRide2_label_Title;
	lv_obj_t *scrRide2_label_Time;
	lv_obj_t *scrRide2_img_GPS_Icon;
	lv_obj_t *scrRide2_label_Distance;
	lv_obj_t *scrRide2_label_Direction;
	lv_obj_t *scrRide2_label_Street;
	lv_obj_t *scrRide2_ima_Calories_Icon;
	lv_obj_t *scrRide2_label_Calories_1;
	lv_obj_t *scrRide2_label_Calories_2;
	lv_obj_t *scrRide2_label_Calories_3;
	lv_obj_t *scrRide2_label_Heart_3;
	lv_obj_t *scrRide2_label_Heart_2;
	lv_obj_t *scrRide2_label_Heart_1;
	lv_obj_t *scrRide2_img_Heart_Icon;
	lv_obj_t *scrRide2_img_Cadence_Icon;
	lv_obj_t *scrRide2_label_Cadence_1;
	lv_obj_t *scrRide2_label_Cadence_3;
	lv_obj_t *scrRide2_label_Cadence_2;
	lv_obj_t *scrRide2_img_Elapsed_Icon;
	lv_obj_t *scrRide2_label_Elapsed_1;
	lv_obj_t *scrRide2_label_Elapsed_2;
	lv_obj_t *scrRide2_line_V_Seperator;
	lv_obj_t *scrRide2_img_Footer;
	lv_obj_t *scrRide2_line_H_Seperator;
	lv_obj_t *scrRide2_label_Indicator_L;
	lv_obj_t *scrRide2_label_Indicator_M;
	lv_obj_t *scrRide2_label_Indicator_R;
	lv_obj_t *scrRide2_label_Distance_Unit;
	lv_obj_t *scrRide2_arc_Watts;
	lv_obj_t *scrRide2_label_Watts_Unit;
	lv_obj_t *scrRide2_label_Watts_Num;
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_scrOverview(lv_ui *ui);
void setup_scr_scrRide1(lv_ui *ui);
void setup_scr_scrRide2(lv_ui *ui);
LV_IMG_DECLARE(_ebike_header_bg_alpha_480x51);
LV_IMG_DECLARE(_ebike_gps_arrow_alpha_28x48);
LV_IMG_DECLARE(_ebike_icn_distance_travelled_alpha_21x14);
LV_IMG_DECLARE(_ebike_icn_average_speed_alpha_21x14);
LV_IMG_DECLARE(_ebike_icn_remaining_distance_alpha_21x20);
LV_IMG_DECLARE(_ebike_icn_elapsed_time_alpha_20x25);
LV_IMG_DECLARE(_ebike_footer_bg_alpha_480x35);
LV_IMG_DECLARE(_logo_alpha_49x10);
LV_IMG_DECLARE(_ebike_header_bg_alpha_480x51);
LV_IMG_DECLARE(_ebike_footer_bg_alpha_480x35);
LV_IMG_DECLARE(_ebike_icn_distance_travelled_big_alpha_42x28);
LV_IMG_DECLARE(_ebike_icn_average_speed_big_alpha_40x31);
LV_IMG_DECLARE(_ebike_icn_elevation_gained_alpha_22x18);
LV_IMG_DECLARE(_ebike_icn_elevation_lost_alpha_22x18);
LV_IMG_DECLARE(_ebike_header_bg_alpha_480x51);
LV_IMG_DECLARE(_ebike_gps_arrow_alpha_28x48);
LV_IMG_DECLARE(_ebike_icn_calories_burned_alpha_19x21);
LV_IMG_DECLARE(_ebike_icn_heart_rate_alpha_24x21);
LV_IMG_DECLARE(_ebike_icn_round_per_minute_alpha_20x20);
LV_IMG_DECLARE(_ebike_icn_elapsed_time_alpha_20x25);
LV_IMG_DECLARE(_ebike_footer_bg_alpha_480x35);

LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_20)
LV_FONT_DECLARE(lv_font_montserratMedium_12)


#ifdef __cplusplus
}
#endif
#endif
