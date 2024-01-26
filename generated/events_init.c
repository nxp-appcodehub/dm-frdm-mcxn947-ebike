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

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

static void scrOverview_event_handler (lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  
  switch (code) 
  {
    case LV_EVENT_GESTURE:
    {
      lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
      
      switch(dir)
      {
        case LV_DIR_LEFT:
        {
          lv_indev_wait_release(lv_indev_get_act());
          jumpToRide2();
        }
        break;
        
        case LV_DIR_RIGHT:
        {
          lv_indev_wait_release(lv_indev_get_act());
          jumpToRide1();
        }
        break;
        
        default:
        {
        }
        break;
      }
    }
    break;
      
    default:
    {
    }
    break;
  }
}

void events_init_scrOverview(lv_ui *ui)
{
  lv_obj_add_event_cb(ui->scrOverview, scrOverview_event_handler, LV_EVENT_ALL, NULL);
}

static void scrRide1_event_handler (lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  
  switch (code) 
  {
    case LV_EVENT_GESTURE:
    {
      lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
      
      switch(dir)
      {
        case LV_DIR_LEFT:
        {
          lv_indev_wait_release(lv_indev_get_act());
          jumpToOverview();
        }
        break;
        
        case LV_DIR_RIGHT:
        {
          lv_indev_wait_release(lv_indev_get_act());
          jumpToRide2();
        }
        break;
        
        default:
        {
        }
        break;
      }
    }
    break;
      
    default:
    {
    }
    break;
  }
}

void events_init_scrRide1(lv_ui *ui)
{
  lv_obj_add_event_cb(ui->scrRide1, scrRide1_event_handler, LV_EVENT_ALL, NULL);
}

static void scrRide2_event_handler (lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  
  switch (code) 
  {
    case LV_EVENT_GESTURE:
    {
      lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
      
      switch(dir)
      {
        case LV_DIR_LEFT:
        {
          lv_indev_wait_release(lv_indev_get_act());
          jumpToRide1();
        }
        break;
        
        case LV_DIR_RIGHT:
        {
          lv_indev_wait_release(lv_indev_get_act());
          jumpToOverview();
        }
        break;
        
        default:
        {
        }
        break;
      }
    }
    break;
      
    default:
    {
    }
    break;
  }
}

void events_init_scrRide2(lv_ui *ui)
{
  lv_obj_add_event_cb(ui->scrRide2, scrRide2_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{

}
