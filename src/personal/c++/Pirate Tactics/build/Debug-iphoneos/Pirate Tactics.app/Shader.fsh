//
//  Shader.fsh
//  Pirate Tactics
//
//  Created by Jonathan Chandler on 2/14/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
	gl_FragColor = colorVarying;
}
