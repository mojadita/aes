/* $Id: aes.c,v 1.4 2003/11/27 00:55:09 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Tue Nov 11 00:24:20 MET 2003
 *
 * Disclaimer:
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#define IN_AES_C

/* Standard include files */
#include <sys/types.h>
#include <stdio.h>
#include "aes.h"

/* constants */
#define MAX(a,b) ((a) > (b) ? (a) : (b))

/* types */

/* prototypes */

/* variables */
static char AES_C_RCSId[]="\n$Id: aes.c,v 1.4 2003/11/27 00:55:09 luis Exp $\n";

/* functions */

void aes_Cipher(BYTE *b, int Nb, BYTE *k, int Nk)
{
	WORD *eKey, *rKey;
	int i;
	int Nr;
	
	Nr = MAX(Nb, Nk) + 6; /* Number of rounds */
	rKey = eKey = aes_KeyExpansion((WORD *)k, Nk, Nb, Nr);

	/* first round */
	printf("Comienzo:\nEntrada:\n");
	aes_PrintState(b, Nb);
	printf("Round Key Value:\n");
	aes_PrintState(eKey, Nb);
	aes_AddRoundKey(b, Nb, eKey);
	/* Nr rounds */
	for (i = 0; i < Nr; i++) {
		printf("Ronda %d: Estado:\n", i+1);
		aes_PrintState(b, Nb);
		aes_SubBytes(b, Nb);
		printf("Tras SubBytes:\n");
		aes_PrintState(b, Nb);
		switch(Nb) {
		case 4: aes_ShiftRows4(b); break;
		case 6: aes_ShiftRows6(b); break;
		case 8: aes_ShiftRows8(b); break;
		default:
			fprintf(stderr, "aes_Cipher: Nb not in {4, 6, 8} (%d)\n", Nb);
			fflush(stderr);
			abort();
		} /* switch */
		printf("Tras ShiftRows:\n");
		aes_PrintState(b, Nb);
		if (i < Nr-1) {
			aes_MixColumns(b, Nb);
			printf("Tras MixColumns:\n");
			aes_PrintState(b, Nb);
		} /* if */
		rKey += Nb;
		printf("Round Key Value:\n");
		aes_PrintState(rKey, Nb);
		aes_AddRoundKey(b, Nb, rKey);
	} /* for */
	printf("Resultado:\n");
	aes_PrintState(b, Nb);
	
} /* aes_Cipher */

void aes_InvCipher(BYTE *b, int Nb, BYTE *k, int Nk)
{
}

main()
{
	BYTE bloque1[] = {
	0x32, 0x43, 0xf6, 0xa8,
	0x88, 0x5a, 0x30, 0x8d,
	0x31, 0x31, 0x98, 0xa2,
	0xe0, 0x37, 0x07, 0x34,
	};
	BYTE clave1[] = {
	0x2b, 0x7e, 0x15, 0x16,
	0x28, 0xae, 0xd2, 0xa6,
	0xab, 0xf7, 0x15, 0x88,
	0x09, 0xcf, 0x4f, 0x3c,
	};
	BYTE bloque2[] = {
	0x00, 0x11, 0x22, 0x33,
	0x44, 0x55, 0x66, 0x77,
	0x88, 0x99, 0xaa, 0xbb,
	0xcc, 0xdd, 0xee, 0xff,
	};
	BYTE clave2[] = {
	0x00, 0x01, 0x02, 0x03,
	0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f,
	};
	BYTE bloque3[] = {
	0x00, 0x11, 0x22, 0x33,
	0x44, 0x55, 0x66, 0x77,
	0x88, 0x99, 0xaa, 0xbb,
	0xcc, 0xdd, 0xee, 0xff,
	};
	BYTE clave3[] = {
	0x00, 0x01, 0x02, 0x03,
	0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13,
	0x14, 0x15, 0x16, 0x17,
	};
	BYTE bloque4[] = {
	0x00, 0x11, 0x22, 0x33,
	0x44, 0x55, 0x66, 0x77,
	0x88, 0x99, 0xaa, 0xbb,
	0xcc, 0xdd, 0xee, 0xff,
	};
	BYTE clave4[] = {
	0x00, 0x01, 0x02, 0x03,
	0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13,
	0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1a, 0x1b,
	0x1c, 0x1d, 0x1e, 0x1f,
	};
	aes_Cipher(bloque1, 4, clave1, 4);
	aes_Cipher(bloque2, 4, clave2, 4);
	aes_Cipher(bloque3, 4, clave3, 6);
	aes_Cipher(bloque4, 4, clave4, 8);
}

/* $Id: aes.c,v 1.4 2003/11/27 00:55:09 luis Exp $ */
