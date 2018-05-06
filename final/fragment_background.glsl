uniform sampler2D diffuse;
uniform vec2 scroll;
varying vec2 texCoordVar;

void main() {
    vec4 finalColor = texture2D(diffuse, texCoordVar + scroll);
    finalColor.a *= 0.6;
    gl_FragColor = finalColor;
}