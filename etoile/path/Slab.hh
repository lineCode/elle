//
// ---------- header ----------------------------------------------------------
//
// project       etoile
//
// license       infinit
//
// file          /home/mycure/infinit/etoile/path/Slab.hh
//
// created       julien quintard   [thu jun 16 10:25:17 2011]
// updated       julien quintard   [mon jul  4 08:05:10 2011]
//

#ifndef ETOILE_PATH_SLAB_HH
#define ETOILE_PATH_SLAB_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/Elle.hh>

namespace etoile
{
  namespace path
  {

//
// ---------- types -----------------------------------------------------------
//

    ///
    /// this type represents the component of a file system path.
    ///
    /// note that such a component may contain a version number indicator
    /// such as '%23' should '%[0-9]+' be the associated version number
    /// regexp.
    ///
    typedef elle::String	Slab;

  }
}

#endif
