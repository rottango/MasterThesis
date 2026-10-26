#include <libserialport.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <iomanip>

/* Helper function for error handling. */
int check(enum sp_return result)
{
	/* For this example we'll just exit on any error by calling abort(). */
	char *error_message;

	switch (result) {
	case SP_ERR_ARG:
		printf("Error: Invalid argument.\n");
		abort();
	case SP_ERR_FAIL:
		error_message = sp_last_error_message();
		printf("Error: Failed: %s\n", error_message);
		sp_free_error_message(error_message);
		abort();
	case SP_ERR_SUPP:
		printf("Error: Not supported.\n");
		abort();
	case SP_ERR_MEM:
		printf("Error: Couldn't allocate memory.\n");
		abort();
	case SP_OK:
	default:
		return result;
	}
}

/* Helper function to give a name for each parity mode. */
const char *parity_name(enum sp_parity parity)
{
	switch (parity) {
	case SP_PARITY_INVALID:
		return "(Invalid)";
	case SP_PARITY_NONE:
		return "None";
	case SP_PARITY_ODD:
		return "Odd";
	case SP_PARITY_EVEN:
		return "Even";
	case SP_PARITY_MARK:
		return "Mark";
	case SP_PARITY_SPACE:
		return "Space";
	default:
		return NULL;
	}
}

/* Example of how to get a list of serial ports on the system.
 *
 * This example file is released to the public domain. */

int main(int argc, char **argv)
{
	char *uwb_port_name;
	/* A pointer to a null-terminated array of pointers to
	 * struct sp_port, which will contain the ports found.*/
	struct sp_port **port_list;

	printf("Getting port list.\n");

	/* Call sp_list_ports() to get the ports. The port_list
	 * pointer will be updated to refer to the array created. */
	enum sp_return result = sp_list_ports(&port_list);

	if (result != SP_OK) {
		printf("sp_list_ports() failed!\n");
		return -1;
	}

	/* Iterate through the ports. When port_list[i] is NULL
	 * this indicates the end of the list. */
	int i;
	for (i = 0; port_list[i] != NULL; i++) {
		struct sp_port *port = port_list[i];

		/* Get the name of the port. */
		char *port_name = sp_get_port_name(port);
		uwb_port_name = strdup(port_name); // assume the one device connected is the actual uwb
		printf("Found port: %s\n", uwb_port_name);
	}

	printf("Found %d ports.\n", i);

	printf("Freeing port list.\n");

	/* Free the array created by sp_list_ports(). */
	sp_free_port_list(port_list);

	/* Note that this will also free all the sp_port structures
	 * it points to. If you want to keep one of them (e.g. to
	 * use that port in the rest of your program), take a copy
	 * of it first using sp_copy_port(). */

//=============================================
     
	/* A pointer to a struct sp_port, which will refer to
	 * the port found. */
	struct sp_port *port;

	printf("Looking for port %s.\n", uwb_port_name);

	/* Call sp_get_port_by_name() to find the port. The port
	 * pointer will be updated to refer to the port found. */
	enum sp_return result_info = sp_get_port_by_name(uwb_port_name, &port);

	if (result_info != SP_OK) {
		printf("sp_get_port_by_name() failed!\n");
		return -1;
	}

	/* Display some basic information about the port. */
	printf("Port name: %s\n", sp_get_port_name(port));
	printf("Description: %s\n", sp_get_port_description(port));

	/* Identify the transport which this port is connected through,
	 * e.g. native port, USB or Bluetooth. */
	enum sp_transport transport = sp_get_port_transport(port);

	if (transport == SP_TRANSPORT_NATIVE) {
		/* This is a "native" port, usually directly connected
		 * to the system rather than some external interface. */
		printf("Type: Native\n");
	} else if (transport == SP_TRANSPORT_USB) {
		/* This is a USB to serial converter of some kind. */
		printf("Type: USB\n");

		/* Display string information from the USB descriptors. */
		printf("Manufacturer: %s\n", sp_get_port_usb_manufacturer(port));
		printf("Product: %s\n", sp_get_port_usb_product(port));
		printf("Serial: %s\n", sp_get_port_usb_serial(port));

		/* Display USB vendor and product IDs. */
		int usb_vid, usb_pid;
		sp_get_port_usb_vid_pid(port, &usb_vid, &usb_pid);
		printf("VID: %04X PID: %04X\n", usb_vid, usb_pid);

		/* Display bus and address. */
		int usb_bus, usb_address;
		sp_get_port_usb_bus_address(port, &usb_bus, &usb_address);
		printf("Bus: %d Address: %d\n", usb_bus, usb_address);
	} else if (transport == SP_TRANSPORT_BLUETOOTH) {
		/* This is a Bluetooth serial port. */
		printf("Type: Bluetooth\n");

		/* Display Bluetooth MAC address. */
		printf("MAC: %s\n", sp_get_port_bluetooth_address(port));
	}

//=============================================

	/* Display some basic information about the port. */
	printf("Port name: %s\n", sp_get_port_name(port));
	printf("Description: %s\n", sp_get_port_description(port));

	/* The port must be open to access its configuration. */
	printf("Opening port.\n");
	check(sp_open(port, SP_MODE_READ_WRITE));

	/* There are two ways to access a port's configuration:
	 *
	 * 1. You can read and write a whole configuration (all settings at
	 *    once) using sp_get_config() and sp_set_config(). This is handy
	 *    if you want to change between some preset combinations, or save
	 *    and restore an existing configuration. It also ensures the
	 *    changes are made together, via an efficient set of calls into
	 *    the OS - in some cases a single system call can be used.
	 *
	 *    Use accessor functions like sp_get_config_baudrate() and
	 *    sp_set_config_baudrate() to get and set individual settings
	 *    from a configuration.
	 *
	 *    Configurations are allocated using sp_new_config() and freed
	 *    with sp_free_config(). You need to manage them yourself.
	 *
	 * 2. As a shortcut, you can set individual settings on a port
	 *    directly by calling functions like sp_set_baudrate() and
	 *    sp_set_parity(). This saves you the work of allocating
	 *    a temporary config, setting it up, applying it to a port
	 *    and then freeing it.
	 *
	 * In this example we'll do a bit of both: apply some initial settings
	 * to the port, read out that config and display it, then switch to a
	 * different configuration and back using sp_set_config(). */

	/* First let's set some initial settings directly on the port.
	 *
	 * You should always configure all settings before using a port.
	 * There are no "default" settings applied by libserialport.
	 * When you open a port it has the defaults from the OS or driver,
	 * or the settings left over by the last program to use it. */

	/* A pointer to a struct sp_port_config, which we'll use for the config
	 * read back from the port. The pointer will be set by sp_new_config(). */
	struct sp_port_config *config;
	const int config_baudrate = 115200;
	const int config_bits = 8;
	const int config_stopbits = 1;
	const enum sp_parity config_parity = SP_PARITY_NONE;
	const enum sp_flowcontrol config_flowcontrol= SP_FLOWCONTROL_NONE;
	/* Allocate a configuration for us to read the port config into. */
	check(sp_new_config(&config));

	printf("Setting port parameters according to MDEK1001 kit user manual.\n");
	check(sp_set_config_baudrate(config, config_baudrate));
	check(sp_set_config_bits(config, config_bits));
	check(sp_set_config_stopbits(config, config_stopbits));
	check(sp_set_config_parity(config, config_parity));
	check(sp_set_config_flowcontrol(config, config_flowcontrol));

	printf("Applying new configuration.\n");
	check(sp_set_config(port, config));

	
	struct sp_port_config *device_config;
	check(sp_new_config(&device_config));

	int device_baudrate, device_bits, device_stopbits;
	enum sp_parity device_parity;

	printf("Verifying device configuration.\n");
	/* Read the current config from the port into that configuration. */
	check(sp_get_config(port, device_config));

	check(sp_get_config_baudrate(device_config, &device_baudrate));
	check(sp_get_config_bits(device_config, &device_bits));
	check(sp_get_config_stopbits(device_config, &device_stopbits));
	check(sp_get_config_parity(device_config, &device_parity));

	if(config_baudrate == device_baudrate &&
		config_bits == device_bits &&
		config_stopbits == device_stopbits &&
		config_parity == device_parity)
	{
			printf("Device has a correct configuration.\n");
	}else{
			printf("Error: Device has an incorrect configuration.\n");

	}
	
	printf("Configuration: Baudrate: %d, data bits: %d, parity: %s, stop bits: %d\n",
			device_baudrate, device_bits, parity_name(device_parity), device_stopbits);

/* This example can be used with one or two ports. With one port, it
	 * will send data and try to receive it on the same port. This can be
	 * done by connecting a single wire between the TX and RX pins of the
	 * port.
	 *
	 * Alternatively it can be used with two serial ports connected to each
	 * other, so that data can be sent on one and received on the other.
	 * This can be done with two ports with TX/RX cross-connected, e.g. by
	 * a "null modem" cable, or with a pair of interconnected virtual ports,
	 * such as those created by com0com on Windows or tty0tty on Linux. */


	// ok boys we bout to write the shit out of this transmit functions you hear me ? Godspeed

	
	uint8_t request[2] = {0x02, 0x00};
	enum sp_return write_result = sp_blocking_write(port,request,sizeof(request),1000);
	if(write_result<0){
		std::cout<<"Timeout reached on write probably... \n";
	}
	else{
		uint8_t response[18];

		enum sp_return read_result = sp_blocking_read(port,response,sizeof(response),1000);

		std::cout<<"Ammount of bytes written is "<<write_result<<" out of "<<sizeof(request) <<"\n";

		if(read_result<0){
		std::cout<<"Timeout reached on read probably... \n";
		}
		else{
			std::cout<<"Ammount of bytes read is "<<read_result<<" out of "<<sizeof(response) <<"\n";
			for (int i = 0; i < read_result; i++) {
            std::cout << "0x"
                      << std::hex
                      << std::uppercase
                      << std::setw(2)
                      << std::setfill('0')
                      << static_cast<unsigned>(response[i])
                      << " ";
        	}
		}
		std::cout<<"\n";
	}

	/* Now clean up by closing the port and freeing structures. */
	check(sp_close(port));
	sp_free_port(port);
	sp_free_config(device_config);
	sp_free_config(config);

	free(uwb_port_name);
	
	return 0;
}
