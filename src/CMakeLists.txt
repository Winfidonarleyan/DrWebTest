cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (DRWebTest "DRWebTest.cpp" "DRWebTest.h" "Dictionary.h" "NotFoundException.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DRWebTest PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
