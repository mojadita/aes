/* $Id: aes.h,v 1.12 2003/11/28 20:42:13 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Tue Nov 11 00:25:04 MET 2003
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

/* Do not include anything BEFORE the line below, as it would not be
 * protected against double inclusion from other files
 */
#ifndef AES_H
#define AES_H

static char AES_H_RCSId[] = "\n$Id: aes.h,v 1.12 2003/11/28 20:42:13 luis Exp $\n";

/* constants */
#define AES_MAX(x,y) (((x)>(y))?(x):(y))
#define AES_POL 0x11b
#define AES_WS	4
#define AES_Nr(Nb,Nk) (AES_MAX((Nb),(Nk)) + 6)

/* types */
typedef unsigned int AES_BYTE;
typedef unsigned char BYTE;
typedef struct {
	BYTE w[AES_WS];
} WORD;

/* prototypes */
AES_BYTE aes_mult(AES_BYTE x, AES_BYTE y, AES_BYTE pol); /* test ok */
AES_BYTE aes_pow(AES_BYTE x, unsigned int n); /* test ok */

void aes_PrintState(BYTE *b, int Nb); /* test ok */

void aes_SubBytes(BYTE *b, int Nb); /* test ok */
void aes_InvSubBytes(BYTE *b, int Nb); /* test ok */

void aes_ShiftRows4(BYTE *b); /* test ok */
void aes_InvShiftRows4(BYTE *b); /* test ok */
void aes_ShiftRows5(BYTE *b); /* test ok */
void aes_InvShiftRows5(BYTE *b); /* test ok */
void aes_ShiftRows6(BYTE *b); /* test ok */
void aes_InvShiftRows6(BYTE *b); /* test ok */
void aes_ShiftRows7(BYTE *b); /* test ok */
void aes_InvShiftRows7(BYTE *b); /* test ok */
void aes_ShiftRows8(BYTE *b); /* test ok */
void aes_InvShiftRows8(BYTE *b); /* test ok */

void aes_MixColumns(BYTE *b, int Nb); /* test ok */
void aes_InvMixColumns(BYTE *b, int Nb); /* test ok */

void aes_AddRoundKey(BYTE *b, int Nb, BYTE *r); /* test ok */

WORD *aes_KeyExpansion(WORD *k, int Nb, int Nk); /* test ok */

void aes_Cipher(BYTE *b, int Nb, int Nk, WORD *eKey); /* test ok */
void aes_InvCipher(BYTE *b, int Nb, int Nk, WORD *eKey); /* test ok */

#endif /* AES_H */
/* Do not include anything AFTER the line above, as it would not be
 * protected against double inclusion from other files.
 */

/* $Id: aes.h,v 1.12 2003/11/28 20:42:13 luis Exp $ */
