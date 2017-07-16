/*
 * Copyright 2007, Hugo Santos. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _FBSD_COMPAT_VM_VM_H_
#define _FBSD_COMPAT_VM_VM_H_


#include <stdint.h>
#include <KernelExport.h>
#include <vm/vm_types.h>

#ifdef B_HAIKU_64_BIT

typedef uint64_t vm_size_t;

#else

typedef uint32_t vm_size_t;

#endif

typedef char vm_inherit_t;	/* inheritance codes */

#define	VM_INHERIT_SHARE	((vm_inherit_t) 0)
#define	VM_INHERIT_COPY		((vm_inherit_t) 1)
#define	VM_INHERIT_NONE		((vm_inherit_t) 2)
#define	VM_INHERIT_ZERO		((vm_inherit_t) 3)
#define	VM_INHERIT_DEFAULT	VM_INHERIT_COPY

typedef u_char vm_prot_t;	/* protection codes */

#define	VM_PROT_NONE		((vm_prot_t) 0x00)
#define	VM_PROT_READ		((vm_prot_t) 0x01)
#define	VM_PROT_WRITE		((vm_prot_t) 0x02)
#define	VM_PROT_EXECUTE		((vm_prot_t) 0x04)
#define	VM_PROT_COPY		((vm_prot_t) 0x08)	/* copy-on-read */

#define	VM_PROT_ALL		(VM_PROT_READ|VM_PROT_WRITE|VM_PROT_EXECUTE)
#define VM_PROT_RW		(VM_PROT_READ|VM_PROT_WRITE)
#define	VM_PROT_DEFAULT		VM_PROT_ALL

typedef page_num_t vm_pindex_t;
typedef void *pmap_t;
typedef addr_t vm_offset_t;
typedef phys_addr_t vm_paddr_t;
typedef char vm_memattr_t;
typedef u_char objtype_t;
typedef uint64_t vm_ooffset_t;

struct vm_object;
typedef struct vm_object *vm_object_t;

#define vmspace_pmap(...)	NULL
#define pmap_extract(...)	NULL


vm_paddr_t pmap_kextract(vm_offset_t virtualAddress);

#define vtophys(virtualAddress) pmap_kextract((vm_offset_t)(virtualAddress))

#endif	/* _FBSD_COMPAT_VM_VM_H_ */
