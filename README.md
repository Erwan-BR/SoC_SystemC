# SoC_SystemC

## Compiler chaque question

Nommons :
- IMAGE.gdr (femme.gdr, grenoble.gdr, bloc.gdr, tintin.gdr, bureau.gdr, demo.gdr, carre.gdr) l'image qui va être traitée.
- TRAITEMENT (gh\_1D, gv\_1D, gh\_2D, gv\_2D, grad, seuil, sobel, roberts) le traitement appliqué.

1. Ouvrir le dossier correspondant à la question : code/sc\_TRAITEMENT

2. Compiler le projet avec la commande bash suivante :
``` bash
make -f TRAITEMENT.mak
```
3. Executer le code compilé avec l'une des images disponibles, et enregistrer la sortie à un endroit approprié.
``` bash
./bin/TRAITEMENT.x ../../images/originales/IMAGE ../../images/TRAITEMENT/IMAGE
```

## Compiler toutes les questions.
Il suffit de compiler le fichier main.cpp.

Attention !
- Si on le compile tel quel, 49 images vont s'afficher. Il est recommandé de garder dans le vecteur suivant uniquement les executables que l'on veut compiler :
```cpp:main.cpp
const std::vector<std::string> executables = {gh_1D_path, gv_1D_path, gh_2D_path, gv_2D_path, grad_path, seuil_path, sobel_path, roberts_path};
```
- Si on veut compiler seuil, il faut passer un argument de seuil et donc l'indiquer à la ligne suivante :
```cpp:main.cpp
const std::string command = executables[index] + " "
                      + original_images_folder + fileName + " "
                      + main_path + "images/" + nom_sortie[index] + "/" + output_file_name + " 30" ;
```
