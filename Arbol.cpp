//SANTIAGO VEIRA Y SEBASTIAN PUENTES
#include <iostream>
#include <conio.h>
using namespace std;

struct nodo
{
    int valor;
    nodo* NodoIzquierda;
    nodo* NodoDerecha;
};

void mostrarPreorden(nodo* arbol) {
    if (arbol != nullptr) {
        cout << arbol->valor << " ";
        mostrarPreorden(arbol->NodoIzquierda);
        mostrarPreorden(arbol->NodoDerecha);
    }
}

void mostrarInorden(nodo* arbol) {
    if (arbol != nullptr) {
        mostrarInorden(arbol->NodoIzquierda);
        cout << arbol->valor << " ";
        mostrarInorden(arbol->NodoDerecha);
    }
}

void mostrarPosorden(nodo* arbol) {
    if (arbol != nullptr) {
        mostrarPosorden(arbol->NodoIzquierda);
        mostrarPosorden(arbol->NodoDerecha);
        cout << arbol->valor << " ";
    }
}

nodo* insertar(nodo* arbol, int valor) {
    if (arbol == nullptr) {
        nodo* nuevo = new nodo;
        nuevo->valor = valor;
        nuevo->NodoIzquierda = nullptr;
        nuevo->NodoDerecha = nullptr;
        return nuevo;
    }

    if (valor < arbol->valor) {
        arbol->NodoIzquierda = insertar(arbol->NodoIzquierda, valor);
    } else if (valor > arbol->valor) {
        arbol->NodoDerecha = insertar(arbol->NodoDerecha, valor);
    }

    return arbol;
}

bool buscarEnPreorden(nodo* arbol, int valor, int& posicion, int& posicionEncontrado) {
    if (arbol != nullptr) {
        if (arbol->valor == valor) {
            posicionEncontrado = posicion++;
            return true;
        }
        posicion++;
        bool encontradoIzquierda = buscarEnPreorden(arbol->NodoIzquierda, valor, posicion, posicionEncontrado);
        bool encontradoDerecha = buscarEnPreorden(arbol->NodoDerecha, valor, posicion, posicionEncontrado);
        return encontradoIzquierda || encontradoDerecha;
    }
    return false;
}

bool buscarEnInorden(nodo* arbol, int valor, int& posicion, int& posicionEncontrado) {
    if (arbol != nullptr) {
        bool encontradoIzquierda = buscarEnInorden(arbol->NodoIzquierda, valor, posicion, posicionEncontrado);
        if (arbol->valor == valor) {
            posicionEncontrado = posicion++;
            return true;
        }
        posicion++;
        bool encontradoDerecha = buscarEnInorden(arbol->NodoDerecha, valor, posicion, posicionEncontrado);
        return encontradoIzquierda || encontradoDerecha;
    }
    return false;
}

bool buscarEnPosorden(nodo* arbol, int valor, int& posicion, int& posicionEncontrado) {
    if (arbol != nullptr) {
        bool encontradoIzquierda = buscarEnPosorden(arbol->NodoIzquierda, valor, posicion, posicionEncontrado);
        bool encontradoDerecha = buscarEnPosorden(arbol->NodoDerecha, valor, posicion, posicionEncontrado);
        if (arbol->valor == valor) {
            posicionEncontrado = posicion++;
            return true;
        }
        posicion++;
        return encontradoIzquierda || encontradoDerecha;
    }
    return false;
}
nodo* encontrarMinimo(nodo* arbol) {
    while (arbol->NodoIzquierda != nullptr) {
        arbol = arbol->NodoIzquierda;
    }
    return arbol;
}

nodo* eliminar(nodo* arbol, int valor) {
    if (arbol == nullptr) {
        return arbol;
    }

    if (valor < arbol->valor) {
        arbol->NodoIzquierda = eliminar(arbol->NodoIzquierda, valor);
    } else if (valor > arbol->valor) {
        arbol->NodoDerecha = eliminar(arbol->NodoDerecha, valor);
    } else {
        if (arbol->NodoIzquierda == nullptr) {
            nodo* temp = arbol->NodoDerecha;
            delete arbol;
            return temp;
        } else if (arbol->NodoDerecha == nullptr) {
            nodo* temp = arbol->NodoIzquierda;
            delete arbol;
            return temp;
        }

        nodo* temp = encontrarMinimo(arbol->NodoDerecha);
        arbol->valor = temp->valor;
        arbol->NodoDerecha = eliminar(arbol->NodoDerecha, temp->valor);
    }
    return arbol;
}

int main() {
    int valor;
    char respuesta;
    nodo* arbol = nullptr;
    system("color 0B");

    do {
        cout << "Ingresar nodo al arbol: ";
        cin >> valor;
        arbol = insertar(arbol, valor);
        cout << "Deseas seguir ingresando nodos al arbol? (s/n): ";
        respuesta = getch();
        cout << endl;
    } while (respuesta == 's');

    cout << "\nRecorrido Preorden: ";
    mostrarPreorden(arbol);
    
    cout << "\nRecorrido Inorden: ";
    mostrarInorden(arbol);

    cout << "\nRecorrido Posorden: ";
    mostrarPosorden(arbol);

    do {
        cout << "\nIngresar valor a buscar: ";
        cin >> valor;
        
        int posicion = 0; 
        int posicionEncontrado = -1; 

        if (buscarEnPreorden(arbol, valor, posicion, posicionEncontrado)) {
            cout << valor << " encontrado en el recorrido preorden en la posicion " << posicionEncontrado << "." << endl;
        } else {
            cout << valor << " no encontrado en el recorrido preorden." << endl;
        }

        posicion = 0; 
        posicionEncontrado = -1; 
        if (buscarEnInorden(arbol, valor, posicion, posicionEncontrado)) {
            cout << valor << " encontrado en el recorrido inorden en la posicion " << posicionEncontrado << "." << endl;
        } else {
            cout << valor << " no encontrado en el recorrido inorden." << endl;
        }

        posicion = 0; 
        posicionEncontrado = -1;

        if (buscarEnPosorden(arbol, valor, posicion, posicionEncontrado)) {
            cout << valor << " encontrado en el recorrido posorden en la posicion " << posicionEncontrado << "." << endl;
        } else {
            cout << valor << " no encontrado en el recorrido posorden." << endl;
        }

        cout << "Deseas seguir buscando elementos? (s/n): ";
        respuesta = getch();
    } while (respuesta == 's');

    do {
        cout << "\nIngresar valor a eliminar: ";
        cin >> valor;
        arbol = eliminar(arbol, valor);
        cout << "\nArbol PreOrder despues de eliminar el valor: ";
        mostrarPreorden(arbol);
        cout << "\nArbol InOrder despues de eliminar el valor: ";
        mostrarInorden(arbol);
        cout << "\nArbol PosOrder despues de eliminar el valor: ";
        mostrarPosorden(arbol);
        cout << "\nDeseas seguir eliminando elementos? (s/n): ";
        respuesta = getch();
    } while (respuesta == 's');

    cout << endl;
    
    return 0;
}