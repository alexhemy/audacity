/*
** Copyright (C) 1999-2001 Erik de Castro Lopo <erikd@zip.com.au>
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation; either version 2.1 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
** 
** You should have received a copy of the GNU Lesser General Public License
** along with this program; if not, write to the Free Software 
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/


#include	<unistd.h>

#include	"sndfile.h"
#include	"floatcast.h"
#include	"common.h"

static int		alaw_read_alaw2s (SF_PRIVATE *psf, short *ptr, unsigned int len) ;
static int		alaw_read_alaw2i (SF_PRIVATE *psf, int *ptr, unsigned int len) ;
static int		alaw_read_alaw2f (SF_PRIVATE *psf, float *ptr, unsigned int len) ;
static int		alaw_read_alaw2d (SF_PRIVATE *psf, double *ptr, unsigned int len, int normalize) ;

static int		alaw_write_s2alaw (SF_PRIVATE *psf, short *ptr, unsigned int len) ;
static int		alaw_write_i2alaw (SF_PRIVATE *psf, int *ptr, unsigned int len) ;
static int		alaw_write_f2alaw (SF_PRIVATE *psf, float *ptr, unsigned int len) ;
static int		alaw_write_d2alaw (SF_PRIVATE *psf, double *ptr, unsigned int len, int normalize) ;

static  void    alaw2s_array      (unsigned char *buffer, unsigned int count, short *ptr, unsigned int index) ;
static  void    alaw2i_array      (unsigned char *buffer, unsigned int count, int *ptr, unsigned int index) ;
static  void    alaw2f_array      (unsigned char *buffer, unsigned int count, float *ptr, unsigned int index, float normfact) ;
static  void    alaw2d_array      (unsigned char *buffer, unsigned int count, double *ptr, unsigned int index, double normfact) ;

static  void    s2alaw_array      (short *buffer, unsigned int count, unsigned char *ptr, unsigned int index) ;
static  void    i2alaw_array      (int *buffer, unsigned int count, unsigned char *ptr, unsigned int index) ;
static  void    f2alaw_array      (float *buffer, unsigned int count, unsigned char *ptr, unsigned int index, float normfact) ;
static  void    d2alaw_array      (double *buffer, unsigned int count, unsigned char *ptr, unsigned int index, double normfact) ;

int
alaw_read_init (SF_PRIVATE *psf)
{
	psf->read_short  = (func_short)  alaw_read_alaw2s ;
	psf->read_int    = (func_int)    alaw_read_alaw2i ;
	psf->read_float  = (func_float)  alaw_read_alaw2f ;
	psf->read_double = (func_double) alaw_read_alaw2d ;

	return 0 ;
} /* alaw_read_init */

int
alaw_write_init (SF_PRIVATE *psf)
{
	psf->write_short  = (func_short)  alaw_write_s2alaw ;
	psf->write_int    = (func_int)    alaw_write_i2alaw ;
	psf->write_float  = (func_float)  alaw_write_f2alaw ;
	psf->write_double = (func_double) alaw_write_d2alaw ;

	return 0 ;
} /* alaw_read_init */

static int
alaw_read_alaw2s (SF_PRIVATE *psf, short *ptr, unsigned int len)
{	unsigned int readcount, thisread, index = 0 ;
	int		bytecount, bufferlen ;
	int		total = 0 ;

	bufferlen = (SF_BUFFER_LEN / psf->blockwidth) * psf->blockwidth ;
	bytecount = len * psf->bytewidth ;
	while (bytecount > 0)
	{	readcount = (bytecount >= bufferlen) ? bufferlen : bytecount ;
		thisread = fread (psf->buffer, 1, readcount, psf->file) ;
		alaw2s_array ((unsigned char*) (psf->buffer), thisread / psf->bytewidth, ptr, index) ;
		total += thisread ;
		if (thisread < readcount)
			break ;
		index += thisread / psf->bytewidth ;
		bytecount -= thisread ;
		} ;

	total /= psf->bytewidth ;
	if (total < len)
		psf->error = SFE_SHORT_READ ;
	
	return total ;
} /* alaw_read_alaw2s */

static int
alaw_read_alaw2i (SF_PRIVATE *psf, int *ptr, unsigned int len)
{	unsigned int readcount, thisread, index = 0 ;
	int		bytecount, bufferlen ;
	int		total = 0 ;

	bufferlen = (SF_BUFFER_LEN / psf->blockwidth) * psf->blockwidth ;
	bytecount = len * psf->bytewidth ;
	while (bytecount > 0)
	{	readcount = (bytecount >= bufferlen) ? bufferlen : bytecount ;
		thisread = fread (psf->buffer, 1, readcount, psf->file) ;
		alaw2i_array ((unsigned char*) (psf->buffer), thisread / psf->bytewidth, ptr, index) ;
		total += thisread ;
		if (thisread < readcount)
			break ;
		index += thisread / psf->bytewidth ;
		bytecount -= thisread ;
		} ;

	total /= psf->bytewidth ;
	if (total < len)
		psf->error = SFE_SHORT_READ ;
	
	return total ;
} /* alaw_read_alaw2i */

static int
alaw_read_alaw2f (SF_PRIVATE *psf, float *ptr, unsigned int len)
{	unsigned int readcount, thisread, index = 0 ;
	int		bytecount, bufferlen ;
	int		total = 0 ;
	float	normfact ;

	normfact = (psf->norm_float == SF_TRUE) ? 1.0 / ((float) 0x8000) : 1.0 ;

	bufferlen = (SF_BUFFER_LEN / psf->blockwidth) * psf->blockwidth ;
	bytecount = len * psf->bytewidth ;
	while (bytecount > 0)
	{	readcount = (bytecount >= bufferlen) ? bufferlen : bytecount ;
		thisread = fread (psf->buffer, 1, readcount, psf->file) ;
		alaw2f_array ((unsigned char*) (psf->buffer), thisread / psf->bytewidth, ptr, index, normfact) ;
		total += thisread ;
		if (thisread < readcount)
			break ;
		index += thisread / psf->bytewidth ;
		bytecount -= thisread ;
		} ;

	total /= psf->bytewidth ;
	if (total < len)
		psf->error = SFE_SHORT_READ ;
	
	return total ;
} /* alaw_read_alaw2f */

static int
alaw_read_alaw2d (SF_PRIVATE *psf, double *ptr, unsigned int len, int normalize)
{	unsigned int readcount, thisread, index = 0 ;
	int		bytecount, bufferlen ;
	int		total = 0 ;
	double	normfact ;
	
	normfact = (normalize ? 1.0 / ((double) 0x8000) : 1.0) ;
	bufferlen = (SF_BUFFER_LEN / psf->blockwidth) * psf->blockwidth ;
	bytecount = len * psf->bytewidth ;
	while (bytecount > 0)
	{	readcount = (bytecount >= bufferlen) ? bufferlen : bytecount ;
		thisread = fread (psf->buffer, 1, readcount, psf->file) ;
		alaw2d_array ((unsigned char*) (psf->buffer), thisread / psf->bytewidth, ptr, index, normfact) ;
		total += thisread ;
		if (thisread < readcount)
			break ;
		index += thisread / psf->bytewidth ;
		bytecount -= thisread ;
		} ;

	total /= psf->bytewidth ;
	if (total < len)
		psf->error = SFE_SHORT_READ ;
	
	return total ;
} /* alaw_read_alaw2d */

/*=============================================================================================
*/

static int
alaw_write_s2alaw	(SF_PRIVATE *psf, short *ptr, unsigned int len)
{	unsigned int	writecount, thiswrite, index = 0 ;
	int		bytecount, bufferlen ;
	int		total = 0 ;

	bufferlen = (SF_BUFFER_LEN / psf->blockwidth) * psf->blockwidth ;
	bytecount = len * psf->bytewidth ;
	while (bytecount > 0)
	{	writecount = (bytecount >= bufferlen) ? bufferlen : bytecount ;
		s2alaw_array (ptr, index, (unsigned char*) (psf->buffer), writecount / psf->bytewidth) ;
		thiswrite = fwrite (psf->buffer, 1, writecount, psf->file) ;
		total += thiswrite ;
		if (thiswrite < writecount)
			break ;
		index += thiswrite / psf->bytewidth ;
		bytecount -= thiswrite ;
		} ;

	total /= psf->bytewidth ;
	if (total < len)
		psf->error = SFE_SHORT_READ ;
	
	return total ;
} /* alaw_write_s2alaw */

static int
alaw_write_i2alaw	(SF_PRIVATE *psf, int *ptr, unsigned int len)
{	unsigned int	writecount, thiswrite, index = 0 ;
	int		bytecount, bufferlen ;
	int		total = 0 ;

	bufferlen = (SF_BUFFER_LEN / psf->blockwidth) * psf->blockwidth ;
	bytecount = len * psf->bytewidth ;
	while (bytecount > 0)
	{	writecount = (bytecount >= bufferlen) ? bufferlen : bytecount ;
		i2alaw_array (ptr, index, (unsigned char*) (psf->buffer), writecount / psf->bytewidth) ;
		thiswrite = fwrite (psf->buffer, 1, writecount, psf->file) ;
		total += thiswrite ;
		if (thiswrite < writecount)
			break ;
		index += thiswrite / psf->bytewidth ;
		bytecount -= thiswrite ;
		} ;

	total /= psf->bytewidth ;
	if (total < len)
		psf->error = SFE_SHORT_READ ;
	
	return total ;
} /* alaw_write_i2alaw */

static int
alaw_write_f2alaw	(SF_PRIVATE *psf, float *ptr, unsigned int len)
{	unsigned int	writecount, thiswrite, index = 0 ;
	int		bytecount, bufferlen ;
	int		total = 0 ;
	float	normfact ;

	normfact = (psf->norm_float == SF_TRUE) ? ((float) 0x8000) : 1.0 ;

	bufferlen = (SF_BUFFER_LEN / psf->blockwidth) * psf->blockwidth ;
	bytecount = len * psf->bytewidth ;
	while (bytecount > 0)
	{	writecount = (bytecount >= bufferlen) ? bufferlen : bytecount ;
		f2alaw_array (ptr, index, (unsigned char*) (psf->buffer), writecount / psf->bytewidth, normfact) ;
		thiswrite = fwrite (psf->buffer, 1, writecount, psf->file) ;
		total += thiswrite ;
		if (thiswrite < writecount)
			break ;
		index += thiswrite / psf->bytewidth ;
		bytecount -= thiswrite ;
		} ;

	total /= psf->bytewidth ;
	if (total < len)
		psf->error = SFE_SHORT_READ ;
	
	return total ;
} /* alaw_write_f2alaw */

static int
alaw_write_d2alaw	(SF_PRIVATE *psf, double *ptr, unsigned int len, int normalize)
{	unsigned int	writecount, thiswrite, index = 0 ;
	int		bytecount, bufferlen ;
	int		total = 0 ;
	double	normfact ;
	
	normfact = (normalize ? ((double) 0x8000) : 1.0) ;

	bufferlen = (SF_BUFFER_LEN / psf->blockwidth) * psf->blockwidth ;
	bytecount = len * psf->bytewidth ;
	while (bytecount > 0)
	{	writecount = (bytecount >= bufferlen) ? bufferlen : bytecount ;
		d2alaw_array (ptr, index, (unsigned char*) (psf->buffer), writecount / psf->bytewidth, normfact) ;
		thiswrite = fwrite (psf->buffer, 1, writecount, psf->file) ;
		total += thiswrite ;
		if (thiswrite < writecount)
			break ;
		index += thiswrite / psf->bytewidth ;
		bytecount -= thiswrite ;
		} ;

	total /= psf->bytewidth ;
	if (total < len)
		psf->error = SFE_SHORT_READ ;
	
	return total ;
} /* alaw_write_d2alaw */

/*=============================================================================================
 *	Private static functions and data.
 */

static	
short	alaw_decode [128] =
{	 -5504,  -5248,  -6016,  -5760,  -4480,  -4224,  -4992,  -4736, 
	 -7552,  -7296,  -8064,  -7808,  -6528,  -6272,  -7040,  -6784, 
	 -2752,  -2624,  -3008,  -2880,  -2240,  -2112,  -2496,  -2368, 
	 -3776,  -3648,  -4032,  -3904,  -3264,  -3136,  -3520,  -3392, 
	-22016, -20992, -24064, -23040, -17920, -16896, -19968, -18944, 
	-30208, -29184, -32256, -31232, -26112, -25088, -28160, -27136, 
	-11008, -10496, -12032, -11520,  -8960,  -8448,  -9984,  -9472, 
	-15104, -14592, -16128, -15616, -13056, -12544, -14080, -13568, 
	  -344,   -328,   -376,   -360,   -280,   -264,   -312,   -296, 
	  -472,   -456,   -504,   -488,   -408,   -392,   -440,   -424, 
	   -88,    -72,   -120,   -104,    -24,     -8,    -56,    -40, 
	  -216,   -200,   -248,   -232,   -152,   -136,   -184,   -168, 
	 -1376,  -1312,  -1504,  -1440,  -1120,  -1056,  -1248,  -1184, 
	 -1888,  -1824,  -2016,  -1952,  -1632,  -1568,  -1760,  -1696, 
	  -688,   -656,   -752,   -720,   -560,   -528,   -624,   -592, 
	  -944,   -912,  -1008,   -976,   -816,   -784,   -880,   -848
} ; /* alaw_decode */

static	
unsigned char	alaw_encode [2049] =
{	0xD5, 0xD4, 0xD7, 0xD6, 0xD1, 0xD0, 0xD3, 0xD2, 0xDD, 0xDC, 0xDF, 0xDE, 
	0xD9, 0xD8, 0xDB, 0xDA, 0xC5, 0xC4, 0xC7, 0xC6, 0xC1, 0xC0, 0xC3, 0xC2, 
	0xCD, 0xCC, 0xCF, 0xCE, 0xC9, 0xC8, 0xCB, 0xCA, 0xF5, 0xF5, 0xF4, 0xF4, 
	0xF7, 0xF7, 0xF6, 0xF6, 0xF1, 0xF1, 0xF0, 0xF0, 0xF3, 0xF3, 0xF2, 0xF2, 
	0xFD, 0xFD, 0xFC, 0xFC, 0xFF, 0xFF, 0xFE, 0xFE, 0xF9, 0xF9, 0xF8, 0xF8, 
	0xFB, 0xFB, 0xFA, 0xFA, 0xE5, 0xE5, 0xE5, 0xE5, 0xE4, 0xE4, 0xE4, 0xE4, 
	0xE7, 0xE7, 0xE7, 0xE7, 0xE6, 0xE6, 0xE6, 0xE6, 0xE1, 0xE1, 0xE1, 0xE1, 
	0xE0, 0xE0, 0xE0, 0xE0, 0xE3, 0xE3, 0xE3, 0xE3, 0xE2, 0xE2, 0xE2, 0xE2, 
	0xED, 0xED, 0xED, 0xED, 0xEC, 0xEC, 0xEC, 0xEC, 0xEF, 0xEF, 0xEF, 0xEF, 
	0xEE, 0xEE, 0xEE, 0xEE, 0xE9, 0xE9, 0xE9, 0xE9, 0xE8, 0xE8, 0xE8, 0xE8, 
	0xEB, 0xEB, 0xEB, 0xEB, 0xEA, 0xEA, 0xEA, 0xEA, 0x95, 0x95, 0x95, 0x95, 
	0x95, 0x95, 0x95, 0x95, 0x94, 0x94, 0x94, 0x94, 0x94, 0x94, 0x94, 0x94, 
	0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x96, 0x96, 0x96, 0x96, 
	0x96, 0x96, 0x96, 0x96, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x93, 0x93, 0x93, 0x93, 
	0x93, 0x93, 0x93, 0x93, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 
	0x9D, 0x9D, 0x9D, 0x9D, 0x9D, 0x9D, 0x9D, 0x9D, 0x9C, 0x9C, 0x9C, 0x9C, 
	0x9C, 0x9C, 0x9C, 0x9C, 0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 
	0x9E, 0x9E, 0x9E, 0x9E, 0x9E, 0x9E, 0x9E, 0x9E, 0x99, 0x99, 0x99, 0x99, 
	0x99, 0x99, 0x99, 0x99, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 
	0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9A, 0x9A, 0x9A, 0x9A, 
	0x9A, 0x9A, 0x9A, 0x9A, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 
	0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x84, 0x84, 0x84, 0x84, 
	0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 
	0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 
	0x87, 0x87, 0x87, 0x87, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 
	0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x81, 0x81, 0x81, 0x81, 
	0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 
	0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x82, 0x82, 0x82, 0x82, 
	0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 
	0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 
	0x8D, 0x8D, 0x8D, 0x8D, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 
	0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8F, 0x8F, 0x8F, 0x8F, 
	0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 
	0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 
	0x8E, 0x8E, 0x8E, 0x8E, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 
	0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x88, 0x88, 0x88, 0x88, 
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 
	0x8B, 0x8B, 0x8B, 0x8B, 0x8B, 0x8B, 0x8B, 0x8B, 0x8B, 0x8B, 0x8B, 0x8B, 
	0x8B, 0x8B, 0x8B, 0x8B, 0x8A, 0x8A, 0x8A, 0x8A, 0x8A, 0x8A, 0x8A, 0x8A, 
	0x8A, 0x8A, 0x8A, 0x8A, 0x8A, 0x8A, 0x8A, 0x8A, 0xB5, 0xB5, 0xB5, 0xB5, 
	0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 
	0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 0xB5, 
	0xB5, 0xB5, 0xB5, 0xB5, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 
	0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 
	0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 
	0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 
	0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 
	0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB7, 0xB6, 0xB6, 0xB6, 0xB6, 
	0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 
	0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 
	0xB6, 0xB6, 0xB6, 0xB6, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 
	0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 
	0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 0xB1, 
	0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 
	0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 
	0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB3, 0xB3, 0xB3, 0xB3, 
	0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 
	0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 
	0xB3, 0xB3, 0xB3, 0xB3, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 
	0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 
	0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 
	0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 
	0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 
	0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBC, 0xBC, 0xBC, 0xBC, 
	0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 
	0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 
	0xBC, 0xBC, 0xBC, 0xBC, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 
	0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 
	0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 
	0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 
	0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 
	0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xBE, 0xB9, 0xB9, 0xB9, 0xB9, 
	0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 
	0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 0xB9, 
	0xB9, 0xB9, 0xB9, 0xB9, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 
	0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 
	0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBA, 0xBA, 0xBA, 0xBA, 
	0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 
	0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 
	0xBA, 0xBA, 0xBA, 0xBA, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 
	0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 
	0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 
	0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 
	0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 
	0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA4, 0xA4, 0xA4, 0xA4, 
	0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 
	0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 
	0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 
	0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 
	0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 
	0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 
	0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 
	0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 
	0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 
	0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 
	0xA7, 0xA7, 0xA7, 0xA7, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 
	0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 
	0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 
	0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 
	0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 
	0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA1, 0xA1, 0xA1, 0xA1, 
	0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 
	0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 
	0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 
	0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 
	0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 
	0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 
	0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 
	0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 
	0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 
	0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 
	0xA0, 0xA0, 0xA0, 0xA0, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 
	0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 
	0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 
	0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 
	0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 
	0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA2, 0xA2, 0xA2, 0xA2, 
	0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 
	0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 
	0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 
	0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 
	0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 
	0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 
	0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 
	0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 
	0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 
	0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 
	0xAD, 0xAD, 0xAD, 0xAD, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 
	0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 
	0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 
	0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 
	0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 
	0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAC, 0xAF, 0xAF, 0xAF, 0xAF, 
	0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 
	0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 
	0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 
	0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 
	0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 
	0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 
	0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 
	0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 
	0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 
	0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 
	0xAE, 0xAE, 0xAE, 0xAE, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 
	0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 
	0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 
	0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 
	0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 
	0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA9, 0xA8, 0xA8, 0xA8, 0xA8, 
	0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 
	0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 
	0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 
	0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 
	0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 
	0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 
	0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 
	0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 
	0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 
	0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 
	0xAB, 0xAB, 0xAB, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x2A
} ; /* alaw_encode */

static void	
alaw2s_array	(unsigned char *buffer, unsigned int count, short *ptr, unsigned int index)
{	int 	k ;
	for (k = 0 ; k < count ; k++)
	{	if (buffer [k] & 0x80)
			ptr [index] = -1 * alaw_decode [((int) buffer [k]) & 0x7F] ;
		else
			ptr [index] = alaw_decode [((int) buffer [k]) & 0x7F] ;
		index ++ ;
		} ;
} /* alaw2s_array */

static void	
alaw2i_array	(unsigned char *buffer, unsigned int count, int *ptr, unsigned int index)
{	int 	k ;
	for (k = 0 ; k < count ; k++)
	{	if (buffer [k] & 0x80)
			ptr [index] = -1 * alaw_decode [((int) buffer [k]) & 0x7F] ;
		else
			ptr [index] = alaw_decode [((int) buffer [k]) & 0x7F] ;
		index ++ ;
		} ;
} /* alaw2i_array */

static void	
alaw2f_array	(unsigned char *buffer, unsigned int count, float *ptr, unsigned int index, float normfact)
{	int 	k ;
	for (k = 0 ; k < count ; k++)
	{	if (buffer [k] & 0x80)
			ptr [index] = -normfact * alaw_decode [((int) buffer [k]) & 0x7F] ;
		else
			ptr [index] = normfact * alaw_decode [((int) buffer [k]) & 0x7F] ;
		index ++ ;
		} ;
} /* alaw2d_array */

static void	
alaw2d_array	(unsigned char *buffer, unsigned int count, double *ptr, unsigned int index, double normfact)
{	int 	k ;
	for (k = 0 ; k < count ; k++)
	{	if (buffer [k] & 0x80)
			ptr [index] = -normfact * alaw_decode [((int) buffer [k]) & 0x7F] ;
		else
			ptr [index] = normfact * alaw_decode [((int) buffer [k]) & 0x7F] ;
		index ++ ;
		} ;
} /* alaw2d_array */

static void    
s2alaw_array      (short *ptr, unsigned int index, unsigned char *buffer, unsigned int count)
{	unsigned int	k ;

	for (k = 0 ; k < count ; k++)
	{	if (ptr [index] >= 0) 
			buffer [k] = alaw_encode [ptr [index] / 16] ;
		else
			buffer [k] = 0x7F & alaw_encode [ptr [index] / -16] ;
		index ++ ;
		} ;
} /* s2alaw_array */

static void    
i2alaw_array      (int *ptr, unsigned int index, unsigned char *buffer, unsigned int count)
{	unsigned int	k ;

	for (k = 0 ; k < count ; k++)
	{	if (ptr [index] >= 0) 
			buffer [k] = alaw_encode [ptr [index] / 16] ;
		else
			buffer [k] = 0x7F & alaw_encode [ptr [index] / -16] ;
		index ++ ;
		} ;
} /* i2alaw_array */

static void    
f2alaw_array      (float *ptr, unsigned int index, unsigned char *buffer, unsigned int count, float normfact)
{	unsigned int	k ;

	for (k = 0 ; k < count ; k++)
	{	if (ptr [index] >= 0) 
			buffer [k] = alaw_encode [(FLOAT_TO_INT (normfact * ptr [index])) / 16] ;
		else
			buffer [k] = 0x7F & alaw_encode [(FLOAT_TO_INT (normfact * ptr [index])) / -16] ;
		index ++ ;
		} ;
} /* f2alaw_array */

static void    
d2alaw_array      (double *ptr, unsigned int index, unsigned char *buffer, unsigned int count, double normfact)
{	unsigned int	k ;

	for (k = 0 ; k < count ; k++)
	{	if (ptr [index] >= 0) 
			buffer [k] = alaw_encode [(DOUBLE_TO_INT (normfact * ptr [index])) / 16] ;
		else
			buffer [k] = 0x7F & alaw_encode [(DOUBLE_TO_INT (normfact * ptr [index])) / -16] ;
		index ++ ;
		} ;
} /* d2alaw_array */

