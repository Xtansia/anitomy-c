# anitomy-c
[![License](https://img.shields.io/badge/license-MPL--2.0-blue.svg?style=flat-square&maxAge=2592000)](https://github.com/Xtansia/anitomy-c/raw/master/LICENSE)
[![Linux & OSX Build Status](https://travis-ci.com/Xtansia/anitomy-c.svg?branch=master)](https://travis-ci.com/Xtansia/anitomy-c)  
*anitomy-c* is a C ABI wrapper for [Anitomy](https://github.com/erengy/anitomy) a C++ library for parsing anime video filenames.

## Requirements
* A C++14 compatible compiler
  - GCC >= 5
  - Clang >= 3.4 (According to the [Clang CXX status page](https://clang.llvm.org/cxx_status.html))
  - [Visual Studio 2017](https://www.visualstudio.com/downloads/) 
    OR [Build Tools for Visual Studio 2017](https://aka.ms/BuildTools)

## Caveats & Limitations
* Only the main general API is implemented so far:
  - Creating & destroying Anitomy instances.
  - Parsing filenames.
  - Access to Elements (const only atm).
  - Access to Options.

## Example
```c
#include <stdio.h>
#include "anitomy_c.h"

int main(void) {
  anitomy_t *anitomy = anitomy_new();

  anitomy_parse(anitomy, "[TaigaSubs]_Toradora!_(2008_-_01v2_-_Tiger_and_Dragon_[1280x720_H.264_FLAC][1234ABCD].mkv");

  elements_t *elements = anitomy_elements(anitomy);
  
  char *anime_title = elements_get(elements, kElementAnimeTitle);
  char *episode_number = elements_get(elements, kElementEpisodeNumber);
  char *release_group = elements_get(elements, kElementReleaseGroup);
  
  printf("%s #%s by %s\n", anime_title, episode_number, release_group);
  
  string_free(anime_title);
  string_free(episode_number);
  string_free(release_group);

  anitomy_destroy(anitomy);
}
```
