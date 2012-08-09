################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testsuite/single/tests/compiler/at_block.c \
../testsuite/single/tests/compiler/constant_expr.c \
../testsuite/single/tests/compiler/succeed.c 

OBJS += \
./testsuite/single/tests/compiler/at_block.o \
./testsuite/single/tests/compiler/constant_expr.o \
./testsuite/single/tests/compiler/succeed.o 

C_DEPS += \
./testsuite/single/tests/compiler/at_block.d \
./testsuite/single/tests/compiler/constant_expr.d \
./testsuite/single/tests/compiler/succeed.d 


# Each subdirectory must supply rules for building sources it contributes
testsuite/single/tests/compiler/%.o: ../testsuite/single/tests/compiler/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


