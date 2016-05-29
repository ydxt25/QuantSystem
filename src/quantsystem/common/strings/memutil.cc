/*
 * \copyright Copyright 2013 Google Inc. All Rights Reserved.
 * \copyright Copyright 2015 All Rights Reserved. 
 * \license @{
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @}
 */
//
// Copyright (C) 2001 and onwards Google, Inc.
//

#include "quantsystem/common/strings/memutil.h"

#include <stdlib.h>        // for malloc, NULL

#include "quantsystem/common/strings/ascii_ctype.h"  // for ascii_tolower

namespace quantsystem {

int memcasecmp(const char *s1, const char *s2, size_t len) {
  const unsigned char *us1 = reinterpret_cast<const unsigned char *>(s1);
  const unsigned char *us2 = reinterpret_cast<const unsigned char *>(s2);

  for ( int i = 0; i < len; i++ ) {
    const int diff =
      static_cast<int>(static_cast<unsigned char>(ascii_tolower(us1[i]))) -
      static_cast<int>(static_cast<unsigned char>(ascii_tolower(us2[i])));
    if (diff != 0) return diff;
  }
  return 0;
}

char *memdup(const char *s, size_t slen) {
  void *copy;
  if ( (copy=malloc(slen)) == NULL )
    return NULL;
  memcpy(copy, s, slen);
  return reinterpret_cast<char *>(copy);
}

char *memrchr(const char *s, int c, size_t slen) {
  for (const char* e = s + slen-1; e >= s; e--) {
    if (*e == c)
      return const_cast<char *>(e);
  }
  return NULL;
}

size_t memspn(const char *s, size_t slen, const char *accept) {
  const char *p = s, *spanp;
  char c, sc;

 cont:
  c = *p++;
  if ( slen-- == 0 )
    return p-1 - s;
  for (spanp = accept; (sc=*spanp++) != '\0';)
    if (sc == c)
      goto cont;
  return p-1 - s;
}


size_t memcspn(const char *s, size_t slen, const char *reject) {
  const char *p = s, *spanp;
  char c, sc;

  while ( slen-- != 0 ) {
    c = *p++;
    for (spanp = reject; (sc=*spanp++) != '\0';)
      if (sc == c)
        return p-1 - s;
  }
  return p - s;
}

char *mempbrk(const char *s, size_t slen, const char *accept) {
  const char *scanp;
  int sc;

  for ( ; slen; ++s, --slen ) {
    for (scanp = accept; (sc=*scanp++) != '\0';)
      if (sc == *s)
        return const_cast<char *>(s);
  }
  return NULL;
}

template<bool case_sensitive>
const char *int_memmatch(const char *phaystack, size_t haylen,
                         const char *pneedle, size_t neelen) {
  if (0 == neelen) {
    return phaystack;  // even if haylen is 0
  }
  const unsigned char *haystack = (const unsigned char *) phaystack;
  const unsigned char *hayend = (const unsigned char *) phaystack + haylen;
  const unsigned char *needlestart = (const unsigned char *) pneedle;
  const unsigned char *needle = (const unsigned char *) pneedle;
  const unsigned char *needleend = (const unsigned char *) pneedle + neelen;

  for (; haystack < hayend; ++haystack) {
    unsigned char hay = case_sensitive ? *haystack :
                        static_cast<unsigned char>(ascii_tolower(*haystack));
    unsigned char nee = case_sensitive ? *needle :
                        static_cast<unsigned char>(ascii_tolower(*needle));
    if (hay == nee) {
      if (++needle == needleend) {
        return (const char *) (haystack + 1 - neelen);
      }
    } else if (needle != needlestart) {
      // must back up haystack in case a prefix matched (find "aab" in "aaab")
      haystack -= needle - needlestart;  // for loop will advance one more
      needle = needlestart;
    }
  }
  return NULL;
}

// explicit template instantiations
template const char *int_memmatch<true>(const char *phaystack, size_t haylen,
                                        const char *pneedle, size_t neelen);
template const char *int_memmatch<false>(const char *phaystack, size_t haylen,
                                        const char *pneedle, size_t neelen);

// This is significantly faster for case-sensitive matches with very
// few possible matches.  See unit test for benchmarks.
const char *memmatch(const char *phaystack, size_t haylen,
                     const char *pneedle, size_t neelen) {
  if (0 == neelen) {
    return phaystack;  // even if haylen is 0
  }
  if (haylen < neelen)
    return NULL;

  const char* match;
  const char* hayend = phaystack + haylen - neelen + 1;
  // A C-style cast is used here to work around the fact that memchr returns a
  // void* on Posix-compliant systems and const void* on Windows.
  while ((match = (const char*)(memchr(phaystack, pneedle[0],
                                       hayend - phaystack)))) {
    if (memcmp(match, pneedle, neelen) == 0)
      return match;
    else
      phaystack = match + 1;
  }
  return NULL;
}

} // namespace quantsystem