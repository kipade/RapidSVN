/*
 * ====================================================================
 * Copyright (c) 2002, 2003 The RapidSvn Group.  All rights reserved.
 *
 * This software is licensed as described in the file LICENSE.txt,
 * which you should have received as part of this distribution.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */

// subversion api
#include "svn_client.h"
#include "svn_path.h"
#include "svn_sorts.h"
#include "svn_utf.h"

// svncpp
#include "client.hpp"
#include "dirent.hpp"
#include "exception.hpp"

static int
compare_items_as_paths (const svn_item_t *a, const svn_item_t *b)
{
  return svn_path_compare_paths ((const char *)a->key, (const char *)b->key);
}

namespace svn
{
  DirEntries
  Client::ls (const char * pathOrUrl,
              svn_opt_revision_t * revision,
              bool recurse) throw (ClientException)
  {
    Pool pool;

    apr_hash_t * hash;
    svn_error_t * error = 
      svn_client_ls (&hash, 
                     pathOrUrl, 
                     revision, 
                     recurse, 
                     *m_context, 
                     pool);

    if (error != 0)
      throw ClientException (error);

    apr_array_header_t * 
      array = apr_hash_sorted_keys (
        hash, compare_items_as_paths, pool);

    DirEntries entries;

    for (int i = 0; i < array->nelts; ++i)
    {
      const char *utf8_entryname;
      svn_dirent_t *dirent;
      svn_item_t *item;
     
      item = &APR_ARRAY_IDX (array, i, svn_item_t);

      utf8_entryname = static_cast<const char *>(item->key);

      dirent = static_cast<svn_dirent_t *> 
        (apr_hash_get (hash, utf8_entryname, item->klen));

      const char * native_entryname;
      error = svn_utf_cstring_from_utf8 (
        &native_entryname, utf8_entryname, pool);      

      std::string fullname (pathOrUrl); 
      std::string name (native_entryname);
      fullname += "/" + name;

      entries.push_back (DirEntry (fullname.c_str (), dirent));
    }

    return entries;
  }
}

/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../../rapidsvn-dev.el")
 * end:
 */