/* $Id: addRoundKey.c,v 1.4 2013/03/14 13:53:42 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: Wed Nov 26 21:17:05 MET 2003
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

#define IN_ADDROUNDKEY_C

/* Standard include files */
#include <sys/types.h>
#include "aes.h"

/* constants */

/* types */

/* prototypes */

/* variables */
static char ADDROUNDKEY_C_RCSId[]="\n$Id: addRoundKey.c,v 1.4 2013/03/14 13:53:42 luis Exp $\n";

/* functions */

void aes_AddRoundKey(AES_BYTE *b, int Nb, AES_BYTE *r)
{
	register int i;

	Nb *= AES_WS;
	for (i = 0; i < Nb; i++) {
		*b++ ^= *r++;
	} /* for */

} /* aes_AddRoundKey */

/* $Id: addRoundKey.c,v 1.4 2013/03/14 13:53:42 luis Exp $ */
