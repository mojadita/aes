/* $Id: keyExpansion.c,v 1.8 2003/12/02 00:44:43 luis Exp $
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
#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef LINES_PER_PAGE
#define LINES_PER_PAGE 24
#endif

#if DEBUG
#include <stdio.h>
#endif

/* types */

/* prototypes */

/* variables */
static char KEYEXPANSION_C_RCSId[]="\n$Id: keyExpansion.c,v 1.8 2003/12/02 00:44:43 luis Exp $\n";

/* functions */

static void RotWord(AES_BYTE *b)
{
	register int i;

	AES_BYTE c = b[0];
	for (i = 0; i < AES_WS - 1; i++) {
		b[i] = b[i+1];
	} /* for */
	b[i] = c;
} /* RotWord */

#if DEBUG
print_header()
{
		fprintf(stderr, 
"===========================================================================\n"
"|  |          |  after  |  after  |   Rcon  |  after  |         |  after  |\n"
"| i|   temp   | RotWord | SubWord |  [i/Nk] |XOR Rcon | W[i-Nk] | W[i-Nk] |\n"
"===========================================================================\n"
		);
} /* print_header */

void aes_PrintWord(AES_BYTE *b)
{
	if (!b) {
		fprintf(stderr, "[________]");
	} else {
		register int i;
		fprintf(stderr, "[");
		for (i = 0; i < AES_WS; i++) {
			fprintf(stderr, "%02x", b[i]);
		} /* for */
		fprintf(stderr, "]");
	} /* if */
} /* aes_PrintWord */
#endif

/* Rijndael key expansion routine */
AES_BYTE *aes_KeyExpansion(AES_BYTE *k, int Nb, int Nk)
{
	AES_BYTE *res, *P;
	int i;
	int Nr = AES_Nr(Nb, Nk);
	int N = Nb*(Nr+1);
	AES_BYTE Rcon[AES_WS] = { 0x01, 0x00, 0x00, 0x00 }; 

	P = res = calloc(N, sizeof(AES_BYTE)*AES_WS);

	if (!res) return NULL;

#if DEBUG
	fprintf(stderr, "Nb = %d; Nk = %d; Nr = %d.\n", Nb, Nk, Nr);
#endif
	/* copiamos la clave */
	for (i = 0; i < Nk; i++) {
		memcpy(P, k, sizeof(AES_BYTE)*AES_WS);
#if DEBUG
		fprintf(stderr, "W[%d] = ", i); aes_PrintWord(P); fprintf(stderr, "\n");
#endif
		P += AES_WS; k += AES_WS;
	} /* for */

	/* i == Nk */
	while (i < N) {
#if DEBUG
		if ((i - Nk + LINES_PER_PAGE) % LINES_PER_PAGE == 0) {
			print_header();
		} /* if */
		fprintf(stderr, "%3d: ", i);
#endif
		memcpy(P, P-AES_WS, sizeof(AES_BYTE)*AES_WS); /* temp */
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
		if (i % Nk == 0 || ((Nk > 6) && (i % Nk == 4))) {
			aes_SubBytes(P, 1);
#if DEBUG
			aes_PrintWord(P);
		} else {
			aes_PrintWord(NULL);
#endif
		} /* if */
		if (i % Nk == 0) {
			aes_AddRoundKey(P, 1, Rcon);
#if DEBUG
			aes_PrintWord(Rcon);
			aes_PrintWord(P);
#endif
			Rcon[0] = aes_mult(Rcon[0], 0x02, AES_POL);
#if DEBUG
		} else {
			aes_PrintWord(NULL);
			aes_PrintWord(NULL);
#endif
		}
#if DEBUG
		aes_PrintWord(P-Nk*AES_WS);
#endif
		aes_AddRoundKey(P, 1, P-Nk*AES_WS);
#if DEBUG
		aes_PrintWord(P);
		fprintf(stderr, " = W[%d]", i);
		fprintf(stderr, "\n");
#endif
		i++;P += AES_WS;
	} /* while */

	return res;
} /* aes_KeyExpansion */

/* $Id: keyExpansion.c,v 1.8 2003/12/02 00:44:43 luis Exp $ */
