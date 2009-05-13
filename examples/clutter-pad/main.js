#!/usr/bin/env seed

imports.gi.versions.Clutter = "0.9";
imports.gi.versions.GtkClutter = "0.9";

Clutter = imports.gi.Clutter;
Gtk = imports.gi.Gtk;
GtkSource = imports.gi.GtkSource;
GtkClutter = imports.gi.GtkClutter;
GLib = imports.gi.GLib;
sandbox = imports.sandbox;
Gio = imports.gi.Gio;
GObject = imports.gi.GObject;

Gtk.init(Seed.argv);
GtkClutter.init(Seed.argv);

function load_file(filename)
{
	new_file();
	
	current_filename = filename;
	window.title = "ClutterPad - " + filename;
	
	file = Gio.file_new_for_path(filename);
	source_buf.text = file.read().get_contents();
	
	execute_file();
}

function new_file()
{
	window.title = "ClutterPad";
	current_filename = "";
	source_buf.text = "GObject = imports.gi.GObject;\nClutter = imports.gi.Clutter;\nstage = Clutter.Stage.get_default();\n";
}

function open_file()
{
	var file_chooser = new Gtk.FileChooserDialog();
	var file_filter = new Gtk.FileFilter();
	
	file_filter.add_mime_type("text/javascript");
	file_chooser.set_filter(file_filter);
	file_chooser.add_button(Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL);
	file_chooser.add_button(Gtk.STOCK_OPEN, Gtk.ResponseType.ACCEPT);
	file_chooser.set_action(Gtk.FileChooserAction.OPEN);

	if(file_chooser.run() == Gtk.ResponseType.ACCEPT)
	{
		load_file(file_chooser.get_filename());
	}

	file_chooser.destroy();
}

function save_file(filename)
{
	if(current_filename == "")
	{
		var file_chooser = new Gtk.FileChooserDialog();
		var file_filter = new Gtk.FileFilter();
		
		file_filter.add_mime_type("text/javascript");
		file_chooser.set_filter(file_filter);
		file_chooser.add_button(Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL);
		file_chooser.add_button(Gtk.STOCK_OPEN, Gtk.ResponseType.ACCEPT);
		file_chooser.set_action(Gtk.FileChooserAction.SAVE);

		if(file_chooser.run() == Gtk.ResponseType.ACCEPT)
		{
			current_filename = file_chooser.get_filename();
			window.title = "ClutterPad - " + current_filename;
		}

		file_chooser.destroy();
	}

	if(current_filename != "")
	{
		try
		{
			Gio.simple_write(current_filename, source_buf.text);
		}
		catch(e)
		{
			Seed.print(e.message);
		}
	}
}

function populate_example_selector(selector)
{
	// Since we're using GtkBuilder, we can't make a Gtk.ComboBox.text. Instead,
	// we'll construct the cell renderer here, once, and use that.
	var cell = new Gtk.CellRendererText();
	selector.pack_start(cell, true);
	selector.add_attribute(cell, "text", 0);

	file = Gio.file_new_for_path("examples");
	enumerator = file.enumerate_children("standard::name");

	while((child = enumerator.next_file()))
	{
		var fname = child.get_name();
		if(fname.match(/\.js$/))
			selector.append_text(child.get_name());
	}
}

function select_example(selector, ud)
{
	load_file("examples/" + selector.get_active_text());
}

function execute_file(button)
{
	var children = stage.get_children();
				
	for(var id in children)
		stage.remove_actor(children[id]);
	
    try
    {
		error_buf.text = '';
		var a = new Gtk.TextIter(); var b = new Gtk.TextIter();
		source_buf.get_selection_bounds(a, b);
		var slice = source_buf.get_slice(a, b);
		if (slice == '')
		{
			context.destroy();
			context = new sandbox.Context();
			context.add_globals();
			context.eval(source_buf.text)
		}
		else
		{
			context.eval(slice)
		}
    }
    catch (e)
    {
		error_buf.text = e.message;
    }
};

var current_filename = "";
var stage_manager = Clutter.StageManager.get_default();
var source_lang_mgr = new GtkSource.SourceLanguageManager();
var js_lang = source_lang_mgr.get_language("js");
var context = new sandbox.Context();
context.add_globals();

var ui = new Gtk.Builder();
ui.add_from_file("clutter-pad.ui");

var window = ui.get_object("window");
var clutter = ui.get_object("clutter");
var stage = clutter.get_stage();
stage_manager.set_default_stage(stage);

var error_buf = ui.get_object("error_view").get_buffer();
var source_buf = new GtkSource.SourceBuffer({language: js_lang});

populate_example_selector(ui.get_object("example_selector"));

ui.get_object("new_button").signal.clicked.connect(new_file);
ui.get_object("open_button").signal.clicked.connect(open_file);
ui.get_object("save_button").signal.clicked.connect(save_file);
ui.get_object("example_selector").signal.changed.connect(select_example);
ui.get_object("execute_button").signal.clicked.connect(execute_file);

ui.get_object("source_view").set_buffer(source_buf);

window.resize(800, 600);
window.show_all();

Gtk.main();
