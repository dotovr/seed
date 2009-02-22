#!/usr/bin/env seed

Seed.import_namespace("Clutter", "0.9");
Clutter.init(null, null);

function create_rectangles(rectangles, colors)
{
	for(var i in colors)
	{
		var c = new Clutter.Color();
		var r = new Clutter.Rectangle();
		
		Clutter.color_parse(colors[i], c);
		
		r.width = r.height = stage.height / colors.length;
		r.color = c;
		r.set_anchor_point_from_gravity(Clutter.Gravity.CENTER);
		r.y = i * r.height + r.height/2
		r.show();
		
		stage.add_actor(r);
		
		rectangles[i] = r;
	}
}

function animate_rectangles(rectangles)
{
	var anim = new Array(rectangles.length);
	var bounce;
	for (var i in rectangles)
	{
		anim[i] = rectangles[i].animate(Clutter.AnimationMode.LINEAR, 5000, {
				x: [GObject.TYPE_INT, stage.width / 2],
				rotation_angle_z: [GObject.TYPE_DOUBLE, 500]
			});
		anim[i].timeline.start();
	}
	anim[i].timeline.signal.completed.connect(
		function(tml)
		{
			var white = new Clutter.Color({red:255,
										   blue:255,
										   green:255,
										   alpha:255});
			
			var text = new Clutter.Text({text:"Congratulations!",
				font_name:"Bitstream Vera Sans 40", color:white});
			
			text.set_anchor_point_from_gravity(Clutter.Gravity.CENTER);
			text.x = stage.width / 2;
			text.y = -text.height;	// Off-stage
			text.y = 0;
			stage.add_actor(text);
			text.show();
			bounce = text.animate(Clutter.AnimationMode.EASE_OUT_BOUNCE, 3000,
				{y: [GObject.TYPE_INT, stage.height / 2]});
			bounce.timeline.start();

			for (var i in rectangles)
			{
				rectangles[i].exp = 
					rectangles[i].animate(Clutter.AnimationMode.EASE_OUT_BOUNCE, 3000,
					{
						x: [GObject.TYPE_INT, Math.random() * stage.width],
						y: [GObject.TYPE_INT, Math.random() * stage.height / 2 + stage.height / 2],
						rotation_angle_z: [GObject.TYPE_DOUBLE, rectangles[i].rotation_angle_z],
						opacity: [GObject.TYPE_UCHAR, 0 ]
					});
					//rotation_angle change makes it stop spinning. don't know why it's still
					//spinning here, it really should have stopped when the timeline did. 

				rectangles[i].exp.timeline.start();
			}
		});
}

function main()
{
	colors = [	"blanched almond", 
				"OldLace", 
				"MistyRose", 
				"White", 
				"LavenderBlush",
				"CornflowerBlue",
				"chartreuse",
				"chocolate",
				"light coral",
				"medium violet red",
				"LemonChiffon2",
				"RosyBrown3"];

	stage = new Clutter.Stage();
	var rectangles = new Array(colors.length);
	stage.signal.hide.connect(function(){Clutter.main_quit();});

	create_rectangles(rectangles, colors);

	stage.color = new Clutter.Color({alpha:255});
	stage.show_all();

	animate_rectangles(rectangles);

	Clutter.main();
}

main();
