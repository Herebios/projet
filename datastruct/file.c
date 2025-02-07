#include "file.h"

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
	*f = NULL;
}

void *defiler(file *f){
	if (f == NULL || f->head == NULL){
		return NULL;
	}
	fileElem *temp = f->head->next;
	void *retVal = f->head->val;
	free(f->head);
	f->head = temp;
	return retVal;
}

void enfiler(file *f, void* val, size_t size){
	f->queue->next = (fileElem*) malloc(sizeof(fileElem));
	f->queue = f->queue->next;
	f->queue->val = malloc(size);
	memcpy(f->queue->val, val, size);
	f->queue->next = NULL;
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
	while (fe->next){
		k++;
		fe = fe->next;
	}
	return k;
}
