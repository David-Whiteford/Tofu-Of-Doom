#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in mat4 view;

// Output data
out vec3 color;

// Number of lights
const int LIGHT_AMOUNT = 25;

// Values that stay constant for the whole mesh.
uniform sampler2D currentTexture;
uniform vec3 LightPosition_worldspace;
uniform vec3 lightPositionsWorldspace[LIGHT_AMOUNT];
uniform float muzzleFlashIntensity;

void main()
{
	// Light emission properties
	// You probably want to put them as uniforms
	vec3 LightColor = vec3(1, 1, 1); // White
	vec3 muzzleFlashColor = vec3(0.98, 0.72, 0.01); // Weird orange
	float LightPower = 200.0f;
	
	// Material properties
	vec3 MaterialDiffuseColor = texture(currentTexture, UV).rgb;
	vec3 MaterialAmbientColor = vec3(0.0, 0.0, 0.0) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.4, 0.4, 0.4);

	// Combine all multiple light sources
	for (int i = 0; i < LIGHT_AMOUNT; i++)
	{
		vec3 LightPosition_cameraspace_temp = ( view * vec4(lightPositionsWorldspace[i],1)).xyz;
		vec3 LightDirection_cameraspace = LightPosition_cameraspace_temp + EyeDirection_cameraspace;

		// Distance to the light
		float distance = length(lightPositionsWorldspace[i] - Position_worldspace);

		// Normal of the computed fragment, in camera space
		vec3 n = normalize(Normal_cameraspace);
		// Direction of the light (from the fragment to the light)
		vec3 l = normalize(LightDirection_cameraspace);
		// Cosine of the angle between the normal and the light direction, 
		// clamped above 0
		//  - light is at the vertical of the triangle -> 1
		//  - light is perpendicular to the triangle -> 0
		//  - light is behind the triangle -> 0
		float cosTheta = clamp( dot( n,l ), 0,1 );
	
		// Eye vector (towards the camera)
		vec3 E = normalize(EyeDirection_cameraspace);
		// Direction in which the triangle reflects the light
		vec3 R = reflect(-l,n);
		// Cosine of the angle between the Eye vector and the Reflect vector,
		// clamped to 0
		//  - Looking into the reflection -> 1
		//  - Looking elsewhere -> < 1
		float cosAlpha = clamp( dot( E,R ), 0,1 );
	
		color += 
			// Ambient : simulates indirect lighting
			MaterialAmbientColor +
			// Diffuse : "color" of the object
			MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
			// Specular : reflective highlight, like a mirror
			MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);
	}

	// I should probably put this in a function so it can be used above, leave it for now
	vec3 LightPosition_cameraspace_temp = ( view * vec4(LightPosition_worldspace, 1)).xyz;
	vec3 LightDirection_cameraspace = LightPosition_cameraspace_temp + EyeDirection_cameraspace;

	// Distance to the light
	float distance = length(LightPosition_worldspace - Position_worldspace);

	// Normal of the computed fragment, in camera space
	vec3 n = normalize(Normal_cameraspace);
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize(LightDirection_cameraspace);
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0,1 );
	
	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 );
	
	color += 
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * muzzleFlashColor * muzzleFlashIntensity * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * muzzleFlashColor * muzzleFlashIntensity * pow(cosAlpha,5) / (distance*distance);
}