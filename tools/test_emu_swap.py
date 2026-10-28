"""Tests for tools/emu_swap.py's patch words and RAM hashes."""

import struct
import unittest

import emu_compare as ec
import emu_swap as sw


class Patch(unittest.TestCase):
    def test_jump_targets_the_address(self) -> None:
        word, delay = struct.unpack("<II", sw.jump(0x801F6010))
        self.assertEqual(word >> 26, 2)  # j
        self.assertEqual(0x80000000 | (word & 0x3FFFFFF) << 2, 0x801F6010)
        self.assertEqual(delay, 0)  # nop in the delay slot


class Hashes(unittest.TestCase):
    def test_swap_area_is_not_hashed(self) -> None:
        ram = bytearray(ec.RAM_SIZE)
        before = sw.page_hashes(bytes(ram))
        ram[sw.SWAP_BASE - ec.RAM_BASE + 100] = 1  # the swapped code and stack
        self.assertEqual(sw.page_hashes(bytes(ram)), before)
        ram[0x10000] = 1  # the game's own RAM
        self.assertNotEqual(sw.page_hashes(bytes(ram)), before)


if __name__ == "__main__":
    unittest.main()
