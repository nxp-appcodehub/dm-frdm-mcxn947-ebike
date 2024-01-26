/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * custom.h
 *
 *  Created on: July 29, 2020
 *      Author: nxf53801
 */

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

void custom_init(lv_ui *ui);
void ebike_timer_create(void);
void jumpToOverview(void);
void jumpToRide1(void);
void jumpToRide2(void);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
