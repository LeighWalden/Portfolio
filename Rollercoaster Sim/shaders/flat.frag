void main(void)
  {
    // Mix primary and secondary colors, 50/50
   vec4 temp = mix(gl_Color, vec4(vec3(gl_SecondaryColor), 1.0), 0.5);
   gl_FragColor = temp; 
  }

