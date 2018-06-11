/*
** Copyright (c) 2018, Thomas Farr
**
** This Source Code Form is subject to the terms of the Mozilla Public
** License, v. 2.0. If a copy of the MPL was not distributed with this
** file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#include "anitomy_c.h"

#include "anitomy/anitomy/anitomy.h"
#include "anitomy/anitomy/string.h"

#include <algorithm>
#include <cassert>
#include <codecvt>
#include <iostream>
#include <locale>

using wstring_converter = std::wstring_convert<std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>, wchar_t>;

inline std::string from_wide(const std::wstring &str) {
  thread_local wstring_converter conv;
  return conv.to_bytes(str);
}

inline std::wstring to_wide(const std::string &str) {
  thread_local wstring_converter conv;
  return conv.from_bytes(str);
}

void string_free(char *string) {
  delete[] string;
}

void array_free(string_array_t array) {
  for (size_t i = array.size; i > 0; --i) {
    delete[] array.data[i - 1];
  }
  delete[] array.data;
}

inline char *dupe_string(const std::string &str) {
  auto len = str.length();
  auto *out = new char[len + 1];
  str.copy(out, len);
  out[len] = '\0';
  return out;
}

//
// elements_t
//

struct elements_t : public anitomy::Elements {
  using anitomy::Elements::Elements;
};

bool elements_empty(const elements_t *elements) {
  assert(elements != nullptr);
  return elements->empty();
}

bool elements_empty_category(const elements_t *elements, element_category_t category) {
  assert(elements != nullptr);
  return elements->empty(static_cast<anitomy::ElementCategory>(category));
}

size_t elements_size(const elements_t *elements) {
  assert(elements != nullptr);
  return elements->size();
}

size_t elements_count(const elements_t *elements, element_category_t category) {
  assert(elements != nullptr);
  return elements->count(static_cast<anitomy::ElementCategory>(category));
}

char *elements_get(const elements_t *elements, element_category_t category) {
  assert(elements != nullptr);
  return dupe_string(from_wide(elements->get(static_cast<anitomy::ElementCategory>(category))));
}

string_array_t elements_get_all(const elements_t *elements, element_category_t category) {
  assert(elements != nullptr);
  auto vals = elements->get_all(static_cast<anitomy::ElementCategory>(category));
  auto count = vals.size();
  auto **out = new char *[count];
  std::transform(vals.begin(), vals.end(), out, [](const auto &val) -> char* { return dupe_string(from_wide(val)); });
  return { out, count };
}

//
// anitomy_t
//

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

bool anitomy_parse(anitomy_t *anitomy, const char *filename) {
  assert(anitomy != nullptr);
  assert(filename != nullptr);
  return anitomy->Parse(to_wide(filename));
}

elements_t *anitomy_elements(anitomy_t *anitomy) {
  assert(anitomy != nullptr);
  return reinterpret_cast<elements_t *>(&anitomy->elements());
}

void anitomy_destroy(anitomy_t *anitomy) {
  assert(anitomy != nullptr);
  delete anitomy;
}