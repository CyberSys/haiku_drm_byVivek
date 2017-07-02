#ifndef	_LINUX_SLAB_H_
#define	_LINUX_SLAB_H_

#include <linux/gfp.h>
#include <linux/types.h>

#include <malloc.h>

#define	kvmalloc(size)			kmalloc(size, GFP_KERNEL)
#define	kzalloc(size, flags)		kmalloc(size, (flags) | __GFP_ZERO)
#define	kzalloc_node(size, flags, node)	kmalloc(size, (flags) | __GFP_ZERO)
#define	kfree_const(ptr)		kfree(ptr)
#define	kcalloc(n, size, flags)		kmalloc((n) * (size), (flags) | __GFP_ZERO)
#define	vzalloc(size)			__vmalloc(size, GFP_KERNEL | __GFP_NOWARN | __GFP_ZERO, 0)
#define	vfree(arg)			kfree(arg)
#define	kvfree(arg)			kfree(arg)
#define	vmalloc_node(size, node)		__vmalloc(size, GFP_KERNEL, 0)
#define	vmalloc_user(size)				__vmalloc(size, GFP_KERNEL | __GFP_ZERO, 0)
#define	vmalloc(size)					__vmalloc(size, GFP_KERNEL, 0)
#define	__kmalloc(...)			kmalloc(__VA_ARGS__)
#define	kmalloc_node(chunk, flags, n)	kmalloc(chunk, flags)

extern void *kmalloc(size_t size, int flags);
extern void *krealloc(void *ptr, size_t size, int flags);
extern void kfree(const void *ptr);

static inline void *
__vmalloc(size_t size, int flags, int other)
{
	return (malloc(size));
}

static inline void *
vmalloc_32(size_t size)
{
	return (malloc(size));
}

static inline void *
kmalloc_array(size_t n, size_t size, int flags)
{
	return (kmalloc(n * size, flags));
}

#endif	/* _LINUX_SLAB_H_ */
