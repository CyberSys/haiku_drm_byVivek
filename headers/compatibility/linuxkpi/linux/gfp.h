/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013-2017 Mellanox Technologies, Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD$
 */
#ifndef	_LINUX_GFP_H_
#define	_LINUX_GFP_H_

#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/systm.h>
#include <sys/malloc.h>

#include <linux/page.h>

#include <vm/vm_param.h>
#include <vm/vm_object.h>
#include <vm/vm_extern.h>
#include <vm/vm_kern.h>

#define M_WAITOK	0x01u
#define M_NOWAIT	0x02u
#define M_USE_RESERVE	0x04u
#define M_ZERO	__GFP_ZERO

#define	__GFP_NOWARN	0
#define	__GFP_HIGHMEM	0
#define	__GFP_ZERO	0x08u
#define	__GFP_NORETRY	0
#define	__GFP_RECLAIM   0
#define	__GFP_RECLAIMABLE   0

#define	__GFP_IO	0
#define	__GFP_NO_KSWAPD	0
#define	__GFP_WAIT	M_WAITOK
#define	__GFP_DMA32	0x10u

#define	GFP_NOWAIT	M_NOWAIT
#define	GFP_ATOMIC	(M_NOWAIT | M_USE_RESERVE)
#define	GFP_KERNEL	M_WAITOK
#define	GFP_USER	M_WAITOK
#define	GFP_HIGHUSER	M_WAITOK
#define	GFP_HIGHUSER_MOVABLE	M_WAITOK
#define	GFP_IOFS	M_NOWAIT
#define	GFP_NOIO	M_NOWAIT
#define	GFP_DMA32	__GFP_DMA32
#define	GFP_TEMPORARY	M_NOWAIT
#define	GFP_NATIVE_MASK	(M_NOWAIT | M_WAITOK | M_USE_RESERVE | M_ZERO)


#endif	/* _LINUX_GFP_H_ */
