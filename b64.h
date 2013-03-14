/* $Id: b64.h,v 1.2 2013/03/14 13:53:43 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: Sun Oct 12 17:30:47 MEST 2003
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
#ifndef B64_H
#define B64_H

static char B64_H_RCSId[] = "\n$Id: b64.h,v 1.2 2013/03/14 13:53:43 luis Exp $\n";

/* constants */

/* types */
typedef struct b64_st {
	unsigned n:3;
	unsigned i:7;
	unsigned bits:8;
} b64_st;

/* prototypes */
void b64_init(b64_st *);
size_t b64_code(b64_st *, unsigned char *, size_t, unsigned char *);
size_t b64_decode(b64_st *, unsigned char *, size_t, unsigned char *);
size_t b64_code_end(b64_st *, unsigned char *);
size_t b64_decode_end(b64_st *, unsigned char *);

#endif /* B64_H */
/* Do not include anything AFTER the line above, as it would not be
 * protected against double inclusion from other files.
 */

/* $Id: b64.h,v 1.2 2013/03/14 13:53:43 luis Exp $ */
