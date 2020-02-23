/*
  Copyright (C) 2020 Conative Labs
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include "lib_orp.h"
#ifdef TEST
#include "lib_orp_config_test.h"
#else
#include "lib_orp_config.h"
#endif

#define MAGIC_NUMBER_DEFAULT 0x66 // 8 bit random number prefered to be unique, for integrity check of params
#define ORIGIN_SHIFT_MV_DEFAULT 0
static lib_orp_params_t *params;

static void calibration_set_default(void) {
  params->shift_mv = ORIGIN_SHIFT_MV_DEFAULT;
}

static void params_set_default(void) {
	params->magic_number = MAGIC_NUMBER_DEFAULT;
	calibration_set_default();
}

void lib_orp_init(lib_orp_params_t *ext_params){
  params = ext_params;
  if(params->magic_number != MAGIC_NUMBER_DEFAULT)
    params_set_default();
}

void lib_orp_cmd(lib_orp_cmd_t cmd, void *buffer) {
  lib_orp_mv_t orp_value_mv;
	switch(cmd) {
  case orp_read:
    orp_value_mv = sensor_mv();
    *(lib_orp_mv_t *)buffer = orp_value_mv - params->shift_mv;
    break;
  case orp_cal_origin:
	    orp_value_mv = sensor_mv();
	    params->shift_mv = orp_value_mv - *(lib_orp_mv_t *)buffer;
    break;
  case orp_cal_get:
	  ((uint8_t *)buffer)[0] = 0;
    if(params->shift_mv != ORIGIN_SHIFT_MV_DEFAULT)
    	((uint8_t *)buffer)[0] = 1;
    break;
  case orp_cal_clear:
    calibration_set_default();
    break;
  case orp_reset:
    params_set_default();
    break;
  }
}
