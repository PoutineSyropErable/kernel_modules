#include <linux/kernel.h>
#include <linux/module.h>
#define IAEFER_SYSCALL_ENABLE 0
#define IAEFER_IA32e_ENABLE 8
#define IAEFER_IA32e_ACTIVE 10
#define PRIx64 "llx"

#define PRINT_PROPERTY(efer, X)                                                \
    printk(KERN_INFO #X " %s\n",                                               \
           ((1 << IAEFER_##X) & efer) ? "Enabled" : "Disabled")

typedef enum msr_t { IA32_EFER = 0xC0000080U } msr_t;

static uint64_t myrdmsr(msr_t which) {
    register uint64_t ret asm("rax");
    asm("rdmsr\n"
        "shlq $32, %%rdx\n"
        "addq %%rdx,%%rax\n"
        : "=a"(ret)
        : "c"(which)
        : "rdx");
    return ret;
}

static int __init dump_msr_start(void) {
    uint64_t efer = myrdmsr(IA32_EFER);
    printk(KERN_INFO "MSR_DUMP: %" PRIx64 "\n", efer);
    PRINT_PROPERTY(efer, IA32e_ENABLE);
    PRINT_PROPERTY(efer, IA32e_ACTIVE);
    PRINT_PROPERTY(efer, SYSCALL_ENABLE);
    // return -EINVAL;
    return 0;
}

static void __exit dump_msr_end(void) { return; }

module_init(dump_msr_start);
module_exit(dump_msr_end);
MODULE_LICENSE("GPL");
