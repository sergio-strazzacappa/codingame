let cities = parseInt(readline());

let x = [];
let y = [];

let distance = 0;

for (let i = 0; i < cities; i++) {
    let inputs = readline().split(' ');

    x[i] = parseInt(inputs[0]);
    y[i] = parseInt(inputs[1]);
}

let start_x = x[0];
let start_y = y[0];

let current_x;
let current_y;

let next = 0;
let current = 0;

let diff;

for (let i = 0; i < x.length - 1; i++) {
	current_x = x[next];
	current_y = y[next];

	delete x[next];
	delete y[next];

	let closest = Number.MAX_VALUE;

	current = next;

	for (let j = 0; j < cities; j++) {
		if (x[j] !== undefined){
			diff = Math.sqrt(
				Math.pow(current_x - x[j], 2) + Math.pow(current_y - y[j], 2));

			if (diff < closest) {
				closest = diff;
				next = j;
			}
		}
	}

	if (closest == Number.MAX_VALUE) {
		closest = 0;
	}

	distance += closest;
}

diff = Math.sqrt(
	Math.pow(start_x - x[next], 2) + Math.pow(start_y - y[next], 2));
distance += diff;

print(Math.round(distance));
