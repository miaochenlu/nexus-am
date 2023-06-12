#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#define BYTE (1)
#define KB (1024*BYTE)
#define MB (1024*KB)
#define GB (1024*MB)

uint64_t _PERF_TEST_ADDR_BASE;
#define _PERF_CACHELINE_SIZE_BYTE (8 * BYTE)
#define _PERF_L1_SIZE_BYTE (128 * KB)
#define _PERF_L2_SIZE_BYTE (512 * KB)
#define _PERF_L3_SIZE_BYTE (2 * MB)
#define _PERF_MEM_SIZE_BYTE (32 *MB)
#define _TEST_NUM_SIZE (32 * KB)

void full_cache_init_i(uint64_t base_addr,uint64_t end_addr,uint64_t step,int choose){
    uint64_t num = 0;
    assert(step % 8 ==0);
    assert(step >= 8);
    for(uint64_t cur_addr = base_addr ; cur_addr < end_addr;){
        uint64_t next_addr = cur_addr + step;
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
void cache_iloop(unsigned long long* instr_count, unsigned long long* cycle_count){
    *instr_count = 0;
    *cycle_count = 0;
    asm volatile(
            "jal zero, init;"
            "xor s8  , zero , zero;"

        "loop:" 
            "ld    s8,0(s6);"
            "add   s8,s8,s7;"
            "ld    s6,0(s8);"

            "addi s4 , s4 , 1;"
            "bleu s4,s5,loop;"

            "jal  zero ,term;"

        "init:"
            "li   s4 , 0;"
            "li   s5 , 500;"
            "add  s6,  t0, %[a];"
            "li   s7 , 0;"
            "li   s8 , 0;"


            "csrr  s9 , mcycle;"
            "csrr  s10, minstret;"

            "jal   zero, loop;"
        "term:"
            "csrr s11 , mcycle;"
            "csrr t3  , minstret;"

            "subw  %[c], s11 , s9;"
            "subw  %[i], t3  , s10;"

        : [c] "=r" (*cycle_count),[i] "=r" (*instr_count)
        : [a] "r" (_PERF_TEST_ADDR_BASE)
        : "zero","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6","cc"
    );
}

int main(){
    uint8_t* array = (uint8_t*)malloc(sizeof(uint8_t) * 8 * 1024 * 1024);
    _PERF_TEST_ADDR_BASE = (uint64_t)array;
    unsigned long long busy_cycles_l1,busy_cycles_l2,busy_cycles_l3,busy_cycles_mem;
    unsigned long long busy_instrs_l1,busy_instrs_l2,busy_instrs_l3,busy_instrs_mem;
    uint64_t start_addr = _PERF_TEST_ADDR_BASE;

    uint64_t end_addr_l2 = (_PERF_TEST_ADDR_BASE + _TEST_NUM_SIZE + (_PERF_L2_SIZE_BYTE/2));
    uint64_t end_addr_l1 = (_PERF_TEST_ADDR_BASE + _PERF_L1_SIZE_BYTE - (2*_TEST_NUM_SIZE));
    uint64_t end_addr_l3 = (_PERF_TEST_ADDR_BASE + _PERF_L1_SIZE_BYTE + _PERF_L2_SIZE_BYTE + _PERF_L2_SIZE_BYTE);
    uint64_t end_addr_mem = (_PERF_TEST_ADDR_BASE + _PERF_L1_SIZE_BYTE + _PERF_L2_SIZE_BYTE + _PERF_L3_SIZE_BYTE + _PERF_L2_SIZE_BYTE);

    full_cache_init_i(start_addr,end_addr_l1,_PERF_CACHELINE_SIZE_BYTE,1);
    cache_iloop(&busy_instrs_l1,&busy_cycles_l1);

    full_cache_init_i(start_addr,end_addr_l2,_PERF_CACHELINE_SIZE_BYTE,2);
    cache_iloop(&busy_instrs_l2,&busy_cycles_l2);

    full_cache_init_i(start_addr,end_addr_l3,_PERF_CACHELINE_SIZE_BYTE,3);
    cache_iloop(&busy_instrs_l3,&busy_cycles_l3);

    full_cache_init_i(start_addr,end_addr_mem,_PERF_CACHELINE_SIZE_BYTE,3);
    cache_iloop(&busy_instrs_mem,&busy_cycles_mem);

    printf("the test of load-add-load hit in l1\n");
    printf("instrs %lld cycles %lld\n",busy_instrs_l1,busy_cycles_l1);
    printf("the test of load-add-load hit in l2\n");
    printf("instrs %lld cycles %lld\n",busy_instrs_l2,busy_cycles_l2);
    printf("the test of load-add-load hit in l3\n");
    printf("instrs %lld cycles %lld\n",busy_instrs_l3,busy_cycles_l3);
    printf("the test of load-add-load hit in mem\n");
    printf("instrs %lld cycles %lld\n",busy_instrs_mem,busy_cycles_mem);
    printf("the test is finish\n");
    free(array);

}
