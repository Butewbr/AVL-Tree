#ifndef ELEMENTO_H
#define ELEMENTO_H

typedef struct Elemento
{
	struct Elemento* _proximo;
	void* _dado;
} Elemento;

#endif /* ELEMENTO_H */