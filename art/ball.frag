uniform sampler2D texture;
uniform mat3 rotationMatrix;

void main(){
    vec2 uv = gl_TexCoord[0].xy;
    vec2 p = uv * 2.0 - 1.0;
    float r2 = dot(p, p);
    if(r2 > 1.0) discard;
    float cosTheta = sqrt(1.0 - r2);

    // screen X maps to world X, screen Y maps to world Z, viewer is along world Y
    vec3 normal = rotationMatrix * vec3(p.x, cosTheta, p.y);

    // spherical coords in XZ plane with Y up
    float u = atan(normal.z, normal.x) / (2.0 * 3.1415926) + 0.5;
    float v = asin(clamp(normal.y, -1.0, 1.0)) / 3.1415926 + 0.5;
    gl_FragColor = texture2D(texture, vec2(u, v));
}
