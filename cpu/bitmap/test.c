#include <stdio.h>
#include <stdlib.h>


void set_bit(unsigned int num, unsigned long* bitmap) {
     //unsigned long m = 0x80000000;
     
     bitmap[num/32] |= ( 0x80000000 >> num%32);
}

int test_bit(unsigned int num, unsigned long* bitmap) {
     // unsigned long m = 0x80000000;
     
     return bitmap[num/32] & (0x80000000 >> num%32);
}


int main() {

     int map_size = 4*32;
     unsigned long* bitmap = (unsigned long*) malloc(sizeof(unsigned long)*map_size);

     int i;
     
     for (i=0; i<map_size; i++) bitmap[i] = 0;

     for (i=0;i<map_size; i++) printf("%d ",test_bit(i, bitmap));
     
     
     printf("\n\n");
     

     
     set_bit(7, bitmap);
     for (i=0;i<map_size; i++) printf("%d ",test_bit(i, bitmap));
     
     printf("\n\n");


     set_bit(44, bitmap);
     for (i=0;i<map_size; i++) printf("%d ",test_bit(i, bitmap));
     


     
     return 0;
}
