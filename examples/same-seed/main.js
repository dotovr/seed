#!/usr/bin/env seed

// Configuration

var tiles_w = 15;
var tiles_h = 10;
var tile_size = 50;
var offset = tile_size/2;

var max_colors = 2;
var fly_score = true;

Seed.import_namespace("Gtk");
Seed.import_namespace("Clutter", "0.9");
Seed.import_namespace("GtkClutter", "0.9");
Seed.import_namespace("GdkPixbuf");
Seed.import_namespace("GConf");
Seed.import_namespace("GLib");
Seed.import_namespace("Pango");

GtkClutter.init(null, null);
GConf.init(null, null);

Seed.include("light.js");
Seed.include("board.js");
Seed.include("score.js");

var score = 0;
var timelines = [];

var gb = new Gtk.Builder();
gb.add_from_file("same-seed.ui");

var window = gb.get_object("main_window");
var clutter = gb.get_object("clutter");
var stage = clutter.get_stage();

window.signal.hide.connect(function () { Gtk.main_quit(); });

stage.color = {alpha: 0};
stage.set_size((tiles_w * tile_size),(tiles_h * tile_size));

var board = new Board();
stage.add_actor(board);

gb.get_object("new_game_item").signal.activate.connect(function () { board.new_game(); });
gb.get_object("quit_item").signal.activate.connect(function () { Gtk.main_quit(); });

clutter.set_size_request(stage.width, stage.height);
window.show_all();

Gtk.main();
