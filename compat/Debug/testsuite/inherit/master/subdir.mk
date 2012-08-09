################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testsuite/inherit/master/valid.c 

OBJS += \
./testsuite/inherit/master/valid.o 

C_DEPS += \
./testsuite/inherit/master/valid.d 


# Each subdirectory must supply rules for building sources it contributes
testsuite/inherit/master/%.o: ../testsuite/inherit/master/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


