/* $Id: main.c,v 1.7 2003/12/08 22:21:32 luis Exp $
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
#include <pwd.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "aes.h"
#include "b64.h"

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
static char MAIN_C_RCSId[]="\n$Id: main.c,v 1.7 2003/12/08 22:21:32 luis Exp $\n";

const char ext[] = ".rjndl";

struct {
	int flags;
	int Nk;
	int Nb;
	AES_BYTE *key;
	AES_BYTE *eKey;
	AES_BYTE *block;
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
"  -a Ascii output (in case of encipherment) or input (in case of decipherment)\n"
"     (base64 coded output/input)\n"
"  -A BINARY output (in case of encipherment) or input (in case of decipherment)\n"
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

void procesa_cipher(b64_st *b64_ptr, char *buffer, FILE *out)
{
	if (cfg.flags & V_FLAG) {
		fprintf(stderr, "aes:"__FILE__"(%d): procesa_cipher(...)\n",
			__LINE__);
	} /* if */

	if (cfg.flags & V_FLAG)
		fprintbuf(stderr, cfg.Nb*AES_WS, buffer, "Cifrando Bloque:");
	aes_Cipher((AES_BYTE *)buffer, cfg.Nb, cfg.Nk, cfg.eKey);
	if (cfg.flags & V_FLAG)
		fprintbuf(stderr, cfg.Nb*AES_WS, buffer, "Bloque Cifrado:");

	if (cfg.flags & A_FLAG) {
		char buff_asc[100];
		size_t n;
		n = b64_code(b64_ptr, buffer, cfg.Nb*AES_WS, buff_asc);
		fwrite(buff_asc, 1, n, out);
	} else {
		fwrite(buffer, 1, cfg.Nb*AES_WS, out);
	} /* if */
} /* procesa_cipher */

void procesa_invcipher(char *buffer, FILE *out)
{
	if (cfg.flags & V_FLAG)
		fprintbuf(stderr, cfg.Nb*AES_WS, buffer,
			"Descifrando Bloque:");
	aes_InvCipher(buffer, cfg.Nb, cfg.Nk, cfg.eKey);
	if (cfg.flags & V_FLAG)
		fprintbuf(stderr, cfg.Nb*AES_WS, buffer,
			"Bloque Descifrado:");
	fwrite(buffer, 1, cfg.Nb*AES_WS, out);
} /* procesa_invcipher */

void procesar(char *nomfich)
{
	FILE *in, *out;
	char *nomout;
	int op = 0;
	size_t bs = AES_WS*cfg.Nb;

	if (nomfich) {
		char *naux = strdup(nomfich);
		int i, l = strlen(naux);

		/* pasamos nomfich a minúsculas, para comparar la extensión */
		for (i = 0; i < l; i++)
			naux[i] = tolower(naux[i]);

		if (cfg.flags & V_FLAG) {
			fprintf(stderr, "aes:"__FILE__"(%d):procesar(\"%s\");\n",
				__LINE__, nomfich);
		} /* if */
		if (strcmp(naux + l - strlen(ext), ext) == 0) {
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
			nomout = malloc(l+strlen(ext)+1);
			sprintf(nomout, "%s%s", nomfich, ext);
			op = OP_CIPHER;
			if (cfg.flags & V_FLAG) {
				fprintf(stderr,
					"aes:"__FILE__"(%d):procesar(\"%s\"): "
					"nomout == %s; op = OP_CIPHER\n",
					__LINE__, nomfich, nomout);
			} /* if */
		} /* if */
		free(naux);
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

	switch(op) {
	case OP_CIPHER: {
		size_t leidos = 0;
		char buffer[8*AES_WS]; /* sizeof buffer debe ser mayor que bs */
		b64_st b64;
		int c;

		if (cfg.flags & A_FLAG) {
			b64_init(&b64);
		} /* if */

		while ((c = fgetc(in)) != EOF) {
			buffer[leidos++] = c;
			if (leidos == bs) {
				procesa_cipher(&b64, buffer, out);
				leidos = 0;
			} /* if */
		} /* while */
		if (leidos > 0) {
			int i;
	
			for (i = leidos; i < bs; i++) {
				buffer[i] = 0;
			} /* for */
			procesa_cipher(&b64, buffer, out);
		} /* if */
		if (cfg.flags & A_FLAG) {
			char buffer[5]; /* como máximo 5 caracteres base64 */
			size_t n;

			n = b64_code_end(&b64, buffer);
			fwrite(buffer, 1, n, out);
		} /* if */
		break;
	} /* OP_CIPHER */

	case OP_DECIPHER: {
		size_t leidos = 0;
		char *buffer = alloca(bs);
		b64_st b64;
		int c;

		if (cfg.flags & A_FLAG) {
			b64_init(&b64);
		} /* if */

		while ((c = fgetc(in)) != EOF) {
			if(!(cfg.flags & A_FLAG)) { /* no base64, insertamos el caracter */
				buffer[leidos++] = c;
			} else { /* base64, procesamos */
				char ca = c;
				char cb;
				size_t n;
				n = b64_decode(&b64, &ca, 1, &cb);
				if (n) {
					buffer[leidos++] = cb;
				} /* if */
			} /* if */

			if (leidos == bs) {
				procesa_invcipher(buffer, out);
				leidos = 0;
			} /* if */
		} /* while */
		if (leidos > 0) {
			int i;
	
			for (i = leidos; i < bs; i++) {
				buffer[i] = 0;
			} /* for */
			procesa_invcipher(buffer, out);
		} /* if */
		break;
	} /* OP_DECIPHER */

	default:
		fprintf(stderr, "aes:"__FILE__"(%d): "
			"(op != OP_CIPHER(%d)) && (op != OP_DECIPHER(%d)); "
			"(op == %d)\n",
			__LINE__, OP_CIPHER, OP_DECIPHER, op);
		fflush(stderr);
		abort();
	} /* switch */
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
	char theKey [100];

	while ((opt = getopt(argc, argv, "aAb:cdhk:p:v")) != EOF) {
		switch(opt) {
		case 'a': cfg.flags |= A_FLAG; break;
		case 'A': cfg.flags &= ~A_FLAG; break;
		case 'b': cfg.Nb = atoi(optarg); break;
		case 'c': cfg.flags |= C_FLAG; break;
		case 'd': cfg.flags &= ~C_FLAG; break;
		case 'k': cfg.Nk = atoi(optarg); break;
		case 'p': cfg.key = (AES_BYTE *)optarg; break;
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
	if (!cfg.key) {
		char *aux;
		cfg.key = (AES_BYTE *)strdup(getpass("Clave:"));
		aux = getpass("Clave(otra vez):");
		if (strcmp((char *)cfg.key, aux)) {
			fprintf(stderr, "aes: "__FILE__"(%d): Son diferentes, terminando\n",
				__LINE__);
			exit(EXIT_FAILURE);
		} /* if */
	} /* if */
	memset(theKey, '\0', sizeof theKey);
	strncpy(theKey, (char *)cfg.key, cfg.Nk*AES_WS);

	/* expansión de la clave */
	cfg.eKey = aes_KeyExpansion(theKey, cfg.Nb, cfg.Nk);

	/* proceso de ficheros/stdin. */
	argc -= optind; argv += optind;
	if (argc) {
		while (argc) {
			procesar(argv[0]);
			argc--; argv++;
		} /* while */
	} else {
		procesar(NULL); /* stdin */
	} /* if */
	exit(EXIT_SUCCESS);
} /* main */

/* $Id: main.c,v 1.7 2003/12/08 22:21:32 luis Exp $ */
