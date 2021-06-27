Stack-Like/Queue-Like Operations
================================

.. TODO!!!

.. rubric:: Implicit Interface
.. list-table::
   :widths: auto
   :width: 100%

   * - `vector_push()`
     - Insert the data at *elmt* as the last element in the *vector*
   * - `vector_pull()`
     - Copy the last element in the *vector* to *elmt* and remove it
   * - `vector_unshift()`
     - Insert the data at *elmt* as the first element in the *vector*
   * - `vector_shift()`
     - Copy the first element in the *vector* to *elmt* and remove it

.. rubric:: Explicit Interface
.. list-table::
   :widths: auto
   :width: 100%

   * - `vector_push_z()`
     - Insert the data at *elmt* as the last element in the *vector*
   * - `vector_pull_z()`
     - Copy the last element in the *vector* to *elmt* and remove it
   * - `vector_unshift_z()`
     - Insert the data at *elmt* as the first element in the *vector*
   * - `vector_shift_z()`
     - Copy the first element in the *vector* to *elmt* and remove it

.. autoaeratemacro:: vector_push
.. autoaeratemacro:: vector_push_z
.. autoaeratefunction:: vector_pull
.. autoaeratefunction:: vector_pull_z
.. autoaeratefunction:: vector_unshift
.. autoaeratefunction:: vector_unshift_z
.. autoaeratefunction:: vector_shift
.. autoaeratefunction:: vector_shift_z
