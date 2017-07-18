/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013-2016 Mellanox Technologies, Ltd.
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
#ifndef	_LINUX_PAGE_H_
#define _LINUX_PAGE_H_

#include <linux/types.h>
#include <linux/gfp.h>

#include <freebsd/vm/vm.h>

#include <KernelExport.h>

#define vm_memattr_t		uint32
#define VM_MEMATTR_DEFAULT	B_MTR_WB
typedef unsigned long linux_pte_t;
typedef unsigned long linux_pmd_t;
typedef unsigned long linux_pgd_t;
typedef unsigned long pgprot_t;

#define page	vm_page

#define	LINUXKPI_PROT_VALID (1 << 4)
#define	LINUXKPI_CACHE_MODE_SHIFT 3

static inline pgprot_t
cachemode2protval(vm_memattr_t attr)
{
	return ((attr | LINUXKPI_PROT_VALID) << LINUXKPI_CACHE_MODE_SHIFT);
}

static inline vm_memattr_t
pgprot2cachemode(pgprot_t prot)
{
	int val;

	val = prot >> LINUXKPI_CACHE_MODE_SHIFT;

	if (val & LINUXKPI_PROT_VALID)
		return (val & ~LINUXKPI_PROT_VALID);
	else
		return (VM_MEMATTR_DEFAULT);
}

#define	virt_to_page(x)		PHYS_TO_VM_PAGE(vtophys((x)))
#define	page_to_pfn(pp)		(VM_PAGE_TO_PHYS((pp)) >> PAGE_SHIFT)
#define	pfn_to_page(pfn)	(PHYS_TO_VM_PAGE((pfn) << PAGE_SHIFT))
#define	nth_page(page,n)	pfn_to_page(page_to_pfn((page)) + (n))

#define	clear_page(page)		memset((page), 0, PAGE_SIZE)
#define	pgprot_noncached(prot)		((pgprot_t)VM_MEMATTR_UNCACHEABLE)
#define	pgprot_writecombine(prot)	((pgprot_t)VM_MEMATTR_WRITE_COMBINING)

#undef	PAGE_MASK
#define	PAGE_MASK	(~(PAGE_SIZE-1))
/*
 * Modifying PAGE_MASK in the above way breaks trunc_page, round_page,
 * and btoc macros. Therefore, redefine them in a way that makes sense
 * so the LinuxKPI consumers don't get totally broken behavior.
 */
#undef	btoc
#define	btoc(x)	(((vm_offset_t)(x) + PAGE_SIZE - 1) >> PAGE_SHIFT)
#undef	round_page
#define	round_page(x)	((((uintptr_t)(x)) + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))
#undef	trunc_page
#define	trunc_page(x)	((uintptr_t)(x) & ~(PAGE_SIZE - 1))

/*
 * Resolve a page into a virtual address:
 *
 * NOTE: This function only works for pages allocated by the kernel.
 */
extern void *linux_page_address(struct page *);

#define	page_address(page) linux_page_address(page)

/*
 * Page management for unmapped pages:
 */
extern vm_page_t linux_alloc_pages(gfp_t flags, unsigned int order);
extern void linux_free_pages(vm_page_t page, unsigned int order);

static inline struct page *
alloc_page(gfp_t flags)
{

	return (linux_alloc_pages(flags, 0));
}

static inline struct page *
alloc_pages(gfp_t flags, unsigned int order)
{

	return (linux_alloc_pages(flags, order));
}

static inline struct page *
alloc_pages_node(int node_id, gfp_t flags, unsigned int order)
{

	return (linux_alloc_pages(flags, order));
}

static inline void
__free_pages(struct page *page, unsigned int order)
{

	linux_free_pages(page, order);
}

static inline void
__free_page(struct page *page)
{

	linux_free_pages(page, 0);
}

/*
 * Page management for mapped pages:
 */
extern vm_offset_t linux_alloc_kmem(gfp_t flags, unsigned int order);
extern void linux_free_kmem(vm_offset_t, unsigned int order);

static inline vm_offset_t
get_zeroed_page(gfp_t flags)
{

	return (linux_alloc_kmem(flags | __GFP_ZERO, 0));
}

static inline vm_offset_t
__get_free_page(gfp_t flags)
{

	return (linux_alloc_kmem(flags, 0));
}

static inline vm_offset_t
__get_free_pages(gfp_t flags, unsigned int order)
{

	return (linux_alloc_kmem(flags, order));
}

static inline void
free_pages(uintptr_t addr, unsigned int order)
{
	if (addr == 0)
		return;

	linux_free_kmem(addr, order);
}

static inline void
free_page(uintptr_t addr)
{
	if (addr == 0)
		return;

	linux_free_kmem(addr, 0);
}

static inline bool
gfpflags_allow_blocking(const gfp_t gfp_flags)
{
	return ((gfp_flags & (M_WAITOK | M_NOWAIT)) == M_WAITOK);
}

#define	SetPageReserved(page)	do { } while (0)	/* NOP */
#define	ClearPageReserved(page)	do { } while (0)	/* NOP */

#endif	/* _LINUX_PAGE_H_ */
