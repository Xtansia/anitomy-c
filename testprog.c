/*
** Copyright (c) 2018, Thomas Farr
**
** This Source Code Form is subject to the terms of the Mozilla Public
** License, v. 2.0. If a copy of the MPL was not distributed with this
** file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#include <assert.h>
#include <stdio.h>
#include "anitomy_c.h"

int main(int argc, char **argv) {
  anitomy_t *ani = anitomy_new();

  bool succ = anitomy_parse(ani, L"[TaigaSubs]_Toradora!_(2008)_-_01v2_-_Tiger_and_Dragon_[1280x720_H.264_FLAC][1234ABCD].mkv");
  assert(succ);

  elements_t *elems = anitomy_elements(ani);

  bool empty = elements_empty(elems);
  assert(!empty);

  size_t size = elements_size(elems);
  assert(size == 12);

  bool anititle_empty = elements_empty_category(elems, kElementAnimeTitle);
  assert(!anititle_empty);

  size_t anititle_count = elements_count(elems, kElementAnimeTitle);
  assert(anititle_count == 1);

  anitomy_destroy(ani);

  return 0;
}