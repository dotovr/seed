#include "../../libseed/seed.h"
#include <sqlite3.h>

#define MAKE_ERROR_ENUM(name)											\
	seed_object_set_property(namespace_ref, #name,						\
							 seed_value_from_int(eng->context, SQLITE_##name, 0))

void seed_module_init(SeedEngine * eng)
{
	SeedObject namespace_ref = seed_make_object(eng->context, 0, 0);
	
	seed_object_set_property(eng->global, "sqlite", namespace_ref);
	
	MAKE_ERROR_ENUM(OK);
	MAKE_ERROR_ENUM(ERROR);
	MAKE_ERROR_ENUM(INTERNAL);
	MAKE_ERROR_ENUM(PERM);
	MAKE_ERROR_ENUM(ABORT);
	MAKE_ERROR_ENUM(BUSY);
	MAKE_ERROR_ENUM(LOCKED);
	MAKE_ERROR_ENUM(NOMEM);
	MAKE_ERROR_ENUM(READONLY);
	MAKE_ERROR_ENUM(INTERRUPT);
	MAKE_ERROR_ENUM(CORRUPT);
	MAKE_ERROR_ENUM(NOTFOUND);
	MAKE_ERROR_ENUM(FULL);
	MAKE_ERROR_ENUM(CANTOPEN);
	MAKE_ERROR_ENUM(PROTOCOL);
	MAKE_ERROR_ENUM(EMPTY);
	MAKE_ERROR_ENUM(SCHEMA);
	MAKE_ERROR_ENUM(TOOBIG);
	MAKE_ERROR_ENUM(CONSTRAINT);
	MAKE_ERROR_ENUM(MISMATCH);
	MAKE_ERROR_ENUM(MISUSE);
	MAKE_ERROR_ENUM(NOLFS);
	MAKE_ERROR_ENUM(AUTH);
	MAKE_ERROR_ENUM(FORMAT);
	MAKE_ERROR_ENUM(RANGE);
	MAKE_ERROR_ENUM(NOTADB);
	MAKE_ERROR_ENUM(ROW);
	MAKE_ERROR_ENUM(DONE);
}
