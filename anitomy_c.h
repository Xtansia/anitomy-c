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

typedef struct anitomy_t anitomy_t;
typedef struct elements_t elements_t;

// Provided by user
char **alloc_array(size_t size);
char *alloc_string(size_t len); // len includes final null

bool elements_empty(const elements_t *elements);
bool elements_empty_category(const elements_t *elements, element_category_t category);
size_t elements_size(const elements_t *elements);
size_t elements_count(const elements_t *elements, element_category_t category);
char *elements_get(const elements_t *elements, element_category_t category);
char **elements_get_all(const elements_t *elements, element_category_t category, size_t *count);

anitomy_t *anitomy_new();
bool anitomy_parse(anitomy_t *anitomy, const char *filename);
elements_t *anitomy_elements(anitomy_t *anitomy);
void anitomy_destroy(anitomy_t *anitomy);

#ifdef __cplusplus
}
#endif