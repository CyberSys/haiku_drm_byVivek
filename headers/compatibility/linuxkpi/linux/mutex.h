#ifndef	_LINUX_MUTEX_H_
#define	_LINUX_MUTEX_H_

#include <lock.h>

typedef mutex mutex_t;

#define	mutex_lock_nested(_m, _s)	mutex_lock((_m))
#define	mutex_lock_nest_lock(_m, _s)	mutex_lock((_m))

#define	mutex_init(_m) \
	mutex_init((_m), mutex_name(#_m))

#define linux_mutex_init(m, name, flags)		\
	mutex_init_etc((m), (name), (flags))


#define linux_mutex_destroy(m)		\
	mutex_destroy((m))

#endif					/* _LINUX_MUTEX_H_ */
