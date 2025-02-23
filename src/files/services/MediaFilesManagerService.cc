#include <memory>
#include "MediaFilesManagerService.h"

MediaFilesManagerService::MediaFilesManagerService(const shared_ptr<ImageCompressorService>& service) : compressorService(service) {}
void MediaFilesManagerService::compressFiles(vector<string> filePaths){
    for (const auto& filePath : filePaths) {
        size_t slashIndex = filePath.rfind('/');
        string fileName = filePath.substr(slashIndex);
        std::string compressedPath = "./compressed/" + fileName;
            compressorService->compress(filePath, compressedPath, 75);
    }
}

