let n = parseInt(readline());
let q = parseInt(readline());

let exts = [];
let mimes = [];

for (let i = 0; i < n; i++) {
    let inputs = readline().split(' ');

    exts[i] = inputs[0];
    mimes[i] = inputs[1];
}

for (let i = 0; i < q; i++) {
    let file = readline();
    let ext = '';

    if (file.includes('.')) {
        ext = file.split('.')[file.split('.').length - 1];
    }

    let mime = "UNKNOWN";
    
    for (let j = 0; j < exts.length; j++) {
        if (exts[j].toUpperCase() === ext.toUpperCase()) {
            mime = mimes[j];
            break;
        }
    }
    console.log(mime);
}