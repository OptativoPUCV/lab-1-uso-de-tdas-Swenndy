#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

// #include "exercises.h"

// Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
// NO MODIFICAR
void imprime_lista(List *L)
{
   int *dato;
   dato = (int *)first(L);
   printf("[");
   while (dato != NULL)
   {
      printf("%d ", *dato);
      dato = (int *)next(L);
   }
   printf("]\n");
}

// Ojo que la pila se vacía al imprimir y se imprime en orden inverso
// NO MODIFICAR
void imprime_y_vacia_pila(Stack *P)
{
   void *dato;
   printf("[");
   while ((dato = pop(P)) != NULL)
   {
      printf("%d ", *(int *)dato);
   }
   printf("]\n");
}

/*
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/

List *crea_lista()
{
   List *L = create_list();

   for (int i = 1; i <= 10; i++)
   {
      int *elemento = (int *)malloc(sizeof(int));
      *(elemento) = i;
      pushBack(L, elemento);
   }

   return L;
}

/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y
retorne la suma de sus elementos.
*/
int sumaLista(List *L)
{
   int suma = 0;
   int *num = first(L);
   while (num != NULL)
   {
      suma += (*num);
      num = next(L);
   }

   return suma;
}

/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/

void eliminaElementos(List *L, int elem)
{
   int *num = first(L);
   while (num != NULL)
   {
      if (*num == elem)
      {
         popCurrent(L);
         num = next(L);
      }
      else
         num = next(L);
   }
}

/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/

void copia_pila(Stack *P1, Stack *P2)
{
   Stack *Aux = create_stack();
   void *elemento = top(P1);
   while (elemento != NULL)
   {
      push(Aux, elemento);
      pop(P1);
      elemento = top(P1);
   }
   elemento = top(Aux);
   while (elemento != NULL)
   {
      push(P1, elemento);
      push(P2, elemento);
      pop(Aux);
      elemento = top(Aux);
   }
}

/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/

int parentesisBalanceados(char *cadena)
{
   char *pila = NULL;
   int indice = -1;

   for (int j = 0; cadena[j] != '\0'; j++)
   {
      char caracter = cadena[j];

      if (caracter == '(' || caracter == '{' || caracter == '[')
      {
         indice++;
         char *temporal = (char *)realloc(pila, (indice + 1) * sizeof(char));
         if (temporal == NULL)
            return EXIT_FAILURE;

         pila = temporal;
         pila[indice] = caracter;
      }
      else if (caracter == ')' || caracter == '}' || caracter == ']')
      {
         if (indice == -1)
         {
            free(pila);
            return 0;
         }

         char tope = pila[indice];
         if ((caracter == ')' && tope != '(') ||
             (caracter == ']' && tope != '[') ||
             (caracter == '}' && tope != '{'))
         {
            free(pila);
            return 0;
         }
         indice--;
      }
   }

   int valido;
   if (indice == -1)
      valido = 1;
   else
      valido = 0;

   free(pila);
   return valido;
}
