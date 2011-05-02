//
// ---------- header ----------------------------------------------------------
//
// project       etoile
//
// license       infinit
//
// file          /home/mycure/infinit/etoile/path/Path.cc
//
// created       julien quintard   [sat aug  8 16:21:09 2009]
// updated       julien quintard   [sun may  1 12:19:26 2011]
//

//
// ---------- includes --------------------------------------------------------
//

#include <etoile/path/Path.hh>

#include <etoile/context/Directory.hh>
#include <etoile/context/Context.hh>

#include <etoile/components/Directory.hh>

// XXX
#include <etoile/components/Contents.hh>

namespace etoile
{
  namespace path
  {

//
// ---------- definitions -----------------------------------------------------
//

    ///
    /// this variable contains the address of the root directory object.
    ///
    hole::Address*		Path::Root = NULL;

//
// ---------- methods ---------------------------------------------------------
//

    ///
    /// this method initialises the path component.
    ///
    elle::Status	Path::Initialize(const hole::Address&	address)
    {
      enter();

      // initialize the root address.
      Path::Root = new hole::Address(address);

      // initialize the cache.
      if (Cache::Initialize() == elle::StatusError)
	escape("unable to initialize the cache");

      leave();
    }

    ///
    /// this method cleans the path module.
    ///
    elle::Status	Path::Clean()
    {
      enter();

      // clean the cache.
      if (Cache::Clean() == elle::StatusError)
	escape("unable to clean the cache");

      // delete the root address.
      delete Path::Root;

      leave();
    }

    ///
    /// this method takes a route and returns the address of the
    /// referenced object.
    ///
    /// this method starts by resolving the route by looking up in the
    /// cache. then, the resolving process retrieved the uncached directory
    /// objects and explore them.
    ///
    elle::Status	Path::Resolve(const Route&		route,
				      hole::Address&		address)
    {
      Venue		venue;
      Route::Scoutor	scoutor;

      enter();

      //printf("[XXX] Path::Resolve()\n");
      //route.Dump();

      // first ask the cache to resolve as much as it can.
      //if (Cache::Resolve(route, venue) == elle::StatusError)
      //escape("unable to resolve part of the route through the cache");

      // if the cache did not resolve anything.
      if (venue == Venue::Null)
	{
	  // start with the root directory.
	  address = *Path::Root;
	}
      else
	{
	  // set the address with the address of the last resolved element.
	  address = venue.elements[venue.elements.size() - 1];
	}

      // if complete, return the address.
      if (route.elements.size() == venue.elements.size())
	leave();

      // otherwise, resolve manually by retrieving the directory object.
      for (scoutor = route.elements.begin() + venue.elements.size();
	   scoutor != route.elements.end();
	   scoutor++)
	{
	  //
	  // note here that all operations are performed on a local context.
	  //
	  // this context is not exported because no application needs to
	  // access it. therefore it is not allocated nor added to the context
	  // container.
	  //
	  // additionally, as a consequence, it must not be "delete"d. once
	  // the context is stored, it ends up in the journal which distinguish
	  // local from external contexts through their identifiers. indeed,
	  // external contexts have proper identifiers and have been allocated,
	  // hence need deletion, while local contexts are allocated on the
	  // stack, hence need no deletion and use the identifier Null.
	  //

	  context::Directory*	context;
	  kernel::Entry*	entry;

	  // allocate a new context.
	  if (context::Context::New(context) == elle::StatusError)
	    escape("unable to allocate a new context");

	  // load the directory referenced by address.
	  if (components::Directory::Load(context, address) ==
	      elle::StatusError)
	    escape("unable to load one of the route's directories");

	  // look up for the name.
	  if (components::Directory::Lookup(context,
					    *scoutor,
					    entry) == elle::StatusError)
	    escape("unable to find one of the route's entries");

	  // if there is no such entry, abort.
	  if (entry == NULL)
	    {
	      // close the context.
	      if (components::Directory::Discard(context) == elle::StatusError)
		escape("unable to close the context");

	      escape("unable to locate the target path");
	    }

	  // set the address.
	  address = entry->address;

	  // record the address in the venue.
	  if (venue.Record(address) == elle::StatusError)
	    escape("unable to record the venue address");

	  // close the context.
	  if (components::Directory::Discard(context) == elle::StatusError)
	    escape("unable to close the context");
	}

      // update the resolved path to the cache.
      //if (Cache::Update(route, venue) == elle::StatusError)
      //escape("unable to update the cache");

      // return the target address.
      address = venue.elements[venue.elements.size() - 1];

      //printf("[XXX] /Path::Resolve()\n");
      //std::cout << address << std::endl;

      leave();
    }

  }
}
