/*
** Copyright (c) 2018, Thomas Farr
**
** This Source Code Form is subject to the terms of the Mozilla Public
** License, v. 2.0. If a copy of the MPL was not distributed with this
** file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#include "anitomy_c.h"

#include "anitomy/anitomy/anitomy.h"

struct elements_t : public anitomy::Elements {
  using anitomy::Elements::Elements;
};

bool elements_empty(const elements_t *elements) {
  return elements->empty();
}

bool elements_empty_category(const elements_t *elements, element_category_t category) {
  return elements->empty(static_cast<anitomy::ElementCategory>(category));
}

size_t elements_size(const elements_t *elements) {
  return elements->size();
}

size_t elements_count(const elements_t *elements, element_category_t category) {
  return elements->count(static_cast<anitomy::ElementCategory>(category));
}

struct anitomy_t : public anitomy::Anitomy {
  using anitomy::Anitomy::Anitomy;
};

anitomy_t *anitomy_new() {
  try {
    return new anitomy_t;
  } catch (...) {
    return nullptr;
  }
}

bool anitomy_parse(anitomy_t *anitomy, const wchar_t *filename) {
  return anitomy->Parse(filename);
}

elements_t *anitomy_elements(anitomy_t *anitomy) {
  return reinterpret_cast<elements_t *>(&anitomy->elements());
}

void anitomy_destroy(anitomy_t *anitomy) {
  delete anitomy;
}