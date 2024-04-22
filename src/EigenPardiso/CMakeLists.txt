set(compile_options_tmp ${base_compile_options})
string(REPLACE " " ";" compile_options_tmp ${compile_options_tmp})

add_library(EP STATIC)
target_sources(EP
  PRIVATE
    EigenPardiso.cpp
)

target_include_directories(EP PUBLIC
  ${PROJECT_SOURCE_DIR}/src/EigenPardiso
)

target_compile_options(EP PUBLIC ${compile_options_tmp})