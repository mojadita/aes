/* $Id: b64.c,v 1.1 2003/12/08 22:07:18 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Sun Oct 12 17:37:07 MEST 2003
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

#define IN_B64_C

/* Standard include files */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "b64.h"

/* constants */

/* variables */
static char B64_C_RCSId[]="\n$Id: b64.c,v 1.1 2003/12/08 22:07:18 luis Exp $\n";

static char ct[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";

/* functions */
void b64_init(b64_st *s)
{
	s->n = s->bits = s->i = 0;
} /* b64_init */

size_t b64_code(
	b64_st *s,
	unsigned char *b,
	size_t n,
	unsigned char *ob)
{
	size_t res = 0;

	for(;n;b++,n--) {
		switch(s->n) {
		case 0: /* primer byte */
			*ob++ = ct[          (b[0]>>2)]; res++;
			s->bits = (b[0]&0x03) << 4;
			s->i++;
			s->n = 2; break;
		case 2: /* segundo byte */
			*ob++ = ct[s->bits | (b[0]>>4)]; res++;
			s->bits = (b[0]&0x0f) << 2;
			s->i++;
			s->n = 4; break;
		case 4: /* tercer byte */
			*ob++ = ct[s->bits | (b[0]>>6)]; res++; s->i++;
			*ob++ = ct[b[0]&0x3f]; res++;
			if (++s->i >= 64) { s->i = 0; *ob++ = '\n'; res++; }
			s->bits = s->n = 0; break;
		} /* switch */
	} /* for */

	return res;
} /* b64_code */

size_t b64_decode(
	b64_st *s,
	unsigned char *b,
	size_t n,
	unsigned char *ob)
{
	size_t res = 0;

	if (s->n == -1) return res;
	for (;n;b++,n--) {
		char *p;
		unsigned char c;

		if (isspace(b[0]))
			continue;

		p = strchr(ct, b[0]);
		if (!p) {
			s->n = -1;
			break;
		}
		c = p - ct;

		switch(s->n) {
		case 0:
			s->bits = c << 2; s->n = 6; break;
		case 2:
			*ob++ = s->bits | (c     ); res++;
			s->bits = 0; s->n = 0; break;
		case 4:
			*ob++ = s->bits | (c >> 2); res++;
			s->bits = (c & 0x03) << 6; s->n = 2; break;
		case 6:
			*ob++ = s->bits | (c >> 4); res++;
			s->bits = (c & 0x0f) << 4; s->n = 4; break;
		} /* switch */
	} /* for */
	return res;
} /* b64_decode */

size_t b64_code_end(
	b64_st *s,
	unsigned char *ob)
{
	size_t res = 0;

	switch(s->n) {
	case 0: /* bytes múltiplo de tres, la salida tiene múltiplo de 4 bytes */
		break; 
	case 2: /* solo hay un byte, ponemos el segundo y los dos terminadores */
		*ob++ = ct[s->bits]; res++;
		*ob++ = '='; res++;
		*ob++ = '='; res++;
		break;
	case 4: /* hay dos bytes, ponemos el tercero y el terminador */
		*ob++ = ct[s->bits]; res++;
		*ob++ = '='; res++;
		break;
	} /* switch */
	*ob++ = '\n'; res++;
	s->bits = s->n = s->i = 0;

	return res;
} /* b64_code_end */

size_t b64_decode_end(b64_st *s, unsigned char *ob)
{
	size_t res = 0;
	char *p;
	unsigned char c;

	switch(s->n) {
	case 0: break;
	case 2: case 4: case 6:
		*ob++ = s->bits; res++;
		s->bits = s->n = 0; break;
	} /* switch */

	return res;
} /* b64_decode_end */

/* $Id: b64.c,v 1.1 2003/12/08 22:07:18 luis Exp $ */
