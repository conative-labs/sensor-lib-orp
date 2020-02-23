![Jenkins](https://img.shields.io/jenkins/build?jobUrl=https%3A%2F%2Fbuild.conativelabs.com%2Fjob%2Fsensor-lib-orp%2Fjob%2Fmaster&style=plastic)
![Jenkins Coverage](https://img.shields.io/jenkins/coverage/cobertura?jobUrl=https%3A%2F%2Fbuild.conativelabs.com%2Fjob%2Fsensor-lib-orp%2Fjob%2Fmaster%2F&style=plastic)
# ORP Sensor library
This library is made to manage the usage of a Oxidation-reduction potential Probe.

# How it works!
The orp value is measured by reading the voltage across the orp sensor in millivolts.

The `lib_orp_cmd` is used to recieve cmds from the *parser or any caller library* and return the required output, To read sensor data, use `orp_read` command, you can use calibrate cmds `orp_cal_origin` to calibrate the sensor at runtime and use `orp_cal_clear` to restore the default calibration, also you can get the calibration status using `orp_cal_get` it should return `1` if calibrated, lastly `orp_reset` resets all the device params back to default.

Notice: `MAGIC_NUMBER_DEFAULT` is used for data integrity check.

# How to use!
Copy lib_orp_config.template.h to lib_orp_config.h and implement the sensor_mv function.
sensor_mv should return the voltage accross the probe in millitvolts.

License
----

GNU General Public License v3.0

***Copyright (C) 2020 Conative Labs***
