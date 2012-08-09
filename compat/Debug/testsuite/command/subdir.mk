################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testsuite/command/codefor.c \
../testsuite/command/dest.c \
../testsuite/command/ed.c \
../testsuite/command/eval.c \
../testsuite/command/quit.c \
../testsuite/command/rm.c \
../testsuite/command/say.c \
../testsuite/command/shutdown.c \
../testsuite/command/speed.c \
../testsuite/command/tests.c \
../testsuite/command/update.c \
../testsuite/command/who.c 

OBJS += \
./testsuite/command/codefor.o \
./testsuite/command/dest.o \
./testsuite/command/ed.o \
./testsuite/command/eval.o \
./testsuite/command/quit.o \
./testsuite/command/rm.o \
./testsuite/command/say.o \
./testsuite/command/shutdown.o \
./testsuite/command/speed.o \
./testsuite/command/tests.o \
./testsuite/command/update.o \
./testsuite/command/who.o 

C_DEPS += \
./testsuite/command/codefor.d \
./testsuite/command/dest.d \
./testsuite/command/ed.d \
./testsuite/command/eval.d \
./testsuite/command/quit.d \
./testsuite/command/rm.d \
./testsuite/command/say.d \
./testsuite/command/shutdown.d \
./testsuite/command/speed.d \
./testsuite/command/tests.d \
./testsuite/command/update.d \
./testsuite/command/who.d 


# Each subdirectory must supply rules for building sources it contributes
testsuite/command/%.o: ../testsuite/command/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


