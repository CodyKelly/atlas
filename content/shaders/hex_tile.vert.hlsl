struct HexTileData
{
    float4 Color;
};

struct Output
{
    float4 Color : TEXCOORD0;
    float4 Position : SV_Position;
}

StructuredBuffer<HexTileData> DataBuffer : register(t0, space0);

cbuffer UniformBlock : register(b0, space1)
{
    float4x4 ViewProjectionMatrix : packoffset(c0);
    float2 mapSize : packoffset(c1.xy);
};

static const float outerRadius = 1f;
static const float innerRadius = outerRadius * 0.866025404f;

static const float2 vertexPos[7] = {
    {0, 0},
    {0, outerRadius},
    {innerRadius, 0.5f * outerRadius},
    {innerRadius, -0.5f * outerRadius},
    {0, -outerRadius},
    {-innerRadius, -0.5f * outerRadius},
    {-innerRadius, 0.5f * outerRadius},
};
static const int triangleIndices[24] = {
    0, 1, 2,
    0, 2, 3,
    0, 3, 4,
    0, 4, 5,
    0, 5, 6,
    0, 6, 1,
};

Output main(uint id: SV_VertexID)
{
    uint tileIndex = id / 24;
    uint vert = triangleIndices[id % 24];
    HexTileData tile = DataBuffer[tileIndex];

    float2 coord = vertexPos[vert] + float2();

    Output output;
    output.Position = mul(ViewProjectionMatrix, float4(coord, 1.0f, 1.0f));
    output.Color = tile.Color;

    return output;
}