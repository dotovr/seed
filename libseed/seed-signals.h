/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * seed-signals.h
 * Copyright (C) Robert Carr 2008 <carrr@rpi.edu>
 *
 * libseed is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libseed is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SEED_SIGNALS_H
#define _SEED_SIGNALS_H

#include "seed-private.h"

typedef struct _SeedClosure {
	GClosure closure;
	JSObjectRef function;
	JSObjectRef object;
	JSObjectRef this;
} SeedClosure;

void
seed_signal_marshal_func(GClosure * closure,
						 GValue * return_value,
						 guint n_param_values,
						 const GValue * param_values,
						 gpointer invocation_hint, gpointer marshall_data);

void seed_add_signals_to_object(JSObjectRef object_ref, GObject * obj);
JSClassDefinition *seed_get_signal_class(void);
extern JSClassRef gobject_signal_class;

#endif
