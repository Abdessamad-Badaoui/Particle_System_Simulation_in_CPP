#include "univers.hxx"
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>

Univers::Univers(int dimension, double rayon_coupure, Point grandeur_univers) {
    assert((dimension >= 1) && (rayon_coupure > 0));
    dim = dimension;
    r_cut = rayon_coupure;
    L_d.resize(3);


    for (int i = 0; i < 3; i++) {
        L_d[i] = grandeur_univers(i);
    }

    particles_collection = {};
    int n_cd1 = (int) (L_d[0]/r_cut);
    int n_cd2 = (int) (L_d[1]/r_cut);
    int n_cd3 = (int) (L_d[2]/r_cut);

    switch (dim)
    {
        case 1:
            this->grid_ = new Grille_1d();
            break;
        case 2:
            this->grid_ = new Grille_2d();
            break;
        case 3:
            this->grid_ = new Grille_3d();
            break;
        default:
            std::cout << "La dimension doit etre soit 1,2 ou 3" << std::endl;
            exit(EXIT_FAILURE);
            break;
    }

    this->grid_->set_number_of_cells(n_cd1, n_cd2, n_cd3);
    this->grid_->initCells(grandeur_univers, r_cut);
    this->grid_->setVoisins(r_cut);
    this->initGridG();
}

void Univers::initGridG() {
    this->grid_->setG(this->G);
}

// Getters
int Univers::getDim(){
    return dim;
}

double Univers::getRCut(){
    return r_cut;
}

std::vector<double>& Univers::getLD(){
    return L_d;
}

Grille *Univers::getGrid() {
    return this->grid_;
}

// Setters
void Univers::setDim(int dim) {
    this->dim = dim;
}

void Univers::setRCut(double r_cut) {
    this->r_cut = r_cut;
}

void Univers::setLD(const std::vector<double>& l_d) {
    this->L_d = l_d;
}

void Univers::setG(double G) {
    this->G = G;
}

void Univers::add_particle(Particule *particule) {
    if (particule->getDim() <= dim) {
        particles_collection.push_back(particule);

        double particule_x = particule->getPosition().val[0];
        double particule_y = particule->getPosition().val[1];
        double particule_z = particule->getPosition().val[2];

        int particle_index_i = (particule_x + L_d[0]/2) >= 0 ? (int) ((particule_x + L_d[0]/2)/r_cut) : -1;
        int particle_index_j = (particule_y + L_d[1]/2) >= 0 ? (int) ((particule_y + L_d[1]/2)/r_cut) : -1;
        int particle_index_k = (particule_z + L_d[2]/2) >= 0 ? (int) ((particule_z + L_d[2]/2)/r_cut) : -1;
        
        this->grid_->add_particle(particule, particle_index_i, particle_index_j, particle_index_k, r_cut);
   }
    else {
        std::cerr << "La dimension de la particule est supérieure à celle de l'univers" << std::endl;
        exit(1);
    }
}

void Univers::evolve(double dt, double duree) {
    double t = 0;
    while (t < duree) {
        t = t + dt;
        for (Particule *particle: particles_collection) {
            particle->advance_position(dt);
            particle->salvageOldForce();
        }
        update_forces_gravitationnelle();

        for (Particule *particle:particles_collection) {
            particle->advance_vitesse(dt);
        }
    }
}

void Univers::initialize_system() {
    for (Particule *particle1:particles_collection) {
        for (Particule *particle2:particles_collection) {
            if (particle1 != particle2) {
                particle1->updateForce(*particle2);
            }
        }
    }
}

void Univers::update_forces_gravitationnelle() {
    int n = particles_collection.size();
    for (Particule *particle : particles_collection) {
        particle->reinitialiseForce();
    }

    int i,j;
    Particule *particle1;
    Particule *particle2;
    for (i = 0; i < n; i++) {
        particle1 = particles_collection.at(i);
        for (j = i+1; j < n; j++) {
            particle2 = particles_collection.at(j);
            particle1->updateForce(*particle2);
            particle2->updateForce(*particle1);
        }
    }
}

void Univers::update_forces_potentielles_no_grille(double sigma, double epsilon) {
    int n = particles_collection.size();
    for (Particule *particle : particles_collection) {
        particle->reinitialiseForce();
    }

    int i,j;
    Particule *particle1;
    Particule *particle2;
    for (i = 0; i < n; i++) {
        particle1 = particles_collection.at(i);
        for (j = i+1; j < n; j++) {
            particle2 = particles_collection.at(j);
            particle1->updateForceChargee(*particle2, sigma, epsilon, r_cut);
            particle2->updateForceChargee(*particle1, sigma, epsilon, r_cut);
        }
    }
}

void Univers::update_forces_potentielles_grille(double sigma, double epsilon, bool gravite, bool reflect_potentiel, std::vector<double> L_d) {
    this->grid_->update_forces_potentielles(sigma, epsilon, r_cut, gravite, reflect_potentiel, L_d);
}

void Univers::evolve_potentiel(double dt, double duree, double sigma, double epsilon, bool gravite) {
    double t = 0;
    int i = 0;
    update_forces_potentielles_grille(sigma, epsilon, true, true, this->L_d);
    int number_of_frames = 20;
    int number_of_iterations = ((int) (duree/dt))/number_of_frames;

    std::string directory = "simulation_frames";

    std::stringstream frame_name;
    std::string radical = directory + "/frame";

    int result = mkdir(directory.c_str(), 0777);

    if (!(result == 0 || errno == EEXIST)) {
        std::cerr << "Failed to create simulation_frames directory" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ofstream animation_file("animation_simulation.pvd");
    animation_file << "<VTKFile type=\"Collection\" version=\"0.1\" byte_order=\"BigEndian\">" << std::endl;
    animation_file << "\t<Collection>" << std::endl;

    while (t <= duree) {
        if ((i++)%number_of_iterations == 0) {
            frame_name << radical << i/number_of_iterations << ".vtu";
            this->generate_vtk_file(frame_name.str());
            animation_file << "\t\t<DataSet timestep=\"" << i/number_of_iterations << "\" file=\"" << frame_name.str() << "\"/>" << std::endl;
            frame_name.str("");
        }
        t = t + dt;
        for (Particule *particle: particles_collection) {
            // particle->advance_position(dt, LimitCondition::Reflection, L_d[0], L_d[1], L_d[2]);
            particle->advance_position(dt);
            // particle->salvageOldForce();
        }
        update_position_logique_particules();
        update_forces_potentielles_grille(sigma, epsilon, true, true, this->L_d);

        for (Particule *particle:particles_collection) {
            particle->advance_vitesse(dt);
        }
    }
    animation_file << "\t</Collection>" << std::endl;
    animation_file << "</VTKFile>" << std::endl;
    animation_file.close();
    
}

void Univers::evolve_potentiel_no_grille(double dt, double duree, double sigma, double epsilon) {
    double t = 0;

    while (t < duree) {
        t = t + dt;
        for (Particule *particle: particles_collection) {
            particle->advance_position(dt);
            particle->salvageOldForce();
        }
        update_forces_potentielles_no_grille(sigma, epsilon);

        for (Particule *particle:particles_collection) {
            particle->advance_vitesse(dt);
        }
    }
}

void Univers::update_position_logique_particules() {
    this->grid_->update_position_logique_particules(L_d[0], L_d[1], L_d[2], r_cut);
}

int Univers::generate_vtk_file(const std::string& file_name) {
    std::ofstream vtk_file(file_name);
    if (!vtk_file) {
        std::cerr << "Failed to open" << file_name << std::endl;
        return 1;
    }
    vtk_file << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"BigEndian\">" << std::endl;
    vtk_file << "\t<UnstructuredGrid>" << std::endl;
    vtk_file << "\t\t<Piece NumberOfPoints=\"" << this->particles_collection.size() << "\" NumberOfCells=\"0\">" << std::endl;
    vtk_file << "\t\t\t<Points>" << std::endl;
    vtk_file << "\t\t\t\t<DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">" << std::endl;
    vtk_file << "\t\t\t\t\t";
    std::stringstream velocity_values;
    std::stringstream mass_values;
    for (Particule *particle : this->particles_collection) {
        vtk_file << particle->getPosition();
        velocity_values << particle->getVitesse();
        mass_values << particle->getMasse() << " ";
    }
    vtk_file << std::endl << "\t\t\t\t</DataArray>" << std::endl;
    vtk_file << "\t\t\t</Points>" << std::endl;
    vtk_file << "\t\t\t<PointData Vectors=\"vector\">" << std::endl;
    vtk_file << "\t\t\t\t<DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">" << std::endl;
    vtk_file << "\t\t\t\t\t";
    vtk_file << velocity_values.str() << std::endl;
    vtk_file << "\t\t\t\t</DataArray>" << std::endl;
    vtk_file << "\t\t\t\t<DataArray type=\"Float32\" Name=\"Masse\" format=\"ascii\">" << std::endl;
    vtk_file << "\t\t\t\t\t";
    vtk_file << mass_values.str() << std::endl;
    vtk_file << "\t\t\t\t</DataArray>" << std::endl;
    vtk_file << "\t\t\t</PointData>" << std::endl;
    vtk_file << "\t\t\t<Cells>" << std::endl;
    vtk_file << "\t\t\t\t<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">" << std::endl;
    vtk_file << "\t\t\t\t</DataArray>" << std::endl;
    vtk_file << "\t\t\t\t<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">" << std::endl;
    vtk_file << "\t\t\t\t</DataArray>" << std::endl;
    vtk_file << "\t\t\t\t<DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">" << std::endl;
    vtk_file << "\t\t\t\t</DataArray>" << std::endl;
    vtk_file << "\t\t\t</Cells>" << std::endl;
    vtk_file << "\t\t</Piece>" << std::endl;
    vtk_file << "\t</UnstructuredGrid>" << std::endl;
    vtk_file << "</VTKFile>";
    vtk_file.close();
    return 0;
}