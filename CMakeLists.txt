cmake_minimum_required(VERSION 3.19)
project(html_server C)

set(CMAKE_C_STANDARD 99)

add_executable(http_server server.c)
add_executable(http_client client.c)