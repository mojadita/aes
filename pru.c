#include <stdio.h>
#include <assert.h>
#include "aes.h"
main()
{
	AES_BYTE i, j;

	for (i = 0; i < 0x10; i++) {
		printf("  ");
		for (j = 0; j < 0x10; j++) {
			assert((aes_mult(aes_pow(i*0x10+j, 0xfe), 0x1f, 0x101)^0x63)
				== aes_subByte(i*0x10+j));
			printf("."); fflush(stdout);
		} /* for */
		printf("\n");
	} /* for */
} /* main */
