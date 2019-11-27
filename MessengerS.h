// -*- C++ -*-
/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v2.5.7
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       https://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     https://www.dre.vanderbilt.edu/~schmidt/TAO.html
 **/

// TAO_IDL - Generated from
// /home/wang/ws/OpenDDS/ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:451

#ifndef _TAO_IDL_MESSENGERS_65E4LV_H_
#define _TAO_IDL_MESSENGERS_65E4LV_H_

#include /**/ "ace/pre.h"

#include "MessengerC.h"
#include "tao/PortableServer/Basic_SArguments.h"
#include "tao/PortableServer/Special_Basic_SArguments.h"
#include "tao/PortableServer/Fixed_Size_SArgument_T.h"
#include "tao/PortableServer/Var_Size_SArgument_T.h"
#include "tao/PortableServer/UB_String_SArguments.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


// TAO_IDL - Generated from
// /home/wang/ws/OpenDDS/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_arg_traits.cpp:66

TAO_BEGIN_VERSIONED_NAMESPACE_DECL


// Arg traits specializations.
namespace TAO
{

  // TAO_IDL - Generated from
  // /home/wang/ws/OpenDDS/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_arg_traits.cpp:945

  template<>
  class SArg_Traits< ::Messenger::Message>
    : public
        Var_Size_SArg_Traits_T<
            ::Messenger::Message,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };
}

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// /home/wang/ws/OpenDDS/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_module/module_sh.cpp:35

namespace POA_Messenger
{
  

// TAO_IDL - Generated from
// /home/wang/ws/OpenDDS/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_module/module_sh.cpp:66

} // module Messenger

#include /**/ "ace/post.h"

#endif /* ifndef */

