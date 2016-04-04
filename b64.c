/* $Id: b64.c,v 1.2 2013/03/14 13:53:43 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
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
static char B64_C_RCSId[]="\n$Id: b64.c,v 1.2 2013/03/14 13:53:43 luis Exp $\n";

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

static int b64_table[] = {
    /* ====  0x0 0x1 0x2 0x3 0x4 0x5 0x6 0x7 0x8 0x9 0xa 0xb 0xc 0xd 0xe 0xf */
    /* 0x00 */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    /* 0x10 */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    /* 0x20 */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
    /*        
    /* 0x30 */52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
    /* 0x40 */-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    /* 0x50 */15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
    /* 0x60 */-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    /* 0x70 */41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
};

size_t b64_decode(
	b64_st *s,
	unsigned char *b,
	size_t n,
	unsigned char *ob)
{
	size_t res = 0;

	if (s->n == -1) return res;
	for (;n;b++,n--) {
		int p;
		unsigned char c;

		if (isspace(*b))
			continue;
        if (*b & 0x80)
            continue;
        if ((p = b64_table[*b]) < 0) {
            s->n = -1;
            break;
        }
		c = p;

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

/* $Id: b64.c,v 1.2 2013/03/14 13:53:43 luis Exp $ */
