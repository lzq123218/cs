/* $Id: sp_ip_fragbits.h,v 1.2 2001/01/02 08:06:01 roesch Exp $ */

/*
** Copyright (C) 1998,1999,2000,2001 Martin Roesch <roesch@clark.net>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/
/* Snort Detection Plugin Header for IP Fragment Bits plugin*/

#ifndef __SP_IP_FRAGBITS_H__
#define __SP_IP_FRAGBITS_H__

#include "snort.h"

#define PLUGIN_FRAG_BITS  21

#define FB_NORMAL   0
#define FB_ALL      1
#define FB_ANY      2
#define FB_NOT      3

#define FB_RB  0x8000
#define FB_DF  0x4000
#define FB_MF  0x2000

typedef struct _FragBitsData
{
    char mode;
    u_int16_t frag_bits;

} FragBitsData;

void FragBitsInit(char *, OptTreeNode *, int);
void SetupFragBits();
void ParseFragBits(char *, OptTreeNode *);
int CheckFragBits(Packet *, struct _OptTreeNode *, OptFpList *);

#endif  /* __SP_IP_FRAGBITS_H__ */
