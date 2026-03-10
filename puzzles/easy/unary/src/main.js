let message = readline();

let binary = '';
let coded = '';

for (let i = 0; i < message.length; i++) {
    let bits = message.charCodeAt(i).toString(2);

    while (bits.length < 7) {
        bits = '0' + bits;
    }
    binary += bits;
}

let i = 0;

while (i < binary.length) {
    if (binary.charAt(i) == '0') {
        coded += '00 ';

        while (binary.charAt(i) == '0') {
            coded += '0';
            i++;
        }
        if (i != binary.length) {
            coded += ' ';
        }
    } else {
        coded += '0 ';

        while (binary.charAt(i) == '1') {
            coded += '0';
            i++;
        }
        if (i != binary.length) {
            coded += ' ';
        }
    }
}

console.log(coded);