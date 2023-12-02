"use strict";
// https://adventofcode.com/2019/day/1
exports.__esModule = true;
var fs = require("fs");
// simple calculation of fuel by mass
var fuelbymass = function (mass) {
    return Math.floor(mass / 3) - 2;
};
// get fuel for a mass while considering the mass of the fuel
var recursiveFuelByMass = function (mass) {
    var fuel = fuelbymass(mass);
    if (fuel > 0) {
        return fuel + recursiveFuelByMass(fuel);
    }
    else {
        return 0;
    }
};
fs.readFile('./day1/data.txt', function (err, data) {
    if (err) {
        console.error(err);
        process.exit(1);
    }
    var masses = data.toString().split('\n').filter(function (l) { return l; }).map(function (l) { return +l; });
    // part 1
    var totalMass = masses.reduce(function (prev, curr) {
        return prev + fuelbymass(curr);
    }, 0);
    console.log('part 1:', totalMass);
    // part 2
    var fueledMass = masses.reduce(function (prev, curr) {
        return prev + recursiveFuelByMass(curr);
    }, 0);
    console.log('part 2:', fueledMass);
});
