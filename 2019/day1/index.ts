// https://adventofcode.com/2019/day/1

import * as fs from 'fs';

// simple calculation of fuel by mass
const fuelbymass = (mass: number): number => {
  return Math.floor(mass / 3) - 2;
}

// get fuel for a mass while considering the mass of the fuel
const recursiveFuelByMass = (mass: number): number => {
  const fuel = fuelbymass(mass);
  if (fuel > 0) {
    return fuel + recursiveFuelByMass(fuel);
  } else {
    return 0;
  }
}

fs.readFile('./day1/data.txt', (err, data) => {
  if (err) {
    console.error(err);
    process.exit(1);
  }

  const masses: Array<number> = data.toString().split('\n').filter(l => l).map(l => +l)

  // part 1
  const totalMass: number = masses.reduce((prev: number, curr: number): number => {
    return prev + fuelbymass(curr);
  }, 0)
  console.log('part 1:', totalMass);

  // part 2
  const fueledMass: number = masses.reduce((prev: number, curr: number): number => {
    return prev + recursiveFuelByMass(curr);
  }, 0)
  console.log('part 2:', fueledMass);
})
