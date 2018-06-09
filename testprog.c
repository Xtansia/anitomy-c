/*
** Copyright (c) 2018, Thomas Farr
**
** This Source Code Form is subject to the terms of the Mozilla Public
** License, v. 2.0. If a copy of the MPL was not distributed with this
** file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#include "anitomy_c.h"

int main(int argc, char **argv) {
  anitomy_t *ani = anitomy_new();

  anitomy_destroy(ani);

  return 0;
}