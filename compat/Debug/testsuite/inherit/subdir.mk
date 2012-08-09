################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testsuite/inherit/base.c \
../testsuite/inherit/clean_up.c \
../testsuite/inherit/tests.c 

OBJS += \
./testsuite/inherit/base.o \
./testsuite/inherit/clean_up.o \
./testsuite/inherit/tests.o 

C_DEPS += \
./testsuite/inherit/base.d \
./testsuite/inherit/clean_up.d \
./testsuite/inherit/tests.d 


# Each subdirectory must supply rules for building sources it contributes
testsuite/inherit/%.o: ../testsuite/inherit/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


