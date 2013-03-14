/* $Id: aes.c,v 1.14 2013/03/14 13:53:43 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
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
#ifndef DEBUG
#define DEBUG 0
#endif

/* types */

/* prototypes */

/* variables */
static char AES_C_RCSId[]="\n$Id: aes.c,v 1.14 2013/03/14 13:53:43 luis Exp $\n";

/* functions */

void aes_Cipher(AES_BYTE *b, int Nb, int Nk, AES_BYTE *eKey)
{
	AES_BYTE *rKey = eKey;
	int i;
	int Nr = AES_Nr(Nb, Nk);
	
	/* first round */
#if DEBUG
	fprintf(stderr, "==================\n");
	fprintf(stderr, "Comienzo: Entrada:\n");
	aes_PrintState(b, Nb);
	fprintf(stderr, "Comienzo: Round Key Value:\n");
	aes_PrintState(rKey, Nb);
#endif
	aes_AddRoundKey(b, Nb, rKey);
	/* Nr rounds */
	for (i = 0; i < Nr; i++) {
#if DEBUG
		fprintf(stderr, "==================\n");
		fprintf(stderr, "#%d: Estado:\n", i+1);
		aes_PrintState(b, Nb);
#endif
		aes_SubBytes(b, Nb);
#if DEBUG
		fprintf(stderr, "#%d: Tras SubBytes:\n", i+1);
		aes_PrintState(b, Nb);
#endif
		aes_ShiftRows(b, Nb);
#if DEBUG
		fprintf(stderr, "#%d: Tras ShiftRows:\n", i+1);
		aes_PrintState(b, Nb);
#endif
		if (i < Nr-1) {
			aes_MixColumns(b, Nb);
#if DEBUG
			fprintf(stderr, "#%d: Tras MixColumns:\n", i+1);
			aes_PrintState(b, Nb);
#endif
		} /* if */
		rKey += Nb*AES_WS;
#if DEBUG
		fprintf(stderr, "#%d: Round Key Value:\n", i+1);
		aes_PrintState(rKey, Nb);
#endif
		aes_AddRoundKey(b, Nb, rKey);
	} /* for */
#if DEBUG
	fprintf(stderr, "==================\n");
	fprintf(stderr, "FIN: Resultado:\n");
	aes_PrintState(b, Nb);
	fprintf(stderr, "==================\n");
#endif
	
} /* aes_Cipher */

void aes_InvCipher(AES_BYTE *b, int Nb, int Nk, AES_BYTE *eKey)
{
	int Nr = AES_Nr(Nb, Nk);
	int i;
	AES_BYTE *rKey = eKey + Nr*Nb*AES_WS; 

	/* first round */
#if DEBUG
	fprintf(stderr, "==================\n");
	fprintf(stderr, "Comienzo: Entrada:\n");
	aes_PrintState(b, Nb);
	fprintf(stderr, "Comienzo: Round Key Value:\n");
	aes_PrintState(rKey, Nb);
#endif
	aes_AddRoundKey(b, Nb, rKey);
	/* Nr rounds */
	for (i = 0; i < Nr; i++) {
#if DEBUG
		fprintf(stderr, "==================\n");
		fprintf(stderr, "#%d: Estado:\n", i+1);
		aes_PrintState(b, Nb);
#endif
		if (i > 0) {
			aes_InvMixColumns(b, Nb);
#if DEBUG
			fprintf(stderr, "#%d: Tras InvMixColumns:\n", i+1);
			aes_PrintState(b, Nb);
#endif
		} /* if */
		aes_InvShiftRows(b, Nb);
#if DEBUG
		fprintf(stderr, "#%d: Tras InvShiftRows:\n", i+1);
		aes_PrintState(b, Nb);
#endif
		aes_InvSubBytes(b, Nb);
#if DEBUG
		fprintf(stderr, "#%d: Tras InvSubBytes:\n", i+1);
		aes_PrintState(b, Nb);
#endif
		rKey -= Nb*AES_WS;
#if DEBUG
		fprintf(stderr, "#%d: Round Key Value:\n", i+1);
		aes_PrintState(rKey, Nb);
#endif
		aes_AddRoundKey(b, Nb, rKey);
	} /* for */
#if DEBUG
	fprintf(stderr, "==================\n");
	fprintf(stderr, "FIN: Resultado:\n");
	aes_PrintState(b, Nb);
	fprintf(stderr, "==================\n");
#endif
} /* aes_InvCipher */

/* $Id: aes.c,v 1.14 2013/03/14 13:53:43 luis Exp $ */
