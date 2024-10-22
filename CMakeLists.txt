cmake_minimum_required(VERSION 3.13)

# This must happen before include() as of SDK 2.0.0
set(PICO_BOARD pico_w)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(network_scanner)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(network_scanner
  src/network_scanner.c
  )

target_compile_definitions(network_scanner PRIVATE
  WIFI_SSID=\"${REPLACE_ME}\"
  WIFI_PASSWORD=\"${REPLACE_ME}\"
  )

target_include_directories(network_scanner PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/include
  )

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(network_scanner pico_stdlib pico_lwip_nosys pico_cyw43_arch_lwip_threadsafe_background pico_multicore)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(network_scanner)
