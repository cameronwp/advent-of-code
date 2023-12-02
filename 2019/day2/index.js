"use strict";
// https://adventofcode.com/2019/day/2
exports.__esModule = true;
var fs = require("fs");
var compute_1 = require("./compute");
fs.readFile("./day2/data.txt", function (err, data) {
    if (err) {
        console.error(err);
        process.exit(1);
    }
    var originalOpcodes = data
        .toString()
        .split(",")
        .map(function (l) { return +l; });
    var part1 = originalOpcodes.slice();
    // the question wants us to do these replacements first to fix the 1202
    part1[1] = 12;
    part1[2] = 2;
    part1 = compute_1["default"](part1);
    console.log("part 1:", part1[0]);
    var found = false;
    for (var i = 0; i < 99; i++) {
        if (found) {
            break;
        }
        for (var j = 0; j < 99; j++) {
            if (found) {
                break;
            }
            var part2 = originalOpcodes.slice();
            part2[1] = i;
            part2[2] = j;
            part2 = compute_1["default"](part2);
            if (part2[0] === 19690720) {
                console.log("part2:", 100 * part2[1] + part2[2]);
                found = true;
            }
        }
    }
    if (!found) {
        console.log("failure :(");
    }
});
