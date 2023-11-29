#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

/// @brief Appelle tous les composants créés pour générer toutes les images automatiquement. Permet de récupérer toutes les images plus simplement.
/// @return 0 si le code a fonctionné. -1 sinon.
int main()
{
    try
    {
        const std::string main_path = "/home/erwan/TP_SoC_3/";
        const std::string original_images_folder = main_path + "images/originales/";
        
        const std::string gh_1D_path   = main_path + "code/sc_gh_1D/bin/gh_1D.x";
        const std::string gv_1D_path   = main_path + "code/sc_gv_1D/bin/gv_1D.x";
        const std::string gh_2D_path   = main_path + "code/sc_gh_2D/bin/gh_2D.x";
        const std::string gv_2D_path   = main_path + "code/sc_gv_2D/bin/gv_2D.x";
        const std::string grad_path    = main_path + "code/sc_grad/bin/grad.x";
        const std::string seuil_path   = main_path + "code/sc_seuil/bin/seuil.x";
        const std::string sobel_path   = main_path + "code/sc_sobel/bin/sobel.x";
        const std::string roberts_path = main_path + "code/sc_roberts/bin/roberts.x";

        const std::vector<std::string> executables = {gh_1D_path, gv_1D_path, gh_2D_path, gv_2D_path, grad_path, seuil_path, sobel_path, roberts_path};
        const std::vector<std::string> nom_sortie  = {"gh_1D", "gv_1D", "gh_2D", "gv_2D", "grad", "seuil", "sobel", "roberts"};

        // Iteration sur tous les executables
        for (long unsigned int index = 0; index < executables.size(); index++)
        {
            for (const auto& entry : fs::directory_iterator(original_images_folder))
            {
                // Nom du fichier traité sous forme de chaine de caractere
                const std::string fileName = entry.path().filename().string();
                std::string output_file_name = fileName;
                output_file_name = output_file_name.replace(fileName.find(".gdr"), 4, "_" + nom_sortie[index] + ".gdr");

                // Construire la commande à executer en utilisant l'exécutable et le nom du fichier
                
                std::string command = executables[index] + " "
                                      + original_images_folder + fileName + " "
                                      + main_path + "images/" + nom_sortie[index] + "/" + output_file_name ;

                std::cout << "La commande est : " << command << std::endl;

                // Exécuter la commande système
                int result = std::system(command.c_str());

                // Vérifier le résultat de l'exécution de la commande
                if (result == 0)
                {
                    std::cout << "Commande exécutée avec succès pour : " << entry.path().filename() << std::endl;
                } else
                {
                    std::cerr << "Erreur lors de l'exécution de la commande pour : " << entry.path().filename() << std::endl;
                }
            }
        }
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
}