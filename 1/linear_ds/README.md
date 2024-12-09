# Estructuras de datos lineales

_© F.J. Madrid Cuevas (fjmadrid@uco.es). Estructura de Datos. Grado de Ingeniería Informática. Universidad de Córdoba. España_

## Objetivos

- Aprender a implementar el TAD CDArray.
- Aprender a implementar el TAD List usando una lista de nodos doblemente enlazados.
- Aprender a implementar el TAD ListIterator.
- Aprender a implementar algoritmos basados en listas: fold, unfold, find, sort, merge.
- Aprender a implementar el TAD Stack usando una lista.
- Aprender a implementar el TAD Queue usando un array dinámico circular.

## Descripción

En esta práctica tienes que implementar varias estructuras de datos lineales. Hay dos estructuras básicas: la lista (List) y el array dinámico circular (CDArray).

Con la lista podrás implementar después la pila (Stack) y con el el array dinámico circular podrás implementar la cola (Queue).

Para implementar la lista, vamos a utilizar un diseño de cadena de nodos doblemente enlazados (DNode).

Para editar la lista utilizaremos iteradores por lo que deberás implementar el TAD ListIterator.

Por último, se propone implementar varios algoritmos aplicados a las listas como son: Plegado/Desplegado (fold/unfold), localizar (find), traspasar nodos (splice), combinar listas ordenadas (merge) y ordenar la lista (mergeSort).

## Evaluación

Esta práctica se evaluará de la forma siguiente:

| Tests                                     | Puntos |
| ----------------------------------------- | :----: |
| test_list 01_tests_dnode                  |   1    |
| test_list 02_tests_simple_list            |   1    |
| test_list 03_tests_list_iterator          |   1    |
| test_list 04_tests_list_editing           |   1    |
| test_list 05_tests_list_fold_unfold       |   1    |
| test_list 06_list_algorithms              |   1    |
| test_stack 07_tests_stack                 |   1    |
| test_cdarray 08_tests_cdarray             |   1    |
| test_cdarray 09_tests_cdarray_fold_unfold |   1    |
| test_queue 10_tests_queue                 |   1    |
