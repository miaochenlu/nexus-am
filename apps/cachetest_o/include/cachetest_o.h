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
void cache_loop_l1d(unsigned long long* instr_count, unsigned long long* cycle_count,unsigned long long c_num){
    *instr_count = 0;
    *cycle_count = 0;
    asm volatile(
            "jal zero, init_l1d;"
            "xor s8  , zero , zero;"

        "loop_l1d:" 
           /* "ld    a2,0(s0);"
            "ld    a2,8(s0);"
            "ld    a2,16(s0);"
            "ld    a2,24(s0);"
            "addi  s0,s0,0;"*/
#if CHOOSE ==3
            "ld    a2,0(s0);"
            "ld    a2,8(s0);"
            "ld    a2,16(s0);"
            "addi  s0,s0,0;"
#elif CHOOSE ==4
            "ld    a2,0(s0);"
            "ld    a2,8(s0);"
            "ld    a2,16(s0);"
            "ld    a2,24(s0);"
            "addi  s0,s0,0;"
#elif CHOOSE ==5
            "ld    a2,0(s0);"
            "ld    a2,8(s0);"
            "ld    a2,16(s0);"
            "ld    a2,24(s0);"
            "ld    a2,32(s0);"
            "addi  s0,s0,0;"
#elif CHOOSE ==12
            "ld    a2,0(s0);"
            "ld    a2,8(s0);"
            "ld    a2,16(s0);"
            "ld    a2,24(s0);"
            "ld    a2,32(s0);"
            "ld    a2,40(s0);"
            "ld    a2,48(s0);"
            "ld    a2,56(s0);"
            "ld    a2,64(s0);"
            "ld    a2,72(s0);"
            "ld    a2,80(s0);"
            "ld    a2,88(s0);"
            "addi  s0,s0,0;"
#endif


            "addi  t0, t0 , 1;"
            "bleu  t0, t1 , loop_l1d;"

            "jal  zero ,term_l1d;"

        "init_l1d:"
            "li   t0  , 0;"
           // "li   t1  , 500;"
            "mv   t1  , %[a];"
            "li   s0  , 0x80010000;"
            /*"addi s1  , s0,72;"
            "addi s2  , s1,80;"
            "addi s3  , s2,88;"
            "addi s4  , s3,96;"
            "addi s5  , s4,104;"
            "addi s6  , s5,112;"
            "addi s7  , s6,120;"
            "addi s8  , s7,128;"
            "addi s9  , s8,136;"
            "addi s10 , s9,144;"
            "addi s11 , s10,152;"*/
            "addi s1  , s0,64;"
            "addi s2  , s1,64;"
            "addi s3  , s2,64;"
            "addi s4  , s3,64;"
            "addi s5  , s4,64;"
            "addi s6  , s5,64;"
            "addi s7  , s6,64;"
            "addi s8  , s7,64;"
            "addi s9  , s8,64;"
            "addi s10 , s9,64;"
            "addi s11 , s10,64;"

            "csrr  t2 , mcycle;"
            "csrr  t3 , minstret;"

            "jal   zero, loop_l1d;"
        "term_l1d:"
            "csrr t4  , mcycle;"
            "csrr t5  , minstret;"

            "subw  %[c], t4 , t2;"
            "subw  %[i], t5 , t3;"

        : [c] "=r" (*cycle_count),[i] "=r" (*instr_count)
        : [a] "r"(c_num)
        : "zero","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6","cc"

    );

}

__attribute__((aligned(256)))
void cache_loop(unsigned long long* instr_count, unsigned long long* cycle_count,unsigned long long c_num){
    *instr_count = 0;
    *cycle_count = 0;
    asm volatile(
            "jal zero, init;"
            "xor s8  , zero , zero;"

        "loop:"
            /*"ld    a2,0(s0);"
            "ld    a2,72(s0);"
            "ld    a2,144(s0);"
            "ld    a2,216(s0);"
            "addi  s0,s0,320;"*/
#if CHOOSE ==3
            "ld    a2,0(s0);"
            "ld    a2,72(s0);"
            "ld    a2,144(s0);"
            "addi  s0,s0,256;"
#elif CHOOSE ==4
            "ld    a2,0(s0);"
            "ld    a2,72(s0);"
            "ld    a2,144(s0);"
            "ld    a2,216(s0);"
            "addi  s0,s0,320;"
#elif CHOOSE ==5
            "ld    a2,0(s0);"
            "ld    a2,72(s0);"
            "ld    a2,144(s0);"
            "ld    a2,216(s0);"
            "ld    a2,288(s0);"
            "addi  s0,s0,384;"
#elif CHOOSE ==12
            "ld    a2,0(s0);"
            "ld    a2,72(s0);"
            "ld    a2,144(s0);"
            "ld    a2,216(s0);"
            "ld    a2,288(s0);"
            "ld    a2,360(s0);"
            "ld    a2,432(s0);"
            "ld    a2,504(s0);"
            "ld    a2,576(s0);"
            "ld    a2,648(s0);"
            "ld    a2,720(s0);"
            "ld    a2,792(s0);"
            "addi  s0,s0,896;"
#endif

            "addi  t0, t0 , 1;"
            "bleu  t0, t1 , loop;"

            "jal  zero ,term;"

        "init:"
            "li   t0  , 0;"
            //"li   t1  , 500;"
            "mv   t1  , %[a];"
            "li   s0  , 0x80010000;"
            "addi s1  , s0,72;"
            "addi s2  , s0,144;"
            "addi s3  , s0,216;"
            "addi s4  , s0,288;"
            "addi s5  , s0,360;"
            "addi s6  , s0,432;"
            "addi s7  , s0,504;"
            "addi s8  , s0,576;"
            "addi s9  , s0,648;"
            "addi s10 , s0,720;"
            "addi s11 , s0,792;"

            "csrr  t2 , mcycle;"
            "csrr  t3 , minstret;"

            "jal   zero, loop;"
        "term:"
            "csrr t4  , mcycle;"
            "csrr t5  , minstret;"

            "subw  %[c], t4 , t2;"
            "subw  %[i], t5 , t3;"

        : [c] "=r" (*cycle_count),[i] "=r" (*instr_count)
        : [a] "r"(c_num)
        : "zero","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6","cc"

    );

}




