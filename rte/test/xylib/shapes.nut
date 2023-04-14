/*=============*\
| XYG SHAPE LIB |
\*=============*/

/////////////
// CLASSES //
/////////////

xyg.Shape <- class{
	//Properties
	x = 0
	y = 0

	//Functions
	function _typeof(){
		return "xyg.Shape";
	}
}

xyg.Dot <- class extends xyg.Shape{
	function _typedef(){
		return "xyg.Dot";
	}
}

///////////////
// FUNCTIONS //
///////////////