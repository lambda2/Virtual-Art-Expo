struct vertexIn
{
	float4 position : POSITION;
	float3 normal	: NORMAL0;
};
 
struct vertexOut
{
	float4 position  		: POSITION;
	float3 normal			: TEXCOORD0;
	float3 viewDir   		: TEXCOORD1;
	float3 pixelToLight[lightCount]	: TEXCOORD2;
};
 
//lighting sub program, read multiTypeLightPS first(this one is called from it)
//--------------------------------------------------------------------------------
void light(	float3 normal, 
		float3 viewDir, 
		float3 pixelToLight,
		float3 spotLightDir,
		float4 spotLightParams,
		float4 diffColor,
		float4 specColor,
		float4 lightAtten,
		float  lightDist,
		float  specShine,
	inout	float4 diff,
	inout	float4 spec
	)
{
	float 	dotNL	 	= dot(pixelToLight, normal);
	float 	luminosity 	= 1 / ( lightAtten.y + lightAtten.z*lightDist + lightAtten.w*pow(lightDist,2));
	float3 	halfAng 	= normalize(viewDir + pixelToLight);
	float 	dotNH		= dot(normal, halfAng);
 
	// if spotlight params are (1, 0, 0, 1) we have a point, directional or empty light; we handle them the same.
	if(spotLightParams.x == 1 && spotLightParams.y == 0 && spotLightParams.z == 0 && spotLightParams.w == 1)
	{
		spec	+= pow(saturate(dotNH),specShine) * specColor * luminosity;
		diff 	+= (saturate(dotNL)) * diffColor * luminosity;		
	}
	else
	if(dotNL > 0)
	{	
		//if it was not either of the above, we have a spotlight
		float 	dotPLd		= dot(-pixelToLight, spotLightDir);
		//diffuse
		//------------------------------
		if	( dotPLd > spotLightParams.y )
			diff += dotNL * (1-(spotLightParams.x - dotPLd)/(spotLightParams.x - spotLightParams.y)) * diffColor * luminosity;
		else
		if	( dotPLd > spotLightParams.x )
			diff += dotNL * diffColor * luminosity;	
		//------------------------------
 
		// specular
		//------------------------------
		if (dotPLd > 0) 
			spec 	+= pow(saturate(dotNH),specShine) * specColor * luminosity;
		//------------------------------
	}
}
//--------------------------------------------------------------------------------
 
// main vertex program
//--------------------------------------------------------------------------------
vertexOut multiTypeLightVS(	vertexIn 	input,
			uniform	float4x4 	worldViewProj_m,
			uniform	float4 		cameraPos,
			uniform	float4 		lightPoses[lightCount]
			)
{
	vertexOut output= (vertexOut)0;
 
	output.position = mul(worldViewProj_m, input.position);
	output.normal 	= input.normal;
	output.viewDir	= cameraPos - input.position;
	int j = 2;
 
	for(int i = 0; i < lightCount; i++)
	{	
		if(lightPoses[i].w == 0)
			output.pixelToLight[i] = lightPoses[i].xyz;
		else
			output.pixelToLight[i] = lightPoses[i] - input.position;
	}
	return output;
}
//--------------------------------------------------------------------------------
 
//main pixel program
//--------------------------------------------------------------------------------
float4 multiTypeLightPS(	vertexOut 	input,
			uniform float4		SLParamsArray[lightCount],
			uniform float3		lightDirs[lightCount],
			uniform	float4		diffColors[lightCount],
			uniform	float4 		specColors[lightCount],
			uniform float4		lightAttens[lightCount],
			uniform float4		lightDists[lightCount],
			uniform	float4		ambientColor,
			uniform float		specShine
			) : COLOR
{
	float4 diff 	= float4(0, 0, 0, 0);
	float4 spec 	= float4(0, 0, 0, 0);
 
	input.viewDir	= normalize( input.viewDir );
	input.normal 	= normalize( input.normal );
 
	for(int i = 0; i<lightCount ; i++)
	{
		input.pixelToLight[i]	= normalize( input.pixelToLight[i] );
 
		light(	input.normal, 
			input.viewDir, 
			input.pixelToLight[i],
			normalize(lightDirs[i]),
			SLParamsArray[i],
			diffColors[i],
			specColors[i],
			lightAttens[i],
			lightDists[i],
			specShine,
			diff,
			spec);
	}
	return ambientColor + diff + spec ;
}
