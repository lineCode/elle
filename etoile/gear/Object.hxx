#ifndef ETOILE_GEAR_OBJECT_HXX
# define ETOILE_GEAR_OBJECT_HXX

# include <elle/serialize/Pointer.hh>

# include <cryptography/SecretKey.hh>

# include <nucleus/neutron/Author.hh>
# include <nucleus/neutron/Object.hh>
# include <nucleus/proton/Location.hh>

ELLE_SERIALIZE_SIMPLE(etoile::gear::Object,
                      archive,
                      value,
                      version)
{
  enforce(version == 0);

  archive & value.location;
  archive & elle::serialize::alive_pointer(value.object);
  archive & elle::serialize::pointer(value.access);
  archive & value.rights.role;
  archive & value.rights.permissions;
  archive & value.rights.key;
  archive & value.rights.record;
  archive & value.author;
}

#endif
