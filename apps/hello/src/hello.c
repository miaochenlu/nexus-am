#include <klib.h>
#include <encoding.h>
int main(){
#if 1
    write_csr(mhpmevent3 , 0x0);
    write_csr(mhpmevent4 , 0x1);
    write_csr(mhpmevent5 , 0x2);
    write_csr(mhpmevent6 , 0x3);
    write_csr(mhpmevent7 , 0x4);
    write_csr(mhpmevent8 , 0x5);
    write_csr(mhpmevent9 , 0x6);
    write_csr(mhpmevent10, 0x7);
    write_csr(mhpmevent11, 0x0);
    write_csr(mhpmevent12, 0x1);
    write_csr(mhpmevent13, 0x2);
    write_csr(mhpmevent14, 0x3);
    write_csr(mhpmevent15, 0x4);
    write_csr(mhpmevent16, 0x5);
    write_csr(mhpmevent17, 0x6);
    write_csr(mhpmevent18, 0x7);
    write_csr(mhpmevent19, 0x0);
    write_csr(mhpmevent20, 0x1);
    write_csr(mhpmevent21, 0x2);
    write_csr(mhpmevent22, 0x3);
    write_csr(mhpmevent23, 0x4);
    write_csr(mhpmevent24, 0x5);
    write_csr(mhpmevent25, 0x6);
    write_csr(mhpmevent26, 0x7);
    write_csr(mhpmevent27, 0x0);
    write_csr(mhpmevent28, 0x1);
    write_csr(mhpmevent29, 0x2);
    write_csr(mhpmevent30, 0x3);
    write_csr(mhpmevent31, 0x4);
#endif
    printf("Hello Xiangshan ! \n");

#if 1
    long tmp3 ;
    long tmp4 ;
    long tmp5 ;
    long tmp6 ;
    long tmp7 ;
    long tmp8 ;
    long tmp9 ;
    long tmp10;
    long tmp11;
    long tmp12;
    long tmp13;
    long tmp14;
    long tmp15;
    long tmp16;
    long tmp17;
    long tmp18;
    long tmp19;
    long tmp20;
    long tmp21;
    long tmp22;
    long tmp23;
    long tmp24;
    long tmp25;
    long tmp26;
    long tmp27;
    long tmp28;
    long tmp29;
    long tmp30;
    long tmp31;
    tmp3  = read_csr(mhpmcounter3 );
    tmp4  = read_csr(mhpmcounter4 );
    tmp5  = read_csr(mhpmcounter5 );
    tmp6  = read_csr(mhpmcounter6 );
    tmp7  = read_csr(mhpmcounter7 );
    tmp8  = read_csr(mhpmcounter8 );
    tmp9  = read_csr(mhpmcounter9 );
    tmp10 = read_csr(mhpmcounter10);
    tmp11 = read_csr(mhpmcounter11);
    tmp12 = read_csr(mhpmcounter12);
    tmp13 = read_csr(mhpmcounter13);
    tmp14 = read_csr(mhpmcounter14);
    tmp15 = read_csr(mhpmcounter15);
    tmp16 = read_csr(mhpmcounter16);
    tmp17 = read_csr(mhpmcounter17);
    tmp18 = read_csr(mhpmcounter18);
    tmp19 = read_csr(mhpmcounter19);
    tmp20 = read_csr(mhpmcounter20);
    tmp21 = read_csr(mhpmcounter21);
    tmp22 = read_csr(mhpmcounter22);
    tmp23 = read_csr(mhpmcounter23);
    tmp24 = read_csr(mhpmcounter24);
    tmp25 = read_csr(mhpmcounter25);
    tmp26 = read_csr(mhpmcounter26);
    tmp27 = read_csr(mhpmcounter27);
    tmp28 = read_csr(mhpmcounter28);
    tmp29 = read_csr(mhpmcounter29);
    tmp30 = read_csr(mhpmcounter30);
    tmp31 = read_csr(mhpmcounter31);
	printf("mhpmcounter3           : 0x%04x\n",tmp3 );
	printf("mhpmcounter4           : 0x%04x\n",tmp4 );
	printf("mhpmcounter5           : 0x%04x\n",tmp5 );
	printf("mhpmcounter6           : 0x%04x\n",tmp6 );
	printf("mhpmcounter7           : 0x%04x\n",tmp7 );
	printf("mhpmcounter8           : 0x%04x\n",tmp8 );
	printf("mhpmcounter9           : 0x%04x\n",tmp9 );
	printf("mhpmcounter10          : 0x%04x\n",tmp10);
	printf("mhpmcounter11          : 0x%04x\n",tmp11);
	printf("mhpmcounter12          : 0x%04x\n",tmp12);
	printf("mhpmcounter13          : 0x%04x\n",tmp13);
	printf("mhpmcounter14          : 0x%04x\n",tmp14);
	printf("mhpmcounter15          : 0x%04x\n",tmp15);
	printf("mhpmcounter16          : 0x%04x\n",tmp16);
	printf("mhpmcounter17          : 0x%04x\n",tmp17);
	printf("mhpmcounter18          : 0x%04x\n",tmp18);
	printf("mhpmcounter19          : 0x%04x\n",tmp19);
	printf("mhpmcounter20          : 0x%04x\n",tmp20);
	printf("mhpmcounter21          : 0x%04x\n",tmp21);
	printf("mhpmcounter22          : 0x%04x\n",tmp22);
	printf("mhpmcounter23          : 0x%04x\n",tmp23);
	printf("mhpmcounter24          : 0x%04x\n",tmp24);
	printf("mhpmcounter25          : 0x%04x\n",tmp25);
	printf("mhpmcounter26          : 0x%04x\n",tmp26);
	printf("mhpmcounter27          : 0x%04x\n",tmp27);
	printf("mhpmcounter28          : 0x%04x\n",tmp28);
	printf("mhpmcounter29          : 0x%04x\n",tmp29);
	printf("mhpmcounter30          : 0x%04x\n",tmp30);
	printf("mhpmcounter31          : 0x%04x\n",tmp31);
#endif                                            
    return 0;
}