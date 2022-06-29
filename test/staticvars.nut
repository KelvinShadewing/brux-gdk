::StaticTest <- class {
	stob = {
		a = 0
		b = 1
		c = 2
		d = 3
	}

	locob = null

	constructor(){
		locob = {}
	}
}

local a = StaticTest()
local b = StaticTest()

print(a.stob.a)

b.stob.a = 1

print(a.stob.a)

a.locob.a <- "blah"

print(a.locob.a)