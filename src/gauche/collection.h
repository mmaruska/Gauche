/*
 * collection.h - Common interface for collection, sequence, and dictionary.
 *
 *   Copyright (c) 2007  Shiro Kawai  <shiro@acm.org>
 * 
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 * 
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   3. Neither the name of the authors nor the names of its contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  $Id: collection.h,v 1.3 2007-03-26 23:11:47 shirok Exp $
 */

/* This file is included from gauche.h */

#ifndef GAUCHE_COLLECTION_H
#define GAUCHE_COLLECTION_H

/* 
 * Class stuff
 */

SCM_CLASS_DECL(Scm_CollectionClass);
SCM_CLASS_DECL(Scm_SequenceClass);
SCM_CLASS_DECL(Scm_DictionaryClass);
SCM_CLASS_DECL(Scm_OrderedDictionaryClass);

#define SCM_CLASS_COLLECTION         (&Scm_CollectionClass)
#define SCM_CLASS_SEQUENCE           (&Scm_SequenceClass)
#define SCM_CLASS_DICTIONARY         (&Scm_DictionaryClass)
#define SCM_CLASS_ORDERED_DICTIONARY (&Scm_OrderedDictionaryClass)

SCM_EXTERN ScmClass *Scm__OrderedDictionaryCPL[];
SCM_EXTERN ScmClass *Scm__SequenceCPL[];

#define SCM_CLASS_COLLECTION_CPL         (Scm__SequenceCPL+1)
#define SCM_CLASS_SEQUENCE_CPL           (Scm__SequenceCPL)
#define SCM_CLASS_DICTIONARY_CPL         (Scm__OrderedDictionaryCPL+2)
#define SCM_CLASS_ORDERED_DICTIONARY_CPL (Scm__OrderedDictionaryCPL)

/*
 * Sequence-related utilities
 */

/* Utility to check start/end range in string and vector operation */
#define SCM_CHECK_START_END(start, end, len)                            \
    do {                                                                \
        if ((start) < 0 || (start) > (len)) {                           \
            Scm_Error("start argument out of range: %d\n", (start));    \
        }                                                               \
        if ((end) < 0) (end) = (len);                                   \
        else if ((end) > (len)) {                                       \
            Scm_Error("end argument out of range: %d\n", (end));        \
        } else if ((end) < (start)) {                                   \
            Scm_Error("end argument (%d) must be greater than or "      \
                      "equal to the start argument (%d)",               \
                      (end), (start));                                  \
        }                                                               \
    } while (0)

/*
 * Dictionary-related utilities
 */

/* "Dictionary" is a common base of hashtables and treemaps.
   The dictionary feature is provided in two layers: The lower
   layer treats key and value as an opaque data (intptr_t) and
   implements the algorithm, while the upper layer treats ScmObj
   keys and values. */

/*
 * Common part of the entry.  This is for the lower layer.
 */
typedef struct ScmDictEntryRec {
    intptr_t  key;
    intptr_t  value;
} ScmDictEntry;

/*
 * Macros for the upper layer.
 */
#define SCM_DICT_KEY(entry)   SCM_OBJ((entry)->key)
#define SCM_DICT_VALUE(entry) SCM_OBJ((entry)->value)
#define SCM_DICT_SET_VALUE(entry, val) \
    SCM_OBJ((entry)->value = (intptr_t)(val))
#define SCM_DICT_DEFAULT_VALUE(entry, val) \
    (SCM_UNBOUNDP(SCM_OBJ((entry)->value))?                             \
     (SCM_OBJ((entry)->value = (intptr_t)(val))) : SCM_OBJ((entry)->value))
     

/*
 * Common operation argument for *Search function
 */
typedef enum {
    SCM_DICT_GET,               /* returns ScmDictEntry* if found,
                                   NULL otherwise. */
    SCM_DICT_CREATE,            /* if not found, create a new entry.
                                   always return ScmDictEntry*. */
    SCM_DICT_DELETE             /* deletes found entry.  */
} ScmDictOp;


#endif /* GAUCHE_COLLECTION_H */

