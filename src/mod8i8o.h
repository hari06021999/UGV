/*
 * mod8i8o.h
 *
 *  Created on: 19-Oct-2021
 *      Author: nataraj
 */

#ifndef MOD8I8O_H_
#define MOD8I8O_H_

#include <stdio.h>
#include <modbus.h>

//read holding registers(0x03)
#define MOD8I8O_VER_TYPE			0x00
#define MOD8I8O_READ_INPUTS			0x32

//read input registers(0x04) -or- preset single register(0x06)
#define MOD8I8O_W_R_OUTPUT 			0x33

//read coil status(0x01) -or- force single coil(0x05) -or- force multiple coils(0x0F)
#define MOD8I8O_W_R_OUTPUT_BIT1 	0x330
#define MOD8I8O_W_R_OUTPUT_BIT2 	0x331
#define MOD8I8O_W_R_OUTPUT_BIT3 	0x332
#define MOD8I8O_W_R_OUTPUT_BIT4 	0x333
#define MOD8I8O_W_R_OUTPUT_BIT5 	0x334
#define MOD8I8O_W_R_OUTPUT_BIT6 	0x335
#define MOD8I8O_W_R_OUTPUT_BIT7 	0x336
#define MOD8I8O_W_R_OUTPUT_BIT8 	0x337

//read input status(0x02)
#define MOD8I8O_READ_INPUTS_BIT1	0x320
#define MOD8I8O_READ_INPUTS_BIT2	0x321
#define MOD8I8O_READ_INPUTS_BIT3	0x322
#define MOD8I8O_READ_INPUTS_BIT4	0x323
#define MOD8I8O_READ_INPUTS_BIT5	0x324
#define MOD8I8O_READ_INPUTS_BIT6	0x325
#define MOD8I8O_READ_INPUTS_BIT7	0x326
#define MOD8I8O_READ_INPUTS_BIT8	0x327

typedef enum{
	PIN_CLR=0,
	PIN_SET=1, //
}PinValue;

class MOD8I8O {
public:
	MOD8I8O();
	virtual ~MOD8I8O();
	void mapModbus(bool mPortState, modbus_t *mCtx, int mSlave); // @suppress("Type cannot be resolved")

	int getHardwareVer(uint16_t *retVal);

	int readInputPort(uint8_t *retVal);
	int readInputPin(int pin, PinValue *retVal);

	int setOutputPort(uint8_t value);
	int readOutputPort(uint8_t *retVal);

	int setOutputPin(int pin, PinValue value);
	int setOutputPins(int pinPairAdd, PinValue val1, PinValue val2);
	int readOutputPin(int pin, PinValue *retVal);
private:
	bool portState;
	modbus_t *ctx; // @suppress("Type cannot be resolved")
	int slave;
};

#endif /* MOD8I8O_H_ */
