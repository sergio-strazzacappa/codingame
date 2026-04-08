let l = parseInt(readline());
let h = parseInt(readline());
let t = readline();

let row = [];

for (let i = 0; i < h; i++) {
    row[i] = readline();
}

for (let i = 0; i < h; i++) {
    let text_line = '';

    for (let j = 0; j < t.length; j++) {
        let c = t.charAt(j);
        let pos = -1;

        if (c == 'a' || c == 'A') {
            pos = 0;
        }

        if (c == 'b' || c == 'B') {
            pos = 1;
        }

        if (c == 'c' || c == 'C') {
            pos = 2;
        }

        if (c == 'd' || c == 'D') {
            pos = 3;
        }

        if (c == 'e' || c == 'E') {
            pos = 4;
        }

        if (c == 'f' || c == 'F') {
            pos = 5;
        }

        if (c == 'g' || c == 'G') {
            pos = 6;
        }

        if (c == 'h' || c == 'H') {
            pos = 7;
        }

        if (c == 'i' || c == 'I') {
            pos = 8;
        }

        if (c == 'j' || c == 'J') {
            pos = 9;
        }

        if (c == 'k' || c == 'K') {
            pos = 10;
        }

        if (c == 'l' || c == 'L') {
            pos = 11;
        }

        if (c == 'm' || c == 'M') {
            pos = 12;
        }

        if (c == 'n' || c == 'N') {
            pos = 13;
        }

        if (c == 'o' || c == 'O') {
            pos = 14;
        }

        if (c == 'p' || c == 'P') {
            pos = 15;
        }

        if (c == 'q' || c == 'Q') {
            pos = 16;
        }

        if (c == 'r' || c == 'R') {
            pos = 17;
        }

        if (c == 's' || c == 'S') {
            pos = 18;
        }

        if (c == 't' || c == 'T') {
            pos = 19;
        }

        if (c == 'u' || c == 'U') {
            pos = 20;
        }

        if (c == 'v' || c == 'V') {
            pos = 21;
        }

        if (c == 'w' || c == 'W') {
            pos = 22;
        }

        if (c == 'x' || c == 'X') {
            pos = 23;
        }

        if (c == 'y' || c == 'Y') {
            pos = 24;
        }

        if (c == 'z' || c == 'Z') {
            pos = 25;
        }

        if (pos == -1) {
            pos = 26;
        }

        text_line += row[i].substring(pos * l, pos * l + l);
    }
    console.log(text_line);
}