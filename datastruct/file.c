#include "file.h"

typedef struct fileElem_s{void * val; struct fileElem_s *next;} fileElem; // structure pour un élément d'une file.
typedef struct file_s{fileElem *head, *queue;} file; // structure pour une file.


// Fonction pour la destrucion 
void file_destroyType(void *val){
	free(val);
}

// Fonction pour créer une nouvelle file.
file *newFile(){
	file *f = (file*) malloc(sizeof (file));
	if (f){ // On assigne les valeurs à NULL si l'allocation à réussit.
		f->head = NULL;
		f->queue = NULL;
	}
	return f; // Renvoie le pointeur ou NULL si l'allocation a échoué
}

char fileVide(file * f){
	return (f->head != NULL);
}

void fileFree(file **f, void (*destroyFunction)(void*)){
	if (f == NULL || fileVide(*f)){
		return;
	}
	fileElem *temp;
	while ((*f)->head != NULL){
		temp = (*f)->head->next;
		destroyFunction((*f)->head->val);
		free((*f)->head);
		(*f)->head = temp;
	}

	free(*f);
	f* = NULL;
}

void *fileRetirerTete(file *f){
	if (f == NULL || f->head == NULL){
		return NULL;
	}
	fileElem *temp = f->head->next;
	void *retVal = f->head->val;
	free(f->head);
	f->head = temp;
	return retVal;
}

void fileAjoutQueue(file *f, void* val){
	f->queue->next = (fileElem*) malloc(sizeof(fileElem));
	f->queue = f->queue->next;
	f->queue->val = val;
	f->queue->next = NULL;
}

int fileLength(file *f){
	int k = 0;
	fileElem *fe = f->head; 
	while (fileElem->next){
		k++;
		fe = fe->next;
	}
	return k;
}
