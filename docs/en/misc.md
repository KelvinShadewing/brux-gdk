# <center>**Brux Scripting Reference Manual**</center>
## <center>Misc</center>



&nbsp;

* <a name="choose"></a>**`choose( array )`**

  Takes an array and returns a random element from it. If any other type is passed, it is returned unchanged.

* <a name="deepClone"></a>**`deepClone( obj )`**

  Takes an array or table and returns a clone. Unlike when using `clone()`, this function works recursively, copying objects within the target object instead of preserving references.