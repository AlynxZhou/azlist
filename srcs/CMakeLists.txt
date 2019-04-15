aux_source_directory("." SRCS)
add_library("azlist" ${SRCS})
target_include_directories("azlist" PUBLIC "include")
