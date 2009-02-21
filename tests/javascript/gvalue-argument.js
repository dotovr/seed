#!/usr/bin/env seed
// Returns: 0
// STDIN:
// STDOUT:
// STDERR:

Seed.import_namespace("Gtk");
Gtk.init(null, null);

var s = new Gtk.ListStore();

s.set_column_types(2, [GObject.TYPE_STRING, GObject.TYPE_INT]);
var iter = new Gtk.TreeIter();

s.append(iter);
s.set_value(iter, 0, "Hi"); 
s.set_value(iter, 1, [GObject.TYPE_INT, 10]);
