/* $Id: aes.h,v 1.1.1.1 2003/11/11 23:54:47 luis Exp $
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

static char AES_H_RCSId[] = "\n$Id: aes.h,v 1.1.1.1 2003/11/11 23:54:47 luis Exp $\n";

/* constants */
#define AES_POL 0x11b

/* types */

/* prototypes */
int aes_mult(int x, int y); /* test ok */

#endif /* AES_H */
/* Do not include anything AFTER the line above, as it would not be
 * protected against double inclusion from other files.
 */

/* $Id: aes.h,v 1.1.1.1 2003/11/11 23:54:47 luis Exp $ */
