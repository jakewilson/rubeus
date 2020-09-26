cmake_minimum_required(VERSION 3.10)

project(rubeus)

set(RUBEUS_SOURCE_FILES
    inc/IController.h
    inc/IListObserver.h
    inc/IModel.h
    inc/ListView.h src/ListView.cpp
    inc/ListViewController.h
    inc/Logger.h src/Logger.cpp
    inc/Model.h src/Model.cpp
    inc/PasswordEntry.h src/PasswordEntry.cpp

    inc/colors.h src/colors.cpp

    src/main.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} ${RUBEUS_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC ncurses)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
