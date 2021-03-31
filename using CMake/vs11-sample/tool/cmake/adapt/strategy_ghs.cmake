# optimization
set(COMPILE_FLAGS_OPTIMIZATION_NOOPT "-Onone")
set(COMPILE_FLAGS_OPTIMIZATION_SPEED "-Ospeed")
set(COMPILE_FLAGS_OPTIMIZATION_SIZE  "-Ospace")

# bit access
set(COMPILE_1_BIT_ACCESS					"-Zuse1bit -asm=-bit_inst_error -list")

# memory region
set(COMPILE_FLAGS_REGION_NOINIT             "-include NOINI_C1.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_STARTUP            "-include startup_StartupSystem.h")
set(COMPILE_FLAGS_REGION_WAKEUP             "-include wakeup_ram_OsAppBaseSystem.h ${COMPILE_1_BIT_ACCESS}")

set(COMPILE_FLAGS_REGION_SDRAM_APP          "-include sdram_OsApp2.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_SDRAM_APP3         "-include sdram_OsApp3.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_SDRAM_APP4         "-include sdram_OsApp4.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_SDRAM_APP5         "-include sdram_OsApp5.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_SDRAM_SYSTEM       "-include sdram_OsAppBaseSystem.h ${COMPILE_1_BIT_ACCESS}")

set(COMPILE_FLAGS_REGION_SRAM_1_APP         "-include sram1_OsApp2.h")
set(COMPILE_FLAGS_REGION_SRAM_1_SYSTEM      "-include sram1_OsAppBaseSystem.h")

set(COMPILE_FLAGS_REGION_SRAM_2_APP         "-include sram2_OsApp2.h")
set(COMPILE_FLAGS_REGION_SRAM_2_APP3        "-include sram2_OsApp3.h")
set(COMPILE_FLAGS_REGION_SRAM_2_APP4        "-include sram2_OsApp4.h")
set(COMPILE_FLAGS_REGION_SRAM_2_APP5        "-include sram2_OsApp5.h")
set(COMPILE_FLAGS_REGION_SRAM_2_SYSTEM      "-include sram2_OsAppBaseSystem.h")
set(COMPILE_FLAGS_REGION_SRAM_2_ZUSE1BIT    "-include sram2_OsApp2.h ${COMPILE_1_BIT_ACCESS}")

set(COMPILE_FLAGS_REGION_VRAM0_ECC_APP      "-include vram0_ecc_OsApp2.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_VRAM0_ECC_APP3     "-include vram0_ecc_OsApp3.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_VRAM0_ECC_APP4     "-include vram0_ecc_OsApp4.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_VRAM0_ECC_APP5     "-include vram0_ecc_OsApp5.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_VRAM0_ECC_SYSTEM   "-include vram0_ecc_OsAppBaseSystem.h ${COMPILE_1_BIT_ACCESS}")

set(COMPILE_FLAGS_REGION_VRAM1_ECC_APP      "-include vram1_ecc_OsApp2.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_VRAM1_ECC_APP3     "-include vram1_ecc_OsApp3.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_VRAM1_ECC_APP4     "-include vram1_ecc_OsApp4.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_VRAM1_ECC_APP5     "-include vram1_ecc_OsApp5.h ${COMPILE_1_BIT_ACCESS}")
set(COMPILE_FLAGS_REGION_VRAM1_ECC_SYSTEM   "-include vram1_ecc_OsAppBaseSystem.h ${COMPILE_1_BIT_ACCESS}")
