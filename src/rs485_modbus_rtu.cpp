/*
 * rs485_modbus_rtu.cpp
 *
 *  Created on: 15-Sep-2021
 *      Author: nataraj
 */

#include "rs485_modbus_rtu.h"
RS485_Modbus_RTU::RS485_Modbus_RTU(RS485_Param mDev) {
	//Create a new RTU context with proper serial parameters (in this example,
	ctx = modbus_new_rtu(mDev.port, mDev.baud, mDev.parity, mDev.dataBit, mDev.stopBit); // @suppress("Invalid arguments")

	if (!ctx) {
		std::cout << "Failed to create the context: " + std::string(modbus_strerror(-1)) + "\n"; // @suppress("Invalid arguments") // @suppress("Symbol is not resolved")
		isPortOpen = false;
		return;
	}

	if (modbus_connect(ctx) == -1) { // @suppress("Invalid arguments")
		std::cout << "Unable to connect: " + std::string(modbus_strerror(-1)) + "\n"; // @suppress("Invalid arguments") // @suppress("Symbol is not resolved")
		modbus_free(ctx); // @suppress("Invalid arguments")
		isPortOpen = false;
		return;
	}
	isPortOpen = true;
}



modbus_t *RS485_Modbus_RTU::getDev(){ // @suppress("Type cannot be resolved") // @suppress("Member declaration not found")
	return this->ctx;
}

std::string getLibModbusVersion(){
	return "Compiled with \"libmodbus\" version" + std::string(LIBMODBUS_VERSION_STRING); // @suppress("Symbol is not resolved")
}

bool RS485_Modbus_RTU::isModbusOpen(){
	return this->isPortOpen;
}

RS485_Modbus_RTU::~RS485_Modbus_RTU() {
	modbus_close(ctx); // @suppress("Invalid arguments")
	modbus_free(ctx); // @suppress("Invalid arguments")
}



