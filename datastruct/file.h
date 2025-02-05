/**
 * @file file.h
 * @brief Fichier d'accés à une file et aux fonctions principales. Fortement lié à file.c.
 * @author Lucas REVERBEL--LONGHI
 * @date 2025-02-04
*/ 

/**
 * @fn file *newFile()
 * @brief Fonction pour l'initialisation d'une nouvelle File.
 * @return Un pointeur sur une File
 */
file *newFile();

/**
 * @fn char fileVide(file *f)
 * @brief Vérifie qu'une File est vide.
 * @param[in] f Un pointeur sur une File.
 * @return Renvoie dans un char 1 si la File est vide, 0 sinon.
 */
char fileVide(file *f);

/**
 * @fn void fileFree(file **f)
 * @brief Supprime une File et met le pointeur sur NULL.
 * @param[in] L'address d'un pointeur sur une File.
 */
void fileFree(file **f);

/**
 * @fn void *fileRetirerTete(file *f)
 * @brief Renvoie et retire la valeur positionné en tête de la File.
 * @param[in] f Un pointeur sur une File.
 * @return Renvoie le pointeur sur la valeur positionné en tête de la File.
 */
void *fileRetirerTete(file *f);

/**
 * @fn void fileAjoutQueue(file *f, void* val)
 * @brief Ajoute une valeur en queue de la File.
 * @param[in] f Un pointeur sur une File.
 * @param[in] val La valeur à inserer dans la File
 */
void fileAjoutQueue(file *f, void* val);

/**
 * @fn int fileLength(file *f)
 * @brief Calcule renvoie la longueur de la File.
 * @param[in] f Un pointeur sur une File.
 * @return Renvoie un entier correspondant à la taille de la File.
 */
int fileLength(file *f);

/**
 * @fn void file_destroyType(void *val)
 * @brief Fonction de destruction des types de bases
 * @param[in] val Une variable allouée dynamiquement à detruire.
 */  
void file_destroyType(void *val);