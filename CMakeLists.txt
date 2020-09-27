cmake_minimum_required(VERSION 3.10)

project(rubeus)

set(RUBEUS_SOURCE_FILES
    inc/IListObserver.hpp
    inc/IModel.hpp
    inc/IView.hpp
    inc/ListView.hpp src/ListView.cpp
    inc/Logger.hpp src/Logger.cpp
    inc/Model.hpp src/Model.cpp
    inc/PasswordEntry.hpp src/PasswordEntry.cpp
    inc/Rubeus.hpp src/Rubeus.cpp

    inc/colors.hpp src/colors.cpp

    src/main.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} ${RUBEUS_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC ncurses)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
