################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/TIMER1/Src/Timer1.c 

OBJS += \
./MCAL/TIMER1/Src/Timer1.o 

C_DEPS += \
./MCAL/TIMER1/Src/Timer1.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/TIMER1/Src/%.o: ../MCAL/TIMER1/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\HAL\BUTTON\Inc" -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\MCAL\EEPROM\Inc" -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\HAL\EEPROM24C16\Inc" -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\HAL\LED\Inc" -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\HAL\SSD\Inc" -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\LIB" -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\MCAL\ADC\Inc" -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\MCAL\DIO\Inc" -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\MCAL\EEPROM\Inc" -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\MCAL\GLBL_INTERPT\Inc" -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\MCAL\I2C\Inc" -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\MCAL\TIMER0\Inc" -I"C:\Users\sreda\eclipse-workspace\Electric_Water_Heater\MCAL\TIMER1\Inc" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


