/* $Id: aes.c,v 1.9 2003/11/29 10:44:25 luis Exp $
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
#define DEBUG 0
#define MAIN 0

/* types */

/* prototypes */

/* variables */
static char AES_C_RCSId[]="\n$Id: aes.c,v 1.9 2003/11/29 10:44:25 luis Exp $\n";

/* functions */

void aes_Cipher(BYTE *b, int Nb, int Nk, WORD *eKey)
{
	WORD *rKey = eKey;
	int i;
	int Nr = AES_Nr(Nb, Nk);
	
	/* first round */
#if DEBUG
	printf("Comienzo: Entrada:\n");
	aes_PrintState(b, Nb);
	printf("Comienzo: Round Key Value:\n");
	aes_PrintState((BYTE *)rKey, Nb);
#endif
	aes_AddRoundKey(b, Nb, (BYTE *)rKey);
	/* Nr rounds */
	for (i = 0; i < Nr; i++) {
#if DEBUG
		printf("Ronda #%d: Estado:\n", i+1);
		aes_PrintState(b, Nb);
#endif
		aes_SubBytes(b, Nb);
#if DEBUG
		printf("Ronda #%d: Tras SubBytes:\n", i+1);
		aes_PrintState(b, Nb);
#endif
		switch(Nb) {
		case 4: aes_ShiftRows4(b); break;
		case 5: aes_ShiftRows5(b); break;
		case 6: aes_ShiftRows6(b); break;
		case 7: aes_ShiftRows7(b); break;
		case 8: aes_ShiftRows8(b); break;
		default:
			fprintf(stderr, __FILE__"(%d): aes_Cipher: Nb not in {4..8} (%d)\n",
				__LINE__, Nb);
			fflush(stderr);
			abort();
		} /* switch */
#if DEBUG
		printf("Ronda #%d: Tras ShiftRows:\n", i+1);
		aes_PrintState(b, Nb);
#endif
		if (i < Nr-1) {
			aes_MixColumns(b, Nb);
#if DEBUG
			printf("Ronda #%d: Tras MixColumns:\n", i+1);
			aes_PrintState(b, Nb);
#endif
		} /* if */
		rKey += Nb;
#if DEBUG
		printf("Ronda #%d: Round Key Value:\n", i+1);
		aes_PrintState((BYTE *)rKey, Nb);
#endif
		aes_AddRoundKey(b, Nb, (BYTE *)rKey);
	} /* for */
#if DEBUG
	printf("FIN: Resultado:\n");
	aes_PrintState(b, Nb);
#endif
	
} /* aes_Cipher */

void aes_InvCipher(BYTE *b, int Nb, int Nk, WORD *eKey)
{
	int Nr = AES_Nr(Nb, Nk);
	int i;
	WORD *rKey = eKey + Nr*Nb;

	/* first round */
#if DEBUG
	printf("Comienzo: Entrada:\n");
	aes_PrintState(b, Nb);
	printf("Comienzo: Round Key Value:\n");
	aes_PrintState((BYTE *)rKey, Nb);
#endif
	aes_AddRoundKey(b, Nb, (BYTE *)rKey);
	/* Nr rounds */
	for (i = 0; i < Nr; i++) {
#if DEBUG
		printf("Ronda %d: Estado:\n", i+1);
		aes_PrintState(b, Nb);
#endif
		if (i > 0) {
			aes_InvMixColumns(b, Nb);
#if DEBUG
			printf("Ronda %d: Tras InvMixColumns:\n", i+1);
			aes_PrintState(b, Nb);
#endif
		} /* if */
		switch(Nb) {
		case 4: aes_InvShiftRows4(b); break;
		case 5: aes_InvShiftRows5(b); break;
		case 6: aes_InvShiftRows6(b); break;
		case 7: aes_InvShiftRows7(b); break;
		case 8: aes_InvShiftRows8(b); break;
		default:
			fprintf(stderr, __FILE__"(%d): aes_InvCipher: Nb not in {4..8} (%d)\n",
				__LINE__, Nb);
			fflush(stderr);
			abort();
		} /* switch */
#if DEBUG
		printf("Ronda %d: Tras InvShiftRows:\n", i+1);
		aes_PrintState(b, Nb);
#endif
		aes_InvSubBytes(b, Nb);
#if DEBUG
		printf("Ronda %d: Tras InvSubBytes:\n", i+1);
		aes_PrintState(b, Nb);
#endif
		rKey -= Nb;
#if DEBUG
		printf("Ronda %d: Round Key Value:\n", i+1);
		aes_PrintState((BYTE *)rKey, Nb);
#endif
		aes_AddRoundKey(b, Nb, (BYTE *)rKey);
	} /* for */
#if DEBUG
	printf("FIN: Resultado:\n");
	aes_PrintState(b, Nb);
#endif
} /* aes_InvCipher */

#if MAIN
main()
{
#define N 5
	WORD *k[N][N];
	static int t[] = { 4, 5, 6, 7, 8, };
	int i, j;

	static BYTE bl[] = {
	0x00, 0x11, 0x22, 0x33,
	0x44, 0x55, 0x66, 0x77,
	0x88, 0x99, 0xaa, 0xbb,
	0xcc, 0xdd, 0xee, 0xff,
	0x00, 0x01, 0x02, 0x03,
	0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f,
	};
	static WORD cl[] = {
	{ { 0x00, 0x01, 0x02, 0x03, } },
	{ { 0x04, 0x05, 0x06, 0x07, } },
	{ { 0x08, 0x09, 0x0a, 0x0b, } },
	{ { 0x0c, 0x0d, 0x0e, 0x0f, } },
	{ { 0x10, 0x11, 0x12, 0x13, } },
	{ { 0x14, 0x15, 0x16, 0x17, } },
	{ { 0x18, 0x19, 0x1a, 0x1b, } },
	{ { 0x1c, 0x1d, 0x1e, 0x1f, } },
	};
	printf("***** Expansión de claves *****\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("CIFRADO RIJNDAEL PARA Nb = %d; Nk = %d; Nr = %d\n",
				t[i], t[j], AES_Nr(t[i],t[j]));
			printf("Expansión de clave:\n");
			printf("***** BLOQUE A CIFRAR ******\n");
			aes_PrintState(bl, t[i]);
			printf("***** CLAVE DE CIFRADO *****\n");
			aes_PrintState((BYTE *)cl, t[j]);
			printf("============================\n");
			k[i][j] = aes_KeyExpansion(cl, t[i], t[j]);
			printf("============================\n");
			printf("***** CIFRANDO *****\n");
			aes_Cipher(bl, t[i], t[j], k[i][j]);
			printf("============================\n");
			printf("***** DESCIFRANDO *****\n");
			aes_InvCipher(bl, t[i], t[j], k[i][j]);
			printf("***** BLOQUE DESCIFRADO *****\n");
			aes_PrintState(bl, t[i]);
			printf("=============================\n");
			printf("/////////////////////////////\n");
		} /*  for */
	} /* for */

	printf("***** FIN DEL PROGRAMA *****\n");

} /* main */
#endif

/* $Id: aes.c,v 1.9 2003/11/29 10:44:25 luis Exp $ */
