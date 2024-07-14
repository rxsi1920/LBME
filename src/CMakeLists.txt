set(SOURCES
    main.c
    app_info.h
    battery.c
    battery.h
    lbme.c
    lbme.h
    pages.c
    pages.h
    plot.c
    plot.h
    screen.c
    screen.h
    util.c
    util.h
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ncursesw)