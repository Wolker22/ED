- Cambiar table\_ a ser un pointer to table entries.
- Objetivo quitar el tercer parámetro hash_f del tipo hash_table.
  - Podemos Rediseñar hash functions a ser un template con parameter Key de forma que exporte el operador()(K)->size_t
  - Podemos crear un tipo en la clase hash table de la forma:
    `typedef std::function<std::uint64_t(K)> Key_to_uint64_t`
    y un atributo
    `Key_to_uint64_t key_to_uint_`
    deforma que se use key*to_uint*(k) en el código y que al crear se le pase un objeto con este tipo.Así podremos quitar el tercer argumento del template hash_table y dejar sólo los argumentos Key y Value.
