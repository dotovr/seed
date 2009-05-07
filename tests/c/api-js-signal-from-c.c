#include "../../libseed/seed.h"
#include "test-common.h"

#include <string.h>

gdouble hello_cb(gpointer w, gint a, gchar * b)
{
	g_assert(a == 2);
	g_assert(strncmp(b, "Test", 4) == 0);

	return 5.12;
}

void js_signal_from_c(TestSimpleFixture * fixture, gconstpointer _data)
{
	TestSharedState *state = (TestSharedState *) _data;

	SeedValue *val = seed_simple_evaluate(state->eng->context,
					      "Gtk = imports.gi.Gtk;"
					      "GObject = imports.gi.GObject;"
					      "Gtk.init(null, null);"
					      "HelloWindowType = {"
					      "    parent: Gtk.Window.type,"
					      "    name: \"HelloWindow\","
					      "    class_init: function(klass, prototype)"
					      "    {"
					      "	var HelloSignalDefinition = {name: \"hello\","
					      "								 parameters: [GObject.TYPE_INT,"
					      "											  GObject.TYPE_STRING],"
					      "								 return_type: GObject.TYPE_DOUBLE};"
					      "	hello_signal_id = klass.install_signal(HelloSignalDefinition);"
					      "    },"
					      "    init: function(instance)"
					      "    {"
					      "    }};"
					      "HelloWindow = new GType(HelloWindowType);"
					      "w = new HelloWindow();", NULL);

	GObject *obj = seed_value_to_object(state->eng->context, val, NULL);

	g_signal_connect(obj, "hello", G_CALLBACK(hello_cb), NULL);

	val =
		seed_simple_evaluate(state->eng->context,
				     "g = w.signal.hello.emit(2,'Test')", NULL);

	g_assert(seed_value_to_double(state->eng->context, val, NULL) == 5.12);
}
