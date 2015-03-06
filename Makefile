CC=sdcc
CFLAGS=-mstm8 --opt-code-size
CFLAGS+=-I/usr/local/share/sdcc/include
#CFLAGS+=-I/usr/local/share/sdcc/lib/small
CFLAGS+=-I.
CFLAGS+=-I$(STM8LIBINC)

#MFLAGS = --debug --model-small --stack-after-data
#MFLAGS = --model-small
#LFLAGS = --code-loc 0x0000

STM8LIBDIR=../stm8_lib
SDCCLIBSMALL=/usr/local/share/sdcc/lib/small

STM8LIBINC=$(STM8LIBDIR)/inc
DEFINES=STM8S003
SRC=main
OUT_DIR=build

SRCS= ministdlib.c gpio.c uart.c adc.c pid.c controller.c
#SRCS= $(wildcard *.c)

OBJS = $(SRCS:%.c=$(OUT_DIR)/%.rel)
#OBJS=	$(OUT_DIR)/uart.rel

STDLIBNAME=libstm8s003.a

TARG=$(OUT_DIR)/$(SRC).hex

all: precomp $(TARG) postcomp

precomp:
	mkdir -p $(OUT_DIR)

postcomp:
	packihx $(OUT_DIR)/$(SRC).ihx > $(SRC).hex
#	makebin -p $(OUT_DIR)/$(SRC).ihx $(SRC).bin
#	ln -s $(OUT_DIR)/$(SRC).map $(SRC).map


$(TARG): $(OBJS)
#!	$(CC) $(CFLAGS) $(LFLAGS) -D $(DEFINES) -L $(SDCCLIBSMALL) -L $(STM8LIBDIR) -l $(STDLIBNAME) -o $(OUT_DIR)/$(SRC).ihx $(SRC).c $(OBJS)
#	$(CC) $(CFLAGS) $(LFLAGS) -D $(DEFINES) -L $(SDCCLIBSMALL) -l libsdcc.lib -L $(STM8LIBDIR) -l $(STDLIBNAME) -o $(OUT_DIR)/$(SRC).ihx $(SRC).c $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -D $(DEFINES) -L $(SDCCLIBSMALL) -o $(OUT_DIR)/$(SRC).ihx $(SRC).c $(OBJS)


$(OUT_DIR)/%.rel: %.c
#!	$(CC) -c $(CFLAGS) $(LFLAGS) -D $(DEFINES) -L $(SDCCLIBSMALL)  -L $(STM8LIBDIR) -l $(STDLIBNAME) -c -o $@ $<
#	$(CC) -c $(CFLAGS) $(LFLAGS) -D $(DEFINES) -L $(SDCCLIBSMALL) -l libsdcc.lib -L $(STM8LIBDIR) -l $(STDLIBNAME) -c -o $@ $<
	$(CC) -c $(CFLAGS) $(LFLAGS) -D $(DEFINES) -L $(SDCCLIBSMALL) -c -o $@ $<




prepare:
	packihx $(OUT_DIR)/$(SRC).ihx > $(OUT_DIR)/$(SRC).hex

clean:
	rm -Rrf $(OUT_DIR)
#	rm $(SRC).bin
	rm -f $(SRC).hex
#	rm -f $(SRC).map

erase:
	vsprog -cstm8s103f3 -ms -oe -V"tvcc.set 3300"
	vsprog -V"tvcc.set 0" -V"tvcc.set 3300"

flash: erase
#	vsprog -cstm8s103f3 -ms -owf -I $(OUT_DIR)/$(SRC).hex -V"tvcc.set 3300"
	vsprog -V"tvcc.set 3300"
	vsprog -cstm8s103f3 -ms -owf -I $(SRC).hex -V"tvcc.set 3300"
#	vsprog -cstm8s103f3 -ms -owf -I $(SRC).bin -V"tvcc.set 3300"
	vsprog -V"tvcc.set 0" -V"tvcc.set 3300" -V"tvcc.set 3300"
