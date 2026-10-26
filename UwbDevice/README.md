# UwbDevice

[DWM1001 Firmware User Guide - Based on DWM1001-DEV board](https://www.qorvo.com/products/p/DWM1001C#tech-docs)

- To create the software for this GOAL you should do this in UwbDevice repository:
  1. Discovere the connected DW1001 device (On linux) - done

  2. Open a serial connection to the DW1001

  3. Send commands to the device

  4. Recieve the status of the device

  5. Recieve measurements from the device

  6. Parse the measurements and store them in proper containers

  7. Think about using Bluetooth as well?

~/libserialport/examples$ ./list_ports
Getting port list.
Found port: /dev/ttyACM0
Found 1 ports.
Freeing port list.

~/libserialport/examples$ ./p
port_config port_info projects/

~/libserialport/examples$ ./port_info
Usage: ./port_info <port name>

~/libserialport/examples$ ./port_info /dev/ttyACM0
Looking for port /dev/ttyACM0.
Port name: /dev/ttyACM0
Description: J-Link - 000760156494
Type: USB
Manufacturer: SEGGER
Product: J-Link
Serial: 000760156494
VID: 1366 PID: 0105
Bus: 3 Address: 6
Freeing port.

~/libserialport/examples$ ./port_config
Usage: ./port_config <port name>

~/libserialport/examples$ ./port_config /dev/ttyACM0
Looking for port /dev/ttyACM0.
Port name: /dev/ttyACM0
Description: J-Link - 000760156494
Opening port.
Setting port to 115200 8N1, no flow control.
Baudrate: 115200, data bits: 8, parity: None, stop bits: 1
Creating new config for 9600 7E2, XON/XOFF flow control.
Applying new configuration.
Setting port back to previous config.

~/libserialport/examples$ ./send_receive
Usage: ./send_receive <port 1> [<port 2>]

~/libserialport/examples$ ./send_receive /dev/ACM0
Looking for port /dev/ACM0.
Error: Invalid argument.
Aborted (core dumped)

~/libserialport/examples$ ./send_receive /dev/ttyACM0
Looking for port /dev/ttyACM0.
Opening port.
Setting port to 9600 8N1, no flow control.
Sending 'Hello!' (6 bytes) on port /dev/ttyACM0.
Sent 6 bytes successfully.
Receiving 6 bytes on port /dev/ttyACM0.
Timed out, 0/6 bytes received.
Received ''.
