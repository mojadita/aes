#include <stdio.h>
#include <assert.h>
#include "aes.h"

main()
{
	AES_BYTE i, j, x;

	x = 0x00;
	for (i = 0; i < 0x10; i++) {
		for (j = 0; j < 0x10; j++, x++) {
			printf("aes_SubByte(0x%02x) -> 0x%02x\n", x, aes_SubByte(x));
		} /* for */
	} /* for */
	puts("");
	x = 0x00;
	for (i = 0; i < 0x10; i++) {
		for (j = 0; j < 0x10; j++, x++) {
			printf("aes_InvSubByte(0x%02x) -> 0x%02x\n", x, aes_InvSubByte(x));
		} /* for */
	} /* for */
} /* main */
