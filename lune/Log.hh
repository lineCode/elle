//
// ---------- header ----------------------------------------------------------
//
// project       lune
//
// license       infinit
//
// file          /home/mycure/infinit/lune/Log.hh
//
// created       julien quintard   [thu jul 28 17:01:13 2011]
// updated       julien quintard   [tue sep  6 22:24:29 2011]
//

#ifndef LUNE_LOG_HH
#define LUNE_LOG_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/Elle.hh>

namespace lune
{

//
// ---------- classes ---------------------------------------------------------
//

  ///
  /// this class represents the local log file.
  ///
  class Log:
    public elle::Object
  {
  public:
    //
    // constants
    //
    static const elle::String		Extension;
  };

}

#endif
