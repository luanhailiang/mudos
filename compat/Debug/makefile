################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include testsuite/subdir.mk
-include testsuite/single/subdir.mk
-include testsuite/single/tests/operators/subdir.mk
-include testsuite/single/tests/efuns/subdir.mk
-include testsuite/single/tests/compiler/subdir.mk
-include testsuite/single/tests/compiler/fail/subdir.mk
-include testsuite/inherit/subdir.mk
-include testsuite/inherit/master/subdir.mk
-include testsuite/command/subdir.mk
-include testsuite/clone/subdir.mk
-include packages/subdir.mk
-include mudlib/subdir.mk
-include compat/simuls/subdir.mk
-include compat/subdir.mk
-include amiga/subdir.mk
-include Win32/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: mudos

# Tool invocations
mudos: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o"mudos" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) mudos
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
