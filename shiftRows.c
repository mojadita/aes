/* $Id: shiftRows.c,v 1.5 2003/12/02 00:44:43 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Sun Nov 23 01:04:51 MET 2003
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

#define IN_SHIFTROWS_C

/* Standard include files */
#include <sys/types.h>
#include <stdio.h>
#include "aes.h"

/* constants */

/* types */

/* prototypes */

/* variables */
static char SHIFTROWS_C_RCSId[]="\n$Id: shiftRows.c,v 1.5 2003/12/02 00:44:43 luis Exp $\n";

/* functions */

static void ShiftRows(AES_BYTE *b, int Nb, char *t) /* test ok */
{
	AES_BYTE *temp = alloca(AES_WS*Nb);
	int i, j;

	/* copiamos los bytes a temp */
	memcpy(temp, b, AES_WS*Nb);

	/* retornamos haciendo los desplazamientos (se suma Nb
	 * para forzar resultados positivos) */
	for (i = 0; i < AES_WS; i++) {
		for (j = 0; j < Nb; j++) {
			b[j*AES_WS + i] = temp[(j + t[i] + Nb) % Nb * AES_WS + i];
		} /* for */
	} /* for */
} /* AES_ShiftRows */

static char C1[] = { 0, 1, 2, 3 };
static char C2[] = { 0, -1, -2, -3 };
static char C3[] = { 0, 1, 2, 4 };
static char C4[] = { 0, -1, -2, -4 };
static char C5[] = { 0, 1, 3, 4 };
static char C6[] = { 0, -1, -3, -4 };

void aes_ShiftRows4(AES_BYTE *b) /* test ok */
{
	ShiftRows(b, 4, C1);
} /* aes_ShiftRows4 */

void aes_InvShiftRows4(AES_BYTE *b) /* test ok */
{
	ShiftRows(b, 4, C2);
} /* aes_InvShiftRows4 */

void aes_ShiftRows5(AES_BYTE *b) /* test ok */
{
	ShiftRows(b, 5, C1);
} /* aes_ShiftRows5 */

void aes_InvShiftRows5(AES_BYTE *b) /* test ok */
{
	ShiftRows(b, 5, C2);
} /* aes_InvShiftRows5 */

void aes_ShiftRows6(AES_BYTE *b) /* test ok */
{
	ShiftRows(b, 6, C1);
} /* aes_ShiftRows6 */

void aes_InvShiftRows6(AES_BYTE *b) /* test ok */
{
	ShiftRows(b, 6, C2);
} /* aes_InvShiftRows4 */

void aes_ShiftRows7(AES_BYTE *b) /* test ok */
{
	ShiftRows(b, 7, C3);
} /* aes_ShiftRows8 */

void aes_InvShiftRows7(AES_BYTE *b) /* test ok */
{
	ShiftRows(b, 7, C4);
} /* aes_InvShiftRows8 */

void aes_ShiftRows8(AES_BYTE *b) /* test ok */
{
	ShiftRows(b, 8, C5);
} /* aes_ShiftRows8 */

void aes_InvShiftRows8(AES_BYTE *b) /* test ok */
{
	ShiftRows(b, 8, C6);
} /* aes_InvShiftRows8 */

/* $Id: shiftRows.c,v 1.5 2003/12/02 00:44:43 luis Exp $ */
