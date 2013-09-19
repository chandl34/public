//
//  Shader.fsh
//  c34_UI
//
//  Created by Jonathan Chandler on 1/24/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
