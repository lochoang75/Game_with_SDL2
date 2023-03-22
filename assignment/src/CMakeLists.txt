# Add compiler errors/warnings flags
set(SOURCES loader_params.cc texture_wrapper.cc game_manage.cc animation_manage.cc animation.cc
            texture_manager.cc game_object_factory.cc box2d_facade.cc SDL_game_object.cc game_debug.cc
            game_contact_listener.cc tree.cc game_container_object.cc bird.cc fruit.cc kids.cc 
            game_speech.cc game_font_manage.cc game_bubble.cc main.cc)        

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
target_compile_definitions(${PROJECT_NAME} PUBLIC LOGGER_PREFIX_LEVEL=3)

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE ../include)
target_include_directories(${PROJECT_NAME} PRIVATE ../box2d/include/box2d)
target_include_directories(${PROJECT_NAME} PRIVATE ../game_event/include)

# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} -lSDL2)

# Add SDL2_image library
find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME} -lSDL2_image)

# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} -lSDL2_ttf)

target_link_libraries(${PROJECT_NAME} eventLib)

# Add SDL2_net library
#find_package(SDL2_net REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Net)

# Add SDL2_mixer library
#find_package(SDL2_mixer REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

# Add SDL2_gfx library
#find_package(SDL2_gfx REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::GFX)



target_link_libraries(${PROJECT_NAME} box2d)