#include "serial_output.h"
#include "interrupts.h"

extern void SER_init(void);
extern int SER_write(const char *buff, int len);
