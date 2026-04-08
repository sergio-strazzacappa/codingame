let user_lon = readline().replace(',', '.');
let user_lat = readline().replace(',', '.');

let user_lon_rads = parseFloat(user_lon) * Math.PI / 180;
let user_lat_rads = parseFloat(user_lat) * Math.PI / 180;

let n = parseInt(readline());

let min_distance;
let desf_name;

for (let i = 0; i < n; i++) {
    let desf = readline().split(';');
    let name = desf[1];
    let lon = desf[4].replace(',', '.');
    let lat = desf[5].replace(',', '.');

    let lon_rads = parseFloat(lon) * Math.PI / 180;
    let lat_rads = parseFloat(lat) * Math.PI / 180;

    let x = (lon_rads - user_lon_rads) * Math.cos((user_lat_rads + lat_rads) / 2);
    let y = lat_rads - user_lat_rads;
    let distance = Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2)) * 6371;

    if (i == 0) {
        min_distance = distance;
        desf_name = name;
    }
    if (distance <= min_distance) {
        min_distance = distance;
        desf_name = name;
    }
}

console.log(desf_name);