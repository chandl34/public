<body onkeypress="input(event)">
  <!-- Debug info -->
  <script>
    document.write("<p id='poss'>possible values: </p>");
  </script>
 
  <!-- Draw puzzle board -->
  <script>
    document.write("<div class='board'>");
        
    for(var row_l = 0; row_l < 3; ++row_l)
    {
      for(var col_l = 0; col_l < 3; ++col_l)
      {
        document.write("<div class='box'>");
        
        for(var row_s = 0; row_s < 3; ++row_s)
        {
          for(var col_s = 0; col_s < 3; ++col_s)
          {
            
            var x = col_l * 3 + col_s;
            var y = row_l * 3 + row_s;
                
            // Box position: for coloring
            var pos = "odd";
            if((x + y) % 2 == 0)
            {
              pos = "even";
            }
            document.write("<div class='block " + pos + "' ");
                    
            // Grid location
            document.write("x='" + x + "' ");
            document.write("y='" + y + "' ");
            
            // Select
            document.write("onmousedown='selectBlock(this)'>");
            
            // Inner html
            document.write(getValue(x, y) + "</div>");  
            
          }
        }
        
        document.write("</div>");
      }
    }
    
    document.write("</div>");
  </script>
  
  <!-- Draw buttons -->
  <div class="buttons">
    <button onclick="clearPuzzle()">Clear</button>
  </div>
    
</body>
