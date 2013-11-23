//
//  Shader.fsh
//  Tactics
//
//  Created by Jonathan Chandler on 2/2/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
	gl_FragColor = colorVarying;
}
