#ifndef LUNE_DICTIONARY_HH
# define LUNE_DICTIONARY_HH

# include <elle/concept/Fileable.hh>

# include <cryptography/PublicKey.hh>
// XXX[temporary: for cryptography]
using namespace infinit;

# include <nucleus/proton/Address.hh>

# include <lune/Map.hh>

# include <elle/idiom/Open.hh>

namespace lune
{

  ///
  /// this class maintains a mapping between local users/groups and
  /// Infinit identifiers so that Infinit can be used with local file
  /// system entities such as UNIX's UIDs/GIDs for instance.
  ///
  class Dictionary:
    public elle::radix::Object,
    public elle::concept::MakeFileable<Dictionary>
  {
  public:
    //
    // methods
    //
  private:
    /// XXX
    static
    elle::io::Path
    _path(elle::String const& user);

    //
    // interfaces
    //
  public:
    // object
    declare(Dictionary);

    // dumpable
    elle::Status        Dump(const elle::Natural32 = 0) const;

    // fileable
    ELLE_CONCEPT_FILEABLE_METHODS();

    void
    load(elle::String const& user);
    void
    store(elle::String const& user) const;
    static
    void
    erase(elle::String const& user);
    static
    elle::Boolean
    exists(elle::String const& user);

    //
    // attributes
    //
    Map<cryptography::PublicKey>        users;
    Map<nucleus::proton::Address> groups;
  };

}

#include <lune/Dictionary.hxx>

#endif
