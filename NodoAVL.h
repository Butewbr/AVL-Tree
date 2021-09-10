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

template<typename T>
NodoAVL<T>* criarNodo(T* dado)
{
	NodoAVL<T>* nodo = (NodoAVL<T> *)malloc(sizeof(NodoAVL<T>));
	nodo ->_filhoEsquerda = nullptr;
	nodo->_filhoDireita = nullptr;
	nodo->_altura = 0;
	nodo->_dado = dado;

	return nodo;
}

template <typename T>
int getAltura(NodoAVL<T> *raiz)
{
	if (raiz == nullptr)
	{
		return -1;
	}
	else
	{
		return raiz->_altura;
	}
}

template<typename T>
int maiordasalturas(NodoAVL<T> *raiz)
{
	if (getAltura(raiz->_filhoEsquerda) > getAltura(raiz->_filhoDireita))
	{
		return getAltura(raiz->_filhoEsquerda);
	}
	else
	{
		return getAltura(raiz->_filhoDireita);
	}
}

template <typename T>
NodoAVL<T> *rotardireita(NodoAVL<T> *raiz)
{
	NodoAVL<T>* nodo = raiz->_filhoEsquerda;
	
	raiz->_filhoEsquerda = nodo->_filhoDireita;
	nodo->_filhoDireita = raiz;
	
	raiz->_altura = maiordasalturas(raiz) + 1;
	nodo->_altura = maiordasalturas(nodo) + 1;

	return nodo;
}


template <typename T>
NodoAVL<T> * rotaresquerda(NodoAVL<T> *raiz)
{
	NodoAVL<T>* nodo = raiz->_filhoDireita;

	raiz->_filhoDireita = nodo->_filhoEsquerda;
	nodo->_filhoEsquerda = raiz;

	raiz->_altura = maiordasalturas(raiz) + 1;
	nodo->_altura = maiordasalturas(nodo) + 1;

	return nodo;
}

template <typename T>
NodoAVL<T> * rotaresquerdadireita(NodoAVL<T> *raiz)
{
	raiz->_filhoEsquerda = rotaresquerda(raiz->_filhoEsquerda);

	return rotardireita(raiz);
}

template <typename T>
NodoAVL<T> * rotardireitaesquerda(NodoAVL<T> *raiz)
{
	raiz->_filhoDireita = rotardireita(raiz->_filhoDireita);

	return rotaresquerda(raiz);
}

template <typename T>
int getBalance(NodoAVL<T> * raiz)
{
	return (getAltura(raiz->_filhoEsquerda) - getAltura(raiz->_filhoDireita));
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

template <typename T>
NodoAVL<T>* balanceamento(NodoAVL<T>* raiz, T* dado)
{
	int balance = getBalance(raiz);

	if (balance > 1 and *dado < *raiz->_filhoEsquerda->_dado)
	{
		raiz = rotardireita(raiz);
	}
	else if (balance < -1 and *dado > *raiz->_filhoDireita->_dado)
	{
		raiz = rotaresquerda(raiz);
	}
	else if (balance > 1 and *dado > *raiz->_filhoEsquerda->_dado)
	{
		raiz = rotaresquerdadireita(raiz);
	}
	else if (balance < -1 and *dado < *raiz->_filhoDireita->_dado)
	{
		raiz = rotardireitaesquerda(raiz);
	}

	return raiz;
}

template<typename T>
NodoAVL<T>* inserirnodo(NodoAVL<T>* raiz, T* dado)
{
	if (raiz == nullptr)
	{
		NodoAVL<T>* nodo = criarNodo(dado);
		
		return nodo;
	}
	if (*dado < *raiz->_dado)
	{
		raiz->_filhoEsquerda = inserirnodo(raiz->_filhoEsquerda, dado);

		raiz = balanceamento(raiz, dado);
	}
	else if (*dado > *raiz->_dado)
	{
		raiz->_filhoDireita = inserirnodo(raiz->_filhoDireita, dado);

		raiz = balanceamento(raiz, dado);
	}

	raiz->_altura = (maiordasalturas(raiz) + 1);

	return raiz;
}

/**
 * @brief Adiciona um dado à árvore AVL
 * @param raiz ponteiro para raiz da árvore
 * @param dado ponteiro para dado a ser inserido
 * @return a raiz da árvore passada como parâmetro ou uma nova raiz caso houve rotação na raiz
 */
template<typename T>
NodoAVL<T>* adicionar(NodoAVL<T>** raiz, T* dado)
{
	if ((*raiz)->_dado == nullptr)
	{
		//(*raiz) = criarNodo(dado);
		(*raiz)->_filhoEsquerda = nullptr;
		(*raiz)->_filhoDireita = nullptr;
		(*raiz)->_altura = 0;
		(*raiz)->_dado = dado;
	}
	else
	{
		(*raiz) = inserirnodo(*raiz, dado);
	}

	return getNodo(*raiz, *dado);
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
	while(raiz != NULL && dado != *raiz->_dado)
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

/**
 * @brief Remove um dado à árvore AVL
 * @param raiz ponteiro para raiz da árvore
 * @param dado dado a ser inserido
 * @return a raiz da árvore passada como parâmetro ou uma nova raiz caso houve rotação na raiz
 */
template<typename T>
T* remover(NodoAVL<T>* raiz, T dado)
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
		NodoAVL<T> * aux1 = raiz;
		if (papis == nullptr) //se eu quero deletar a raiz principal
		{
			retorno = raiz->_dado;
		}
		else
		{
			if (*raiz->_dado < *papis->_dado)
			{
				retorno = papis->_filhoEsquerda->_dado;
				papis->_filhoEsquerda = nullptr;
			}
			else
			{
				retorno = papis->_filhoDireita->_dado;
				papis->_filhoDireita = nullptr;
			}

			free(aux1);
			return retorno;
			
			//free(minimo);
		}
	}
	else
	{
		T* aux = minimo->_dado;

		remover(raiz, *aux);

		raiz->_dado = aux;
	}

	raiz->_altura = maiordasalturas(raiz) + 1;

	raiz = balanceamento(raiz, &dado);

	return retorno;
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