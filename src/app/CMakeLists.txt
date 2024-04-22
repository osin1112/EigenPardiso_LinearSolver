set(compile_options_tmp ${base_compile_options} " -D_GLOG")

string(REPLACE " " ";" compile_options_tmp ${compile_options_tmp})

set(main_target "main.o")

add_executable(${main_target} ${main_src})
target_sources(${main_target}
  PRIVATE
    main.cpp
)
target_compile_options(${main_target} PUBLIC ${compile_options_tmp})

target_link_libraries(${main_target} PRIVATE
  EP
  LA
  iomp5
  ${GLOG_LIBRARY}
  ${TP_LIBRARY}
  ${VTK_LIBRARIES}
)

target_include_directories(${main_target} PRIVATE
  ${PROJECT_SOURCE_DIR}/src/EigenPardiso
  ${PROJECT_SOURCE_DIR}/src/Laplace
)

install(TARGETS ${main_target} DESTINATION ${CMAKE_INSTALL_PREFIX})