
uniform sampler2D diffuse;
uniform float alpha_mask;
varying vec2 texCoordVar;

void main() {
    vec4 finalColor = texture2D(diffuse, texCoordVar);
    finalColor.a *= alpha_mask;
    gl_FragColor = finalColor;
}