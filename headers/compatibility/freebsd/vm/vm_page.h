#include <freebsd/vm/vm.h>

#define PQ_ACTIVE 0x00
#define PQ_NONE 0x01

#define VM_PAGE_TO_PHYS(p) ((p)->physical_page_number)

extern void vm_page_dirty(vm_page_t m);
extern void vm_page_reference(vm_page_t m);
extern void vm_page_lock(vm_page_t m);
extern void vm_page_unlock(vm_page_t m);
extern void vm_page_hold(vm_page_t m);
extern void vm_page_unhold(vm_page_t m);
extern void vm_page_wire(vm_page_t m);
extern boolean_t vm_page_unwire(vm_page_t m, uint8_t queue);

extern vm_page_t PHYS_TO_VM_PAGE(vm_paddr_t paddr);
