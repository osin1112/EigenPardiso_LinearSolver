set(compile_options_tmp ${base_compile_options})
string(REPLACE " " ";" compile_options_tmp ${compile_options_tmp})

add_library(LA STATIC)
target_sources(LA
  PRIVATE
    Geometry.cpp
    Laplace.cpp
    ${PROJECT_SOURCE_DIR}/src/EigenPardiso/EigenPardiso.cpp
)

target_include_directories(LA PUBLIC
  ${PROJECT_SOURCE_DIR}/src/EigenPardiso
  ${PROJECT_SOURCE_DIR}/src/Laplace
)

target_link_libraries(LA PUBLIC ${EIGEN_LIBRARIES} ${MKL_LIBRARIES} TBB::tbb)

target_compile_options(LA PUBLIC ${compile_options_tmp})