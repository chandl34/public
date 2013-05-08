// Selected
var _selected = new Object();
_selected.elem;
_selected.block;


// Puzzle Object
var _puzzle = new Object();
{
  // Block Object
  _puzzle.block = new Array(9);
  for(var i = 0; i < 9; i++) 
  {
    _puzzle.block[i] = new Array(9);
    for (var j = 0; j < 9; j++)
    {
      _puzzle.block[i][j] = new Object();
      _puzzle.block[i][j].loc = i + ", " + j;
      _puzzle.block[i][j].poss = "123456789";
    }
  }
}


// Block Methods
function getValue(x, y)
{
  block = _puzzle.block[x][y];
  
  if(block.poss.length > 1)
    return '';
  else
    return block.poss;
}

function setValue(val)
{
  _selected.elem.innerHTML = val;
  _selected.block.poss = val;
}


// Page I/O
function selectBlock(elem)
{
  _selected.elem = elem;
  x = _selected.elem.getAttribute("x");
  y = _selected.elem.getAttribute("y");
  _selected.block = _puzzle.block[x][y];
}

function input(e)
{
  char = String.fromCharCode(e.charCode);
  if(char >= '1' && char <= '9')
    setValue(char);
}

