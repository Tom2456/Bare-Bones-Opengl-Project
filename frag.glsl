#version 330 core
out vec4 FragColor;
void main()
{
     if(gl_FragCoord.x < 50){
          FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
          return;
     }
     FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
}