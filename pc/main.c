#include "polymorphic_c.h"
#include <stdio.h>

BEGIN_DEF_CLASS(base, object)
  const char *name;
END_DEF_CLASS(base, object)

DECL_CLASS_VFUNCS(base, object,
                  get_name,
                  say_hello)

DEF_CTOR(base) {
  this->name = NULL;
}

DEF_DTOR(base) {
}

DEF_VFUNC(const char *, base, get_name) {
  return "base";
}

DEF_VFUNC(void, base, say_hello) {
  printf("Hello, I'm %s.\n", VFUNC_CALL(this, get_name));
}

REGISTER_CLASS_VFUNCS(base, object,
                      get_name, VFUNC_REF(base, get_name),
                      say_hello, VFUNC_REF(base, say_hello))

BEGIN_DEF_CLASS(derived, base)
END_DEF_CLASS(derived, base)

DECL_CLASS_VFUNCS(derived, base,
                  set_name)

DEF_CTOR(derived) {
}

DEF_DTOR(derived) {
}

OVERRIDE_VFUNC(const char *, derived, get_name) {
  if (this->parent.name == NULL) {
    return "derived";
  }
  return this->parent.name;
}

DEF_VFUNC(void, derived, set_name, const char *name) {
  this->parent.name = name;
}

REGISTER_CLASS_VFUNCS(derived, base,
                      get_name, VFUNC_REF(derived, get_name),
                      set_name, VFUNC_REF(derived, set_name))

REGISTER_CLASSES(CLASS_REF(base),
                 CLASS_REF(derived))

int main() {
  polymorphic_c_init();

  base *b = new(base);
  derived *d = new(derived);
  base *bd = (base *)d;

  VFUNC_CALL(b, say_hello);
  VFUNC_CALL(bd, say_hello);
  VFUNC_CALL(d, set_name, "renamed");
  VFUNC_CALL(bd, say_hello);
  VFUNC_CALL((base *)d, say_hello);

  delete(b);
  delete(bd);

  return 0;
}
