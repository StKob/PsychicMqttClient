file(GLOB_RECURSE lib_srcs "src/*.cpp" "src/*.c")

idf_component_register(
    SRCS "${lib_srcs}"
    INCLUDE_DIRS "src"
    REQUIRES espressif__arduino-esp32 mqtt
)
