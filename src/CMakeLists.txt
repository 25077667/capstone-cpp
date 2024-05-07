set(INCLUDE_DITS 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${capstone_SOURCE_DIR}/include
)

set(SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/capstone-wrapper.cpp
)

add_library(${PROJECT_NAME}-internal STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME}-internal PUBLIC ${INCLUDE_DITS})
target_link_libraries(${PROJECT_NAME}-internal PUBLIC capstone)
