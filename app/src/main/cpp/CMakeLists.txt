cmake_minimum_required(VERSION 3.10.2)


aux_source_directory(. SOURCE)

#add_library(native-lib
#        SHARED
#        native-lib.cpp JavaListener.cpp)
add_library(
        native-lib
        SHARED
        ${SOURCE})



find_library(
              log-lib
              log )

target_link_libraries(
                       native-lib
                       ${log-lib} )