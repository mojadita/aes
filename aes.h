/* $Id: aes.h,v 1.7 2003/11/17 11:30:34 luis Exp $
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

static char AES_H_RCSId[] = "\n$Id: aes.h,v 1.7 2003/11/17 11:30:34 luis Exp $\n";

/* constants */
#define AES_POL 0x11b
#define AES_WS	4
#define AES_MAX_Nb	8
#define AES_MAX_Nk	8
#define AES_MAX_Nr	14
#define AES_MAX_Nrk	(AES_MAX_Nb*(AES_MAX_Nr+1))

/* types */
typedef unsigned int AES_BYTE;
typedef unsigned char BYTE;
typedef BYTE AES_STATE[AES_MAX_Nb][AES_WS];
typedef BYTE AES_ROUNDS[AES_MAX_Nrk][AES_WS];

typedef struct AES_State {
	size_t Nb;
	size_t Nk;
	size_t Nr;
	AES_STATE State;
	AES_ROUNDS RoundKey;
} AES_State;

/* prototypes */
AES_BYTE aes_mult(AES_BYTE x, AES_BYTE y, AES_BYTE pol); /* test ok */
AES_BYTE aes_pow(AES_BYTE x, unsigned int n); /*test ok */

AES_BYTE aes_SubByte(AES_BYTE n);
AES_BYTE aes_InvSubByte(AES_BYTE n);
void aes_SubBytes(BYTE *b, size_t n);
void aes_InvSubBytes(BYTE *b, size_t n);

#endif /* AES_H */
/* Do not include anything AFTER the line above, as it would not be
 * protected against double inclusion from other files.
 */

/* $Id: aes.h,v 1.7 2003/11/17 11:30:34 luis Exp $ */
