cmake_minimum_required(VERSION 3.09)

## Project name
project("Atmega32 Firmware")

## Product filename
set(PRODUCT_NAME base)

## AVR Chip Configuration ##
# 8Mhz, this sould match the crystal on board
set(F_CPU 8000000UL)
# CPU
set(MCU atmega328p)
# Default baudrate for UART
set(BAUD 9600)
# The programmer, avrdude 
set(PROG_TYPE linuxgpio)

# AVR Fuses
set(E_FUSE 0xff)
set(H_FUSE 0xd9)
set(L_FUSE 0xe2)
set(LOCK_BIT 0xff)

## Use AVR GCC toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILE avr-gcc)

# Pass defines to compiler
add_definitions(
    -DF_CPU=${F_CPU}
    -DBAUD=${BAUD}
)

# mmcu MUST be passed to bot the compliler and linker, this handle the linker
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

add_compile_options(
    -mmcu=${MCU} # MCU
    #-std=gnu99   # C99 standard
    -Os          # optimize
    -Wall        # enable warnings
    -fpermissive
    #-Wno-main    
    #-Wundef 
    #-pedantic 
    #-Wstrict-prototypes
    #-Werror 
    #-Wfatal-errors
    #-Wl,--relax,--gc-sections 
    #-g 
    #-gdwarf-2 
    #-funsigned-char  # a few optimizations
    #-funsigned-bitfields 
    #-fpack-struct 
    #-fshort-enums 
    #-ffunction-sections 
    #-fdata-sections 
    #-fno-split-wide-types 
    #-fno-tree-scev-cprop 
)   

# Load all files in src folder
file(GLOB SRC_FILES "src/*.cpp")

# Create one target
add_executable(${PRODUCT_NAME} ${SRC_FILES})

# Rename the output to .elf as we will create multiple files 
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME}.elf)

# Strip binary for upload 
add_custom_target(strip ALL avr-strip ${PRODUCT_NAME}.elf DEPENDS ${PRODUCT_NAME})

# Transform binary into hex file, we ignore the eeprom segments in the step
add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.hex DEPENDS strip)

# Transform binary into hex file, this is the eeprom part (empty if you don't use eeprom static variable)
add_custom_target(eeprom avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.eep DEPENDS strip)

# Erase chip
add_custom_target(erase sudo avrdude -c ${PROG_TYPE} -p ${MCU} -e)

# Upload the firmware with avrdude
add_custom_target(upload sudo avrdude -c ${PROG_TYPE} -p ${MCU} -U flash:w:${PRODUCT_NAME}.hex DEPENDS hex erase)

# Upload the eeprom with avrdude
add_custom_target(upload_eeprom sudo avrdude -c ${PROG_TYPE} -p ${MCU} -U eeprom:w:${PRODUCT_NAME}.eep DEPENDS eeprom erase)

# Burn fuses 
add_custom_target(fuses sudo avrdude -c ${PROG_TYPE} -p ${MCU} -U lfuse:w:${L_FUSE}:m -U hfuse:w:${H_FUSE}:m -U efuse:w:${E_FUSE}:m -U lock:w:${LOCK_BIT}:m)

## clean extra files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PRODUCT_NAME}.hex;${PRODUCT_NAME}.eeprom;${PRODUCT_NAME}.lst;${PRODUCT_NAME}.eep")

