const lander = {
	point: {
		x: 0,
		y: 0,
	},
	hSpeed: 0,
	vSpeed: 0,
	fuel: 0,
	rotate: 0,
	power: 0,
};

const mars = {
	surfaceN: 0,
	points: [],
};

const output = {
	tiltAngle: 0,
	thrust: 0,
};

function init() {
	mars.surfaceN = parseInt(readline());

	for (let i = 0; i < mars.surfaceN; i++) {
		let inputs = readline().split(' ');

		const point = {
			x: parseInt(inputs[0]),
			y: parseInt(inputs[1]),
		};

		mars.points.push(point);
	}
}

function updateLander() {
	let inputs = readline().split(' ');

	lander.point.x = parseInt(inputs[0]);
	lander.point.y = parseInt(inputs[1]);
	lander.hSpeed = parseInt(inputs[2]);
	lander.vSpeed = parseInt(inputs[3]);
	lander.fuel = parseInt(inputs[4]);
	lander.rotate = parseInt(inputs[5]);
	lander.power = parseInt(inputs[6]);
}

function solve() {
	if (lander.vSpeed < -39) {
		output.thrust = 4;
	} else {
		output.thrust = 0;
	}
}

init();

while (true) {
	updateLander();
	solve();
	console.log(output.tiltAngle, output.thrust);
}
