Fundamentals
============

.. table::
   :widths: auto
   :width: 100%
   :align: left

   +-------------------+-------------------------------------------------------+
   | `vector_on()`     | Construct the name of a vector type with element type |
   |                   | as the operand                                        |
   +-------------------+-------------------------------------------------------+
   | `vector_t`        | Used to indicate a vector with an indeterminate       |
   |                   | element type                                          |
   +-------------------+-------------------------------------------------------+
   | `vector_c`        | A `vector_t` with a ``const`` element type            |
   +-------------------+-------------------------------------------------------+
   | `vector_length()` | Return the length of the *vector*                     |
   +-------------------+-------------------------------------------------------+
   | `vector_volume()` | Return the volume of the *vector*                     |
   +-------------------+-------------------------------------------------------+

.. autoaeratemacro:: vector_on
.. autoaeratetype:: vector_t
.. autoaeratetype:: vector_c
.. autoaeratefunction:: vector_length
.. autoaeratefunction:: vector_volume
