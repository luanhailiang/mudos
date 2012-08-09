################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testsuite/clone/login.c \
../testsuite/clone/user.c 

OBJS += \
./testsuite/clone/login.o \
./testsuite/clone/user.o 

C_DEPS += \
./testsuite/clone/login.d \
./testsuite/clone/user.d 


# Each subdirectory must supply rules for building sources it contributes
testsuite/clone/%.o: ../testsuite/clone/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


