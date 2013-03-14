/* $Id: pru.c,v 1.6 2013/03/14 13:53:43 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date:
 * Disclaimer: (C) 2003-2013 LUIS COLORADO SISTEMAS S.L.U.
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
#include <stdio.h>
#include <assert.h>
#include "aes.h"

main()
{
	AES_INT i, j, x;

	x = 0x00;
	for (i = 0; i < 0x10; i++) {
		for (j = 0; j < 0x10; j++, x++) {
			printf("aes_SubByte(0x%02x) -> 0x%02x\n", x, aes_SubByte(x));
		} /* for */
	} /* for */
	puts("");
	x = 0x00;
	for (i = 0; i < 0x10; i++) {
		for (j = 0; j < 0x10; j++, x++) {
			printf("aes_InvSubByte(0x%02x) -> 0x%02x\n", x, aes_InvSubByte(x));
		} /* for */
	} /* for */
} /* main */

/* $Id: pru.c,v 1.6 2013/03/14 13:53:43 luis Exp $ */
