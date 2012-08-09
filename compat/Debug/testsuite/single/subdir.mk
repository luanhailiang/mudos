################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testsuite/single/inh.c \
../testsuite/single/master.c \
../testsuite/single/simul_efun.c \
../testsuite/single/void.c 

OBJS += \
./testsuite/single/inh.o \
./testsuite/single/master.o \
./testsuite/single/simul_efun.o \
./testsuite/single/void.o 

C_DEPS += \
./testsuite/single/inh.d \
./testsuite/single/master.d \
./testsuite/single/simul_efun.d \
./testsuite/single/void.d 


# Each subdirectory must supply rules for building sources it contributes
testsuite/single/%.o: ../testsuite/single/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


