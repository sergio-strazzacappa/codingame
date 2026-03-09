const n = parseInt(readline());
let closestTemperature = 0;
let inputs = readline().split(' ');

for (let i = 0; i < n; i++) {
	const t = parseInt(inputs[i]);

	if (i === 0) {
		closestTemperature = t;
	} else if (Math.abs(t) < Math.abs(closestTemperature)) {
		closestTemperature = t;
	} else if (Math.abs(t) === Math.abs(closestTemperature)) {
		closestTemperature = t > closestTemperature ? t : closestTemperature;
	}
}

console.log(closestTemperature);
