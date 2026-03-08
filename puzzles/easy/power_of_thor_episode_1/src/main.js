let thor = {
	x: 0,
	y: 0,
};

let light = {
	x: 0,
	y: 0,
};

let inputs = readline().split(' ');

light.x = parseInt(inputs[0]);
light.y = parseInt(inputs[1]);

thor.x = parseInt(inputs[2]);
thor.y = parseInt(inputs[3]);

while (true) {
	const remainingTurns = parseInt(readline());
	let move = '';

	if (thor.y > light.y) {
		move += 'N';
		thor.y--;
	} else if (thor.y < light.y) {
		move += 'S';
		thor.y++;
	}

	if (thor.x > light.x) {
		move += 'W';
		thor.x--;
	} else if (thor.x < light.x) {
		move += 'E';
		thor.x++;
	}

	console.log(move);
}
