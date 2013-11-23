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



// Debug info
function refreshDebugInfo()
{
  pe = document.getElementById("poss");
  pe.innerHTML = "possible values: " + _selected.block.poss;
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
  
  refreshDebugInfo();
}



// Page I/O
function selectBlock(elem)
{
  _selected.elem = elem;
  x = _selected.elem.getAttribute("x");
  y = _selected.elem.getAttribute("y");
  _selected.block = _puzzle.block[x][y];
  
  refreshDebugInfo();
  
  //alert(x + ", " + y);
}

function input(e)
{
  char = String.fromCharCode(e.charCode);
  if(char >= '1' && char <= '9')
    setValue(char);
}

function clearPuzzle()
{
  // Clear Debug info
  pe = document.getElementById("poss");
  pe.innerHTML = "possible values: ";
  
  // Clear Block Data
  for(var i = 0; i < 9; i++) 
  {
    for (var j = 0; j < 9; j++)
    {
      _puzzle.block[i][j].poss = "123456789";
    }
  }
  
  // Clear HTML Display
  blocks = document.getElementsByClassName("block");
  for(var i = 0; i < blocks.length; ++i)
    blocks[i].innerHTML = ' ';
}

