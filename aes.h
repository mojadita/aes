/* $Id: aes.h,v 1.13 2003/12/02 00:44:43 luis Exp $
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

static char AES_H_RCSId[] = "\n$Id: aes.h,v 1.13 2003/12/02 00:44:43 luis Exp $\n";

/* constants */
#define AES_MAX(x,y) (((x)>(y))?(x):(y))
#define AES_POL 0x11b
#define AES_WS	4
#define AES_Nr(Nb,Nk) (AES_MAX((Nb),(Nk)) + 6)

/* types */
typedef unsigned int AES_INT;
typedef unsigned char AES_BYTE;

/* prototypes */
AES_INT aes_mult(AES_INT x, AES_INT y, AES_INT pol); /* test ok */
AES_INT aes_pow(AES_INT x, unsigned int n); /* test ok */

void aes_PrintState(AES_BYTE *b, int Nb); /* test ok */

void aes_SubBytes(AES_BYTE *b, int Nb); /* test ok */
void aes_InvSubBytes(AES_BYTE *b, int Nb); /* test ok */

void aes_ShiftRows4(AES_BYTE *b); /* test ok */
void aes_InvShiftRows4(AES_BYTE *b); /* test ok */
void aes_ShiftRows5(AES_BYTE *b); /* test ok */
void aes_InvShiftRows5(AES_BYTE *b); /* test ok */
void aes_ShiftRows6(AES_BYTE *b); /* test ok */
void aes_InvShiftRows6(AES_BYTE *b); /* test ok */
void aes_ShiftRows7(AES_BYTE *b); /* test ok */
void aes_InvShiftRows7(AES_BYTE *b); /* test ok */
void aes_ShiftRows8(AES_BYTE *b); /* test ok */
void aes_InvShiftRows8(AES_BYTE *b); /* test ok */

void aes_MixColumns(AES_BYTE *b, int Nb); /* test ok */
void aes_InvMixColumns(AES_BYTE *b, int Nb); /* test ok */

void aes_AddRoundKey(AES_BYTE *b, int Nb, AES_BYTE *r); /* test ok */

AES_BYTE *aes_KeyExpansion(AES_BYTE *k, int Nb, int Nk); /* test ok */

void aes_Cipher(AES_BYTE *b, int Nb, int Nk, AES_BYTE *eKey); /* test ok */
void aes_InvCipher(AES_BYTE *b, int Nb, int Nk, AES_BYTE *eKey); /* test ok */

#endif /* AES_H */
/* Do not include anything AFTER the line above, as it would not be
 * protected against double inclusion from other files.
 */

/* $Id: aes.h,v 1.13 2003/12/02 00:44:43 luis Exp $ */
