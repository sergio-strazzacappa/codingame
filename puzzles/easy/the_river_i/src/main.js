let river1 = parseInt(readline());
let river2 = parseInt(readline());

while (river1 != river2) {
	if (river1 < river2) {
		let str = river1.toString();
		let len = str.length;

		for (let i = 0; i < len; i++) {
			river1 += parseInt(str.charAt(i));
		}
	}

	if (river1 > river2) {
		let str = river2.toString();
		let len = str.length;

		for (let i = 0; i < len; i++) {
			river2 += parseInt(str.charAt(i));
		}
	}
}

print(river1);
