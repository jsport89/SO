#include "init_IDT_entries.h"
#include "../lib/so_string.h"
#include "interrupts.h"
#include <stdint-gcc.h>

void init_IDT(void);

void init_IDT() {
   memset((void*)Global_IDT, 0, sizeof(Interrupt_Descriptor) * 256);
   for (int i = 0; i < 256; i++) {
      Global_IDT[i].dpl = 0;
      Global_IDT[i].present = 1;
      Global_IDT[i].type = 0xE;
   }

   uint64_t isr_address;
   uint32_t target_offset_3;
   uint16_t target_offset_2;

   isr_address = (uint64_t)(isr_wrapper_0);
   target_offset_3 = isr_address >> 32;
   Global_IDT[0].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[0].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[0].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_1);
   target_offset_3 = isr_address >> 32;
   Global_IDT[1].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[1].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[1].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_2);
   target_offset_3 = isr_address >> 32;
   Global_IDT[2].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[2].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[2].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_3);
   target_offset_3 = isr_address >> 32;
   Global_IDT[3].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[3].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[3].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_4);
   target_offset_3 = isr_address >> 32;
   Global_IDT[4].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[4].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[4].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_5);
   target_offset_3 = isr_address >> 32;
   Global_IDT[5].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[5].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[5].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_6);
   target_offset_3 = isr_address >> 32;
   Global_IDT[6].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[6].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[6].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_7);
   target_offset_3 = isr_address >> 32;
   Global_IDT[7].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[7].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[7].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_8);
   target_offset_3 = isr_address >> 32;
   Global_IDT[8].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[8].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[8].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_9);
   target_offset_3 = isr_address >> 32;
   Global_IDT[9].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[9].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[9].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_10);
   target_offset_3 = isr_address >> 32;
   Global_IDT[10].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[10].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[10].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_11);
   target_offset_3 = isr_address >> 32;
   Global_IDT[11].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[11].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[11].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_12);
   target_offset_3 = isr_address >> 32;
   Global_IDT[12].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[12].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[12].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_13);
   target_offset_3 = isr_address >> 32;
   Global_IDT[13].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[13].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[13].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_14);
   target_offset_3 = isr_address >> 32;
   Global_IDT[14].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[14].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[14].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_15);
   target_offset_3 = isr_address >> 32;
   Global_IDT[15].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[15].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[15].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_16);
   target_offset_3 = isr_address >> 32;
   Global_IDT[16].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[16].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[16].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_17);
   target_offset_3 = isr_address >> 32;
   Global_IDT[17].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[17].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[17].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_18);
   target_offset_3 = isr_address >> 32;
   Global_IDT[18].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[18].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[18].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_19);
   target_offset_3 = isr_address >> 32;
   Global_IDT[19].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[19].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[19].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_20);
   target_offset_3 = isr_address >> 32;
   Global_IDT[20].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[20].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[20].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_21);
   target_offset_3 = isr_address >> 32;
   Global_IDT[21].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[21].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[21].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_22);
   target_offset_3 = isr_address >> 32;
   Global_IDT[22].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[22].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[22].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_23);
   target_offset_3 = isr_address >> 32;
   Global_IDT[23].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[23].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[23].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_24);
   target_offset_3 = isr_address >> 32;
   Global_IDT[24].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[24].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[24].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_25);
   target_offset_3 = isr_address >> 32;
   Global_IDT[25].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[25].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[25].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_26);
   target_offset_3 = isr_address >> 32;
   Global_IDT[26].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[26].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[26].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_27);
   target_offset_3 = isr_address >> 32;
   Global_IDT[27].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[27].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[27].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_28);
   target_offset_3 = isr_address >> 32;
   Global_IDT[28].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[28].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[28].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_29);
   target_offset_3 = isr_address >> 32;
   Global_IDT[29].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[29].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[29].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_30);
   target_offset_3 = isr_address >> 32;
   Global_IDT[30].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[30].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[30].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_31);
   target_offset_3 = isr_address >> 32;
   Global_IDT[31].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[31].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[31].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_32);
   target_offset_3 = isr_address >> 32;
   Global_IDT[32].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[32].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[32].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_33);
   target_offset_3 = isr_address >> 32;
   Global_IDT[33].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[33].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[33].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_34);
   target_offset_3 = isr_address >> 32;
   Global_IDT[34].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[34].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[34].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_35);
   target_offset_3 = isr_address >> 32;
   Global_IDT[35].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[35].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[35].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_36);
   target_offset_3 = isr_address >> 32;
   Global_IDT[36].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[36].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[36].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_37);
   target_offset_3 = isr_address >> 32;
   Global_IDT[37].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[37].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[37].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_38);
   target_offset_3 = isr_address >> 32;
   Global_IDT[38].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[38].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[38].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_39);
   target_offset_3 = isr_address >> 32;
   Global_IDT[39].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[39].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[39].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_40);
   target_offset_3 = isr_address >> 32;
   Global_IDT[40].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[40].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[40].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_41);
   target_offset_3 = isr_address >> 32;
   Global_IDT[41].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[41].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[41].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_42);
   target_offset_3 = isr_address >> 32;
   Global_IDT[42].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[42].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[42].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_43);
   target_offset_3 = isr_address >> 32;
   Global_IDT[43].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[43].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[43].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_44);
   target_offset_3 = isr_address >> 32;
   Global_IDT[44].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[44].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[44].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_45);
   target_offset_3 = isr_address >> 32;
   Global_IDT[45].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[45].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[45].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_46);
   target_offset_3 = isr_address >> 32;
   Global_IDT[46].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[46].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[46].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_47);
   target_offset_3 = isr_address >> 32;
   Global_IDT[47].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[47].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[47].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_48);
   target_offset_3 = isr_address >> 32;
   Global_IDT[48].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[48].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[48].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_49);
   target_offset_3 = isr_address >> 32;
   Global_IDT[49].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[49].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[49].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_50);
   target_offset_3 = isr_address >> 32;
   Global_IDT[50].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[50].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[50].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_51);
   target_offset_3 = isr_address >> 32;
   Global_IDT[51].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[51].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[51].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_52);
   target_offset_3 = isr_address >> 32;
   Global_IDT[52].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[52].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[52].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_53);
   target_offset_3 = isr_address >> 32;
   Global_IDT[53].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[53].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[53].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_54);
   target_offset_3 = isr_address >> 32;
   Global_IDT[54].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[54].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[54].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_55);
   target_offset_3 = isr_address >> 32;
   Global_IDT[55].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[55].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[55].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_56);
   target_offset_3 = isr_address >> 32;
   Global_IDT[56].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[56].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[56].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_57);
   target_offset_3 = isr_address >> 32;
   Global_IDT[57].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[57].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[57].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_58);
   target_offset_3 = isr_address >> 32;
   Global_IDT[58].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[58].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[58].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_59);
   target_offset_3 = isr_address >> 32;
   Global_IDT[59].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[59].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[59].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_60);
   target_offset_3 = isr_address >> 32;
   Global_IDT[60].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[60].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[60].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_61);
   target_offset_3 = isr_address >> 32;
   Global_IDT[61].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[61].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[61].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_62);
   target_offset_3 = isr_address >> 32;
   Global_IDT[62].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[62].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[62].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_63);
   target_offset_3 = isr_address >> 32;
   Global_IDT[63].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[63].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[63].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_64);
   target_offset_3 = isr_address >> 32;
   Global_IDT[64].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[64].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[64].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_65);
   target_offset_3 = isr_address >> 32;
   Global_IDT[65].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[65].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[65].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_66);
   target_offset_3 = isr_address >> 32;
   Global_IDT[66].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[66].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[66].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_67);
   target_offset_3 = isr_address >> 32;
   Global_IDT[67].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[67].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[67].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_68);
   target_offset_3 = isr_address >> 32;
   Global_IDT[68].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[68].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[68].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_69);
   target_offset_3 = isr_address >> 32;
   Global_IDT[69].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[69].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[69].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_70);
   target_offset_3 = isr_address >> 32;
   Global_IDT[70].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[70].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[70].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_71);
   target_offset_3 = isr_address >> 32;
   Global_IDT[71].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[71].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[71].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_72);
   target_offset_3 = isr_address >> 32;
   Global_IDT[72].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[72].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[72].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_73);
   target_offset_3 = isr_address >> 32;
   Global_IDT[73].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[73].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[73].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_74);
   target_offset_3 = isr_address >> 32;
   Global_IDT[74].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[74].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[74].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_75);
   target_offset_3 = isr_address >> 32;
   Global_IDT[75].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[75].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[75].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_76);
   target_offset_3 = isr_address >> 32;
   Global_IDT[76].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[76].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[76].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_77);
   target_offset_3 = isr_address >> 32;
   Global_IDT[77].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[77].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[77].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_78);
   target_offset_3 = isr_address >> 32;
   Global_IDT[78].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[78].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[78].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_79);
   target_offset_3 = isr_address >> 32;
   Global_IDT[79].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[79].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[79].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_80);
   target_offset_3 = isr_address >> 32;
   Global_IDT[80].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[80].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[80].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_81);
   target_offset_3 = isr_address >> 32;
   Global_IDT[81].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[81].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[81].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_82);
   target_offset_3 = isr_address >> 32;
   Global_IDT[82].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[82].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[82].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_83);
   target_offset_3 = isr_address >> 32;
   Global_IDT[83].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[83].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[83].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_84);
   target_offset_3 = isr_address >> 32;
   Global_IDT[84].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[84].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[84].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_85);
   target_offset_3 = isr_address >> 32;
   Global_IDT[85].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[85].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[85].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_86);
   target_offset_3 = isr_address >> 32;
   Global_IDT[86].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[86].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[86].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_87);
   target_offset_3 = isr_address >> 32;
   Global_IDT[87].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[87].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[87].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_88);
   target_offset_3 = isr_address >> 32;
   Global_IDT[88].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[88].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[88].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_89);
   target_offset_3 = isr_address >> 32;
   Global_IDT[89].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[89].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[89].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_90);
   target_offset_3 = isr_address >> 32;
   Global_IDT[90].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[90].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[90].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_91);
   target_offset_3 = isr_address >> 32;
   Global_IDT[91].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[91].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[91].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_92);
   target_offset_3 = isr_address >> 32;
   Global_IDT[92].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[92].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[92].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_93);
   target_offset_3 = isr_address >> 32;
   Global_IDT[93].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[93].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[93].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_94);
   target_offset_3 = isr_address >> 32;
   Global_IDT[94].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[94].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[94].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_95);
   target_offset_3 = isr_address >> 32;
   Global_IDT[95].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[95].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[95].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_96);
   target_offset_3 = isr_address >> 32;
   Global_IDT[96].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[96].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[96].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_97);
   target_offset_3 = isr_address >> 32;
   Global_IDT[97].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[97].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[97].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_98);
   target_offset_3 = isr_address >> 32;
   Global_IDT[98].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[98].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[98].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_99);
   target_offset_3 = isr_address >> 32;
   Global_IDT[99].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[99].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[99].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_100);
   target_offset_3 = isr_address >> 32;
   Global_IDT[100].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[100].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[100].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_101);
   target_offset_3 = isr_address >> 32;
   Global_IDT[101].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[101].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[101].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_102);
   target_offset_3 = isr_address >> 32;
   Global_IDT[102].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[102].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[102].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_103);
   target_offset_3 = isr_address >> 32;
   Global_IDT[103].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[103].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[103].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_104);
   target_offset_3 = isr_address >> 32;
   Global_IDT[104].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[104].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[104].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_105);
   target_offset_3 = isr_address >> 32;
   Global_IDT[105].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[105].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[105].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_106);
   target_offset_3 = isr_address >> 32;
   Global_IDT[106].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[106].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[106].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_107);
   target_offset_3 = isr_address >> 32;
   Global_IDT[107].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[107].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[107].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_108);
   target_offset_3 = isr_address >> 32;
   Global_IDT[108].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[108].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[108].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_109);
   target_offset_3 = isr_address >> 32;
   Global_IDT[109].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[109].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[109].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_110);
   target_offset_3 = isr_address >> 32;
   Global_IDT[110].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[110].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[110].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_111);
   target_offset_3 = isr_address >> 32;
   Global_IDT[111].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[111].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[111].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_112);
   target_offset_3 = isr_address >> 32;
   Global_IDT[112].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[112].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[112].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_113);
   target_offset_3 = isr_address >> 32;
   Global_IDT[113].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[113].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[113].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_114);
   target_offset_3 = isr_address >> 32;
   Global_IDT[114].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[114].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[114].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_115);
   target_offset_3 = isr_address >> 32;
   Global_IDT[115].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[115].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[115].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_116);
   target_offset_3 = isr_address >> 32;
   Global_IDT[116].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[116].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[116].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_117);
   target_offset_3 = isr_address >> 32;
   Global_IDT[117].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[117].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[117].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_118);
   target_offset_3 = isr_address >> 32;
   Global_IDT[118].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[118].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[118].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_119);
   target_offset_3 = isr_address >> 32;
   Global_IDT[119].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[119].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[119].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_120);
   target_offset_3 = isr_address >> 32;
   Global_IDT[120].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[120].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[120].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_121);
   target_offset_3 = isr_address >> 32;
   Global_IDT[121].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[121].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[121].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_122);
   target_offset_3 = isr_address >> 32;
   Global_IDT[122].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[122].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[122].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_123);
   target_offset_3 = isr_address >> 32;
   Global_IDT[123].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[123].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[123].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_124);
   target_offset_3 = isr_address >> 32;
   Global_IDT[124].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[124].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[124].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_125);
   target_offset_3 = isr_address >> 32;
   Global_IDT[125].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[125].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[125].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_126);
   target_offset_3 = isr_address >> 32;
   Global_IDT[126].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[126].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[126].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_127);
   target_offset_3 = isr_address >> 32;
   Global_IDT[127].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[127].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[127].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_128);
   target_offset_3 = isr_address >> 32;
   Global_IDT[128].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[128].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[128].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_129);
   target_offset_3 = isr_address >> 32;
   Global_IDT[129].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[129].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[129].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_130);
   target_offset_3 = isr_address >> 32;
   Global_IDT[130].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[130].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[130].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_131);
   target_offset_3 = isr_address >> 32;
   Global_IDT[131].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[131].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[131].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_132);
   target_offset_3 = isr_address >> 32;
   Global_IDT[132].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[132].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[132].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_133);
   target_offset_3 = isr_address >> 32;
   Global_IDT[133].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[133].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[133].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_134);
   target_offset_3 = isr_address >> 32;
   Global_IDT[134].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[134].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[134].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_135);
   target_offset_3 = isr_address >> 32;
   Global_IDT[135].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[135].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[135].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_136);
   target_offset_3 = isr_address >> 32;
   Global_IDT[136].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[136].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[136].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_137);
   target_offset_3 = isr_address >> 32;
   Global_IDT[137].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[137].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[137].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_138);
   target_offset_3 = isr_address >> 32;
   Global_IDT[138].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[138].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[138].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_139);
   target_offset_3 = isr_address >> 32;
   Global_IDT[139].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[139].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[139].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_140);
   target_offset_3 = isr_address >> 32;
   Global_IDT[140].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[140].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[140].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_141);
   target_offset_3 = isr_address >> 32;
   Global_IDT[141].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[141].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[141].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_142);
   target_offset_3 = isr_address >> 32;
   Global_IDT[142].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[142].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[142].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_143);
   target_offset_3 = isr_address >> 32;
   Global_IDT[143].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[143].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[143].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_144);
   target_offset_3 = isr_address >> 32;
   Global_IDT[144].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[144].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[144].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_145);
   target_offset_3 = isr_address >> 32;
   Global_IDT[145].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[145].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[145].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_146);
   target_offset_3 = isr_address >> 32;
   Global_IDT[146].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[146].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[146].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_147);
   target_offset_3 = isr_address >> 32;
   Global_IDT[147].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[147].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[147].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_148);
   target_offset_3 = isr_address >> 32;
   Global_IDT[148].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[148].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[148].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_149);
   target_offset_3 = isr_address >> 32;
   Global_IDT[149].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[149].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[149].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_150);
   target_offset_3 = isr_address >> 32;
   Global_IDT[150].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[150].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[150].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_151);
   target_offset_3 = isr_address >> 32;
   Global_IDT[151].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[151].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[151].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_152);
   target_offset_3 = isr_address >> 32;
   Global_IDT[152].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[152].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[152].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_153);
   target_offset_3 = isr_address >> 32;
   Global_IDT[153].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[153].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[153].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_154);
   target_offset_3 = isr_address >> 32;
   Global_IDT[154].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[154].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[154].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_155);
   target_offset_3 = isr_address >> 32;
   Global_IDT[155].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[155].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[155].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_156);
   target_offset_3 = isr_address >> 32;
   Global_IDT[156].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[156].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[156].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_157);
   target_offset_3 = isr_address >> 32;
   Global_IDT[157].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[157].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[157].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_158);
   target_offset_3 = isr_address >> 32;
   Global_IDT[158].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[158].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[158].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_159);
   target_offset_3 = isr_address >> 32;
   Global_IDT[159].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[159].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[159].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_160);
   target_offset_3 = isr_address >> 32;
   Global_IDT[160].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[160].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[160].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_161);
   target_offset_3 = isr_address >> 32;
   Global_IDT[161].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[161].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[161].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_162);
   target_offset_3 = isr_address >> 32;
   Global_IDT[162].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[162].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[162].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_163);
   target_offset_3 = isr_address >> 32;
   Global_IDT[163].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[163].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[163].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_164);
   target_offset_3 = isr_address >> 32;
   Global_IDT[164].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[164].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[164].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_165);
   target_offset_3 = isr_address >> 32;
   Global_IDT[165].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[165].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[165].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_166);
   target_offset_3 = isr_address >> 32;
   Global_IDT[166].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[166].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[166].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_167);
   target_offset_3 = isr_address >> 32;
   Global_IDT[167].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[167].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[167].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_168);
   target_offset_3 = isr_address >> 32;
   Global_IDT[168].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[168].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[168].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_169);
   target_offset_3 = isr_address >> 32;
   Global_IDT[169].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[169].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[169].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_170);
   target_offset_3 = isr_address >> 32;
   Global_IDT[170].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[170].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[170].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_171);
   target_offset_3 = isr_address >> 32;
   Global_IDT[171].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[171].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[171].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_172);
   target_offset_3 = isr_address >> 32;
   Global_IDT[172].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[172].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[172].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_173);
   target_offset_3 = isr_address >> 32;
   Global_IDT[173].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[173].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[173].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_174);
   target_offset_3 = isr_address >> 32;
   Global_IDT[174].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[174].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[174].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_175);
   target_offset_3 = isr_address >> 32;
   Global_IDT[175].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[175].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[175].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_176);
   target_offset_3 = isr_address >> 32;
   Global_IDT[176].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[176].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[176].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_177);
   target_offset_3 = isr_address >> 32;
   Global_IDT[177].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[177].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[177].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_178);
   target_offset_3 = isr_address >> 32;
   Global_IDT[178].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[178].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[178].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_179);
   target_offset_3 = isr_address >> 32;
   Global_IDT[179].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[179].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[179].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_180);
   target_offset_3 = isr_address >> 32;
   Global_IDT[180].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[180].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[180].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_181);
   target_offset_3 = isr_address >> 32;
   Global_IDT[181].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[181].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[181].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_182);
   target_offset_3 = isr_address >> 32;
   Global_IDT[182].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[182].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[182].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_183);
   target_offset_3 = isr_address >> 32;
   Global_IDT[183].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[183].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[183].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_184);
   target_offset_3 = isr_address >> 32;
   Global_IDT[184].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[184].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[184].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_185);
   target_offset_3 = isr_address >> 32;
   Global_IDT[185].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[185].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[185].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_186);
   target_offset_3 = isr_address >> 32;
   Global_IDT[186].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[186].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[186].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_187);
   target_offset_3 = isr_address >> 32;
   Global_IDT[187].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[187].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[187].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_188);
   target_offset_3 = isr_address >> 32;
   Global_IDT[188].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[188].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[188].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_189);
   target_offset_3 = isr_address >> 32;
   Global_IDT[189].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[189].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[189].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_190);
   target_offset_3 = isr_address >> 32;
   Global_IDT[190].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[190].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[190].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_191);
   target_offset_3 = isr_address >> 32;
   Global_IDT[191].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[191].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[191].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_192);
   target_offset_3 = isr_address >> 32;
   Global_IDT[192].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[192].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[192].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_193);
   target_offset_3 = isr_address >> 32;
   Global_IDT[193].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[193].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[193].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_194);
   target_offset_3 = isr_address >> 32;
   Global_IDT[194].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[194].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[194].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_195);
   target_offset_3 = isr_address >> 32;
   Global_IDT[195].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[195].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[195].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_196);
   target_offset_3 = isr_address >> 32;
   Global_IDT[196].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[196].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[196].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_197);
   target_offset_3 = isr_address >> 32;
   Global_IDT[197].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[197].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[197].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_198);
   target_offset_3 = isr_address >> 32;
   Global_IDT[198].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[198].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[198].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_199);
   target_offset_3 = isr_address >> 32;
   Global_IDT[199].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[199].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[199].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_200);
   target_offset_3 = isr_address >> 32;
   Global_IDT[200].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[200].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[200].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_201);
   target_offset_3 = isr_address >> 32;
   Global_IDT[201].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[201].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[201].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_202);
   target_offset_3 = isr_address >> 32;
   Global_IDT[202].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[202].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[202].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_203);
   target_offset_3 = isr_address >> 32;
   Global_IDT[203].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[203].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[203].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_204);
   target_offset_3 = isr_address >> 32;
   Global_IDT[204].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[204].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[204].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_205);
   target_offset_3 = isr_address >> 32;
   Global_IDT[205].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[205].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[205].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_206);
   target_offset_3 = isr_address >> 32;
   Global_IDT[206].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[206].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[206].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_207);
   target_offset_3 = isr_address >> 32;
   Global_IDT[207].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[207].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[207].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_208);
   target_offset_3 = isr_address >> 32;
   Global_IDT[208].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[208].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[208].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_209);
   target_offset_3 = isr_address >> 32;
   Global_IDT[209].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[209].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[209].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_210);
   target_offset_3 = isr_address >> 32;
   Global_IDT[210].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[210].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[210].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_211);
   target_offset_3 = isr_address >> 32;
   Global_IDT[211].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[211].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[211].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_212);
   target_offset_3 = isr_address >> 32;
   Global_IDT[212].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[212].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[212].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_213);
   target_offset_3 = isr_address >> 32;
   Global_IDT[213].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[213].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[213].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_214);
   target_offset_3 = isr_address >> 32;
   Global_IDT[214].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[214].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[214].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_215);
   target_offset_3 = isr_address >> 32;
   Global_IDT[215].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[215].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[215].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_216);
   target_offset_3 = isr_address >> 32;
   Global_IDT[216].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[216].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[216].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_217);
   target_offset_3 = isr_address >> 32;
   Global_IDT[217].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[217].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[217].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_218);
   target_offset_3 = isr_address >> 32;
   Global_IDT[218].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[218].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[218].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_219);
   target_offset_3 = isr_address >> 32;
   Global_IDT[219].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[219].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[219].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_220);
   target_offset_3 = isr_address >> 32;
   Global_IDT[220].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[220].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[220].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_221);
   target_offset_3 = isr_address >> 32;
   Global_IDT[221].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[221].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[221].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_222);
   target_offset_3 = isr_address >> 32;
   Global_IDT[222].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[222].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[222].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_223);
   target_offset_3 = isr_address >> 32;
   Global_IDT[223].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[223].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[223].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_224);
   target_offset_3 = isr_address >> 32;
   Global_IDT[224].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[224].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[224].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_225);
   target_offset_3 = isr_address >> 32;
   Global_IDT[225].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[225].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[225].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_226);
   target_offset_3 = isr_address >> 32;
   Global_IDT[226].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[226].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[226].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_227);
   target_offset_3 = isr_address >> 32;
   Global_IDT[227].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[227].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[227].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_228);
   target_offset_3 = isr_address >> 32;
   Global_IDT[228].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[228].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[228].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_229);
   target_offset_3 = isr_address >> 32;
   Global_IDT[229].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[229].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[229].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_230);
   target_offset_3 = isr_address >> 32;
   Global_IDT[230].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[230].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[230].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_231);
   target_offset_3 = isr_address >> 32;
   Global_IDT[231].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[231].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[231].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_232);
   target_offset_3 = isr_address >> 32;
   Global_IDT[232].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[232].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[232].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_233);
   target_offset_3 = isr_address >> 32;
   Global_IDT[233].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[233].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[233].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_234);
   target_offset_3 = isr_address >> 32;
   Global_IDT[234].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[234].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[234].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_235);
   target_offset_3 = isr_address >> 32;
   Global_IDT[235].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[235].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[235].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_236);
   target_offset_3 = isr_address >> 32;
   Global_IDT[236].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[236].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[236].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_237);
   target_offset_3 = isr_address >> 32;
   Global_IDT[237].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[237].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[237].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_238);
   target_offset_3 = isr_address >> 32;
   Global_IDT[238].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[238].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[238].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_239);
   target_offset_3 = isr_address >> 32;
   Global_IDT[239].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[239].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[239].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_240);
   target_offset_3 = isr_address >> 32;
   Global_IDT[240].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[240].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[240].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_241);
   target_offset_3 = isr_address >> 32;
   Global_IDT[241].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[241].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[241].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_242);
   target_offset_3 = isr_address >> 32;
   Global_IDT[242].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[242].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[242].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_243);
   target_offset_3 = isr_address >> 32;
   Global_IDT[243].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[243].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[243].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_244);
   target_offset_3 = isr_address >> 32;
   Global_IDT[244].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[244].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[244].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_245);
   target_offset_3 = isr_address >> 32;
   Global_IDT[245].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[245].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[245].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_246);
   target_offset_3 = isr_address >> 32;
   Global_IDT[246].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[246].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[246].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_247);
   target_offset_3 = isr_address >> 32;
   Global_IDT[247].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[247].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[247].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_248);
   target_offset_3 = isr_address >> 32;
   Global_IDT[248].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[248].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[248].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_249);
   target_offset_3 = isr_address >> 32;
   Global_IDT[249].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[249].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[249].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_250);
   target_offset_3 = isr_address >> 32;
   Global_IDT[250].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[250].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[250].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_251);
   target_offset_3 = isr_address >> 32;
   Global_IDT[251].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[251].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[251].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_252);
   target_offset_3 = isr_address >> 32;
   Global_IDT[252].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[252].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[252].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_253);
   target_offset_3 = isr_address >> 32;
   Global_IDT[253].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[253].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[253].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_254);
   target_offset_3 = isr_address >> 32;
   Global_IDT[254].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[254].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[254].target_offset_1 = isr_address & 0xFFFF;

   isr_address = (uint64_t)(isr_wrapper_255);
   target_offset_3 = isr_address >> 32;
   Global_IDT[255].target_offset_3 = target_offset_3;
   target_offset_2 = isr_address >> 16;
   Global_IDT[255].target_offset_2 = target_offset_2 & 0xFFFF;
   Global_IDT[255].target_offset_1 = isr_address & 0xFFFF;

}