/* $Id: keyExpansion.c,v 1.3 2003/11/27 23:03:05 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Wed Nov 26 21:33:53 MET 2003
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

#define IN_KEYEXPANSION_C

/* Standard include files */
#include <sys/types.h>
#include <malloc.h>
#include "aes.h"

/* constants */
#define DEBUG 0
#define MAIN 0

/* types */

/* prototypes */

/* variables */
static char KEYEXPANSION_C_RCSId[]="\n$Id: keyExpansion.c,v 1.3 2003/11/27 23:03:05 luis Exp $\n";

/* functions */
static void SubWord(WORD *b)
{
	register int i;

	for (i = 0; i < AES_WS; i++) {
		b->w[i] = aes_SubByte(b->w[i]);
	} /* for */
} /* SubWord */

static void RotWord(WORD *b)
{
	register int i;
	BYTE c = b->w[0];
	for (i = 0; i < AES_WS - 1; i++) {
		b->w[i] = b->w[i+1];
	} /* for */
	b->w[i] = c;
} /* RotWord */

#if DEBUG
print_header()
{
		printf(
"===========================================================================\n"
"|  |          |  after  |  after  |   Rcon  |  after  |         |  after  |\n"
"| i|   temp   | RotWord | SubWord |  [i/Nk] |XOR Rcon | W[i-Nk] | W[i-Nk] |\n"
"===========================================================================\n"
		);
} /* print_header */

void aes_PrintWord(WORD *b)
{
	if (!b) {
		printf("[________]");
	} else {
		register int i;
		printf("[");
		for (i = 0; i < AES_WS; i++) {
			printf("%02x", b->w[i]);
		} /* for */
		printf("]");
	} /* if */
} /* aes_PrintWord */
#endif

/* Rijndael key expansion routine */
WORD *aes_KeyExpansion(WORD *k, int Nb, int Nk)
{
	WORD *res, *P;
	int i;
	int Nr = AES_Nr(Nb, Nk);
	int N = Nb*(Nr+1);
	WORD Rcon = {{ 0x01, 0x00, 0x00, 0x00 }};

	P = res = calloc(N, sizeof(WORD));

	if (!res) return NULL;

#if DEBUG
	printf("Nb = %d; Nk = %d; Nr = %d.\n", Nb, Nk, Nr);
#endif
	/* copiamos la clave */
	for (i = 0; i < Nk; i++) {
		memcpy(P, k, sizeof(WORD));
#if DEBUG
		printf("W[%d] = ", i); aes_PrintWord(P); printf("\n");
#endif
		P++; k++;
	} /* for */

	/* i == Nk */
	while (i < N) {
#if DEBUG
		if ((i - Nk + 24)%24 == 0) {
			print_header();
		} /* if */
		printf("%3d: ", i);
#endif
		memcpy(P, P-1, sizeof(WORD)); /* temp */
#if DEBUG
		aes_PrintWord(P);
#endif
		if (i%Nk == 0) {
			RotWord(P);
#if DEBUG
			aes_PrintWord(P);
		} else {
			aes_PrintWord(NULL);
#endif
		} /* if */
		if (i%Nk == 0 || ((Nk > 6) && (i%Nk == 4))) {
			SubWord(P);
#if DEBUG
			aes_PrintWord(P);
		} else {
			aes_PrintWord(NULL);
#endif
		} /* if */
		if (i%Nk == 0) {
			aes_AddRoundKey(P, 1, &Rcon);
#if DEBUG
			aes_PrintWord(&Rcon);
			aes_PrintWord(P);
#endif
			Rcon.w[0] = aes_mult(Rcon.w[0], 0x02, AES_POL);
#if DEBUG
		} else {
			aes_PrintWord(NULL);
			aes_PrintWord(NULL);
#endif
		}
#if DEBUG
		aes_PrintWord(P-Nk);
#endif
		aes_AddRoundKey(P, 1, P-Nk);
#if DEBUG
		aes_PrintWord(P);
		printf(" = W[%d]", i);
		printf("\n");
#endif
		i++;P++;
	} /* while */

	return res;
} /* aes_KeyExpansion */

#if MAIN
main()
{
	WORD key4[] = {
		0x2b, 0x7e, 0x15, 0x16,
		0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88,
		0x09, 0xcf, 0x4f, 0x3c,	
	};
	WORD key6[] = {
		0x8e, 0x73, 0xb0, 0xf7,
		0xda, 0x0e, 0x64, 0x52,
		0xc8, 0x10, 0xf3, 0x2b,
		0x80, 0x90, 0x79, 0xe5,
		0x62, 0xf8, 0xea, 0xd2,
		0x52, 0x2c, 0x6b, 0x7b,
	};
	WORD key8[] = {
		0x60, 0x3d, 0xeb, 0x10,
		0x15, 0xca, 0x71, 0xbe,
		0x2b, 0x73, 0xae, 0xf0,
		0x85, 0x7d, 0x77, 0x81,
		0x1f, 0x35, 0x2c, 0x07,
		0x3b, 0x61, 0x08, 0xd7,
		0x2d, 0x98, 0x10, 0xa3,
		0x09, 0x14, 0xdf, 0xf4,
	};
	aes_KeyExpansion(key4, 4, 4);
	aes_KeyExpansion(key6, 4, 6);
	aes_KeyExpansion(key8, 4, 8);
} /* main */
#endif

/* $Id: keyExpansion.c,v 1.3 2003/11/27 23:03:05 luis Exp $ */
