#pragma once

#include <dwm1001_messages.hpp>
#include <libserialport.h>

#include <array>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

class Application;

int check(enum sp_return result);

const char *parity_name(enum sp_parity parity);

int UwbDeviceProcess(Application &app);