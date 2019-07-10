#ifndef lib_orp_h
#define lib_orp_h

#include <stdint.h>

typedef float lib_orp_mv_t;
typedef lib_orp_mv_t lib_orp_reading_t;

typedef struct lib_orp_params_t {
  uint8_t magic_number;
  lib_orp_mv_t shift_mv;
}lib_orp_params_t;

typedef enum lib_orp_cmd_t {
                           orp_read,
                           orp_cal_origin,
                           orp_cal_get,
                           orp_cal_clear,
                           orp_reset,
} lib_orp_cmd_t;

void lib_orp_init(lib_orp_params_t *params_struct);
void lib_orp_cmd(lib_orp_cmd_t command, void *output_buffer);

#endif
