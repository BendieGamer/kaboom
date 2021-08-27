// tiled sprite

kaboom({
	scale: 2,
});

loadRoot("/assets/");
loadSprite("grass", "sprites/grass.png");

add([
	sprite("grass", {
		width: width(),
		height: height(),
		tiled: true,
	}),
]);
