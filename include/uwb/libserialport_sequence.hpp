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
#include <poll.h>
#include <fcntl.h>

class Application;

/* Helper function for error handling. */
int check(enum sp_return result);

/* Helper function to give a name for each parity mode. */
const char *parity_name(enum sp_parity parity);

int openFifoFileDescriptor(std::string fifo_path_string);

int configureFifo(struct pollfd &poll_fifo, int &fd);

void pollInEvent(struct pollfd &poll_fifo, int &fd, UwbMessages &messages);

struct sp_port *configureLibserialport();

int UwbDeviceProcess(Application &app);

void changingMessegeRequestFunction(UwbMessages &messages, std::vector<uint8_t> &response, std::uint8_t *&current_request, std::uint16_t &current_read_size, std::uint8_t &current_write_size, std::uint16_t &delay, std::uint16_t &uart_read_timeout, bool &dwm_upd_rate_set_flag);