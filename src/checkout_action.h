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
#ifndef _CHECKOUT_ACTION_H_INCLUDED_
#define _CHECKOUT_ACTION_H_INCLUDED_

#include "action_thread.h"
#include "checkout_dlg.h"

class CheckoutAction:public ActionThread
{
private:
  CheckoutDlg::sData Data;
  wxFrame *m_pFrame;

public:
   CheckoutAction (wxFrame * frame, apr_pool_t * __pool, Tracer * tr);

  void Perform ();
  void *Entry ();
};

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */