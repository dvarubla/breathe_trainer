project(breathe_trainer_tests)
add_library(testlib STATIC mocks/TrainerModelListenerMock.h)
target_link_libraries(testlib PUBLIC gtest_main gmock)
target_include_directories(testlib PUBLIC ${CURRENT_SRC_DIR} mocks)

function(add_bt_test name src)
    add_executable(${name} "${src}")
    target_link_libraries(${name} PUBLIC testlib)
    target_link_libraries(${name} PUBLIC BreatheTrainerL)
endfunction()

add_bt_test(TrainerModelTest TrainerModelT.cpp)

