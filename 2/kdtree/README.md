# TAD "KDTree"

_© F.J. Madrid Cuevas (fjmadrid@uco.es)_
_Estructuras de Datos. Grado de Ingeniería Informática_
_Universidad de Córdoba. España_

## Objetivos

- Aprender qué es un KDTree y como se puede implementar usando un árbol binario.
- Aprender cuál es el problema del vecino más cercano y cómo resolverlo usando un KDTree.

## Descripción

Un KDTree [1] es un árbol binario que se utiliza para organizar un espacio vectorial de $K$ dimensiones. Cada subárbol en el nivel $l$ representa un subconjuto $\mathcal{S}$ del dataset y utiliza la dimensión $d = l \mod K$, para definir el hiperplano $$x_d = \mathrm{p[d]},$$ que particiona $\mathcal{S}$ en dos subconjuntos (se crea un árbol binario).

El patrón $p\in \mathcal{S}$ comúnmente se selecciona como el patrón cuyo valor de la dimensión $p[d]$ es la mediana de los valores para esa dimensión $d$ en el subconjunto $\mathcal{S}$ de patrones que representa el subárbol y será la raíz del mismo.

Una vez seleccionado el patrón $p$ se divide el subconjunto $\mathcal{S}$ de patrones en dos partes: la parte izquierda $\mathcal{S}_l$ estará formada por todo patrón $t\in \{\mathcal{S}-p\}$, $t[d]\le p[d]$, y será representada por subárbol izquierdo del nivel $l+1$. La parte derecha $\mathcal{S}_r$ estará formada por los patrones $t$, $t[d]>p[d]$ y será representada por el subárbol derecho en nivel $l+1$ (ver Algoritmo 1 para más detalles).

<div style="border-style:solid;">

**Algoritmo 1.**

```algo
Algorithm make_kdtree (ds:DArray[Point],
    depth:Integer):Binarytree[Point]
Var
    kdtree:BinaryTree[Point]
    axis:Integer
Begin
    kdtree ← BinaryTree.make()
    If ds.size()>0 Then
        axis ← depth mod Point.dimensions();
        sort_axis(ds, axis)
        median ← ds[ds.size()//2]
        kdtree.createRoot(median)
        kdtree.set_left(make_kdtree(ds[0:ds.size()//2], depth+1);
        kdtree.set_right(make_kdtree(ds[ds.size()//2+1:], depth+1);
    End-if
    Return kdtree
End.
```

</div>

### Búsqueda del vecino más cercano

Un KDTree puede realizar la búsqueda del vecino más cercano [2] con $O(\log N)$ en el caso promedio y por eso se suele utilizar en algoritmos como por ejemplo el algoritmo "k-medias" [3] (ver Algoritmo 2).

<div style="border-style:solid;">

**Algoritmo 2.**

```algo
Algorithm find_NN(t:KDTree, p:Point, depth:Integer): Point
Prec: Not t.is_empty()
Var
    axis:Integer //The axis to inspect.
    curr, curr2: Point //The best up to date.
Begin
    axis ← depth mod p.dim() //Selected the axis to split.
    curr ← t.root()
    curr2 ← curr
    If p[axis]<t.item()[axis] And Not t.left().is_empty() Then
        curr2 ← find_NN(t.left(), p, depth+1)
    Else If p[axis]>=t.item()[axis] And Not t.right().is_empty() Then
        curr2 ← find_NN(t.right(), p, depth+1)
    End-If
    If dist(p, curr2)<dist(p, curr) Then
        curr ← curr2
    If dist(curr, p) > abs(p[axis]-t.item()[axis]) Then
        curr2 ← curr
        If p[axis]>t.root()[axis] And Not t.left().is_empty() Then
            curr2 ← find_NN(t.left(), p, depth+1)
        Else If Not t.right.is_empty() Then
            curr2 ← find_NN(t.right(), p, depth+1)
        End-If
        If dist(curr2, p)<dist(curr, p) Then
            curr ← curr2
    End-If
    Return curr
End.
```

</div>

## Evaluación

| Concepto                                                       | Puntos |
| :------------------------------------------------------------- | :----: |
| **pattern/test_pattern pattern/tests_pattern**                 |  1/12  |
| **pattern/test_pattern pattern/tests_pattern_dataset**         |  1/12  |
| pattern/test_pattern pattern/tests_pattern_arithmetic          |  1/12  |
| pattern/test_pattern pattern/tests_pattern_distances           |  1/12  |
|                                                                |        |
| **binary_tree/test_btree_node binary_tree/tests_btree_node**   |  1/12  |
| **binary_tree/test_btree binary_tree/tests_btree_fold_unfold** |  1/12  |
| binary_tree/test_btree binary_tree/tests_btree_height_size     |  1/12  |
| binary_tree/test_btree binary_tree/tests_traversals            |  1/12  |
| binary_tree/test_btree binary_tree/tests_inorder               |  1/12  |
|                                                                |        |
| **test_kdtree tests_create_kdtree**                            |  1/12  |
| **test_kdtree tests_find_nn_L1**                               |  1/12  |
| test_kdtree tests_find_nn_L2                                   |  1/12  |

## Referencias

- [1] Tad KDTree: https://en.wikipedia.org/wiki/K-d_tree
- [2] Algoritmo K-NN: https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm
- [3] Algoritmo K-means: https://en.wikipedia.org/wiki/K-means_clustering
