/* $Id: aes_test.c,v 1.1 2003/12/02 00:44:43 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Tue Dec  2 01:13:08 MET 2003
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

#define IN_AES_TEST_C

/* Standard include files */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "aes.h"

/* constants */

/* types */

/* prototypes */

/* variables */
static char AES_TEST_C_RCSId[]="\n$Id: aes_test.c,v 1.1 2003/12/02 00:44:43 luis Exp $\n";

/* functions */

/* main test function */
main()
{
#define N 5
	AES_BYTE *k[N][N];
	static int t[] = { 4, 5, 6, 7, 8, };
	int i, j;

	static AES_BYTE bl[] = {
	0x00, 0x11, 0x22, 0x33,
	0x44, 0x55, 0x66, 0x77,
	0x88, 0x99, 0xaa, 0xbb,
	0xcc, 0xdd, 0xee, 0xff,
	0x00, 0x01, 0x02, 0x03,
	0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f,
	};
	static AES_BYTE cl[] = {
	0x00, 0x01, 0x02, 0x03,
	0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13,
	0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1a, 0x1b,
	0x1c, 0x1d, 0x1e, 0x1f,
	};
	fprintf(stderr, "***** Expansión de claves *****\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			fprintf(stderr, "CIFRADO RIJNDAEL PARA Nb = %d; Nk = %d; Nr = %d\n",
				t[i], t[j], AES_Nr(t[i],t[j]));
			fprintf(stderr, "============================\n");
			fprintf(stderr, "***** BLOQUE A CIFRAR ******\n");
			aes_PrintState(bl, t[i]);
			fprintf(stderr, "============================\n");
			fprintf(stderr, "***** CLAVE DE CIFRADO *****\n");
			aes_PrintState(cl, t[j]);
			fprintf(stderr, "============================\n");
			fprintf(stderr, "Expansión de clave:\n");
			k[i][j] = aes_KeyExpansion(cl, t[i], t[j]);
			fprintf(stderr, "============================\n");
			fprintf(stderr, "***** CIFRANDO *****\n");
			aes_Cipher(bl, t[i], t[j], k[i][j]);
			fprintf(stderr, "============================\n");
			fprintf(stderr, "***** DESCIFRANDO *****\n");
			aes_InvCipher(bl, t[i], t[j], k[i][j]);
			fprintf(stderr, "============================\n");
			fprintf(stderr, "***** BLOQUE DESCIFRADO *****\n");
			aes_PrintState(bl, t[i]);
			fprintf(stderr, "=============================\n");
			fprintf(stderr, "/////////////////////////////\n");
		} /*  for */
	} /* for */

	fprintf(stderr, "***** FIN DEL PROGRAMA *****\n");

} /* main */

/* $Id: aes_test.c,v 1.1 2003/12/02 00:44:43 luis Exp $ */
