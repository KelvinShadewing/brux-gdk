/*
This program is to test the speed difference between if statements vs. switch statements, as well as table lookups vs. array lookups.

When run, it will display an empty window for a few seconds, and then print the results.
*/

local ifTime = 0
local switchTime = 0
local tableTime = 0
local outTableTime = 0
local arrayTime = 0
local loopMax = 10000000
local testTable = {
	"0" : "0",
	"1" : "1",
	"2" : "2",
	"3" : "3"
}
local testArray = [0, 1, 2, 3]

for(local i = 0; i < loopMax; i++) {
	local thing = 0

	local timeStart = getTicks()
	if(i % 4 == 0) { thing = 0 }
	else if(i % 4 == 1) { thing = 1 }
	else if(i % 4 == 2) { thing = 2 }
	else if(i % 4 == 3) { thing = 3 }
	ifTime += getTicks() - timeStart

	timeStart = getTicks()
	switch(i % 4) {
		case 0:
			thing = 0
			break
		case 1:
			thing = 1
			break
		case 2:
			thing = 2
			break
		case 3:
			thing = 3
			break
	}
	switchTime += getTicks() - timeStart

	timeStart = getTicks()
	thing = testTable["1"]
	tableTime += getTicks() - timeStart

	timeStart = getTicks()
	if(i % 8 in testTable)
		thing = thing = testTable["3"]
	outTableTime += getTicks() - timeStart

	timeStart = getTicks()
	thing = testArray[2]
	arrayTime += getTicks() - timeStart
}

ifTime /= float(loopMax)
switchTime /= float(loopMax)
tableTime /= float(loopMax)
outTableTime /= float(loopMax)
arrayTime /= float(loopMax)

print("Average if statement time: " + str(ifTime))
print("Average switch statement time: " + str(switchTime))
print("Average table lookup time: " + str(tableTime))
print("Average table lookup with 'in' check time: " + str(outTableTime))
print("Average array lookup time: " + str(arrayTime))