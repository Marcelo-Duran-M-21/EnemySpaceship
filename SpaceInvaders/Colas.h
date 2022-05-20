// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

template<typename T> class Colas;

template<typename T>

class Nodo {
	friend Colas<T>;
private:
	T valor;
	Nodo<T>* siguiente;

public:
	Nodo(T _valor, Nodo<T>* _siguiente = nullptr) {
		valor = _valor;
		siguiente = _siguiente;
	}
};

//class STARFIGHTER_API TCola
//{
//public:
//	TCola();
//	~TCola();
//};

template<class T>
class Colas {
private:
	Nodo<T>* primero;
	Nodo<T>* ultimo;
public:
	Colas() : primero(nullptr), ultimo(nullptr) {}
	~Colas();
	void Push(T _valor);
	T Pop();
};



template<class T>
Colas<T>::~Colas() {
	while (primero != nullptr) {
		Pop();
	}
}

template<class T>
void Colas<T>::Push(T _valor) {


	Nodo<T>* nodoNuevo = new Nodo<T>(_valor);

	if (ultimo != nullptr) {
		ultimo->siguiente = nodoNuevo;
	}

	ultimo = nodoNuevo;

	if (primero == nullptr) {
		primero = nodoNuevo;
	}
}



template<class T>
T Colas<T>::Pop() {
	Nodo<T>* nodoActual;
	T valorNodo;

	nodoActual = primero;
	if (nodoActual == nullptr) {
		return 0;
	}

	primero = nodoActual->siguiente;// como eliminare este nodo le paso la posicion del siguiente
	valorNodo = nodoActual->valor; // valor que eliminare
	delete nodoActual;

	if (primero == nullptr) {
		ultimo = nullptr;
	}

	return valorNodo;
}










/**
 * 
 */
//UCLASS()
//class SPACEINVADERS_API UColas : public UObject
//{
//	GENERATED_BODY()
//	
//};
