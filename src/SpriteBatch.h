//
// Created by hoy on 11/21/25.
//

#ifndef ATLAS_SPRITEBATCH_H
#define ATLAS_SPRITEBATCH_H

#include <vector>
#include <SDL3/SDL.h>

#include "ResourceManager.h"
#include "math.h"

struct SpriteInstance
{
    float x, y, z, rotation;
    float scale, padding1, padding2, padding3;
    float r, g, b, a;
};

class SpriteBatch
{
private:
    ResourceManager* resourceManager;
    SDL_GPUBuffer* spriteBuffer;
    SDL_GPUTransferBuffer* transferBuffer;

    std::vector<SpriteInstance> sprites;
    Uint32 maxSprites;
    bool isDirty;

public:
    SpriteBatch(ResourceManager* rm, Uint32 maxSpriteCount);

    // Reserve space for sprites
    void Reserve(size_t count);

    // Add a single sprite
    void AddSprite(float x, float y, float scale = 1.0f);

    // Get raw pointer to sprite data for bulk updates
    SpriteInstance* GetSpriteData();
    const SpriteInstance* GetSpriteData() const;

    // Get a single sprite
    SpriteInstance& GetSprite(size_t index);
    const SpriteInstance& GetSprite(size_t index) const;

    size_t GetSpriteCount() const;
    void Clear();

    // Mark data as dirty (call after bulk updates)
    void MarkDirty();

    // Upload sprite data to GPU
    void Upload(SDL_GPUCommandBuffer* commandBuffer);

    // Draw all sprites in the batch
    void Draw(SDL_GPURenderPass* renderPass, SDL_GPUCommandBuffer* commandBuffer,
              const Matrix4x4& viewProjection);
};

#endif //ATLAS_SPRITEBATCH_H
