# Créer une bibliothèque à partir d'un ensemble de fichier sans main
add_library(particules particules.cxx point.cxx)
add_library(point point.cxx)
add_library(univers univers.cxx particules.cxx point.cxx fast_exponentiation.cxx cellule.cxx grille.cxx grille_1d.cxx grille_2d.cxx grille_3d.cxx)
add_library(cellule cellule.cxx particules.cxx point.cxx)
add_library(fast_exponentiation fast_exponentiation.cxx)