while (true) {
	let mountainHeights = [];

	for (let i = 0; i < 8; i++) {
		const mountainH = parseInt(readline());
		mountainHeights.push(mountainH);
	}

	let currentHeight = mountainHeights[0];
	let highestMountain = 0;

	for (let i = 1; i < 8; i++) {
		if (mountainHeights[i] > currentHeight) {
			currentHeight = mountainHeights[i];
			highestMountain = i;
		}
	}

	console.log(highestMountain);
}
