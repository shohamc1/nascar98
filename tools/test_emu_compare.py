"""Tests for tools/emu_compare.py's pad scripts and car decoding."""

import struct
import unittest

import emu_compare as ec


class PadScript(unittest.TestCase):
    def test_buttons_hold_until_the_next_line(self) -> None:
        script = ec.parse_pad("0 -\n100 start\n105 -\n200 cross+left\n")
        self.assertEqual(ec.held(script, 99), set())
        self.assertEqual(ec.held(script, 100), {"start"})
        self.assertEqual(ec.held(script, 104), {"start"})
        self.assertEqual(ec.held(script, 105), set())
        self.assertEqual(ec.held(script, 5000), {"cross", "left"})

    def test_unknown_button_stops(self) -> None:
        with self.assertRaises(SystemExit):
            ec.parse_pad("10 jump\n")


class Cars(unittest.TestCase):
    def test_chain_from_the_player_car(self) -> None:
        ram = bytearray(ec.RAM_SIZE)
        player, other, pointer = 0x80100000, 0x80100500, 0x80010000
        struct.pack_into("<I", ram, pointer - ec.RAM_BASE, player)
        struct.pack_into("<iii", ram, player - ec.RAM_BASE, 1, 2, 3)
        struct.pack_into("<I", ram, player - ec.RAM_BASE + ec.CAR_NEXT, other)
        struct.pack_into("<i", ram, other - ec.RAM_BASE + 0x90, 50 << 16)
        struct.pack_into("<I", ram, other - ec.RAM_BASE + ec.CAR_NEXT, player)  # a loop ends the walk
        found = ec.walk_cars(bytes(ram), pointer)
        self.assertEqual([c.address for c in found], [player, other])
        self.assertEqual((found[0].x, found[0].y, found[0].z), (1, 2, 3))
        self.assertEqual(found[1].speed, 50 << 16)


if __name__ == "__main__":
    unittest.main()
