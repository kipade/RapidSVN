/*
 * ====================================================================
 * Copyright (c) 2002 The RapidSvn Group.  All rights reserved.
 *
 * This software is licensed as described in the file LICENSE.txt,
 * which you should have received as part of this distribution.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */

#ifndef _SVNCPP_POOL_H_
#define _SVNCPP_POOL_H_

/**
 * Forward declarations
 */
typedef struct apr_pool_t;

/**
 * SvnCpp namespace
 */
namespace svn
{
  /**
   * Class for encapsulation of apr/subversion pools
   */
  class Pool
  {
  public:
   /**
     * creates a subpool new pool to an existing pool
     *
     * @param parent NULL -> global pool
     */
    Pool (apr_pool_t * = (apr_pool_t *)0);

    virtual ~ Pool ();

    /**
     * @return apr handle to the pool
     */
    apr_pool_t * 
    pool () const;

  private:
    apr_pool_t * m_pool;

    Pool& operator=(const Pool&);

    Pool (const Pool &);

  };
}

#endif

/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../../rapidsvn-dev.el")
 * end:
 */