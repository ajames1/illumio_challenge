# illumio_challenge

## Summary
This is a NAT table simulation program. To run it, run the `challenge` binary. The program has been implemented in C++11.
This was implemented in roughly 90 mins. The code is far from production ready. I've provided a checklist of TODOs at the end to take this to production-level.

## Design decisions
The implementation converts IP/port pairs into the `long long` data-type by bit-shifting so that it can be stored in a space-efficient manner. The source IP/port pairs are mapped to destination IP/port pairs using an unordered hashmap. This makes the time complexity of route checking `O(1)`. In order to match the "*" regular expressions, I created separate port-only and IP-only hashmaps. Initially I tried fitting it all into the same map, but there was a risk of edge-cases and incorrect behaviour with that approach, so I decided to maintain separate maps. All this is encapsulated into a NATTable class. The test program derives from this class for testing. Even though long long is 64-bits in width, we only utilize 48 bits of those bits for storage (32-bit IP + 16-bit port number).

I optimized for functionality and performance, which took most of the alloted time for the project, so I didn't have time to add enough comments to explain important/tricky parts of the code. I understand the importance of well-documented code and would have spent time on that if I had a little more time. Code could also have been written more cleanly and a bit more modular. Error handling is not comprehensive and the program will likely crash if passed malformed input.

## Building
To build the program, run `make`.

To build the tests, run `make tests`.

## Testing
Testing was done via writing a unit-test program. The test cases test base cases for the NAT Table. There is a lot of scope for increasing the test coverage here.

## Checklist
 * Check for malformed input.
 * Use a unit-test framework for better testing.
 * better error handling in `main` and `NATTable.c`.
 * Use `#defines` for magic numbers.
 * Add more comments.
