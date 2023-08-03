#include "univers.hxx"
#include <gtest/gtest.h>

void affiche_voisins(Cellule *cellule, std::ostream& output_stream) {
    output_stream << cellule->getCentre() << " => ";
    for (Cellule *cellule_voisine : cellule->getVoisins()) {
        if (cellule_voisine != nullptr) {
            output_stream << cellule_voisine->getCentre() << "; ";
        }
    }
    output_stream << "FIN";
}

void affiche_particules_de_cellule(Cellule *cellule, std::ostream& output_stream) {
    output_stream << cellule->getCentre() << " => ";
    for (Particule *particle : cellule->getParticles()) {
        output_stream << particle->getPosition() << "; ";
    }
    output_stream << "FIN";
}

TEST(TestGrille, VoisinsGrille1d) {
    Univers *univers_1d = new Univers(1, 1, Point(6, 0, 0));
    int n_cd1 = univers_1d->getGrid()->get_ncd1();
    Cellule *cellule;
    std::stringstream output;
    std::stringstream expected_output;
    for (int i = 0; i < n_cd1; i++) {
        cellule = univers_1d->getGrid()->getCell(i, 0, 0);
        affiche_voisins(cellule, output);
        output << std::endl;
    }

    expected_output << "-2.5 0 0  => -2.5 0 0 ; -1.5 0 0 ; FIN\n-1.5 0 0  => -2.5 0 0 ; -1.5 0 0 ; -0.5 0 0 ; FIN\n-0.5 0 0  => -1.5 0 0 ; -0.5 0 0 ; 0.5 0 0 ; FIN\n0.5 0 0  => -0.5 0 0 ; 0.5 0 0 ; 1.5 0 0 ; FIN\n1.5 0 0  => 0.5 0 0 ; 1.5 0 0 ; 2.5 0 0 ; FIN\n2.5 0 0  => 1.5 0 0 ; 2.5 0 0 ; FIN\n";
    
    EXPECT_EQ(output.str(), expected_output.str()) << "Les voisins des cellules dans un grille_1d ne sont pas corrects";
}


TEST(TestGrille, VoisinsGrille2d) {

    Univers *univers_2d = new Univers(2, 1, Point(4, 4, 0));

    int n_cd1 = univers_2d->getGrid()->get_ncd1();
    int n_cd2 = univers_2d->getGrid()->get_ncd2();
    int i, j;
    Cellule *cellule;
    i = 0;
    j = 0;
    cellule = univers_2d->getGrid()->getCell(i, j, 0);
    std::stringstream output;
    std::stringstream expected_output;

    affiche_voisins(cellule, output);

    expected_output << "-1.5 -1.5 0  => -1.5 -1.5 0 ; -1.5 -0.5 0 ; -0.5 -1.5 0 ; -0.5 -0.5 0 ; FIN";

    EXPECT_EQ(output.str(), expected_output.str()) << "Les voisins d'une Cellule au coin de l'univers ne sont pas corrects";

    output.str("");
    expected_output.str("");

    i = 0;
    j = n_cd2/2;
    cellule = univers_2d->getGrid()->getCell(i, j, 0);
    affiche_voisins(cellule, output);

    expected_output << "-1.5 0.5 0  => -1.5 -0.5 0 ; -1.5 0.5 0 ; -1.5 1.5 0 ; -0.5 -0.5 0 ; -0.5 0.5 0 ; -0.5 1.5 0 ; FIN";

    EXPECT_EQ(output.str(), expected_output.str()) << "Les voisins d'une Cellule au bord de l'univers (coins exclu) ne sont pas corrects";

    output.str("");
    expected_output.str("");

    i = n_cd1/2;
    j = n_cd2/2;
    cellule = univers_2d->getGrid()->getCell(i, j, 0);
    affiche_voisins(cellule, output);

    expected_output << "0.5 0.5 0  => -0.5 -0.5 0 ; -0.5 0.5 0 ; -0.5 1.5 0 ; 0.5 -0.5 0 ; 0.5 0.5 0 ; 0.5 1.5 0 ; 1.5 -0.5 0 ; 1.5 0.5 0 ; 1.5 1.5 0 ; FIN";

    EXPECT_EQ(output.str(), expected_output.str()) << "Les voisins d'une Cellule à l'intérieur de l'univers (coins et bords exclus) ne sont pas corrects";
}

TEST(TestGrille, VoisinsGrille3d) {
    Univers *univers_3d = new Univers(3, 1, Point(4, 4, 4));
    int n_cd1 = univers_3d->getGrid()->get_ncd1();
    int n_cd2 = univers_3d->getGrid()->get_ncd2();
    int n_cd3 = univers_3d->getGrid()->get_ncd3();
    int i, j, k;
    Cellule *cellule;
    std::stringstream output;
    std::stringstream expected_output;

    i = 0;
    j = 0;
    k = 0;
    cellule = univers_3d->getGrid()->getCell(i, j, k);
    affiche_voisins(cellule, output);
    expected_output << "-1.5 -1.5 -1.5  => -1.5 -1.5 -1.5 ; -1.5 -1.5 -0.5 ; -1.5 -0.5 -1.5 ; -1.5 -0.5 -0.5 ; -0.5 -1.5 -1.5 ; -0.5 -1.5 -0.5 ; -0.5 -0.5 -1.5 ; -0.5 -0.5 -0.5 ; FIN";

    EXPECT_EQ(output.str(), expected_output.str()) << "Les Cellules voisines d'une Cellule située à un coin de l'univers (sommet) ne sont pas correctes";

    output.str("");
    expected_output.str("");

    i = 0;
    j = 0;
    k = n_cd3/2;
    cellule = univers_3d->getGrid()->getCell(i, j, k);
    affiche_voisins(cellule, output);
    expected_output << "-1.5 -1.5 0.5  => -1.5 -1.5 -0.5 ; -1.5 -1.5 0.5 ; -1.5 -1.5 1.5 ; -1.5 -0.5 -0.5 ; -1.5 -0.5 0.5 ; -1.5 -0.5 1.5 ; -0.5 -1.5 -0.5 ; -0.5 -1.5 0.5 ; -0.5 -1.5 1.5 ; -0.5 -0.5 -0.5 ; -0.5 -0.5 0.5 ; -0.5 -0.5 1.5 ; FIN";

    EXPECT_EQ(output.str(), expected_output.str()) << "Les Cellules voisines d'une Cellule située sur une arête de l'univers ne sont pas correctes";

    output.str("");
    expected_output.str("");

    i = 0;
    j = n_cd2/2;
    k = n_cd3/2;
    cellule = univers_3d->getGrid()->getCell(i, j, k);
    affiche_voisins(cellule, output);
    expected_output << "-1.5 0.5 0.5  => -1.5 -0.5 -0.5 ; -1.5 -0.5 0.5 ; -1.5 -0.5 1.5 ; -1.5 0.5 -0.5 ; -1.5 0.5 0.5 ; -1.5 0.5 1.5 ; -1.5 1.5 -0.5 ; -1.5 1.5 0.5 ; -1.5 1.5 1.5 ; -0.5 -0.5 -0.5 ; -0.5 -0.5 0.5 ; -0.5 -0.5 1.5 ; -0.5 0.5 -0.5 ; -0.5 0.5 0.5 ; -0.5 0.5 1.5 ; -0.5 1.5 -0.5 ; -0.5 1.5 0.5 ; -0.5 1.5 1.5 ; FIN";

    EXPECT_EQ(output.str(), expected_output.str()) << "Les Cellules voisines d'une Cellule située sur la face de l'univers ne sont pas correctes";

    output.str("");
    expected_output.str("");

    i = n_cd1/2;
    j = n_cd2/2;
    k = n_cd3/2;
    cellule = univers_3d->getGrid()->getCell(i, j, k);
    affiche_voisins(cellule, output);
    expected_output << "0.5 0.5 0.5  => -0.5 -0.5 -0.5 ; -0.5 -0.5 0.5 ; -0.5 -0.5 1.5 ; -0.5 0.5 -0.5 ; -0.5 0.5 0.5 ; -0.5 0.5 1.5 ; -0.5 1.5 -0.5 ; -0.5 1.5 0.5 ; -0.5 1.5 1.5 ; 0.5 -0.5 -0.5 ; 0.5 -0.5 0.5 ; 0.5 -0.5 1.5 ; 0.5 0.5 -0.5 ; 0.5 0.5 0.5 ; 0.5 0.5 1.5 ; 0.5 1.5 -0.5 ; 0.5 1.5 0.5 ; 0.5 1.5 1.5 ; 1.5 -0.5 -0.5 ; 1.5 -0.5 0.5 ; 1.5 -0.5 1.5 ; 1.5 0.5 -0.5 ; 1.5 0.5 0.5 ; 1.5 0.5 1.5 ; 1.5 1.5 -0.5 ; 1.5 1.5 0.5 ; 1.5 1.5 1.5 ; FIN";

    EXPECT_EQ(output.str(), expected_output.str()) << "Les Cellules voisines d'une Cellule située à l'intérieur de l'univers ne sont pas correctes";
}

TEST(TestGrille, UpdateLogicalPosition) {
    Univers *univers_3d = new Univers(3, 1, Point(4, 4, 4));

    int n_cd1 = univers_3d->getGrid()->get_ncd1();
    int n_cd2 = univers_3d->getGrid()->get_ncd2();
    int n_cd3 = univers_3d->getGrid()->get_ncd3();

    Particule *particle = new Particule(Point(0.2, 0.2, 0.2), Point(0, 0, 0), 1, 3, 0);
    std::stringstream output;
    std::stringstream expected_output;

    univers_3d->add_particle(particle);

    Cellule *cellule = univers_3d->getGrid()->getCell(n_cd1/2, n_cd2/2, n_cd3/2);
    affiche_particules_de_cellule(cellule, output);
    expected_output << "0.5 0.5 0.5  => 0.2 0.2 0.2 ; FIN";

    EXPECT_EQ(output.str(), expected_output.str()) << "La particule de coordonnées (0.2, 0.2, 0.2) n'est pas insérée dans la bonne Cellule de centre (0.5, 0.5, 0.5)";
    output.str("");
    expected_output.str("");

    particle->setPosition(Point(0.2, 0.2, 1.2));

    univers_3d->update_position_logique_particules();

    cellule = univers_3d->getGrid()->getCell(n_cd1/2, n_cd2/2, n_cd3/2);
    affiche_particules_de_cellule(cellule, output);
    expected_output << "0.5 0.5 0.5  => FIN";
    
    EXPECT_EQ(output.str(), expected_output.str()) << "La particule de coordonnées (0.2, 0.2, 1.2) ne doit plus être dans la Cellule de centre (0.5, 0.5, 0.5)";
    output.str("");
    expected_output.str("");

    cellule = univers_3d->getGrid()->getCell(n_cd1/2, n_cd2/2, n_cd3/2 + 1);
    affiche_particules_de_cellule(cellule, output);
    expected_output << "0.5 0.5 1.5  => 0.2 0.2 1.2 ; FIN";
    EXPECT_EQ(output.str(), expected_output.str()) << "La particule de coordonnées (0.2, 0.2, 1.2) doit être dans la Cellule de centre (0.5, 0.5, 1.5)";
}