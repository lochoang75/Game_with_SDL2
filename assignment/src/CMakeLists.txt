# Add compiler errors/warnings flags

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O0 -Wno-reorder -Wno-sign-compare -Wno-switch")

find_package(SDL2 REQUIRED)

find_package(SDL2_image REQUIRED)

#find_package((SDL2_))
#pkg_check_modules(SDL2 SDL2)
#pkg_check_modules(SDL2_image SDL2_image)
#pkg_check_modules(SDL2_ttf SDL2_ttf)

set(SOURCES texture_wrapper.cc game_manage.cc animation_manage.cc animation.cc
            texture_manager.cc game_object_factory.cc SDL_game_object.cc loader_params.cc main.cc)        

add_executable(${PROJECT_NAME} ${SOURCES})
# target_include_directories(${PROJECT_NAME} PUBLIC "../include"
#                      "${SDL2_INCLUDE_DIR}"
#                      "${SDL2_IMAGE_INCLUDE_DIR}"
#                      "${SDL2_TTF_INCLUDE_DIR}"
#                      "${SDL2_MIXER_INCLUDE_DIRS}"
# )

# target_link_libraries(${PROJECT_NAME} PUBLIC
#                       "${SDL2_LIBRARY}"
#                       "${SDL2_image_LDFLAGS}"
#                       "${SDL2_ttf_LDFLAGS}"
#                       "${SDL2_MIXER_LDFLAGS}")

target_include_directories(${PROJECT_NAME} PRIVATE ../include)
target_link_libraries(${PROJECT_NAME} SDL2::Main)
target_link_libraries(${PROJECT_NAME} SDL2::Image)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic )
target_compile_definitions(${PROJECT_NAME} PUBLIC LOGGER_PREFIX_LEVEL=3)