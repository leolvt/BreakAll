set(BREAKALL_SRC 
    ${BREAKALL_SRC} 
    Level.cpp
    GameMode.cpp
    BreakAll.cpp
    main.cpp 
)

add_executable(BreakAll ${BREAKALL_SRC})
target_link_libraries(BreakAll ${BREAKALL_LIBS})

install(TARGETS BreakAll DESTINATION bin)
