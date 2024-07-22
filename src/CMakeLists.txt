set(SOURCES
    main.c
    battery.c
    lbme.c
    pages.c
    plot.c
    screen.c
    util.c
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ncursesw)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)