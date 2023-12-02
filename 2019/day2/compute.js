"use strict";
exports.__esModule = true;
var compute = function (opcodes) {
    var newOpcodes = opcodes.slice();
    var addition = function (inPos1, inPos2, outPos) {
        var res = newOpcodes[inPos1] + newOpcodes[inPos2];
        newOpcodes[outPos] = res;
    };
    var multiplication = function (inPos1, inPos2, outPos) {
        var res = newOpcodes[inPos1] * newOpcodes[inPos2];
        newOpcodes[outPos] = res;
    };
    for (var i = 0; newOpcodes[i] !== 99; i = i + 4) {
        var opcode = newOpcodes[i];
        if (opcode === 1) {
            addition(newOpcodes[i + 1], newOpcodes[i + 2], newOpcodes[i + 3]);
        }
        else if (opcode === 2) {
            multiplication(newOpcodes[i + 1], newOpcodes[i + 2], newOpcodes[i + 3]);
        }
        else {
            console.error("unknown opcode '" + opcode + "' at position " + i);
        }
    }
    return newOpcodes;
};
exports["default"] = compute;
