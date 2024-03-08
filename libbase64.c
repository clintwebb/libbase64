/***************************************************************************
 *   Copyright (C) 2007-2024 by Clinton Webb,,,                            *
 *   Copyright (C) 2006-2007 by Hyper-Active Systems,,,                    *
 *   Copyright (C) 2003-2005 by Clinton Webb,,,                            *
 *   webb.clint@gmail.com                                                  *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "base64.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#if (BASE64_VERSION != 0x00000100)
#error "Incorrect header version.  code and header versions must match."
#endif


static char _codes[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static unsigned char _reverse[123] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  62,
	0,  0,  0,  63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0,  0,  0,  0,  0,  0,  0,  0,
	1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 0,  0,  0,  0,  0,  0,  26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };
static int mod_table[] = {0, 2, 1};


char *base64_encode(const unsigned char *data, int input_length, int *output_length) 
{
    int i, j;

    *output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = malloc(*output_length);
    if (encoded_data == NULL) return NULL;

    for (i=0, j=0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = _codes[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = _codes[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = _codes[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = _codes[(triple >> 0 * 6) & 0x3F];
    }

    for (i=0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    return encoded_data;
}



//-----------------------------------------------------------------------------
// Decode a sequence of 4 byte base64 blocks into a 3 byte binary block stream.
// the base64 encoded stream should be a null-terminated string.
int base64_decode(char *source, unsigned char *output, int *buflen)
{
	int len;
	int newlen;
	int i, j, used;
	char *in;
	unsigned char *out;
	unsigned char ch;
	
	assert(source && output && buflen);
	assert(buflen[0] > 0);

	len = strlen(source);
	assert(len > 0);
	
	newlen = 0;
	for(i=0,j=0,in=source,out=output; j<len; i+=3,j+=4,in+=4,out+=3) {
		while(*in == '\n' || *in == '\r' || *in == ' ' || *in == '\t') {
			j++;
			in++;
		}

		assert(j < len);
		assert((i+3)<buflen[0]);
		assert(newlen == i);
		
		assert(in && out);
		assert(in[0] != '=' && in[0] != 0);
		assert(in[1] != '=' && in[1] != 0);
		
		used = 1;
		out[0] = (_reverse[(int)in[0]]) << 2;
		ch = _reverse[(int)in[1]];
		out[0] |= ((ch >> 4) & 0x03);
		if (in[2] != '=') {
			used ++;
			out[1] = ((ch & 0x0f) << 4);
			ch = _reverse[(int)in[2]];
			out[1] |= (ch >> 2);
			
			if (in[3] != '=') {
				used ++;
				out[2] = (ch & 0x03) << 6;
				out[2] |= _reverse[(int)in[3]];
			}
		}
		
		assert(used > 0 && used <= 3);
		newlen += used;
		assert(newlen < len);
		assert(newlen < *buflen);
	}
	assert(newlen < *buflen);
	output[newlen] = '\0';
	
	buflen[0] = newlen;
	
	return(0);
}





