<body onkeypress="input(event)">

  <section>
  <script>
    for(var j = 0; j < 9; ++j)
    {
      for(var i = 0; i < 9; ++i)
      {
        // Box position: for coloring
        str = "block_odd";
        if((i + j) % 2 == 0)
        {
          str = "block_even";
        }
        document.write("<div class='" + str + "' ");
        
        // Grid location
        document.write("x='" + i + "' ");
        document.write("y='" + j + "' ");
        
        // Select
        document.write("onclick='selectBlock(this)'>");
        
        // Inner html
        document.write(getValue(i, j) + "</div>");
      }
    }     
  </script>
  </section>

</body>
