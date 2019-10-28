#version 330

in vec4 vertexColor;
in vec2 texCoord;
in vec3 Normal;
in vec3 fragPos;

out vec4 color;

struct DirectionalLight
{
    vec3 color;
    vec3 direction;

    float ambientIntensity;
    float diffuseIntensity;
};

struct Material
{
    float specularIntensity;
    float shininess;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
uniform Material material;

uniform vec3 eyePosition;

void main()
{
    vec4 ambientColor = vec4(directionalLight.color, 1.0F) * 
        directionalLight.ambientIntensity;

    float diffuseFactor = max(dot(normalize(Normal), 
     normalize(directionalLight.direction)), 0.0F);

    vec4 diffuseColor = vec4(directionalLight.color, 1.0F) * 
        directionalLight.diffuseIntensity * diffuseFactor;

    vec4 specularColor = vec4(0.0F, 0.0F, 0.0F, 0.0F);

    if(diffuseFactor > 0.0F)
    {
        vec3 fragToEye = normalize(eyePosition - fragPos);

        vec3 reflectedVertex = normalize(reflect(directionalLight.direction, 
            normalize(Normal)));

        float specularFactor = dot(fragToEye, reflectedVertex);

        if(specularFactor > 0.0F)
        {
            specularFactor = pow(specularFactor, material.shininess);
            specularColor= vec4(directionalLight.color * material.specularIntensity
                * specularFactor, 1.0F);
        }
    }

    color = texture(theTexture, texCoord) * (ambientColor + diffuseColor +
                specularColor);
}