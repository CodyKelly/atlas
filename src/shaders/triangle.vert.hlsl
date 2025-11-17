struct ShapeData
{
    float3 Position;
    float Rotation;
    float Scale;
    float3 Padding;
    float4 Color;
};

struct Output
{
    float4 Color : TEXCOORD0;
    float4 Position : SV_Position;
};

StructuredBuffer<ShapeData> DataBuffer : register(t0, space0);

cbuffer UniformBlock : register(b0, space1)
{
    float4x4 ViewProjectionMatrix : packoffset(c0);
};

static const float2 vertexPos[3] = {
    { 0.0f, 0.0f },
    { 1.0f, 0.0f },
    { 0.0f, 1.0f }
};

Output main(uint id: SV_VertexID)
{
    uint shapeIndex = id / 3;
    uint vert = id % 3;
    ShapeData shape = DataBuffer[shapeIndex];

    float c = cos(shape.Rotation);
    float s = sin(shape.Rotation);

    float2 coord = vertexPos[vert];
    coord *= shape.Scale;
    float2x2 rotation = { c, s, -s, c };
    coord = mul(coord, rotation);

    float3 coordWithDepth = float3(coord + shape.Position.xy, shape.Position.z);

    Output output;

    output.Position = mul(ViewProjectionMatrix, float4(coordWithDepth, 1.0f));
    output.Color = float4(vert == 0 ? 1.0f : 0.0f, vert == 1 ? 1.0f : 0.0f, vert == 2 ? 1.0f : 0.0f, 1.0f); // shape.Color;

    return output;
}
