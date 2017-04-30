#ifndef SERIAL_OUTPUT_H
#define SERIAL_OUTPUT_H
#define BUFF_SIZE 32

struct State {
   char buff[BUFF_SIZE];
   char *head, *tail;
   unsigned short busy_flag;
};

extern void SER_init(void);
extern int SER_write(const char *buff, int len);
extern int SER_write_char(const char c);
extern int is_serial_BB_empty(void);


#endif /* serial_output.h */
