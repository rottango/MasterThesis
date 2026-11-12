#pragma once

#include <libserialport.h>
#include <position_sample.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>


int check(enum sp_return result);

const char *parity_name(enum sp_parity parity);

int UwbDeviceProcess();