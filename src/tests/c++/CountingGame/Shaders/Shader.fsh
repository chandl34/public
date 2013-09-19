//
//  Shader.fsh
//  CountingGame
//
//  Created by Jonathan Chandler on 11/27/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
