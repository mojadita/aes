/* $Id: main.c,v 1.1 2003/11/29 10:44:25 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Fri Nov 28 21:48:59 MET 2003
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

#define IN_MAIN_C

/* Standard include files */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "aes.h"

/* constants */
#define C_FLAG	0x01
#define A_FLAG	0x02
#define V_FLAG	0x04
#define H_FLAG	0x08
#define OP_CIPHER 1
#define OP_DECIPHER	2

/* types */

/* prototypes */

/* variables */
static char MAIN_C_RCSId[]="\n$Id: main.c,v 1.1 2003/11/29 10:44:25 luis Exp $\n";

const char ext[] = ".rjndl";

struct {
	int flags;
	int Nk;
	int Nb;
	WORD *key;
	WORD *eKey;
	BYTE *block;
} cfg = {
	C_FLAG | A_FLAG,
	4,
	4,
	NULL,
	NULL,
	NULL,
};

/* functions */
void do_usage(void)
{
	printf(
"Usage: aes [ options ... ] [ file ... ]\n"
"Options:\n"
"  -k <number>\n"
"     This option sets the Key Block Size in 4 byte words. The key block\n"
"	 input is truncated or padded with zeros to get the required size.\n"
"	 Default: 4 (128 bit key). Possible values: 4, 5, 6, 7, 8.\n"
"  -p <password>\n"
"     Password to use. In case this option is not specified, it will be\n"
"     asked, via getpass(3).\n"
"  -b <number>\n"
"     This option sets the Block Size in 4 byte words. The input file\n"
"	 is padded with zero bytes until a full number of blocks is filled\n"
"	 with data.\n"
"	 Default: 4 (128 bit block). Possible values: 4, 5, 6, 7, 8.\n"
"  -c\n"
"     Use this option to cipher. Default option.\n"
"  -d\n"
"     Use this option to uncipher.\n"
"  -v\n"
"     Be verbose. Show info about what aes is doing.\n"
"  -h\n"
"     Help. This help screen.\n"
	);
} /* do_usage */
void procesa_bloque(int op, char *buffer, FILE *out)
{
	if (cfg.flags & V_FLAG) {
		fprintf(stderr, "aes:"__FILE__"(%d): procesa_bloque(...)\n",
			__LINE__);
	} /* if */
	switch(op) {
	case OP_CIPHER:
		aes_Cipher((BYTE *)buffer, cfg.Nb, cfg.Nk, cfg.eKey); break;
	case OP_DECIPHER:
		aes_InvCipher((BYTE *)buffer, cfg.Nb, cfg.Nk, cfg.eKey); break;
	default: abort();
	} /* switch */
	fwrite(buffer, cfg.Nb*AES_WS, 1, out);
} /* procesa_bloque */

void procesar(char *nomfich)
{
	FILE *in, *out;
	char *nomout;
	int op = 0;
	int leidos;
	char buffer[100];

	if (nomfich) {
		if (cfg.flags & V_FLAG) {
			fprintf(stderr, "aes:"__FILE__"(%d):procesar(\"%s\");\n",
				__LINE__, nomfich);
		} /* if */
		if (strcmp(nomfich + strlen(nomfich) - strlen(ext), ext) == 0) {
			/* enciphered file, decrypt */
			nomout = strdup(nomfich);
			nomout[strlen(nomfich) - strlen(ext)] = '\0';
			op = OP_DECIPHER;
			if (cfg.flags & V_FLAG) {
				fprintf(stderr,
					"aes:"__FILE__"(%d):procesar(\"%s\"): "
					"nomout == %s; op = OP_DECIPHER\n",
					__LINE__, nomfich, nomout);
			} /* if */
		} else {
			nomout = malloc(strlen(nomfich)+strlen(ext)+1);
			sprintf(nomout, "%s%s", nomfich, ext);
			op = OP_CIPHER;
			if (cfg.flags & V_FLAG) {
				fprintf(stderr,
					"aes:"__FILE__"(%d):procesar(\"%s\"): "
					"nomout == %s; op = OP_CIPHER\n",
					__LINE__, nomfich, nomout);
			} /* if */
		} /* if */
		in = fopen(nomfich, "r");
		if (!in) {
			fprintf(stderr, "aes:"__FILE__"(%d):%s:%s(%d)\n",
				__LINE__, nomfich, sys_errlist[errno], errno);
			return;
		} /* if */
		out = fopen(nomout, "w");
		if (!out) {
			fprintf(stderr, "aes:"__FILE__"(%d):%s:%s(%d)\n",
				__LINE__, nomout, sys_errlist[errno], errno);
			return;
		} /* if */
	} else {
		op = (cfg.flags & C_FLAG) ? OP_CIPHER : OP_DECIPHER;
		in = stdin;
		out = stdout;
		if (cfg.flags & V_FLAG) {
			fprintf(stderr,
				"aes:"__FILE__"(%d):procesar(<<stdin>>): "
				"out == stdout; op = %s\n",
				__LINE__,
				(cfg.flags & C_FLAG)
					? "OP_CIPHER"
					: "OP_DECIPHER");
		} /* if */
	} /* if */
	while ((leidos = fread(buffer, 1, cfg.Nb*AES_WS, in)) == cfg.Nb*AES_WS) {
		if (cfg.flags & V_FLAG) {
			fprintf(stderr,
				"aes:"__FILE__"(%d):procesar(...): lectura completa\n",
				__LINE__);
		} /* if */
		procesa_bloque(op, buffer, out);
	} /* while */
	if (leidos > 0) {
		int i;

		if (cfg.flags & V_FLAG) {
			fprintf(stderr,
				"aes:"__FILE__"(%d):procesar(...): lectura incompleta (leidos == %d)\n",
				__LINE__, leidos);
		} /* if */
		for (i = leidos; i < cfg.Nb*AES_WS; i++) {
			buffer[i] = 0;
		} /* for */
		procesa_bloque(op, buffer, out);
	}
	if (nomfich) {
		fclose(in); fclose(out);
	} /* if */

} /* procesar */

/* main program */
int main (int argc, char **argv)
{

	extern int optind;
	extern char *optarg;
	int opt;

	while ((opt = getopt(argc, argv, "ab:cdhk:p:v")) != EOF) {
		switch(opt) {
		case 'a': cfg.flags |= A_FLAG; break;
		case 'b': cfg.Nb = atoi(optarg); break;
		case 'c': cfg.flags |= C_FLAG; break;
		case 'd': cfg.flags &= ~C_FLAG; break;
		case 'k': cfg.Nk = atoi(optarg); break;
		case 'v': cfg.flags |= V_FLAG; break;
		case 'h': default: cfg.flags |= H_FLAG; break;
		} /* switch */
	} /* while */
	/* testeo de errores en los datos */
	if (cfg.flags & H_FLAG
		|| cfg.Nb < 4 || cfg.Nb > 8
		|| cfg.Nk < 4 || cfg.Nk > 8)
	{
		do_usage();
		exit(EXIT_FAILURE);
	} /* if */
	/* proceso de la clave */
	cfg.key = getpass("Clave:");
	cfg.eKey = aes_KeyExpansion(cfg.key, cfg.Nb, cfg.Nk);
	argc -= optind; argv += optind;
	if (argc) {
		while (argc) {
			procesar(argv[0]);
		} /* while */
	} else {
		procesar(NULL); /* stdin */
	} /* if */
	exit(EXIT_SUCCESS);
} /* main */

/* $Id: main.c,v 1.1 2003/11/29 10:44:25 luis Exp $ */
