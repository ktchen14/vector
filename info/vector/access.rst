Access and Lookup
=================

.. table::
   :widths: auto
   :width: 100%
   :align: left

   +-------------------+-------------------------------------------------------+
   | `vector_at()`     | Return a pointer to the element in the *vector* at    |
   |                   | index *i*                                             |
   +-------------------+-------------------------------------------------------+
   | `vector_tail()`   | Return a pointer to the last element in the *vector*  |
   +-------------------+                                                       |
   | `vector_tail_z()` |                                                       |
   +-------------------+-------------------------------------------------------+
   | `vector_index()`  | Return the index of the element at *elmt* in the      |
   |                   | *vector*                                              |
   +-------------------+-------------------------------------------------------+
   | `vector_get()`    | Copy the element at index *i* in the *vector* into    |
   |                   | *elmt*                                                |
   +-------------------+-------------------------------------------------------+
   | `vector_set()`    | Copy the object at *elmt* into the *vector* at index  |
   |                   | *i*                                                   |
   +-------------------+-------------------------------------------------------+

.. autoaeratefunction:: vector_at
.. autoaeratefunction:: vector_tail
.. autoaeratefunction:: vector_tail_z
.. autoaeratefunction:: vector_index
.. autoaeratefunction:: vector_get
.. autoaeratefunction:: vector_set
