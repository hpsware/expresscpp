include(CTest)

add_executable(test_${PROJECT_NAME}
               layer.cpp
               basic.cpp
               routing.cpp
               hello_world.cpp
               console.cpp
               long_session.cpp
               error_handler.cpp
               path_to_regexp.cpp
               url.cpp
               date.cpp
               http_methods.cpp
               middleware.cpp
               multiple_handlers.cpp
               routing_table.cpp
               test_main.cpp
               serve_favicon.cpp
               static_file_middleware.cpp)

target_link_libraries(test_${PROJECT_NAME}
                      ${PROJECT_NAME}
                      GTest::GTest
                      ${Boost_LIBRARIES}
                      Threads::Threads)

add_test(test_${PROJECT_NAME}
         ${CMAKE_BINARY_DIR}/bin/test_${PROJECT_NAME})
