NAME_1 = cachetest_o
CFLAGS += -DCHOOSE=$(CHOOSE) -g
CFLAGS += -DINST=$(INST) -g
NAME = build-$(NAME_1)-$(CHOOSE)-$(INST)
$(NAME).c:cachetest_o.c
	cp cachetest_o.c $(NAME).c
#NAME = cachetest_o
SRCS = $(NAME).c
include $(AM_HOME)/Makefile.app
clean-build:
	rm -f build-*