/* $Id: keyExpansion_test.c,v 1.1 2003/12/02 00:44:43 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Tue Dec  2 01:14:38 MET 2003
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

#define IN_KEYESPANSION_TEST_C

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
static char KEYESPANSION_TEST_C_RCSId[]="\n$Id: keyExpansion_test.c,v 1.1 2003/12/02 00:44:43 luis Exp $\n";

/* functions */

/* main program */
main()
{
	AES_BYTE key4[] = {
		0x2b, 0x7e, 0x15, 0x16,
		0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88,
		0x09, 0xcf, 0x4f, 0x3c,	
	};
	AES_BYTE key6[] = {
		0x8e, 0x73, 0xb0, 0xf7,
		0xda, 0x0e, 0x64, 0x52,
		0xc8, 0x10, 0xf3, 0x2b,
		0x80, 0x90, 0x79, 0xe5,
		0x62, 0xf8, 0xea, 0xd2,
		0x52, 0x2c, 0x6b, 0x7b,
	};
	AES_BYTE key8[] = {
		0x60, 0x3d, 0xeb, 0x10,
		0x15, 0xca, 0x71, 0xbe,
		0x2b, 0x73, 0xae, 0xf0,
		0x85, 0x7d, 0x77, 0x81,
		0x1f, 0x35, 0x2c, 0x07,
		0x3b, 0x61, 0x08, 0xd7,
		0x2d, 0x98, 0x10, 0xa3,
		0x09, 0x14, 0xdf, 0xf4,
	};
	aes_KeyExpansion(key4, 4, 4);
	aes_KeyExpansion(key6, 4, 6);
	aes_KeyExpansion(key8, 4, 8);
} /* main */

/* $Id: keyExpansion_test.c,v 1.1 2003/12/02 00:44:43 luis Exp $ */
