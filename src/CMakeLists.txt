set(BREAKOUT_SRC 
    ${BREAKOUT_SRC} 
    main.cpp 
    )

add_executable(Breakout ${BREAKOUT_SRC})
target_link_libraries(Breakout ${BREAKOUT_LIBS})

install(TARGETS Breakout DESTINATION bin)
