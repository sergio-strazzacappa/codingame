let horses = parseInt(readline());
let strength = [];

for (let i = 0; i < horses; i++) {
    strength[i] = parseInt(readline());
}

strength.sort((a, b) => {
    return a - b;
});

let closest = Number.MAX_VALUE;

for (let i = 0; i < strength.length - 1; i++) {
    closest = Math.min(closest, strength[i + 1] - strength[i]);
}

console.log(closest);
