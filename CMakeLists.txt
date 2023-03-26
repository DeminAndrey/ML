cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(fashio_mnist VERSION ${PROJECT_VESRION})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(fashio_mnist
  src/main.cxx
  src/TFClassifier.cxx)

add_executable(fashio_mnist_test
  tests/ModelTest.cxx
  src/TFClassifier.cxx)

set_target_properties(fashio_mnist PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

target_include_directories(fashio_mnist
  PUBLIC include)
target_include_directories(fashio_mnist_test
  PUBLIC include)
target_link_libraries(fashio_mnist
  tensorflow)
target_link_libraries(fashio_mnist_test
  ${GTEST_LIBRARY}
  ${GTEST_MAIN_LIBRARY}
  Threads::Threads tensorflow)

install(TARGETS fashio_mnist RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()
gtest_add_tests(TARGET fashio_mnist_test
        TEST_LIST First
)

