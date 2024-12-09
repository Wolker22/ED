# Implementación del TAD AVLTree[T]

_© F.J. Madrid Cuevas (fjmadrid@uco.es)
Estructuras de Datos. Grado de Ingeniería Informática. Universidad de Córdoba. España_

## Objetivos

- Implementar el TAD Árbol Binario de Búsqueda.
- Implementar los algoritmos de equilibrio AVL.

## Descripción

En esta práctica se propone implementar el TAD BSTree[T] y el TAD AVLTree[T].

Recuerda que un árbol AVL extiende al árbol binario de búsqueda (BST) asegurando además el invariante:

[1] "En todo subárbol $s$ se cumple que $\left| s.\mathrm{right().height()} - s\mathrm{.left().right()} \right| \le 1$",

es decir, Un árbol AVL es un árbol binario de búsqueda equilibrado.

Para conseguir mantener este invariante, tras realizar una operación de inserción/borrado en el árbol (usando el mismo algoritmo que en el árbol BST), se procederá a revisar si el subárbol afectado en la inserción, o los subárboles en el camino que conecta el nodo borrado con la raíz, están equilibrados (cumplen el invariante [1]). Si no es así, se procederá a realizar una o dos operaciones de rotación en el subárbol que ha perdido el equilibrio para equilibrarlo de nuevo.

La práctica se estructurará en dos etapas:

1. La primera etapa se debe implementar sólo las operaciones de árbol binario de búsqueda (**ONLY_BSTREE**): localización, inserción y borrado de claves sin balanceo. También se implementará la generación de un árbol binario de búsqueda perfectamente equilibrado conocidas todas las claves.

2. En la segunda etapa, se deben implementar las operaciones para obtener el árbol de búsqueda balanceado: extensión del TAD BSTNode al TAD AVLTNode y las operaciones de rotación necesarias para equilibrar el árbol y el algoritmo de balanceo.

## Evaluación

| Tests                                         | Puntos |
| :-------------------------------------------- | :----: |
| `test_bstree tests_bstnode`                  |   1    |
| `test_bstree tests_bstree`                    |   3    |
| `test_bstree tests_bstree_perfectly_balanced` |   1    |
| `test_avltree tests_avltnode`                |   1    |
| `test_avltree tests_avltree`                  |   4    |
