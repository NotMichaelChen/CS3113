
uniform vec4 color;
uniform float alpha_mask;

void main() {
	vec4 finalColor = color;
	finalColor.a *= alpha_mask;
	gl_FragColor = finalColor;
}
