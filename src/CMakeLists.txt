execute_process(COMMAND sdl-config --cflags WORKING_DIRECTORY src OUTPUT_VARIABLE SDL_C_FLAGS)
execute_process(COMMAND sdl-config --libs WORKING_DIRECTORY src OUTPUT_VARIABLE SDL_LINK_FLAGS)

string(STRIP ${SDL_C_FLAGS} SDL_C_FLAGS)
string(STRIP ${SDL_LINK_FLAGS} SDL_LINK_FLAGS)

execute_process(COMMAND pkg-config --cflags cairo WORKING_DIRECTORY src OUTPUT_VARIABLE CAIRO_C_FLAGS)
execute_process(COMMAND pkg-config --libs cairo WORKING_DIRECTORY src OUTPUT_VARIABLE CAIRO_LINK_FLAGS)

string(STRIP ${CAIRO_C_FLAGS} CAIRO_C_FLAGS)
string(STRIP ${CAIRO_LINK_FLAGS} CAIRO_LINK_FLAGS)



add_executable(SimpleSDLDemo main.cpp)

add_definitions(${SDL_C_FLAGS})

add_definitions(${CAIRO_C_FLAGS})



set_target_properties(SimpleSDLDemo PROPERTIES
	LINK_FLAGS "${CAIRO_LINK_FLAGS} ${SDL_LINK_FLAGS}")

add_custom_target(run SimpleSDLDemo
                    DEPENDS SimpleSDLDemo
                    WORKING_DIRECTORY src
                    COMMENT "Ejecutando SimpleSDLDemo ... ")
