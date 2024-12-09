# Pattern

*© F.J. Madrid Cuevas (fjmadrid@uco.es)*
*Estructura de Datos. Grado de Ingeniería Informática*
*Universidad de Córdoba. España*

# Objetivos

- Aprender a usar el tipo `std::valarray`.

# Descripción

Esta práctica modela el concepto "patrón" en el contexto del aprendizaje automático.

Para nosotros, un patrón representa un vector en $\mathcal{R}^n$ que puede tener asociada una etiqueta de clase, el cual será un número entero, normalmente positivo, dejando el valor $-1$ para indicar "sin etiqueta".

Un conjunto de patrones se denomina "*dataset*" y, cuando los patrones tienen etiquetas, tendremos un *dataset* anotado.

Para representar un patrón usaremos el tipo `std::valarray` y de esta forma nos podremos utilizar sus operaciones matemáticas vectorizadas que están altamente optimizadas.

Para representar un *dataset* utilizaremos el tipo `std::vector` que permite una gestión cómoda de la memoria.

