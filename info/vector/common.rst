Core Definitions and Operations
===============================

.. rubric:: Common Interface
.. list-table::
   :widths: auto
   :width: 100%

   * - `vector_t`
     - Used to indicate a vector with an indeterminate element type
   * - `vector_t()`
     - Construct the type name of a vector with element type *type*
   * - `vector_c`
     - A `vector_t` with a ``const`` element type
   * - `vector_c()`
     - Construct the type name of a vector with ``const`` element type *type*
   * - `vector_length()`
     - Return the length of the *vector*
   * - `vector_volume()`
     - Return the volume of the *vector*

.. autoaeratetype:: vector_t
.. autoaeratemacro:: vector_t
.. autoaeratetype:: vector_c
.. autoaeratemacro:: vector_c
.. autoaeratefunction:: vector_length
.. autoaeratefunction:: vector_volume
