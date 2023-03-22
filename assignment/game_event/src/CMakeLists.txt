set(input_event_source game_touch_event_impl.cc)
add_library(eventLib STATIC ${input_event_source})
target_include_directories(eventLib PRIVATE "../include")
target_include_directories(eventLib PRIVATE "../../include")

find_package(Threads REQUIRED)  
target_link_libraries(eventLib PRIVATE Threads::Threads)