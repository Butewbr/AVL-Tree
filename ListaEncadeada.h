#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H


#include "Elemento.h"
#include <stdbool.h>
#include <exception>
#include <new>

class posicao_invalida_exception : public std::exception
{
	virtual const char* what() const throw()
  	{
    	return "Posicao invalida na lista encadeada";
  	}
} ; 

class lista_encadeada_vazia_exception : public std::exception
{
	virtual const char* what() const throw()
  	{
    	return "Lista encadeada vazia";
  	}
} ; 


typedef struct 
{
	Elemento* _primeiro;
	int _quantidade;
} ListaEncadeada;

ListaEncadeada* iniciaListaEncadeada();
void destroiListaEncadeada(ListaEncadeada* umaLista);
bool listaVazia(ListaEncadeada* umaLista);
int posicao(ListaEncadeada* umaLista, void* umDado);
bool contem(ListaEncadeada* umaLista, void* umDado);
void adicionaNoInicio(ListaEncadeada* umaLista, void* umDado);
void adicionaNaPosicao(ListaEncadeada* umaLista, void* umDado, int umaPosicao);
void adicionaNoFim(ListaEncadeada* umaLista, void* umDado);
void* retiraDoInicio(ListaEncadeada* umaLista);
void* retiraDaPosicao(ListaEncadeada* umaLista, int umaPosicao);
void* retiraDoFim(ListaEncadeada* umaLista);
void* retiraEspecifico(ListaEncadeada* umaLista, void* umDado);

#endif /* LISTAENCADEADA_H */
