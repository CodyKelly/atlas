#ifndef ATLAS_RESOURCEMANAGER_H
#define ATLAS_RESOURCEMANAGER_H

#include <SDL3/SDL.h>

class GPUBufferPair {
public:
    SDL_GPUTransferBuffer *_transferBuffer;
    SDL_GPUBuffer *_dataBuffer;
    SDL_GPUDevice *_gpuDevice;

    GPUBufferPair(Uint32 size, SDL_GPUDevice *gpuDevice) : _gpuDevice(gpuDevice) {
        SDL_GPUTransferBufferCreateInfo shapeTransferBufferCreateInfo = {
            .usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
            .size = size,
        };
        _transferBuffer = SDL_CreateGPUTransferBuffer(_gpuDevice, &shapeTransferBufferCreateInfo);

        SDL_GPUBufferCreateInfo shapeBufferCreateInfo = {
            .usage = SDL_GPU_BUFFERUSAGE_GRAPHICS_STORAGE_READ,
            .size = size,
        };
        _dataBuffer = SDL_CreateGPUBuffer(_gpuDevice, &shapeBufferCreateInfo);
    }

    ~GPUBufferPair() {
        ReleaseBuffers();
    }

    void ReleaseBuffers() {
        SDL_ReleaseGPUBuffer(_gpuDevice, _dataBuffer);
        SDL_ReleaseGPUTransferBuffer(_gpuDevice, _transferBuffer);
    }
};

class ResourceManager {
private:
    SDL_Window *window;
    SDL_GPUDevice *gpuDevice;
    SDL_GPUGraphicsPipeline *graphicsPipelines;
    GPUBufferPair *gpuBufferPairs;
};


#endif //ATLAS_RESOURCEMANAGER_H
