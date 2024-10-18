#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

// Definici�n de un nodo del �rbol
struct Nodo {
    int valor;
    struct Nodo *izquierdo;
    struct Nodo *derecho;
};

// Declaraciones de las funciones
struct Nodo* crearNodo(int valor);
struct Nodo* insertar(struct Nodo* raiz, int valor);
struct Nodo* eliminarNodo(struct Nodo* raiz, int valor);
void dibujarArbol(struct Nodo* raiz, int x, int y, int nivel);
void buscar(struct Nodo* raiz, int valor, int x, int y, int nivel);
void recorridoInorden(struct Nodo* raiz, int x, int y, int nivel);
void recorridoPreorden(struct Nodo* raiz, int x, int y, int nivel);
void recorridoPosorden(struct Nodo* raiz, int x, int y, int nivel);
struct Nodo* buscarNodo(struct Nodo* raiz, int valor);
void agregarHojas(struct Nodo* raiz, int numHojas);

// Funci�n para crear un nuevo nodo
struct Nodo* crearNodo(int valor) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->valor = valor;
    nuevoNodo->izquierdo = NULL;
    nuevoNodo->derecho = NULL;
    return nuevoNodo;
}

// Funci�n para insertar un nodo en el �rbol
struct Nodo* insertar(struct Nodo* raiz, int valor) {
    if (raiz == NULL) return crearNodo(valor);
    
    if (valor < raiz->valor) {
        raiz->izquierdo = insertar(raiz->izquierdo, valor);
    } else if (valor > raiz->valor) {
        raiz->derecho = insertar(raiz->derecho, valor);
    }
    
    return raiz;
}

// Funci�n para eliminar un nodo del �rbol
struct Nodo* eliminarNodo(struct Nodo* raiz, int valor) {
    if (raiz == NULL) return raiz;

    if (valor < raiz->valor) {
        raiz->izquierdo = eliminarNodo(raiz->izquierdo, valor);
    } else if (valor > raiz->valor) {
        raiz->derecho = eliminarNodo(raiz->derecho, valor);
    } else {
        if (raiz->izquierdo == NULL) {
            struct Nodo* temp = raiz->derecho;
            free(raiz);
            return temp;
        } else if (raiz->derecho == NULL) {
            struct Nodo* temp = raiz->izquierdo;
            free(raiz);
            return temp;
        }

        struct Nodo* temp = raiz->derecho;
        while (temp && temp->izquierdo != NULL)
            temp = temp->izquierdo;

        raiz->valor = temp->valor;
        raiz->derecho = eliminarNodo(raiz->derecho, temp->valor);
    }
    
    return raiz;
}

// Funci�n para realizar el recorrido inorden
void recorridoInorden(struct Nodo* raiz, int x, int y, int nivel) {
    if (raiz == NULL) return;

    recorridoInorden(raiz->izquierdo, x-50/nivel, y+50, nivel+1);
    
    char texto[5];
    sprintf(texto, "%d", raiz->valor);
    setcolor(BLUE);
    circle(x, y, 20);
    outtextxy(x-10, y-10, texto);
    delay(1000);
    setcolor(WHITE);
    circle(x, y, 20);
    outtextxy(x-10, y-10, texto);

    recorridoInorden(raiz->derecho, x+50/nivel, y+50, nivel+1);
}

// Funci�n para realizar el recorrido preorden
void recorridoPreorden(struct Nodo* raiz, int x, int y, int nivel) {
    if (raiz == NULL) return;

    char texto[5];
    sprintf(texto, "%d", raiz->valor);
    setcolor(BLUE);
    circle(x, y, 20);
    outtextxy(x-10, y-10, texto);
    delay(1000);
    setcolor(WHITE);
    circle(x, y, 20);
    outtextxy(x-10, y-10, texto);

    recorridoPreorden(raiz->izquierdo, x-50/nivel, y+50, nivel+1);
    recorridoPreorden(raiz->derecho, x+50/nivel, y+50, nivel+1);
}

// Funci�n para realizar el recorrido posorden
void recorridoPosorden(struct Nodo* raiz, int x, int y, int nivel) {
    if (raiz == NULL) return;

    recorridoPosorden(raiz->izquierdo, x-50/nivel, y+50, nivel+1);
    recorridoPosorden(raiz->derecho, x+50/nivel, y+50, nivel+1);

    char texto[5];
    sprintf(texto, "%d", raiz->valor);
    setcolor(BLUE);
    circle(x, y, 20);
    outtextxy(x-10, y-10, texto);
    delay(1000);
    setcolor(WHITE);
    circle(x, y, 20);
    outtextxy(x-10, y-10, texto);
}

// Funci�n para dibujar el �rbol (simplificada)
void dibujarArbol(struct Nodo* raiz, int x, int y, int nivel) {
    if (raiz == NULL) return;

    char texto[5];
    sprintf(texto, "%d", raiz->valor);
    setcolor(GREEN);
    circle(x, y, 20);
    outtextxy(x-10, y-10, texto);

    if (raiz->izquierdo != NULL)
        line(x, y, x-50/nivel, y+50);
    if (raiz->derecho != NULL)
        line(x, y, x+50/nivel, y+50);

    dibujarArbol(raiz->izquierdo, x-50/nivel, y+50, nivel+1);
    dibujarArbol(raiz->derecho, x+50/nivel, y+50, nivel+1);
}

// Funci�n para buscar un nodo
struct Nodo* buscarNodo(struct Nodo* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) return raiz;

    if (valor < raiz->valor)
        return buscarNodo(raiz->izquierdo, valor);
    else
        return buscarNodo(raiz->derecho, valor);
}

// Funci�n para buscar visualmente en el �rbol
void buscar(struct Nodo* raiz, int valor, int x, int y, int nivel) {
    if (raiz == NULL) return;

    if (raiz->valor == valor) {
        setcolor(RED);
        circle(x, y, 20);
        outtextxy(x-10, y-10, "Found");
        return;
    }

    if (valor < raiz->valor)
        buscar(raiz->izquierdo, valor, x-50/nivel, y+50, nivel+1);
    else
        buscar(raiz->derecho, valor, x+50/nivel, y+50, nivel+1);
}

// Funci�n para agregar hojas a un nodo
void agregarHojas(struct Nodo* raiz, int numHojas) {
    for (int i = 0; i < numHojas; i++) {
        int valor;
        printf("Ingrese el valor de la nueva hoja: ");
        scanf("%d", &valor);
        raiz = insertar(raiz, valor);
    }
}

// Funci�n para inicializar los gr�ficos
void initGrafico() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");  // Ajusta esta ruta seg�n tu entorno
}

// Funci�n principal
int main() {
    initGrafico(); // Inicializar gr�ficos correctamente

    struct Nodo* raiz = NULL;
    int opcion, valor, numHojas, raizSeleccionada;
    struct Nodo* nodoSeleccionado;

    while (1) {
        printf("\nOpciones:\n1. Insertar\n2. Eliminar\n3. Buscar\n4. Recorrido Inorden\n5. Recorrido Preorden\n6. Recorrido Posorden\n7. Agregar hojas a una rama\n8. Salir\nElija una opci�n: ");
        scanf("%d", &opcion);
        
        cleardevice(); // Limpia la pantalla gr�fica
        
        switch (opcion) {
            case 1:
                printf("Ingrese el valor a insertar: ");
                scanf("%d", &valor);
                raiz = insertar(raiz, valor);
                break;
            case 2:
                printf("Ingrese el valor a eliminar: ");
                scanf("%d", &valor);
                raiz = eliminarNodo(raiz, valor);
                break;
            case 3:
                printf("Ingrese el valor a buscar: ");
                scanf("%d", &valor);
                buscar(raiz, valor, getmaxx()/2, 30, 2);
                break;
            case 4:
                recorridoInorden(raiz, getmaxx()/2, 30, 2);
                break;
            case 5:
                recorridoPreorden(raiz, getmaxx()/2, 30, 2);
                break;
            case 6:
                recorridoPosorden(raiz, getmaxx()/2, 30, 2);
                break;
            case 7:
                printf("Ingrese el valor de la ra�z donde desea agregar las hojas: ");
                scanf("%d", &raizSeleccionada);
                nodoSeleccionado = buscarNodo(raiz, raizSeleccionada);
                
                if (nodoSeleccionado == NULL) {
                    printf("El nodo con valor %d no existe.\n", raizSeleccionada);
                } else {
                    printf("Ingrese el n�mero de hojas que desea agregar: ");
                    scanf("%d", &numHojas);
                    agregarHojas(nodoSeleccionado, numHojas);
                }
                break;
            case 8:
                closegraph();
                exit(0);
            default:
                printf("Opci�n no v�lida.\n");
                break;
        }
        
        dibujarArbol(raiz, getmaxx()/2, 30, 2); // Dibujar el �rbol actualizado
    }
    
    closegraph(); // Cerrar la ventana gr�fica
    return 0;
}

