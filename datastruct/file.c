#include "file.h"

/* Fonction pour créer une nouvelle file.
Renvoie NULL en cas d'échec, la file en cas de réussite
*/
file *newFile(){
	file *f = (file*) malloc(sizeof (file));
	if (f){
		f->head = f->queue = NULL;
	}
	return f;
}

char fileVide(file * f){
	return f->head==NULL;
}

void fileFree(file **f, void (*destroyFunction)(void*)){
	if (f == NULL || fileVide(*f)){
		return;
	}
	fileElem *temp;
	while ((*f)->head){
		temp = (*f)->head->next;
		destroyFunction((*f)->head->val);
		free((*f)->head);
		(*f)->head = temp;
	}
	free(*f);
	*f = NULL;
}

void *defiler(file *f){
	if (f->head == NULL)
		return NULL;
	fileElem *temp = f->head->next;
	void *retVal = f->head->val;
	free(f->head);
	f->head = temp;
	if (f->head == NULL){
		f->queue = NULL;
	}
	return retVal;
}

void enfiler(file *f, void* val, size_t size){
	if(f->queue){
		f->queue->next = (fileElem*) malloc(sizeof(fileElem));
		f->queue = f->queue->next;
	}else{
		f->head=f->queue = (fileElem*) malloc(sizeof(fileElem));
	}
	f->queue->val = malloc(size);
	memcpy(f->queue->val, val, size);
	f->queue->next = NULL;
}

int fileLength(file *f){
	int len = 0;
	fileElem *temp = f->head;
	while (temp->next){
		len++;
		temp = temp->next;
	}
	return len;
}
