cmake_minimum_required(VERSION 3.10)

project(rubeus)

set(USR_LOCAL /usr/local)

set(RUBEUS_SOURCE_FILES
    inc/CommandView.hpp src/CommandView.cpp
    inc/CreateView.hpp src/CreateView.cpp
    inc/Engine.hpp src/Engine.cpp
    inc/IListObserver.hpp
    inc/IModel.hpp
    inc/IView.hpp src/IView.cpp
    inc/ListView.hpp src/ListView.cpp
    inc/Logger.hpp src/Logger.cpp
    inc/Model.hpp src/Model.cpp
    inc/PasswordEntry.hpp src/PasswordEntry.cpp
    inc/Rubeus.hpp src/Rubeus.cpp
    inc/RubeusCommand.hpp src/RubeusCommand.cpp

    inc/colors.hpp src/colors.cpp
    inc/crypto.hpp src/crypto.cpp

    src/main.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} ${RUBEUS_SOURCE_FILES})

target_link_directories(${PROJECT_NAME} PUBLIC ${USR_LOCAL}/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC ncurses sqlite3 crypto scrypt-kdf)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc ${USR_LOCAL}/include)
