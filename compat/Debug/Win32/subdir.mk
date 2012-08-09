################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Win32/ar.c \
../Win32/touch.c 

OBJS += \
./Win32/ar.o \
./Win32/touch.o 

C_DEPS += \
./Win32/ar.d \
./Win32/touch.d 


# Each subdirectory must supply rules for building sources it contributes
Win32/%.o: ../Win32/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


