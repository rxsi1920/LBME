set(SOURCES
    main.c
    app_info.h
    lbme.c
    lbme.h
    screen.c
    screen.h
    battery.c
    battery.h
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ncurses)