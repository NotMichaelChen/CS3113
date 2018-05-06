uniform sampler2D diffuse;
uniform vec2 scroll;
uniform float alpha_mask;
varying vec2 texCoordVar;

void main() {
    vec4 finalColor = texture2D(diffuse, texCoordVar + scroll);
    finalColor.a *= alpha_mask;
    gl_FragColor = finalColor;
}