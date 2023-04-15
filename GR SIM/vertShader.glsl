/*#version 460

layout (location=0) in vec3 position;

//uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 move_matrix;
uniform float timeFactor;
uniform mat4 v_matrix;

out vec4 varyingColor;

//rotate about the x-axis
mat4 buildRotateX(float rad)
{
	mat4 xrot = mat4(1.0, 0.0, 0.0, 0.0,
					 0.0, cos(rad), -sin(rad), 0.0,
					 0.0, sin(rad), cos(rad), 0.0,
					 0.0, 0.0, 0.0, 1.0);
	return xrot;
}

//rotate about the y axis
mat4 buildRotateY(float rad)
{
	mat4 yrot = mat4(cos(rad), 0.0, sin(rad), 0.0,
					 0.0, 1.0, 0.0, 0.0,
					 -sin(rad), 0.0, cos(rad), 0.0,
					 0.0, 0.0, 0.0, 1.0);
	return yrot;
}

//rotate about the z axis
mat4 buildRotateZ(float rad)
{
	mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
					 sin(rad), cos(rad), 0.0, 0.0,
					 0.0, 0.0, 1.0, 0.0,
					 0.0, 0.0, 0.0, 1.0);
	return zrot;
}

//translate an object in a specific direction
mat4 buildTranslate(float x, float y, float z)
{
	mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
					  0.0, 1.0, 0.0, 0.0,
					  0.0, 0.0, 1.0, 0.0,
					  x, y, z, 1.0);
	return trans;
}

void main(void) 
{
	float i = gl_InstanceID + timeFactor;
	float a = sin(203.0 * i/8000.0) * 403.0;
	float b = cos(301.0 * i/4001.0) * 401.0;
	float c = sin(400.0 * i/6003.0) * 405.0;

	mat4 localRotX = buildRotateX(10*i);
	mat4 localRotY = buildRotateY(10*i);
	mat4 localRotZ = buildRotateZ(10*i);
	mat4 localTrans = buildTranslate(a,b,c);

	mat4 newM_matrix = localTrans * localRotX * localRotY + localRotZ;
	mat4 mv_matrix = v_matrix * newM_matrix;

	gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
	varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}*/

#version 460
layout (location=0) in vec3 position;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
out vec4 varyingColor;

void main(void)
{ 
	gl_Position = proj_matrix * mv_matrix * vec4(position,1.0);
	varyingColor = vec4(position,1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}