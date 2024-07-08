// Cloning an array
local array = [1, [2, 3], {"a": 4, "b": 5}]
local clonedArray = deepClone(array)
clonedArray[1][0] = 99
print(jsonWrite(array))
print(jsonWrite(clonedArray))

// Cloning a table
local table = {"key1": 1, "key2": {"subkey1": 2, "subkey2": 3}, "key3": [4, 5, 6]}
local clonedTable = deepClone(table)
clonedTable["key2"]["subkey1"] = 99
print(jsonWrite(table))
print(jsonWrite(clonedTable))