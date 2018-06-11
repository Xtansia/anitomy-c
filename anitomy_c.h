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
#include <stddef.h>
#include <stdint.h>

typedef enum ElementCategory {
  kElementIterateFirst,
  kElementAnimeSeason = kElementIterateFirst,
  kElementAnimeSeasonPrefix,
  kElementAnimeTitle,
  kElementAnimeType,
  kElementAnimeYear,
  kElementAudioTerm,
  kElementDeviceCompatibility,
  kElementEpisodeNumber,
  kElementEpisodeNumberAlt,
  kElementEpisodePrefix,
  kElementEpisodeTitle,
  kElementFileChecksum,
  kElementFileExtension,
  kElementFileName,
  kElementLanguage,
  kElementOther,
  kElementReleaseGroup,
  kElementReleaseInformation,
  kElementReleaseVersion,
  kElementSource,
  kElementSubtitles,
  kElementVideoResolution,
  kElementVideoTerm,
  kElementVolumeNumber,
  kElementVolumePrefix,
  kElementIterateLast,
  kElementUnknown = kElementIterateLast
} element_category_t;

typedef struct string_array_t {
  char **data;
  size_t size;
} string_array_t;
typedef struct element_pair_t element_pair_t;
typedef struct elements_t elements_t;
typedef struct anitomy_t anitomy_t;

void string_free(char *string);
void array_free(string_array_t array);

const char *element_category_name(element_category_t element_category);

element_category_t element_pair_category(const element_pair_t *element_pair);
char *element_pair_value(const element_pair_t *element_pair);

bool elements_empty(const elements_t *elements);
bool elements_empty_category(const elements_t *elements,
                             element_category_t category);
size_t elements_count(const elements_t *elements);
size_t elements_count_category(const elements_t *elements,
                               element_category_t category);
const element_pair_t *elements_at(const elements_t *elements, size_t pos);
char *elements_get(const elements_t *elements, element_category_t category);
string_array_t elements_get_all(const elements_t *elements,
                                element_category_t category);

anitomy_t *anitomy_new();
bool anitomy_parse(anitomy_t *anitomy, const char *filename);
const elements_t *anitomy_elements(const anitomy_t *anitomy);
void anitomy_destroy(anitomy_t *anitomy);

#ifdef __cplusplus
}
#endif
