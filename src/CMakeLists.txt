set(BREAKALL_SRC 
    ${BREAKALL_SRC} 
    paddle.cpp
    Brick.cpp
	Ball.cpp
    Level.cpp
    GameMode.cpp
    BreakAll.cpp
    main.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++0x")

add_executable(BreakAll ${BREAKALL_SRC})
target_link_libraries(BreakAll ${BREAKALL_LIBS})

install(TARGETS BreakAll DESTINATION bin)
