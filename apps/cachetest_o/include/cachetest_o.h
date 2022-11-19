#include <klib.h>
#include <csr.h>


#define BYTE (1)
#define KB (1024*BYTE)
#define MB (1024*KB)
#define GB (1024*MB)

//#define _PERF_TEST_ADDR_BASE 0x80040000
#define _PERF_TEST_ADDR_BASE 0x80010000
#define _PERF_CACHELINE_SIZE_BYTE (8 * BYTE)
//#define _PERF_L1_SIZE_BYTE (32 * KB)
#define _PERF_L1_SIZE_BYTE (128 * KB)
#define _PERF_L2_SIZE_BYTE (1 * MB)
#define _PERF_L3_SIZE_BYTE (6 * MB)
#define _PERF_MEM_SIZE_BYTE (32 *MB)
#define _TEST_NUM_SIZE (32 * KB)


void full_cache_init(uint64_t base_addr, uint64_t end_addr, uint64_t step ,int choose){
    //printf("111\n");
    uint64_t num = 0;
    assert(step % 8 == 0);
    assert(step >=8);
    for(uint64_t cur_addr = base_addr;cur_addr < end_addr;){
        //printf("cur_addr 0x%lx\n",cur_addr);
        //printf("end_addr 0x%lx\n",end_addr);
       /* if(cur_addr >( 0x80730000 - 100)){
            printf("cur_addr 0x%lx\n",cur_addr);
        }*/
        uint64_t next_addr = cur_addr + step;
        //*((uint64_t*)cur_addr) = next_addr+16;
        if(choose == 1){
            *((uint64_t*)cur_addr) = cur_addr;
        }
        else{
            *((uint64_t*)cur_addr) = cur_addr + 64;
        }
        
        cur_addr = next_addr;
        num ++;
    }
}

__attribute__((aligned(256)))
void cache_loop(unsigned long long* instr_count, unsigned long long* cycle_count){
    *instr_count = 0;
    *cycle_count = 0;
    asm volatile(
            "jal zero, init;"
            "xor s8  , zero , zero;"

        "loop:" 
            "ld    s6,0(s6);"
            "ld    s7,0(s7);"
            "ld    s8,0(s8);"

            "addi s4 , s4 , 1;"
            "bleu s4,s5,loop;"

            "jal  zero ,term;"

        "init:"
            "li   s4 , 0;"
            "li   s5 , 500;"
            "li   s6 , 0x80010000;"
            "addi s7 , s6,64;"
            "addi s8 , s7,64;"

            "csrr  s9 , mcycle;"
            "csrr  s10, minstret;"

            "jal   zero, loop;"
        "term:"
            "csrr s11 , mcycle;"
            "csrr t3  , minstret;"

            "subw  %[c], s11 , s9;"
            "subw  %[i], t3  , s10;"

        : [c] "=r" (*cycle_count),[i] "=r" (*instr_count)
        : 
        : "zero","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6","cc"

    );

}


