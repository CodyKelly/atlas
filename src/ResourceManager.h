#ifndef ATLAS_RESOURCEMANAGER_H
#define ATLAS_RESOURCEMANAGER_H

#include <vector>
#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>

using std::vector, std::unordered_map, std::string;

struct ShaderInfo
{
    const char* shaderPath;
    Uint32 samplerCount;
    Uint32 uniformBufferCount;
    Uint32 storageBufferCount;
    Uint32 storageTextureCount;
};

//
// class GPUBufferPair {
// public:
//     SDL_GPUTransferBuffer *_transferBuffer;
//     SDL_GPUBuffer *_dataBuffer;
//     SDL_GPUDevice *_gpuDevice;
//
//     GPUBufferPair(Uint32 size, SDL_GPUDevice *gpuDevice) : _gpuDevice(gpuDevice) {
//         SDL_GPUTransferBufferCreateInfo shapeTransferBufferCreateInfo = {
//             .usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
//             .size = size,
//         };
//         _transferBuffer = SDL_CreateGPUTransferBuffer(_gpuDevice, &shapeTransferBufferCreateInfo);
//
//         SDL_GPUBufferCreateInfo shapeBufferCreateInfo = {
//             .usage = SDL_GPU_BUFFERUSAGE_GRAPHICS_STORAGE_READ,
//             .size = size,
//         };
//         _dataBuffer = SDL_CreateGPUBuffer(_gpuDevice, &shapeBufferCreateInfo);
//     }
//
//     ~GPUBufferPair() {
//         ReleaseBuffers();
//     }
//
//     void ReleaseBuffers() {
//         SDL_ReleaseGPUBuffer(_gpuDevice, _dataBuffer);
//         SDL_ReleaseGPUTransferBuffer(_gpuDevice, _transferBuffer);
//     }
// };

class ResourceManager
{
private:
    SDL_Window* window;
    SDL_GPUDevice* gpuDevice;
    unordered_map<string, SDL_GPUGraphicsPipeline*> pipelines;
    unordered_map<string, SDL_GPUBuffer*> buffers;
    vector<SDL_GPUTransferBuffer*> transferBuffers;

public:
    void Init(const char* windowTitle, int width, int height, SDL_WindowFlags windowFlags);
    SDL_GPUBuffer* CreateBuffer(const string& name, const SDL_GPUBufferCreateInfo* createInfo);
    SDL_GPUTransferBuffer* AcquireTransferBuffer(const SDL_GPUTransferBufferCreateInfo* createInfo);
    SDL_GPUGraphicsPipeline* CreateGraphicsPipeline(
        const string& name,
        const ShaderInfo& vertexShaderInfo,
        const ShaderInfo& fragmentShaderInfo
    );
    SDL_GPUShader* LoadShader(const ShaderInfo& info) const;
    SDL_GPUDevice* GetGPUDevice() const { return gpuDevice; }
    SDL_Window* GetWindow() const { return window; }
    SDL_GPUGraphicsPipeline* GetGraphicsPipeline(const string& name) { return pipelines[name]; }
    ~ResourceManager();
};


#endif //ATLAS_RESOURCEMANAGER_H
