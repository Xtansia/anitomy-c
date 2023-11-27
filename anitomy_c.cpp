/*
** Copyright (c) 2018, Thomas Farr
**
** This Source Code Form is subject to the terms of the Mozilla Public
** License, v. 2.0. If a copy of the MPL was not distributed with this
** file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#include "anitomy_c.h"

#include "anitomy/anitomy/anitomy.h"

#include <algorithm>
#include <cassert>
#include <codecvt>
#include <iostream>
#include <locale>

using wstring_converter = std::wstring_convert<
    std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>>;

inline std::string from_wide(const std::wstring &str) {
  thread_local wstring_converter conv;
  return conv.to_bytes(str);
}

inline std::wstring to_wide(const std::string &str) {
  thread_local wstring_converter conv;
  return conv.from_bytes(str);
}

void string_free(const char *string) {
  assert(string != nullptr);
  delete[] string;
}

inline char *dupe_string(const std::wstring &wstr) {
  const auto str = from_wide(wstr);
  const auto len = str.length();
  auto *out = new char[len + 1];
  str.copy(out, len);
  out[len] = '\0';
  return out;
}

//
// string_array_t
//

struct string_array_t : std::vector<std::string> {
  string_array_t() : std::vector<std::string>() {}

  explicit string_array_t(const std::vector<anitomy::string_t> &strings)
      : std::vector<std::string>() {
    this->reserve(strings.size());
    std::transform(strings.begin(), strings.end(), std::back_inserter(*this),
                   from_wide);
  }
};

string_array_t *string_array_new() { return new string_array_t; }

size_t string_array_size(const string_array_t *array) {
  assert(array != nullptr);
  return array->size();
}

const char *string_array_at(const string_array_t *array, size_t pos) {
  assert(array != nullptr);
  assert(pos < array->size());
  return array->at(pos).c_str();
}

void string_array_add(string_array_t *array, const char *value) {
  assert(array != nullptr);
  assert(value != nullptr);
  array->push_back(value);
}

void string_array_free(const string_array_t *array) {
  assert(array != nullptr);
  delete array;
}

//
// options_t
//

struct options_t : anitomy::Options {};

void options_allowed_delimiters(options_t *options,
                                const char *allowed_delimiters) {
  assert(options != nullptr);
  if (allowed_delimiters == nullptr) {
    options->allowed_delimiters.clear();
    return;
  }
  options->allowed_delimiters = to_wide(allowed_delimiters);
}

void options_ignored_strings(options_t *options,
                             const string_array_t *ignored_strings) {
  assert(options != nullptr);
  options->ignored_strings.clear();
  if (ignored_strings == nullptr) {
    return;
  }
  options->ignored_strings.reserve(ignored_strings->size());
  std::transform(ignored_strings->begin(), ignored_strings->end(),
                 std::back_inserter(options->ignored_strings), to_wide);
}

void options_parse_episode_number(options_t *options,
                                  bool parse_episode_number) {
  assert(options != nullptr);
  options->parse_episode_number = parse_episode_number;
}

void options_parse_episode_title(options_t *options, bool parse_episode_title) {
  assert(options != nullptr);
  options->parse_episode_title = parse_episode_title;
}

void options_parse_file_extension(options_t *options,
                                  bool parse_file_extension) {
  assert(options != nullptr);
  options->parse_file_extension = parse_file_extension;
}

void options_parse_release_group(options_t *options, bool parse_release_group) {
  assert(options != nullptr);
  options->parse_release_group = parse_release_group;
}

//
// elements_t
//

struct elements_t : anitomy::Elements {
  using Elements::Elements;
};

bool elements_empty(const elements_t *elements) {
  assert(elements != nullptr);
  return elements->empty();
}

bool elements_empty_category(const elements_t *elements,
                             element_category_t category) {
  assert(elements != nullptr);
  return elements->empty(static_cast<anitomy::ElementCategory>(category));
}

size_t elements_count(const elements_t *elements) {
  assert(elements != nullptr);
  return elements->size();
}

size_t elements_count_category(const elements_t *elements,
                               element_category_t category) {
  assert(elements != nullptr);
  return elements->count(static_cast<anitomy::ElementCategory>(category));
}

element_pair_t elements_at(const elements_t *elements, size_t pos) {
  assert(elements != nullptr);
  assert(pos < elements->size());
  const auto &pair = elements->at(pos);
  return {static_cast<element_category_t>(pair.first),
          dupe_string(pair.second)};
}

char *elements_get(const elements_t *elements, element_category_t category) {
  assert(elements != nullptr);
  return dupe_string(
      elements->get(static_cast<anitomy::ElementCategory>(category)));
}

string_array_t *elements_get_all(const elements_t *elements,
                                 element_category_t category) {
  assert(elements != nullptr);
  return new string_array_t(
      elements->get_all(static_cast<anitomy::ElementCategory>(category)));
}

//
// anitomy_t
//

struct anitomy_t : anitomy::Anitomy {
  using Anitomy::Anitomy;
};

anitomy_t *anitomy_new() {
  return new anitomy_t;
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

options_t *anitomy_options(anitomy_t *anitomy) {
  assert(anitomy != nullptr);
  return reinterpret_cast<options_t *>(&anitomy->options());
}

void anitomy_destroy(const anitomy_t *anitomy) {
  assert(anitomy != nullptr);
  delete anitomy;
}
