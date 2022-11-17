#include <hidapi.h>
#include <iostream>
#include <wchar.h>
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"

std::string toString(wchar_t *wide_str) {
	std::wstring wstr(wide_str);
	return std::string(wstr.begin(), wstr.end());
}
int main(int argc, char* argv[])
{
	int res;
	unsigned char buf[65];
    wchar_t wstr[255];
	hid_device *handle;
	int i;

	plog::init(plog::debug, "debug.log");
	// Initialize the hidapi library
	res = hid_init();

	// Open the device using the VID, PID,
	// and optionally the Serial number.
    // Device 009: ID 320f:5044
	handle = hid_open(0x320f, 0x5044, NULL);
	if (!handle) {
        std::wcout << "Unable to open device." << hid_error(handle) << std::endl;
		LOG(plog::debug) << "Unable to open device: " <<toString(wstr) << std::endl;
		hid_exit();
 		return 1;
	}

	// Read the Manufacturer String
	res = hid_get_manufacturer_string(handle, wstr, 255);
    std::wcout << "Manufacturer string: " << std::wstring(wstr).c_str() << std::endl;
    LOG(plog::debug) << "Manufacturer string: " << std::wstring(wstr).c_str() << std::endl;

	// Read the Product String
	res = hid_get_product_string(handle, wstr, 255);
    std::wcout << "Product string: " << wstr << std::endl;
    LOG(plog::debug) << "Product string: " << wstr << std::endl;

	// Read the Serial Number String
	res = hid_get_serial_number_string(handle, wstr, 255);
    std::wcout << "Serial number string: " << wstr << std::endl;
    LOG(plog::debug) << "Serial number string: " << wstr << std::endl;

	// // Read Indexed String 1
	// res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
	// printf("Indexed String 1: %ls\n", wstr);

	// // Toggle LED (cmd 0x80). The first byte is the report number (0x0).
	// buf[0] = 0x0;
	// buf[1] = 0x80;
	// res = hid_write(handle, buf, 65);

	// // Request state (cmd 0x81). The first byte is the report number (0x0).
	// buf[0] = 0x0;
	// buf[1] = 0x81;
	// res = hid_write(handle, buf, 65);

	// // Read requested state
	// res = hid_read(handle, buf, 65);

	// // Print out the returned buffer.
	// for (i = 0; i < 4; i++)
	// 	printf("buf[%d]: %d\n", i, buf[i]);

	// // Close the device
	// hid_close(handle);

	// Finalize the hidapi library
	res = hid_exit();

	return 0;
}