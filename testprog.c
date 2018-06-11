/*
** Copyright (c) 2018, Thomas Farr
**
** This Source Code Form is subject to the terms of the Mozilla Public
** License, v. 2.0. If a copy of the MPL was not distributed with this
** file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#include "anitomy_c.h"
#include <assert.h>
#include <string.h>

int main(void) {
  anitomy_t *ani = anitomy_new();

  bool succ =
      anitomy_parse(ani, "[TaigaSubs]_Toradora!_(2008)_-_01-03v2_-_Tiger_and_"
                         "Dragon_[1280x720_H.264_FLAC][1234ABCD].mkv");
  assert(succ);

  elements_t *elems = anitomy_elements(ani);

  bool empty = elements_empty(elems);
  assert(!empty);

  size_t size = elements_size(elems);
  assert(size == 13);

  bool anititle_empty = elements_empty_category(elems, kElementAnimeTitle);
  assert(!anititle_empty);

  size_t anititle_count = elements_count(elems, kElementAnimeTitle);
  assert(anititle_count == 1);

  char *anititle = elements_get(elems, kElementAnimeTitle);
  assert(strcmp(anititle, "Toradora!") == 0);
  string_free(anititle);

  string_array_t epnums = elements_get_all(elems, kElementEpisodeNumber);
  assert(epnums.size == 2);
  assert(strcmp(epnums.data[0], "01") == 0);
  assert(strcmp(epnums.data[1], "03") == 0);
  array_free(epnums);

  anitomy_destroy(ani);

  return 0;
}
