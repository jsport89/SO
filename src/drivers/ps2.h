#ifndef PS2_H
#define PS2_H
#include "../helpers/ioaccess.h"

#define PS2_DATA 0x60
#define PS2_CMD 0x64
#define PS2_STATUS PS2_CMD
#define PS2_STATUS_OUTPUT 1
#define PS2_STATUS_INPUT (1 << 1)

void ps2_init(void);
void write_to_cmd_port(uint8_t msg);
void write_to_data_port(uint8_t msg);
char read_from_data_port(void);
char read_poll_data_port(void);

#endif /* ps2.h */
