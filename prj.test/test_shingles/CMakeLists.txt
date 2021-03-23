add_executable(test_shingles test_shingles.cpp)
target_link_libraries(test_shingles shingles)
set_property(TARGET shingles PROPERTY CXX_STANDARD 17)