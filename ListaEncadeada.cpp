#include "ListaEncadeada.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//throw nome_do_throw();

using namespace std;

ListaEncadeada *iniciaListaEncadeada() //funcionando
{
	ListaEncadeada *umaLista;
	umaLista = (ListaEncadeada *)calloc(1, sizeof(ListaEncadeada));
	umaLista->_primeiro = NULL;
	umaLista->_quantidade = 0;
	return umaLista;
}

void destroiListaEncadeada(ListaEncadeada *umaLista) //funcionando
{

	Elemento *elementoatual = umaLista->_primeiro; // inicializa o elemento atual pro primeiro
	for (int i = 0; i > umaLista->_quantidade; i++)
	{
		Elemento *proximoelemento = elementoatual->_proximo; // pega o proximo elemento
		free(elementoatual);								 // deleta o atual
		elementoatual = proximoelemento;					 // coloca o atual como o "proximo antigo"
	}

	free(umaLista); //agora a lista fica vazia!

	return;
}

bool listaVazia(ListaEncadeada *umaLista) //funcionando
{
	return (umaLista->_primeiro == NULL);
}

int posicao(ListaEncadeada *umaLista, void *umDado) //funcionando
{
	if (listaVazia(umaLista))
	{
		throw lista_encadeada_vazia_exception();
	}
	int i = 1;
	Elemento *auxiliar = umaLista->_primeiro;

	while (i < umaLista->_quantidade + 1)
	{
		if (auxiliar->_dado == umDado)
		{
			return i;
		}
		else
		{
			auxiliar = auxiliar->_proximo;
			i++;
		}
	}
	return -1;
}

bool contem(ListaEncadeada *umaLista, void *umDado) //funcionando
{
	if (listaVazia(umaLista))
	{
		return false;
	}
	Elemento *auxiliar = umaLista->_primeiro;
	for (int i = 0; i < umaLista->_quantidade; i++)
	{
		if (umDado == auxiliar->_dado)
		{
			return true;
		}
		auxiliar = auxiliar->_proximo;
	}
	return false;
}

int getQuantidade(ListaEncadeada *umaLista)
{
	return umaLista->_quantidade;
}

void *getDadoemP(ListaEncadeada *umaLista, int p)
{
	if (listaVazia(umaLista))
	{
		throw lista_encadeada_vazia_exception();
	}
	Elemento *auxiliar = umaLista->_primeiro;

	for (int i = 0; i < p; i++)
	{
		auxiliar = auxiliar->_proximo;
	}

	return auxiliar->_dado;
}

void adicionaNoInicio(ListaEncadeada *umaLista, void *umDado) //funcionando
{
	Elemento *novo = (Elemento *)calloc(1, sizeof(Elemento));
	if (novo == NULL) //testa se é possível
	{
		throw("ERROSEMMEMORIA");
	}
	else
	{
		novo->_proximo = umaLista->_primeiro; //fazer o próximo do novo ser o primeiro
		novo->_dado = umDado;
		umaLista->_primeiro = novo; //fazer a cabeça apontar para o novo
		umaLista->_quantidade = umaLista->_quantidade + 1;
	}

	return;
}

void adicionaNaPosicao(ListaEncadeada *umaLista, void *umDado, int umaPosicao) //funcionando
{
	if (umaPosicao < 1 or umaPosicao > umaLista->_quantidade + 1)
	{
		throw posicao_invalida_exception();
	}

	if (umaPosicao == 1)
	{
		return (adicionaNoInicio(umaLista, umDado));
	}

	Elemento *anterior;
	Elemento *novo = (Elemento *)calloc(1, sizeof(Elemento));
	;

	if (novo == NULL)
	{
		throw lista_encadeada_vazia_exception();
	}

	anterior = umaLista->_primeiro;
	for (int i = 0; i < umaPosicao - 2; i++)
	{
		anterior = anterior->_proximo;
	}
	novo->_proximo = anterior->_proximo;
	novo->_dado = umDado;
	anterior->_proximo = novo;
	umaLista->_quantidade = umaLista->_quantidade + 1;

	return;
}

void adicionaNoFim(ListaEncadeada *umaLista, void *umDado) //funcionando
{
	if (listaVazia(umaLista))
	{
		return adicionaNoInicio(umaLista, umDado);
	}

	return adicionaNaPosicao(umaLista, umDado, umaLista->_quantidade + 1);
}

void *retiraDoInicio(ListaEncadeada *umaLista) //funcionando
{
	Elemento *saiu; //auxiliar
	void *volta;
	if (listaVazia(umaLista))
	{
		throw lista_encadeada_vazia_exception();
	}
	else
	{
		saiu = umaLista->_primeiro;
		volta = saiu->_dado;
		umaLista->_primeiro = saiu->_proximo;
		umaLista->_quantidade = umaLista->_quantidade - 1;

		free(saiu);
	}
	return volta;
}

void *retiraDaPosicao(ListaEncadeada *umaLista, int umaPosicao)
{
	if (listaVazia(umaLista))
	{
		throw lista_encadeada_vazia_exception();
	}
	if (umaPosicao > umaLista->_quantidade or umaPosicao < 1)
	{
		throw posicao_invalida_exception();
	}
	if (umaPosicao == 1)
	{
		return retiraDoInicio(umaLista);
	}
	else if (umaPosicao == umaLista->_quantidade)
	{
		return retiraDoFim(umaLista);
	}

	Elemento *anterior, *eliminar;
	void *volta;

	anterior = umaLista->_primeiro; //vira o primeiro elemento da lista

	for (int i = 1; i < umaPosicao - 1; i++)
	{
		anterior = anterior->_proximo; //viaja pelos elementos da lista, até a posição -1
	}

	eliminar = anterior->_proximo;					   //o eliminar se transforma no elemento DA posição
	volta = eliminar->_dado;						   //ponteiro volta aponta para o dado do elemento
	anterior->_proximo = eliminar->_proximo;		   //o ponteiro da posição-1 começa a apontar para o elemento DEPOIS da posição
	umaLista->_quantidade = umaLista->_quantidade - 1; //diminui-se a quantidade de elementos da lista

	free(eliminar); //joga fora o elemento da posição

	return volta;
}

void *retiraDoFim(ListaEncadeada *umaLista)
{
	if (listaVazia(umaLista))
	{
		throw lista_encadeada_vazia_exception();
	}
	if (umaLista->_quantidade == 1)
	{
		return (retiraDoInicio(umaLista));
	}

	Elemento *anterior, *eliminar;
	void *volta;

	anterior = umaLista->_primeiro;

	for (int i = 1; i < umaLista->_quantidade - 1; ++i)
	{
		anterior = anterior->_proximo; //elemento da penultima posição
	}

	eliminar = anterior->_proximo;					   //último elemento
	volta = eliminar->_dado;						   //dado do último elemento
	anterior->_proximo = NULL;						   //penúltimo elemento passa a apontar pra nada
	umaLista->_quantidade = umaLista->_quantidade - 1; //reduz a quantidade

	free(eliminar);

	return volta;
}

void *retiraEspecifico(ListaEncadeada *umaLista, void *umDado)
{
	int posicaodoelemento = posicao(umaLista, umDado);

	if (posicaodoelemento != -1)
	{
		return (retiraDaPosicao(umaLista, posicaodoelemento));
	}
	else
	{
		throw("Elemento n existe");
	}
}