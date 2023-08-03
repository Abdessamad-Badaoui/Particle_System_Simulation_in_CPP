# Pour chaque test (famille de test), un exécutable est cré
add_executable(test_point test_point.cc)
add_executable(test_grille test_grille.cc)
add_executable(test_fast_exponentiation test_fast_exponentiation.cc)

## Ne pas oublier d'ajouter la bibliothèque du projet (xxxx)
target_link_libraries(test_point gtest_main point)
target_link_libraries(test_grille gtest_main univers)
target_link_libraries(test_fast_exponentiation gtest_main fast_exponentiation)

include(GoogleTest)
gtest_discover_tests(test_point)