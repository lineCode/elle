#ifndef SATELLITES_DIARY_MEMOIRS_HXX
# define SATELLITES_DIARY_MEMOIRS_HXX

# include <elle/utility/Buffer.hh>

# include "Memoirs.hh"

ELLE_SERIALIZE_SIMPLE(satellite::Memoirs,
                      archive,
                      memoirs,
                      version)
{
  assert(version == 0);
  archive & memoirs.archive;
}

#endif
