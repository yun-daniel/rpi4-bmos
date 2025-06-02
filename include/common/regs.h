// regs.h
#ifndef __REGS_H__
#define __REGS_H__

#include "common/types.h"


struct pt_regs {
    uint64_t regs[31];  // x0 ~ x30
    uint64_t sp;        // Stack Pointer
    uint64_t pc;        // ELR_ELx
    uint64_t pstate;    // SPSR_ELx
};


#endif // __REGS_H__
