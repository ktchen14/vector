Creation and Deletion
=====================

.. table::
   :widths: auto
   :width: 100%
   :align: left

   +------------------------+--------------------------------------------------+
   | `vector_create()`      | Allocate and initialize a vector with zero       |
   |                        | length and volume                                |
   +------------------------+--------------------------------------------------+
   | `vector_import()`      | Allocate and initialize a vector from *length*   |
   +------------------------+ elements of *data*                               |
   | `vector_import_z()`    |                                                  |
   +------------------------+--------------------------------------------------+
   | `vector_define()`      | Allocate and initialize a vector from the        |
   |                        | argument list                                    |
   +------------------------+--------------------------------------------------+
   | `vector_duplicate()`   | Allocate and initialize a vector by duplicating  |
   +------------------------+ *source*                                         |
   | `vector_duplicate_z()` |                                                  |
   +------------------------+--------------------------------------------------+
   | `vector_delete()`      | Deallocate the *vector* and return ``NULL``      |
   +------------------------+--------------------------------------------------+

.. autoaeratefunction:: vector_create
.. autoaeratefunction:: vector_import
.. autoaeratefunction:: vector_import_z
.. autoaeratemacro:: vector_define
.. autoaeratefunction:: vector_duplicate
.. autoaeratefunction:: vector_duplicate_z

.. autoaeratefunction:: vector_delete
