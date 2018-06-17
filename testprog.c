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

const char *element_category_name(element_category_t element_category) {
  switch (element_category) {
  case kElementAnimeSeason:
    return "AnimeSeason";
  case kElementAnimeSeasonPrefix:
    return "AnimeSeasonPrefix";
  case kElementAnimeTitle:
    return "AnimeTitle";
  case kElementAnimeType:
    return "AnimeType";
  case kElementAnimeYear:
    return "AnimeYear";
  case kElementAudioTerm:
    return "AudioTerm";
  case kElementDeviceCompatibility:
    return "DeviceCompatibility";
  case kElementEpisodeNumber:
    return "EpisodeNumber";
  case kElementEpisodeNumberAlt:
    return "EpisodeNumberAlt";
  case kElementEpisodePrefix:
    return "EpisodePrefix";
  case kElementEpisodeTitle:
    return "EpisodeTitle";
  case kElementFileChecksum:
    return "FileChecksum";
  case kElementFileExtension:
    return "FileExtension";
  case kElementFileName:
    return "FileName";
  case kElementLanguage:
    return "Language";
  case kElementOther:
    return "Other";
  case kElementReleaseGroup:
    return "ReleaseGroup";
  case kElementReleaseInformation:
    return "ReleaseInformation";
  case kElementReleaseVersion:
    return "ReleaseVersion";
  case kElementSource:
    return "Source";
  case kElementSubtitles:
    return "Subtitles";
  case kElementVideoResolution:
    return "VideoResolution";
  case kElementVideoTerm:
    return "VideoTerm";
  case kElementVolumeNumber:
    return "VolumeNumber";
  case kElementVolumePrefix:
    return "VolumePrefix";
  case kElementUnknown:
  default:
    return "Unknown";
  }
}

int main(void) {
  anitomy_t *ani = anitomy_new();
  assert(ani);

  const char *filename =
      "[異域字幕組][漆黑的子彈][Black Bullet][11-12][1280x720][繁体].mp4";
  printf("Filename: %s\n", filename);

  options_t *opts = anitomy_options(ani);
  assert(opts);

  string_array_t *ignored = string_array_new();
  assert(ignored);
  string_array_add(ignored, "Black");
  assert(string_array_size(ignored) == 1);
  options_ignored_strings(opts, ignored);
  string_array_free(ignored);

  assert(anitomy_parse(ani, filename));

  const elements_t *elems = anitomy_elements(ani);
  assert(elems);

  assert((!elements_empty(elems)));
  assert((elements_count(elems) == 7));
  assert((!elements_empty_category(elems, kElementAnimeTitle)));
  assert((elements_count_category(elems, kElementAnimeTitle) == 1));

  char *anititle = elements_get(elems, kElementAnimeTitle);
  assert((strcmp(anititle, "Bullet") == 0));
  string_free(anititle);

  string_array_t *epnums = elements_get_all(elems, kElementEpisodeNumber);
  assert((string_array_size(epnums) == 2));
  assert((strcmp(string_array_at(epnums, 0), "11") == 0));
  assert((strcmp(string_array_at(epnums, 1), "12") == 0));
  string_array_free(epnums);

  printf("Elements:\n");

  size_t count = elements_count(elems);
  for (size_t i = 0; i < count; ++i) {
    element_pair_t pair = elements_at(elems, i);
    printf("  - %d: %s => '%s'\n", (int)i, element_category_name(pair.category),
           pair.value);
    string_free(pair.value);
  }

  anitomy_destroy(ani);

  return 0;
}
