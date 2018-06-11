/*
** Copyright (c) 2018, Thomas Farr
**
** This Source Code Form is subject to the terms of the Mozilla Public
** License, v. 2.0. If a copy of the MPL was not distributed with this
** file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#include "anitomy_c.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  anitomy_t *ani = anitomy_new();

  const char *filename =
      "[異域字幕組][漆黑的子彈][Black Bullet][11-12][1280x720][繁体].mp4";

  printf("Filename: %s\n", filename);

  bool succ = anitomy_parse(ani, filename);
  assert(succ);

  const elements_t *elems = anitomy_elements(ani);

  bool empty = elements_empty(elems);
  assert(!empty);

  size_t size = elements_count(elems);
  assert(size == 7);

  bool anititle_empty = elements_empty_category(elems, kElementAnimeTitle);
  assert(!anititle_empty);

  size_t anititle_count = elements_count_category(elems, kElementAnimeTitle);
  assert(anititle_count == 1);

  char *anititle = elements_get(elems, kElementAnimeTitle);
  assert(strcmp(anititle, "Black Bullet") == 0);
  string_free(anititle);

  string_array_t epnums = elements_get_all(elems, kElementEpisodeNumber);
  assert(epnums.size == 2);
  assert(strcmp(epnums.data[0], "11") == 0);
  assert(strcmp(epnums.data[1], "12") == 0);
  array_free(epnums);

  printf("Elements:\n");

  for (size_t i = 0; i < size; ++i) {
    const element_pair_t *pair = elements_at(elems, i);
    element_category_t category = element_pair_category(pair);
    char *value = element_pair_value(pair);
    printf("  - %d: %s => '%s'\n", (int)i, element_category_name(category), value);
    string_free(value);
  }

  anitomy_destroy(ani);

  return 0;
}
