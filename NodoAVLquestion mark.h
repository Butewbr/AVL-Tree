#ifndef NODOAVL_H
#define NODOAVL_H

#include "ListaEncadeada.h"
#include <stdlib.h>

template<typename T>
struct NodoAVL
{
	NodoAVL * _filhoEsquerda;
	NodoAVL * _filhoDireita;
	T* _dado;
	int _altura;
};

template <typename T>
int getHigh(NodoAVL<T> *raiz)
{
    if (raiz == nullptr)
    {
        return -1;
    }
    return raiz->_altura;
}
int maxEntre(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

template<typename T>
NodoAVL<T>* criarNodo(T* dado)
{
	NodoAVL<T>* nodo = (NodoAVL<T> *)calloc(1, sizeof(NodoAVL<T>));
	nodo->_dado = dado;
	nodo ->_filhoEsquerda = NULL;
	nodo->_filhoDireita = NULL;
	nodo->_altura = 0;

	return nodo;
}

template<typename T>
NodoAVL<T>* rotardireita(NodoAVL<T>* raiz)
{
    NodoAVL<T> *aux = raiz->_filhoEsquerda;
    raiz->_filhoEsquerda = aux->_filhoDireita;
    aux->_filhoDireita = raiz;
    raiz->_altura = maxEntre(getHigh(raiz->_filhoDireita), getHigh(raiz->_filhoEsquerda)) + 1;
    aux->_altura = maxEntre(getHigh(aux->_filhoEsquerda), raiz->_altura) + 1;
    return aux;
}

template<typename T>
NodoAVL<T>* rotaresquerda(NodoAVL<T>* raiz)
{
    NodoAVL<T> *aux = raiz->_filhoDireita;
    raiz->_filhoDireita = aux->_filhoEsquerda;
    aux->_filhoEsquerda = raiz;
    raiz->_altura = maxEntre(getHigh(raiz->_filhoDireita), getHigh(raiz->_filhoEsquerda)) + 1;
    aux->_altura = maxEntre(getHigh(aux->_filhoEsquerda), raiz->_altura) + 1;
    return aux;
}

template<typename T>
int getBalance(NodoAVL<T>* raiz)
{
	if (raiz != nullptr)
	{
		if (raiz->_filhoEsquerda != nullptr and raiz->_filhoDireita != nullptr)
		{
			return raiz->_filhoEsquerda->_altura - raiz->_filhoDireita->_altura;
		}
		else if (raiz->_filhoEsquerda == nullptr and raiz->_filhoDireita != nullptr)
		{
			return -(raiz->_filhoDireita->_altura);
		}
		else if (raiz->_filhoEsquerda != nullptr and raiz->_filhoDireita == nullptr)
		{
			return raiz->_filhoEsquerda->_altura;
		}
		else		
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

template <typename T>
NodoAVL<T> *balancearNodo(NodoAVL<T> *raiz, T dadoF, int fb)
{
    if (fb == 2 || fb == -2)
    {
        if (dadoF < *raiz->_dado)
        {
            if (dadoF < *raiz->_filhoEsquerda->_dado)
            {
                raiz = rotardireita(raiz);
            }
            else
            {
                raiz = rotEsquerdaDireita(raiz);
            }
        }
        else
        {
            if (dadoF > *raiz->_filhoDireita->_dado)
            {
                raiz = rotaresquerda(raiz);
            }
            else
            {
                raiz = rotDireitaEsquerda(raiz);
            }
        }
    }
    return raiz;
}

template <typename T>
NodoAVL<T> *rotEsquerdaDireita(NodoAVL<T> *raiz)
{
    raiz->_filhoEsquerda = rotaresquerda(raiz->_filhoEsquerda);
    return rotardireita(raiz);
}
template <typename T>
NodoAVL<T> *rotDireitaEsquerda(NodoAVL<T> *raiz)
{
    raiz->_filhoDireita = rotardireita(raiz->_filhoDireita);
    return rotaresquerda(raiz);
}

template <typename T>
int getFB(NodoAVL<T> *raiz)
{

    return (getHigh(raiz->_filhoEsquerda) - getHigh(raiz->_filhoDireita));
}

template<typename T>
NodoAVL<T>* inserirnodo(NodoAVL<T>* raiz, T* dado)
{
    if (raiz == nullptr)
    {
        return criarNodo(dado);
    }

    if (*dado < *raiz->_dado)
    {
        raiz->_filhoEsquerda = inserirnodo(raiz->_filhoEsquerda, dado);
        int fb = getFB(raiz);
        raiz = balancearNodo(raiz, *dado, fb);
    }
    else
    {

        if (*dado > *raiz->_dado)
        {
            raiz->_filhoDireita = inserirnodo(raiz->_filhoDireita, dado);
            int balanco = getBalance(raiz);

            raiz = balancearNodo(raiz, *dado, balanco);
        }
    }
    raiz->_altura = maxEntre(getHigh(raiz->_filhoEsquerda), getHigh(raiz->_filhoDireita)) + 1;

    return raiz;
}

template <typename T>
NodoAVL<T> *adicionar(NodoAVL<T> *raiz, T *dado)
{
    if (raiz->_dado == nullptr)
    {
        raiz->_filhoEsquerda = nullptr;
        raiz->_filhoDireita = nullptr;
        raiz->_dado = dado;
        raiz->_altura = 0;
    }
    else
    {
        raiz = inserirnodo(raiz, dado);
    }
    return raiz;
}

/**
 * @brief Adiciona um dado à árvore AVL
 * @param raiz ponteiro para raiz da árvore
 * @param dado ponteiro para dado a ser inserido
 * @return a raiz da árvore passada como parâmetro ou uma nova raiz caso houve rotação na raiz
 */
template<typename T>
NodoAVL<T>* adicionar2(NodoAVL<T>* raiz, T* dado)
{
    //NodoAVL<T>* aux = nullptr;

	if (raiz == nullptr)
	{
		return criarNodo(dado);
	}

	else if (*dado < *raiz->_dado)
	{
		if (raiz->_filhoEsquerda == nullptr)
		{
			raiz->_filhoEsquerda = inserirnodo(raiz->_filhoEsquerda, dado);
			int balanco = getBalance(raiz);

			raiz = balancearNodo(raiz, *dado, balanco);
		}
		else
		{
			//aux = adicionar(raiz->_filhoEsquerda, dado);
			raiz = adicionar(raiz->_filhoEsquerda, dado);
		}
	}
	else
	{
		if (raiz->_filhoDireita == nullptr)
		{
			NodoAVL<T>* novo = criarNodo(dado);
			raiz->_filhoDireita = novo;
			//aux = novo;
		}
		else
		{
			//aux = adicionar(raiz->_filhoDireita, dado);
			raiz = adicionar(raiz->_filhoDireita, dado);
		}
	}

	if (raiz->_filhoEsquerda == nullptr and raiz->_filhoDireita == nullptr)
	{
		raiz->_altura = 0;
	}
	else if (raiz->_filhoEsquerda == nullptr and raiz->_filhoDireita != nullptr)
	{
		raiz->_altura = raiz->_filhoDireita->_altura + 1;
	}
	else if (raiz->_filhoEsquerda != nullptr and raiz->_filhoDireita == nullptr)
	{
		raiz->_altura = raiz->_filhoEsquerda->_altura + 1;
	}
	else if (raiz->_filhoEsquerda->_altura >= raiz->_filhoDireita->_altura)
	{
		raiz->_altura = raiz->_filhoEsquerda->_altura + 1;
	}
	else
	{
		raiz->_altura = raiz->_filhoDireita->_altura + 1;
	}

	int balanco = getBalance(raiz);

	if (balanco > 1 and *dado < *raiz->_filhoEsquerda->_dado)
	{
		return rotardireita(raiz);
	}
    
    if (balanco < -1 and *dado > *raiz->_filhoDireita->_dado)
    {    
    	return rotaresquerda(raiz);
    }

    if (balanco > 1 and *dado > *raiz->_filhoEsquerda->_dado and *dado < *raiz->_dado)
    {
        raiz->_filhoEsquerda = rotaresquerda(raiz->_filhoEsquerda);
        return rotardireita(raiz);
    }
 
    if (balanco < -1 and *dado < *raiz->_filhoDireita->_dado and *dado > *raiz->_dado)
    {
        raiz->_filhoDireita = rotardireita(raiz->_filhoDireita);
        return rotaresquerda(raiz);
    }

	return raiz;
}

/**
 * @brief Percorre árvore AVL em pré-ordem
 * @param raiz ponteiro para raiz da árvore
 * @param lista lista onde os nodos da árvore serão inseridos em pré-ordem
 */
template<typename T>
void preOrdem(NodoAVL<T>* raiz, ListaEncadeada* lista)
{
	if (raiz != NULL and raiz->_dado != NULL)
	{
		adicionaNoFim(lista, raiz->_dado);
		preOrdem(raiz->_filhoEsquerda, lista);
		preOrdem(raiz->_filhoDireita, lista);
	}
}

/**
 * @brief Percorre árvore AVL em ordem
 * @param raiz ponteiro para raiz da árvore
 * @param lista lista onde os nodos da árvore serão inseridos em ordem
 */
template<typename T>
void emOrdem(NodoAVL<T>* raiz, ListaEncadeada* lista)
{
    if (raiz != NULL and raiz->_dado != NULL)
    {
    	emOrdem(raiz->_filhoEsquerda, lista);
    	adicionaNoFim(lista, raiz->_dado);
    	emOrdem(raiz->_filhoDireita, lista);
    }
}

/**
 * @brief Percorre árvore AVL em pós-ordem
 * @param raiz ponteiro para raiz da árvore
 * @param lista lista onde os nodos da árvore serão inseridos em pós-ordem
 */
template<typename T>
void posOrdem(NodoAVL<T>* raiz, ListaEncadeada* lista)
{
    if (raiz != NULL and raiz->_dado != NULL)
    {
    	posOrdem(raiz->_filhoEsquerda, lista);
    	posOrdem(raiz->_filhoDireita, lista);
    	adicionaNoFim(lista, raiz->_dado);
    }
}

//NAO MODIFIQUE A FUNCAO ABAIXO
template<typename T>
NodoAVL<T>* getNodo(NodoAVL<T>* raiz, T dado)
{
	while(raiz != NULL and dado != *raiz->_dado)
	{
		if(dado < *raiz->_dado)
		{
			raiz = raiz->_filhoEsquerda;
		}
		else 
		{
			raiz = raiz->_filhoDireita;
		}
	}
	return raiz;
}

template<typename T>
NodoAVL<T>* getMin(NodoAVL<T> *raiz)
{
	if (raiz == nullptr)
	{
		return raiz;
	}
	else 
	{
		while (raiz->_filhoEsquerda != NULL)
		{
			raiz = raiz->_filhoEsquerda;
		}

		return raiz;
	}
}

template<typename T>
NodoAVL<T>* getPaidominimo(NodoAVL<T> *raiz)
{
	NodoAVL<T>* pai = nullptr;
	if (raiz == nullptr)
	{
		return raiz;
	}
	else 
	{
		while (raiz->_filhoEsquerda != NULL)
		{
			pai = raiz;
			raiz = raiz->_filhoEsquerda;
		}

		return pai;
	}
}

/**
 * @brief Remove um dado à árvore AVL
 * @param raiz ponteiro para raiz da árvore
 * @param dado dado a ser inserido
 * @return a raiz da árvore passada como parâmetro ou uma nova raiz caso houve rotação na raiz
 */
template<typename T>
NodoAVL<T>* remover(NodoAVL<T>* raiz, T dado)
{
	NodoAVL<T>* papis = nullptr;
	NodoAVL<T>* minimo = nullptr;
	T* retorno;

	while(raiz != nullptr and dado != *raiz->_dado)
	{
		papis = raiz;
		if (dado < *raiz->_dado)
		{
			raiz = raiz->_filhoEsquerda;
		}
		else
		{
			raiz = raiz->_filhoDireita;
		}
	}
	if (raiz == nullptr)
	{
		return nullptr;
	}
	else
	{
		retorno = raiz->_dado;
	}

	minimo = getMin(raiz->_filhoDireita);
	
	if (minimo == nullptr) //se a raiz é o mínimo da subárvore
	{
		if (papis == nullptr) //se eu quero deletar a raiz principal
		{
			raiz = raiz->_filhoDireita;
			retorno = raiz->_dado;
			free(raiz);
		}
		else
		{
			if (*raiz->_dado < *papis->_dado)
			{
				papis->_filhoEsquerda = nullptr;
			}
			else
			{
				papis->_filhoDireita = nullptr;
			}
			free(raiz);
		}
	}
	else
	{
		T* aux = minimo->_dado;

		remover(raiz, *aux);

		raiz->_dado = aux;
	}

	if (raiz->_filhoEsquerda->_altura >= raiz->_filhoDireita->_altura)
	{
		raiz->_altura = raiz->_filhoEsquerda->_altura + 1;
	}
	else
	{
		raiz->_altura = raiz->_filhoDireita->_altura + 1;
	}

	int balanco = getBalance(raiz);

	if (balanco > 1 and dado < *raiz->_filhoEsquerda->_dado)
	{
	    return rotardireita(raiz);
	}
 
    if (balanco < -1 and dado > *raiz->_filhoDireita->_dado)
    {
        return rotaresquerda(raiz);
	}

    if (balanco > 1 and dado > *raiz->_filhoEsquerda->_dado)
    {
        raiz->_filhoEsquerda = rotaresquerda(raiz->_filhoEsquerda);
        return rotardireita(raiz);
    }

    if (balanco < -1 and dado < *raiz->_filhoDireita->_dado)
    {
        raiz->_filhoDireita = rotardireita(raiz->_filhoDireita);
        return rotaresquerda(raiz);
    }

	return raiz;
}

/**
 * @brief Desaloca todos os nodos de uma árvore. Os dados não são desalocados.
 * @param raiz ponteiro para raiz da árvore
 */
template<typename T>
void destruir(NodoAVL<T>* raiz)
{
	if (raiz != nullptr)
	{
		if (raiz->_filhoEsquerda != nullptr)
		{
			destruir(raiz->_filhoEsquerda);
		}
		if (raiz->_filhoDireita != nullptr)
		{
			destruir(raiz->_filhoDireita);
		}

		free(raiz);
	}
}

#endif /* NODOAVL_H */
