#include <stdio.h>
#include "aes.h"
main()
{
	char buffer[1000];
	AES_BYTE x;
	int n;

	for (;;) {
		fputs("* ", stderr);
		if (!fgets(buffer, sizeof buffer, stdin))
			break;
		if (sscanf(buffer, "%x %u", &x, &n) != 2) {
			fprintf(stderr, "Error en la entrada (x = 0x%02x; n = %d)\n",
				x, n);
			continue;
		} /* if */
		printf("pow(0x%02x, %d) -> 0x%02x\n", x, n, aes_pow(x, n));
	} /* for */
	n = 254;
	for (x = 0; x < 256; x++) {
		printf("0x%02x^(%d) == 0x%02x\n", x, n, aes_pow(x, n));
	} /* for */
} /* main */
