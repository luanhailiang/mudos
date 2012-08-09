################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../add_action.c \
../addr_server.c \
../array.c \
../avltree.c \
../backend.c \
../binaries.c \
../bsdmalloc.c \
../buffer.c \
../call_out.c \
../ccode.c \
../cfuns.c \
../class.c \
../comm.c \
../compile_file.c \
../compiler.c \
../crc32.c \
../crypt.c \
../debug.c \
../debugmalloc.c \
../disassembler.c \
../dumpstat.c \
../ed.c \
../edit_source.c \
../efuns_main.c \
../efuns_port.c \
../eoperators.c \
../file.c \
../func_spec.c \
../function.c \
../generate.c \
../hash.c \
../icode.c \
../interpret.c \
../lex.c \
../main.c \
../make_malloc.c \
../mapping.c \
../master.c \
../md.c \
../object.c \
../op_spec.c \
../otable.c \
../parse.c \
../plainwrapper.c \
../port.c \
../portbind.c \
../preprocess.c \
../program.c \
../qsort.c \
../rc.c \
../reclaim.c \
../regexp.c \
../replace_program.c \
../scratchpad.c \
../simul_efun.c \
../simulate.c \
../smalloc.c \
../socket_ctrl.c \
../socket_efuns.c \
../socket_err.c \
../sprintf.c \
../stralloc.c \
../strfuncs.c \
../swap.c \
../sysmalloc.c \
../trees.c \
../ualarm.c \
../wrappedmalloc.c 

OBJS += \
./add_action.o \
./addr_server.o \
./array.o \
./avltree.o \
./backend.o \
./binaries.o \
./bsdmalloc.o \
./buffer.o \
./call_out.o \
./ccode.o \
./cfuns.o \
./class.o \
./comm.o \
./compile_file.o \
./compiler.o \
./crc32.o \
./crypt.o \
./debug.o \
./debugmalloc.o \
./disassembler.o \
./dumpstat.o \
./ed.o \
./edit_source.o \
./efuns_main.o \
./efuns_port.o \
./eoperators.o \
./file.o \
./func_spec.o \
./function.o \
./generate.o \
./hash.o \
./icode.o \
./interpret.o \
./lex.o \
./main.o \
./make_malloc.o \
./mapping.o \
./master.o \
./md.o \
./object.o \
./op_spec.o \
./otable.o \
./parse.o \
./plainwrapper.o \
./port.o \
./portbind.o \
./preprocess.o \
./program.o \
./qsort.o \
./rc.o \
./reclaim.o \
./regexp.o \
./replace_program.o \
./scratchpad.o \
./simul_efun.o \
./simulate.o \
./smalloc.o \
./socket_ctrl.o \
./socket_efuns.o \
./socket_err.o \
./sprintf.o \
./stralloc.o \
./strfuncs.o \
./swap.o \
./sysmalloc.o \
./trees.o \
./ualarm.o \
./wrappedmalloc.o 

C_DEPS += \
./add_action.d \
./addr_server.d \
./array.d \
./avltree.d \
./backend.d \
./binaries.d \
./bsdmalloc.d \
./buffer.d \
./call_out.d \
./ccode.d \
./cfuns.d \
./class.d \
./comm.d \
./compile_file.d \
./compiler.d \
./crc32.d \
./crypt.d \
./debug.d \
./debugmalloc.d \
./disassembler.d \
./dumpstat.d \
./ed.d \
./edit_source.d \
./efuns_main.d \
./efuns_port.d \
./eoperators.d \
./file.d \
./func_spec.d \
./function.d \
./generate.d \
./hash.d \
./icode.d \
./interpret.d \
./lex.d \
./main.d \
./make_malloc.d \
./mapping.d \
./master.d \
./md.d \
./object.d \
./op_spec.d \
./otable.d \
./parse.d \
./plainwrapper.d \
./port.d \
./portbind.d \
./preprocess.d \
./program.d \
./qsort.d \
./rc.d \
./reclaim.d \
./regexp.d \
./replace_program.d \
./scratchpad.d \
./simul_efun.d \
./simulate.d \
./smalloc.d \
./socket_ctrl.d \
./socket_efuns.d \
./socket_err.d \
./sprintf.d \
./stralloc.d \
./strfuncs.d \
./swap.d \
./sysmalloc.d \
./trees.d \
./ualarm.d \
./wrappedmalloc.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


