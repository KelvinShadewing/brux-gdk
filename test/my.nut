#!/usr/bin/brux

/*================*\
| TEST APPLICATION |
\*================*/

/*
# This nut is used for testing features of Brux.
# When a standard library file is done being tested,
# it is moved into the std folder. The std folder
# can then be copied into any game project that
# needs it. These may be baked into the runtime
# itself in the future to prevent duplication of
# code, similar to how core.nut was.
#
# Other newly implemented features will also be
# tested here.
*/

donut("src/assets.nut");
donut("src/actors.nut");
donut("src/shapes.nut");
donut("src/tilemap.nut");
donut("src/main.nut");

main();
