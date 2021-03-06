#include <stdio.h>

class base {
public:
  base();
  virtual ~base();
  virtual const char *get_name();
  virtual void say_hello();

protected:
  const char *name;
};

base::base()
    : name(NULL) {
}

base::~base() {
}

const char *base::get_name() {
  return "base";
}

void base::say_hello() {
  printf("Hello, I'm %s.\n", get_name());
}

class derived : public base {
public:
  derived();
  virtual ~derived();
  virtual const char *get_name();
  virtual void set_name(const char *name);
};

derived::derived() {
}

derived::~derived() {
}

const char *derived::get_name() {
  if (name == NULL) {
    return "derived";
  }
  return name;
}

void derived::set_name(const char *name) {
  this->name = name;
}

int main() {
  base *b = new base;
  derived *d = new derived;
  base *bd = d;

  b->say_hello();
  bd->say_hello();
  d->set_name("renamed");
  bd->say_hello();
  d->say_hello();

  delete b;
  delete bd;

  return 0;
}
