foreach (module IN LISTS VECTOR_MODULE_LIST)
  define_test("vector_${module}")
endforeach (module)

define_test(vector_define)
define_test(vector_duplicate)
define_test(vector_ensure)
define_test(vector_shrink)
define_test(vector_swap)

# define_veto(vector_define_veto_1 "expected a type")
# define_veto(vector_at_veto_1 "incompatible integer to pointer conversion")
define_veto(vector_resize_veto_1 "ignoring return value of")
