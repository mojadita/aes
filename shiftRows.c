/* $Id: shiftRows.c,v 1.3 2003/11/27 23:43:14 luis Exp $
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
static char SHIFTROWS_C_RCSId[]="\n$Id: shiftRows.c,v 1.3 2003/11/27 23:43:14 luis Exp $\n";

/* functions */

static void ShiftRows(BYTE *b, int Nb, char *t)
{
	BYTE *temp = alloca(4*Nb);
	int i, j;

	/* copiamos los bytes a temp */
	memcpy(temp, b, 4*Nb);

	/* retornamos haciendo los desplazamientos */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < Nb; j++) {
			b[j*4 + i] = temp[(j + t[i] + Nb)%Nb*4 + i];
		} /* for */
	} /* for */
} /* AES_ShiftRows */

static char C1[] = { 0, 1, 2, 3 };
static char C2[] = { 0, -1, -2, -3 };
static char C3[] = { 0, 1, 2, 4 };
static char C4[] = { 0, -1, -2, -4 };
static char C5[] = { 0, 1, 3, 4 };
static char C6[] = { 0, -1, -3, -4 };

void aes_ShiftRows4(BYTE *b)
{
	ShiftRows(b, 4, C1);
} /* aes_ShiftRows4 */

void aes_InvShiftRows4(BYTE *b)
{
	ShiftRows(b, 4, C2);
} /* aes_InvShiftRows4 */

void aes_ShiftRows5(BYTE *b)
{
	ShiftRows(b, 5, C1);
} /* aes_ShiftRows5 */

void aes_InvShiftRows5(BYTE *b)
{
	ShiftRows(b, 5, C2);
} /* aes_InvShiftRows5 */

void aes_ShiftRows6(BYTE *b)
{
	ShiftRows(b, 6, C1);
} /* aes_ShiftRows6 */

void aes_InvShiftRows6(BYTE *b)
{
	ShiftRows(b, 6, C2);
} /* aes_InvShiftRows4 */

void aes_ShiftRows7(BYTE *b)
{
	ShiftRows(b, 7, C3);
} /* aes_ShiftRows8 */

void aes_InvShiftRows7(BYTE *b)
{
	ShiftRows(b, 7, C4);
} /* aes_InvShiftRows8 */

void aes_ShiftRows8(BYTE *b)
{
	ShiftRows(b, 8, C5);
} /* aes_ShiftRows8 */

void aes_InvShiftRows8(BYTE *b)
{
	ShiftRows(b, 8, C6);
} /* aes_InvShiftRows8 */

/* $Id: shiftRows.c,v 1.3 2003/11/27 23:43:14 luis Exp $ */
