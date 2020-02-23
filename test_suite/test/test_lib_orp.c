#include "unity.h"
#include "lib_orp.h"

#include "mock_lib_orp_config_test.h"

#define MAGIC_NUMBER_DEFAULT 0x66


void setUP(void)
{
}

void tearDown(void)
{
}

void test_lib_orp_init_withMagicNumberAlreadySet(void)
{
  lib_orp_params_t params;

  params.shift_mv = 13221;
  params.magic_number = MAGIC_NUMBER_DEFAULT; // mock the magic number 
  lib_orp_init(&params);

  TEST_ASSERT_EQUAL_FLOAT(13221, params.shift_mv);
}

void test_lib_orp_init_withoutMagicNumberAlreadySet(void)
{
  lib_orp_params_t params;

  params.shift_mv = 13221;
  lib_orp_init(&params);

  TEST_ASSERT_EQUAL_FLOAT(0, params.shift_mv);
}

void test_lib_orp_cmd_ReadWithNoShift(void)
{
  lib_orp_params_t params;
  lib_orp_reading_t reading;
  sensor_mv_ExpectAndReturn(1000);
  
  lib_orp_init(&params);

  lib_orp_cmd(orp_read, &reading);

  TEST_ASSERT_EQUAL_FLOAT(1000, reading);
}

void test_lib_orp_cmd_ReadWithShift(void)
{
  lib_orp_params_t params;
  lib_orp_reading_t reading;
  sensor_mv_ExpectAndReturn(1000);
  
  lib_orp_init(&params);
  params.shift_mv = 100;
  lib_orp_cmd(orp_read, &reading);

  TEST_ASSERT_EQUAL_FLOAT(900, reading);
}

/* void test_lib_orp_cmd_ACFreqSetAndGet(void) */
/* { */
/*   lib_orp_params_t params; */
/*   lib_orp_shift_mv_t temp = 60, temp_val; */
/*   lib_orp_init(&params); */

/*   lib_orp_cmd(orp_set_shift_mv, &temp); */
/*   lib_orp_cmd(orp_get_shift_mv, &temp_val); */

/*   TEST_ASSERT_EQUAL_FLOAT(60, temp_val); */
/* } */

void test_lib_orp_cmd_OrpCal(void)
{
  lib_orp_params_t params;
  lib_orp_mv_t temp = 100;

  sensor_mv_ExpectAndReturn(1000);
    
  lib_orp_init(&params);
  lib_orp_cmd(orp_cal_origin, &temp);

  TEST_ASSERT_EQUAL_FLOAT(900, params.shift_mv);
}


void test_lib_orp_cmd_ShiftCalGetNotCalib(void)
{
  lib_orp_params_t params;
  char temp;
  lib_orp_init(&params);

  lib_orp_cmd(orp_cal_get, &temp);

  TEST_ASSERT_EQUAL_INT(0, temp);
}

void test_lib_orp_cmd_ShiftCalGetCalib(void)
{
  lib_orp_params_t params;
  char temp;
  lib_orp_init(&params);
  params.shift_mv = 12; // any number than default
  lib_orp_cmd(orp_cal_get, &temp);

  TEST_ASSERT_EQUAL_INT(1, temp);
}

void test_lib_orp_cmd_Clear(void)
{
  lib_orp_params_t params;

  lib_orp_init(&params);
  params.shift_mv = 13221;
  params.magic_number = 0x50;
  lib_orp_cmd(orp_cal_clear, NULL);

  TEST_ASSERT_EQUAL(0x50, params.magic_number);
  TEST_ASSERT_EQUAL_FLOAT(0, params.shift_mv);
}


void test_lib_orp_cmd_Reset(void)
{
  lib_orp_params_t params;

  lib_orp_init(&params);
  params.shift_mv = 13221;
  params.magic_number = 0x50;
  lib_orp_cmd(orp_reset, NULL);

  TEST_ASSERT_EQUAL(MAGIC_NUMBER_DEFAULT, params.magic_number);
  TEST_ASSERT_EQUAL_FLOAT(0, params.shift_mv);
}
