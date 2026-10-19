#!/usr/bin/env python3
"""Encode an explicitly supplied TTL control-word map into a ROM image.

Input JSON format:
  {"word_bits": 16, "step_bits": 3,
   "signals": {"PC_OUT": 0, "IR_LOAD": 1},
   "instructions": {"00": [["PC_OUT", "IR_LOAD"], ["HALT"]]}}
Each instruction value is a list of control-signal lists, one per microstep.
ROM address = (opcode << step_bits) | step. The script deliberately has no
default signal map: bit assignments depend on the user's physical datapath.
"""
import argparse
import json
from pathlib import Path
import sys


def build(data):
    bits = data.get("word_bits")
    step_bits = data.get("step_bits")
    if not isinstance(bits, int) or bits not in (8, 16, 24, 32):
        raise ValueError("word_bits must be one of 8, 16, 24, or 32")
    if not isinstance(step_bits, int) or not 1 <= step_bits <= 8:
        raise ValueError("step_bits must be between 1 and 8")
    signals = data.get("signals", {})
    if not isinstance(signals, dict) or not signals:
        raise ValueError("provide the hardware's signal-to-bit mapping in 'signals'")
    positions = list(signals.values())
    if any(not isinstance(p, int) or p < 0 or p >= bits for p in positions):
        raise ValueError("signal bit positions must be within the control word")
    if len(set(positions)) != len(positions):
        raise ValueError("control signal bit positions must be unique")
    steps_per_opcode = 1 << step_bits
    rom = [0] * (256 * steps_per_opcode)
    instructions = data.get("instructions", {})
    if not isinstance(instructions, dict) or not instructions:
        raise ValueError("provide instruction microsteps in 'instructions'")
    for opcode_text, steps in instructions.items():
        opcode = int(opcode_text, 16)
        if not 0 <= opcode <= 255 or not isinstance(steps, list) or len(steps) > steps_per_opcode:
            raise ValueError(f"invalid opcode or too many steps for {opcode_text}")
        for step, asserted in enumerate(steps):
            if not isinstance(asserted, list):
                raise ValueError(f"step {step} of {opcode_text} must be a list of signal names")
            word = 0
            for name in asserted:
                if name not in signals:
                    raise ValueError(f"unknown signal {name!r} in opcode {opcode_text}, step {step}")
                word |= 1 << signals[name]
            rom[(opcode << step_bits) | step] = word
    width = bits // 8
    image = bytearray()
    for word in rom:
        image.extend(word.to_bytes(width, "little"))
    return image, bits, len(rom)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("definition", help="JSON control-word definition")
    ap.add_argument("output", help="output binary EEPROM image")
    ap.add_argument("--hex", dest="hex_output", help="also write a hexadecimal listing")
    args = ap.parse_args()
    try:
        data = json.loads(Path(args.definition).read_text(encoding="utf-8"))
        image, bits, words = build(data)
        Path(args.output).write_bytes(image)
        if args.hex_output:
            width = bits // 4
            values = [int.from_bytes(image[i:i + bits // 8], "little") for i in range(0, len(image), bits // 8)]
            Path(args.hex_output).write_text("\n".join(f"{v:0{width}X}" for v in values) + "\n", encoding="ascii")
        print(f"wrote {words} control words ({len(image)} bytes)")
        return 0
    except (OSError, ValueError, TypeError, json.JSONDecodeError) as exc:
        print(f"microcode: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
