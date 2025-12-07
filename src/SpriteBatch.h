//
// Created by hoy on 11/21/25.
//

#ifndef ATLAS_SPRITEBATCH_H
#define ATLAS_SPRITEBATCH_H

#include <vector>
#include <SDL3/SDL.h>

#include "ResourceManager.h"
#include "math.h"

struct PositionTextureVertex
{
    float x, y, z;
    float u, v;
};

struct SpriteInstance
{
    float x, y, z;
    float rotation;
    float w, h, pad1, pad2;
    float tex_u, tex_v, tex_w, tex_h;
    float r, g, b, a;
};

class SpriteBatch
{
private:
    ResourceManager* resourceManager;
    SDL_GPUBuffer* spriteBuffer;
    SDL_GPUTransferBuffer* transferBuffer;
    SDL_GPUTexture* texture = nullptr;
    SDL_GPUSampler* sampler = nullptr;

    std::string name;
    std::vector<SpriteInstance> sprites;
    Uint32 maxSprites;
    bool isDirty;

public:
    SpriteBatch(std::string batchName, ResourceManager* rm, Uint32 maxSpriteCount);

    // Reserve space for sprites
    void Reserve(size_t count);

    // Add a single sprite
    void AddSprite(const SpriteInstance&);

    void SetTexture(SDL_GPUTexture* tex, SDL_GPUSampler* samp);

    // Get raw pointer to sprite data for bulk updates
    SpriteInstance* GetSpriteData();
    const SpriteInstance* GetSpriteData() const;

    // Get a single sprite
    SpriteInstance& GetSprite(size_t index);
    const SpriteInstance& GetSprite(size_t index) const;

    size_t GetSpriteCount() const;
    void Clear();

    void MarkDirty();

    void Upload(SDL_GPUCommandBuffer* commandBuffer);

    void Draw(SDL_GPURenderPass* renderPass, SDL_GPUCommandBuffer* commandBuffer,
              const Matrix4x4& viewProjection);
};

#endif //ATLAS_SPRITEBATCH_H
