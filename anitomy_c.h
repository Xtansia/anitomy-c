/*
** Copyright (c) 2018, Thomas Farr
**
** This Source Code Form is subject to the terms of the Mozilla Public
** License, v. 2.0. If a copy of the MPL was not distributed with this
** file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <wchar.h>

typedef struct anitomy_t anitomy_t;
typedef struct elements_t elements_t;

anitomy_t *anitomy_new();
bool anitomy_parse(anitomy_t *anitomy, const wchar_t *filename);
elements_t *anitomy_elements(anitomy_t *anitomy);
void anitomy_destroy(anitomy_t *anitomy);

#ifdef __cplusplus
}
#endif