// https://adventofcode.com/2019/day/2

import * as fs from "fs";
import compute from "./compute";

fs.readFile("./day2/data.txt", (err, data) => {
  if (err) {
    console.error(err);
    process.exit(1);
  }

  const originalOpcodes: Array<number> = data
    .toString()
    .split(",")
    .map(l => +l);

  let part1 = originalOpcodes.slice();
  // the question wants us to do these replacements first to fix the 1202
  part1[1] = 12;
  part1[2] = 2;

  part1 = compute(part1);
  console.log("part 1:", part1[0]);

  // I'm so sorry
  // taking a brute force search approach to part 2
  let found = false;
  for (let i = 0; i < 99; i++) {
    if (found) {
      break;
    }

    for (let j = 0; j < 99; j++) {
      if (found) {
        break;
      }

      let part2 = originalOpcodes.slice();
      part2[1] = i;
      part2[2] = j;
      part2 = compute(part2);
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
